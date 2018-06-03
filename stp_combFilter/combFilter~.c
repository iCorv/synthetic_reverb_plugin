#include "m_pd.h"
#include <math.h>
#include <stdlib.h>

#define BUFFSIZE 44100

static t_class *combFilter_tilde_class;

typedef struct combFilter_tilde
{
    t_object  x_obj;
    t_sample f;
    t_outlet* x_out;
    t_float rptr;
    t_int wptr;
	t_sample* buffer;
	t_float fb;
	t_sample lpOut;
	t_float damp;
	t_sample last_sample;
	t_sample dOut;
	t_float alpha;
	t_int rpi;
	t_float delaySample;

} combFilter_tilde;


t_int *combFilter_tilde_perform(t_int *w)
{
    combFilter_tilde *x = (combFilter_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
    int i;

    for(i=0; i<n; i++) {

    		out[i]= in[i] + (x->fb * x->lpOut);
    		x->buffer[x->wptr]=out[i];
    		x->rptr = x->wptr - x->delaySample;
    		if (x->rptr < 0){
    			x->rptr+=BUFFSIZE-1;
    		}
    		x->rpi = floor(x->rptr);
    		x->alpha = x->rptr - x->rpi;
    		x->dOut = x->alpha * x->buffer[x->rpi] + (1-x->alpha) * x->buffer[x->rpi+1];

            x->lpOut = (1-x->damp) * x->dOut + x->damp * x->last_sample;
            x->last_sample = x->lpOut;

    		if (x->wptr>=(BUFFSIZE-1)) x->wptr = 0; else x->wptr+=1;
    }


    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

void combFilter_tilde_dsp(combFilter_tilde *x, t_signal **sp)
{
    dsp_add(combFilter_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void combFilter_tilde_free(combFilter_tilde *x)
{
    outlet_free(x->x_out);
    free(x->buffer);
}

void *combFilter_tilde_new(t_floatarg f)
{
    combFilter_tilde *x = (combFilter_tilde *)pd_new(combFilter_tilde_class);

    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x-> rptr = 0;
    x-> wptr = 0;
	x-> fb = 0;
	x-> lpOut = 0;
	x-> damp = 0.1;
	x-> dOut = 0;
	x-> last_sample = 0;
	x-> alpha = 0;
	x-> rpi = 0;
	x-> delaySample = 0;
    x->buffer = (t_sample *) calloc (BUFFSIZE , sizeof(t_sample));
    return (void *)x;
}

void combFilterDelay_set(combFilter_tilde *x, float delay)
{
	if (delay < 0 || delay>=(BUFFSIZE-1)) delay = 0;
	x->delaySample = delay;
}

void combFilterFeedback_set(combFilter_tilde *x, float fb)
{
    if (fb > 0.9) fb = 0.9;
    if (fb < 0)  fb = 0;
	x->fb = fb;

}
void combFilterLowpass_set(combFilter_tilde *x, t_float fc)
{
	if (fc > 0.9) fc = 0.9;
	if (fc < 0) fc = 0;
    x-> damp = fc;
}

void combFilter_tilde_setup(void)
{
      combFilter_tilde_class = class_new(gensym("combFilter~"),
            (t_newmethod)combFilter_tilde_new,
            (t_method)combFilter_tilde_free,
        sizeof(combFilter_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(combFilter_tilde_class, (t_method)combFilter_tilde_dsp, gensym("dsp"), 0);
      class_addmethod(combFilter_tilde_class, (t_method)combFilterDelay_set, gensym("delay"), A_DEFFLOAT,0);
      class_addmethod(combFilter_tilde_class, (t_method)combFilterFeedback_set, gensym("feedback"), A_DEFFLOAT,0);
      class_addmethod(combFilter_tilde_class, (t_method)combFilterLowpass_set, gensym("damping"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(combFilter_tilde_class, combFilter_tilde, f);
}
