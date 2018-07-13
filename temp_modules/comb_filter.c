/*
 * comb_filter.c
 *
 *  Created on: 21.06.2018
 *      Author: Alberto
 */

#include "comb_filter.h"

comb_filter* comb_filter_new(long buffsize)
{
	comb_filter *x = (comb_filter*)malloc(sizeof(comb_filter));
	x->feedback = 0;
	x->lowpass = stp_lowpass_new();
	x->delayline = delay_new(buffsize);
	x->delay_out = (float *) calloc (x->delayline->buffer_size, sizeof(float));
	x->lowpass_out = (float *) calloc (x->delayline->buffer_size, sizeof(float));
    return (comb_filter*)x;
}

void comb_filter_free(comb_filter *x)
{
    free(x);
}

void comb_filter_setFeedback(comb_filter *x, float _feedback)
{
	if (_feedback >= 0.99) _feedback = 0.99;
	if ( _feedback <= 0) _feedback = 0;
	x->feedback = _feedback;
}

void comb_filter_setDelay(comb_filter *x, float _delay)
{
	delay_setDelay(x->delayline, _delay);
}

void comb_filter_setCutoff (comb_filter *x, float _cutoff)
{
	stp_lowpass_setCutoff(x->lowpass, _cutoff);
}

void comb_filter_perform(comb_filter *x, float *in, float *out, int vectorSize)
{
	for (int i=0; i< vectorSize; i++){
	        out[i] = in[i] + x->feedback * x->lowpass_out[i];
	}
    delay_perform(x->delayline, out, x->delay_out, vectorSize);
    stp_lowpass_perform(x->lowpass, x->delay_out, x->lowpass_out, vectorSize);
}

