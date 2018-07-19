//
//  stp_all_pass_filter.h
//  stp_synthetic_reverb~
//
//  Created by C.Jaedicke on 07.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#ifndef stp_all_pass_filter_h
#define stp_all_pass_filter_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "stp_delay.h"

typedef struct stp_all_pass_filter
{
    stp_delay *delayline1;
    stp_delay *delayline2;
    float *delayline_out1;
    float *delayline_out2;
    float gain;
    
} stp_all_pass_filter;

stp_all_pass_filter* stp_all_pass_filter_new();
void stp_all_pass_filter_free(stp_all_pass_filter *x);
void stp_all_pass_filter_perform(stp_all_pass_filter *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize);
void stp_all_pass_filter_set_delay(stp_all_pass_filter *x, float _delay_in_samples);
void stp_all_pass_filter_set_gain(stp_all_pass_filter *x, float g);

#endif /* stp_all_pass_filter_h */
