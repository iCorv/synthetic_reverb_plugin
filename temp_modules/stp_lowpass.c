/*
 * stp_lowpass.c
 *
 *  Created on: 26.06.2018
 *      Author: Alberto
 */


#include "stp_lowpass.h"

 stp_lowpass* stp_lowpass_new(void)
{
	stp_lowpass *x = (stp_lowpass*)malloc(sizeof(stp_lowpass));
	x->cutoff = 0;
	x->last_sample = 0;
    return (stp_lowpass*)x;
}

void stp_lowpass_free(stp_lowpass *x)
{
    free(x);
}

void stp_lowpass_setCutoff(stp_lowpass *x, float _cutoff)
{
	if (_cutoff >= 1) _cutoff = 1;
	if (_cutoff <= 0) _cutoff = 0;
    x->cutoff = _cutoff;
}

void stp_lowpass_perform(stp_lowpass *x, float *in, float *out, int vectorSize)
{
	for(int i=0; i<vectorSize; i++)
	{
		out[i] = (1-x->cutoff) * in[i] + x-> cutoff * x->last_sample;
	    x->last_sample = out[i];
	}
}

