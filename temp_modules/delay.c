/*
 * delay.c
 *
 *  Created on: 14.06.2018
 *      Author: Alberto
 */

#include "delay.h"

 delay* delay_new(long buffsize)
{
	delay *x = (delay*)malloc(sizeof(delay));
	x-> buffer_size = buffsize;
	x-> rptr = 0;
    x-> wptr = 0;
	x-> alpha = 0;
	x-> rpi = 0;
	x-> delay_in_samples = 0;
    x-> buffer = (float *) calloc(x->buffer_size, sizeof(float));
    return (delay*)x;
}

void delay_free(delay *x)
{
    free(x);
}

void delay_setDelay(delay *x, float _delay_in_samples)
{
    if (_delay_in_samples < 0 || _delay_in_samples >= ((x->buffer_size) - 1))
        _delay_in_samples = 0;
    x->delay_in_samples = _delay_in_samples ;
}

void delay_perform(delay *x, float *in, float *out, int vectorSize)
{
	for(int i=0; i<vectorSize; i++)
	{
			x->buffer[x->wptr]=in[i];
    		x->rptr = x->wptr - x->delay_in_samples;
    		if (x->rptr < 0) x->rptr+=x->buffer_size-1;
    		x->rpi = floor(x->rptr);
    		x->alpha = x->rptr - x->rpi;
    		out[i] = x->alpha * x->buffer[x->rpi] + (1-x->alpha) * x->buffer[x->rpi+1];
    		if (x->wptr>=(x->buffer_size-1)) x->wptr = 0; else x->wptr+=1;
	}
}
