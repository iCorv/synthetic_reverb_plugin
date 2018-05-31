#include "m_pd.h"

#define BUFFSIZE 44100

static t_class *stp_delay_tilde_class;

typedef struct stp_delay_tilde
{
    t_object  x_obj;
    t_sample f;
    t_outlet* x_out;
    t_int rptr;
    t_int wptr;
	t_sample* buffer;

} stp_delay_tilde;


t_int *stp_delay_tilde_perform(t_int *w)
{
    stp_delay_tilde *x = (stp_delay_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
    int i;

    for(i=0; i<n; i++) {
    	x->buffer[x->wptr++] = in[i];
    	out[i] = x->buffer[x->rptr++];

    	if (x->wptr>=(BUFFSIZE-1)) {x->wptr = 0;}
    	if (x->rptr>=(BUFFSIZE-1)) {x->rptr = 0;}

    }

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

void stp_delay_tilde_dsp(stp_delay_tilde *x, t_signal **sp)
{
    dsp_add(stp_delay_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void stp_delay_tilde_free(stp_delay_tilde *x)
{
    outlet_free(x->x_out);
    free(x->buffer);
}

void *stp_delay_tilde_new(t_floatarg f)
{
    stp_delay_tilde *x = (stp_delay_tilde *)pd_new(stp_delay_tilde_class);

    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x-> rptr = 0;
    x-> wptr = 0;
    x->buffer = (t_sample *) calloc (BUFFSIZE , sizeof(t_sample));
    return (void *)x;
}

void stp_delay_set(stp_delay_tilde *x, int delay)
{
    x->rptr = delay;
    if (x->rptr>=(BUFFSIZE-1)) {
    	x->rptr = 0;
    }

}

void stp_delay_tilde_setup(void)
{
      stp_delay_tilde_class = class_new(gensym("stp_delay~"),
            (t_newmethod)stp_delay_tilde_new,
            (t_method)stp_delay_tilde_free,
        sizeof(stp_delay_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(stp_delay_tilde_class, (t_method)stp_delay_tilde_dsp, gensym("dsp"), 0);

      // this adds the delay message to our object
      class_addmethod(stp_delay_tilde_class, (t_method)stp_delay_set, gensym("delay"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(stp_delay_tilde_class, stp_delay_tilde, f);
}
