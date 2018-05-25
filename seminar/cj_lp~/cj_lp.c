#include "m_pd.h"

static t_class *cj_lp_tilde_class;

typedef struct cj_lp_tilde
{
    t_object  x_obj;
    t_sample f;
    t_outlet* x_out;
    t_sample last_sample;
    t_float a0;
} cj_lp_tilde;

t_int *cj_lp_tilde_perform(t_int *w)
{
    cj_lp_tilde *x = (cj_lp_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
    int i;

    for(i=0; i<n; i++) {
        out[i] = x->a0 * in[i] + .5 * x->last_sample;
        x->last_sample = out[i];
    }

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

void cj_lp_tilde_dsp(cj_lp_tilde *x, t_signal **sp)
{
    dsp_add(cj_lp_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void cj_lp_tilde_free(cj_lp_tilde *x)
{
    outlet_free(x->x_out);
}

void *cj_lp_tilde_new(t_floatarg f)
{
    cj_lp_tilde *x = (cj_lp_tilde *)pd_new(cj_lp_tilde_class);
    
    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->last_sample = 0;
    x->a0 = 0.5;
    return (void *)x;
}

void cj_lp_setFrequency(cj_lp_tilde *x, t_float cut_off_frequency)
{
    x->a0 = cut_off_frequency * (2.0 * 3.14159) / 44100.0;
    if(x->a0 < 0)
        x->a0 = 0;
    else if(x->a0 > 1)
        x->a0 = 1;
}

void cj_lp_tilde_setup(void)
{
      cj_lp_tilde_class = class_new(gensym("cj_lp~"),
            (t_newmethod)cj_lp_tilde_new,
            (t_method)cj_lp_tilde_free,
        sizeof(cj_lp_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(cj_lp_tilde_class, (t_method)cj_lp_tilde_dsp, gensym("dsp"), 0);
    
      // this adds the CutOff message to our object
      class_addmethod(cj_lp_tilde_class, (t_method)cj_lp_setFrequency, gensym("CutOff"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(cj_lp_tilde_class, cj_lp_tilde, f);
}
