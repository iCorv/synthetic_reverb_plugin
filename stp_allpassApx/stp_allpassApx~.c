#include "m_pd.h"
#include <math.h>
#include <stdlib.h>

#define BUFFSIZE 48000

static t_class *stp_allpassApx_tilde_class;

typedef struct stp_allpassApx_tilde
{
    t_object  x_obj;
    t_sample f;
    t_outlet* x_out;
    t_float rptr;
    t_int wptr;
	t_sample* buffer1;
	t_sample* buffer2;
	t_sample dOut1;
	t_sample dOut2;
	t_float gain;
	t_float alpha;
	t_int rpi;
	t_float delaySample;

} stp_allpassApx_tilde;


t_int *stp_allpassApx_tilde_perform(t_int *w)
{
    stp_allpassApx_tilde *x = (stp_allpassApx_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
    int i;

    for(i=0; i<n; i++) {
    	x->buffer1[x->wptr] = in[i];
    	x->rptr = x->wptr - x->delaySample;
    	if (x->rptr < 0) x->rptr+=BUFFSIZE-1;
    	x->rpi = floor(x->rptr);
    	x->alpha = x->rptr - x->rpi;
    	x->dOut1 = x->alpha * x->buffer1[x->rpi] + (1-x->alpha) * x->buffer1[x->rpi+1];
    	x->dOut2 = x->alpha * x->buffer2[x->rpi] + (1-x->alpha) * x->buffer2[x->rpi+1];
    	out[i] = ((1+x->gain) * (x->dOut1)) - in[i] + x->dOut2 * x->gain;
    	x->buffer2[x->wptr]=out[i];
    	if (x->wptr>=(BUFFSIZE-1)) x->wptr = 0; else x->wptr+=1;
    }
    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

void stp_allpassApx_tilde_dsp(stp_allpassApx_tilde *x, t_signal **sp)
{
    dsp_add(stp_allpassApx_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void stp_allpassApx_tilde_free(stp_allpassApx_tilde *x)
{
    outlet_free(x->x_out);
    free(x->buffer1);
    free(x->buffer2);
}

void *stp_allpassApx_tilde_new(t_floatarg f)
{
    stp_allpassApx_tilde *x = (stp_allpassApx_tilde *)pd_new(stp_allpassApx_tilde_class);

    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
	x-> rptr       =0;
    x-> wptr       =0;
    x-> buffer1    =0;
    x-> buffer2    =0;
    x-> dOut1      =0;
    x-> dOut2      =0;
    x-> gain       =0;
    x-> alpha      =0;
    x-> rpi        =0;
    x-> delaySample=0;
    x->buffer1 = (t_sample *) calloc (BUFFSIZE , sizeof(t_sample));
    x->buffer2 = (t_sample *) calloc (BUFFSIZE , sizeof(t_sample));
    return (void *)x;
}

void stp_allpassApxDelay_set(stp_allpassApx_tilde *x, float delay)
{
	if (delay < 0 || delay>=(BUFFSIZE-1)) delay = 0;
	x->delaySample = delay;
}

void stp_allpassApxGain_set(stp_allpassApx_tilde *x, float g)
{
	if (g >= 1) g = 1;
	if (g <= 0) g = 0;
    x-> gain = g;
}

void stp_allpassApx_tilde_setup(void)
{
      stp_allpassApx_tilde_class = class_new(gensym("stp_allpassApx~"),
            (t_newmethod)stp_allpassApx_tilde_new,
            (t_method)stp_allpassApx_tilde_free,
        sizeof(stp_allpassApx_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(stp_allpassApx_tilde_class, (t_method)stp_allpassApx_tilde_dsp, gensym("dsp"), 0);
      class_addmethod(stp_allpassApx_tilde_class, (t_method)stp_allpassApxDelay_set, gensym("delay"), A_DEFFLOAT,0);
      class_addmethod(stp_allpassApx_tilde_class, (t_method)stp_allpassApxGain_set, gensym("gain"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(stp_allpassApx_tilde_class, stp_allpassApx_tilde, f);
}
