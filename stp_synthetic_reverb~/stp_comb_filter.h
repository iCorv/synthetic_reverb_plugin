//
//  stp_comb_filter.h
//  stp_synthetic_reverb~
//
//  Created by A.Monciero, C.Jaedicke, P. on 07.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#ifndef COMB_FILTER_H_
#define COMB_FILTER_H_

#include "stp_delay.h"
#include "stp_lowpass.h"

typedef struct comb_filter
{
    stp_delay *delayline;
    stp_lowpass* lowpass;
    float feedback;
    float *delay_out;
    float *lowpass_out;
    
} comb_filter;

comb_filter* comb_filter_new(long _buffer_size);
void comb_filter_free(comb_filter *x);
void comb_filter_setFeedback( comb_filter *x, float _feedback);
void comb_filter_setDelay( comb_filter *x, float _delay);
void comb_filter_setCutoff (comb_filter *x, float _cutoff);
void comb_filter_perform(comb_filter *x, float *in, float *out, int vectorSize);

#endif /* COMB_FILTER_H_ */
