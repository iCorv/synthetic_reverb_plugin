/*
 * comb_filter.h
 *
 *  Created on: 21.06.2018
 *      Author: Alberto
 */

#ifndef COMB_FILTER_H_
#define COMB_FILTER_H_

#include "delay.h"
#include "stp_lowpass.h"

typedef struct comb_filter
{
	delay *delayline;
	stp_lowpass* lowpass;
	float feedback;
	float *delay_out;
	float *lowpass_out;

} comb_filter;

comb_filter* comb_filter_new(long buffsize);
void comb_filter_free(comb_filter *x);
void comb_filter_setFeedback( comb_filter *x, float _feedback);
void comb_filter_setDelay( comb_filter *x, float _delay);
void comb_filter_setCutoff (comb_filter *x, float _cutoff);
void comb_filter_perform(comb_filter *x, float *in, float *out, int vectorSize);

#endif /* COMB_FILTER_H_ */
