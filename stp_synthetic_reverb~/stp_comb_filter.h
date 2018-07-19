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
#include "stp_low_pass.h"

typedef struct stp_comb_filter
{
    stp_delay *delayline;
    stp_low_pass* lowpass;
    float feedback;
    float *delay_out;
    float *lowpass_out;
    
} stp_comb_filter;

stp_comb_filter* stp_comb_filter_new(long _buffer_size);
void stp_comb_filter_free(stp_comb_filter *x);
void stp_comb_filter_setFeedback( stp_comb_filter *x, float _feedback);
void stp_comb_filter_setDelay( stp_comb_filter *x, float _delay);
void stp_comb_filter_setCutoff (stp_comb_filter *x, float _cutoff);
void stp_comb_filter_perform(stp_comb_filter *x, float *in, float *out, int vectorSize);

#endif /* COMB_FILTER_H_ */
