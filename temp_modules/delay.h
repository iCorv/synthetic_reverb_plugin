/*
 * delay.h
 *
 *  Created on: 14.06.2018
 *      Author: Alberto
 */

#ifndef DELAY_H_
#define DELAY_H_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

typedef struct delay
{
	    float rptr;
	    int wptr;
		float alpha;
		int rpi;
		float delay_in_samples;
	    float *buffer;
	    long buffer_size;
} delay;

delay* delay_new(long buffsize);
void delay_free(delay *x);
void delay_setDelay(delay *x, float _delay_in_samples);
void delay_perform(delay *x, float *in, float *out, int vectorSize);

#endif /* DELAY_H_ */
