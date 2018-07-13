#include "m_pd.h"
#include <math.h>
#include <stdlib.h>
#include "delay.h"

static t_class *stp_allpassApx_tilde_class;

typedef struct stp_allpassApx_tilde
{
    t_object  x_obj;
    t_sample f;
    t_outlet* x_out;
    delay *delayline1;
    delay *delayline2;
    t_sample *delayline_out1;
    t_sample *delayline_out2;
    t_float gain;

} stp_allpassApx_tilde;


t_int *stp_allpassApx_tilde_perform(t_int *w)
{
    stp_allpassApx_tilde *x = (stp_allpassApx_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);


   delay_perform(x->delayline1, in, x->delayline_out1, n);

    for (int i=0; i<n; i++){
        	out[i] = ((1+x->gain) * (x->delayline_out1[i])) - in[i] + x->delayline_out2[i] * x->gain;
        }
    delay_perform(x->delayline2, out, x->delayline_out2, n);

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
    delay_free(x->delayline1);
    delay_free(x->delayline2);
}

void *stp_allpassApx_tilde_new(t_floatarg f)
{
    stp_allpassApx_tilde *x = (stp_allpassApx_tilde *)pd_new(stp_allpassApx_tilde_class);

    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);

    x-> gain = 0;
    x->delayline1 = delay_new(44100);
    x->delayline2 = delay_new(44100);
    x->delayline_out1 = (t_sample *) calloc (x->delayline1->buffer_size, sizeof(t_sample));
    x->delayline_out2 = (t_sample *) calloc (x->delayline2->buffer_size, sizeof(t_sample));
    return (void *)x;
}

void stp_allpassApxDelay_set(stp_allpassApx_tilde *x, float _delay)
{
	delay_setDelay(x->delayline1, _delay);
	delay_setDelay(x->delayline2, _delay);
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
