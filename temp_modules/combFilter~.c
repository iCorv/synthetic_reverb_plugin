#include "m_pd.h"
#include "comb_filter.h"

static t_class *combFilter_tilde_class;

typedef struct combFilter_tilde
{
    t_object  x_obj;
    t_sample f;
    t_outlet* x_out;
	comb_filter* comb;

} combFilter_tilde;

t_int *combFilter_tilde_perform(t_int *w)
{
    combFilter_tilde *x = (combFilter_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    comb_filter_perform(x->comb, in, out, n);


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
    comb_filter_free(x->comb);
}

void *combFilter_tilde_new(t_floatarg f)
{
    combFilter_tilde *x = (combFilter_tilde *)pd_new(combFilter_tilde_class);

    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->comb = comb_filter_new(44100);
    return (void *)x;
}

void combFilterDelay_set(combFilter_tilde *x, float _delay)
{
	comb_filter_setDelay(x->comb, _delay);
}

void combFilterFeedback_set(combFilter_tilde *x, float _feedback)
{
	comb_filter_setFeedback(x->comb, _feedback);
}

void combFilterDamping_set(combFilter_tilde *x, float _cutoff)
{
	comb_filter_setCutoff(x->comb, _cutoff);
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
    class_addmethod(combFilter_tilde_class, (t_method)combFilterDamping_set, gensym("damping"), A_DEFFLOAT,0);

    CLASS_MAINSIGNALIN(combFilter_tilde_class, combFilter_tilde, f);
}
