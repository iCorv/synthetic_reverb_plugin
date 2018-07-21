//
//  stp_comb_filter.c
//  stp_synthetic_reverb~
//
//  Created by C.Jaedicke on 07.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#include "stp_comb_filter.h"

stp_comb_filter* stp_comb_filter_new(long _buffer_size)
{
    stp_comb_filter *x = (stp_comb_filter*)malloc(sizeof(stp_comb_filter));
    x->feedback = 0;
    x->lowpass = stp_low_pass_new();
    x->delayline = stp_delay_new(_buffer_size);
    x->delay_out = (float *) calloc (x->delayline->buffer_size, sizeof(float));
    x->lowpass_out = (float *) calloc (x->delayline->buffer_size, sizeof(float));
    return (stp_comb_filter*)x;
}

void stp_comb_filter_free(stp_comb_filter *x)
{
    free(x-> delay_out);
    free(x-> lowpass_out);
    stp_low_pass_free(x-> lowpass);
    stp_delay_free(x-> delayline);
    free(x);
}

void stp_comb_filter_setFeedback(stp_comb_filter *x, float _feedback)
{
    if (_feedback >= 0.99) _feedback = 0.99;
    if ( _feedback <= 0) _feedback = 0;
    x->feedback = _feedback;
}

void stp_comb_filter_setDelay(stp_comb_filter *x, float _delay)
{
    stp_delay_setDelay(x->delayline, _delay);
}

void stp_comb_filter_setCutoff (stp_comb_filter *x, float _cutoff)
{
    stp_low_pass_setCutoff(x->lowpass, _cutoff);
}

void stp_comb_filter_perform(stp_comb_filter *x, float *in, float *out, int vector_size)
{
    for (int i=0; i< vector_size; i++){
        out[i] = in[i] + x->feedback * x->lowpass_out[i];
    }
    stp_delay_perform(x->delayline, out, x->delay_out, vector_size);
    stp_low_pass_perform(x->lowpass, x->delay_out, x->lowpass_out, vector_size);
}
