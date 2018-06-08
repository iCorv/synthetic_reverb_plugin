#include "m_pd.h"
//#include "stp_synthetic_reverb.h"
#include "stp_delay.h"



static t_class *stp_synthetic_reverb_tilde_class;

typedef struct stp_synthetic_reverb_tilde
{
    t_object  x_obj;
    t_sample f;
    stp_delay *my_delay;
    t_outlet *x_out;
} stp_synthetic_reverb_tilde;

t_int *stp_synthetic_reverb_tilde_perform(t_int *w)
{
    stp_synthetic_reverb_tilde *x = (stp_synthetic_reverb_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
            
    stp_delay_perform(x-> my_delay, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

void stp_synthetic_reverb_tilde_dsp(stp_synthetic_reverb_tilde *x, t_signal **sp)
{
    dsp_add(stp_synthetic_reverb_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void stp_synthetic_reverb_tilde_free(stp_synthetic_reverb_tilde *x)
{
    outlet_free(x->x_out);
}

void stp_synthetic_reverb_tilde_setDelay(stp_synthetic_reverb_tilde *x, float delay)
{
    x-> my_delay-> delay_in_samples = delay;
}

void *stp_synthetic_reverb_tilde_new(t_floatarg f)
{
    stp_synthetic_reverb_tilde *x = (stp_synthetic_reverb_tilde *)pd_new(stp_synthetic_reverb_tilde_class);
    
    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->my_delay = stp_delay_new(44100);

    return (void *)x;
}

void stp_synthetic_reverb_tilde_setup(void)
{
      stp_synthetic_reverb_tilde_class = class_new(gensym("stp_synthetic_reverb~"),
            (t_newmethod)stp_synthetic_reverb_tilde_new,
            (t_method)stp_synthetic_reverb_tilde_free,
        sizeof(stp_synthetic_reverb_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(stp_synthetic_reverb_tilde_class, (t_method)stp_synthetic_reverb_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      class_addmethod(stp_synthetic_reverb_tilde_class, (t_method)stp_synthetic_reverb_tilde_setDelay, gensym("delay"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(stp_synthetic_reverb_tilde_class, stp_synthetic_reverb_tilde, f);
}
