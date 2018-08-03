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

stp_comb_filter* stp_comb_filter_new();
void stp_comb_filter_free(stp_comb_filter *x);
void stp_comb_filter_set_feedback( stp_comb_filter *x, float _feedback);
void stp_comb_filter_set_delay( stp_comb_filter *x, float _delay);
void stp_comb_filter_set_cutoff (stp_comb_filter *x, float _cutoff);
void stp_comb_filter_perform(stp_comb_filter *x, float *in, float *out, int vector_size);
void stp_comb_filter_allocate_temp_buffer(stp_comb_filter *x, int vector_size);

#endif /* COMB_FILTER_H_ */
