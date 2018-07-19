//
//  stp_comb_filter.c
//  stp_synthetic_reverb~
//
//  Created by C.Jaedicke on 07.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#include "stp_comb_filter.h"

comb_filter* comb_filter_new(long _buffer_size)
{
    comb_filter *x = (comb_filter*)malloc(sizeof(comb_filter));
    x->feedback = 0;
    x->lowpass = stp_lowpass_new();
    x->delayline = stp_delay_new(_buffer_size);
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
    stp_delay_setDelay(x->delayline, _delay);
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
    stp_delay_perform(x->delayline, out, x->delay_out, vectorSize);
    stp_lowpass_perform(x->lowpass, x->delay_out, x->lowpass_out, vectorSize);
}
