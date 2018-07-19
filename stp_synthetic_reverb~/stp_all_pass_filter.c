//
//  stp_all_pass_filter.c
//  stp_synthetic_reverb~
//
//  Created by C.Jaedicke on 07.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#include "stp_all_pass_filter.h"


stp_all_pass_filter* stp_all_pass_filter_new()
{
    stp_all_pass_filter *x = (stp_all_pass_filter*)malloc(sizeof(stp_all_pass_filter));

    x-> gain = .0;
    x->delayline1 = stp_delay_new(44100);
    x->delayline2 = stp_delay_new(44100);
    x->delayline_out1 = (float *) calloc (x->delayline1->buffer_size, sizeof(float));
    x->delayline_out2 = (float *) calloc (x->delayline2->buffer_size, sizeof(float));
    return (void *)x;
}
void stp_all_pass_filter_free(stp_all_pass_filter *x)
{
    stp_delay_free(x->delayline1);
    stp_delay_free(x->delayline2);
}
void stp_all_pass_filter_perform(stp_all_pass_filter *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize)
{
    stp_delay_perform(x->delayline1, in, x->delayline_out1, vectorSize);
    
    for (int i=0; i<vectorSize; i++){
        out[i] = ((1+x->gain) * (x->delayline_out1[i])) - in[i] + x->delayline_out2[i] * x->gain;
    }
    stp_delay_perform(x->delayline2, out, x->delayline_out2, vectorSize);
}
void stp_all_pass_filter_set_delay(stp_all_pass_filter *x, float _delay_in_samples)
{
    stp_delay_setDelay(x->delayline1, _delay_in_samples);
    stp_delay_setDelay(x->delayline2, _delay_in_samples);
}
void stp_all_pass_filter_set_gain(stp_all_pass_filter *x, float g)
{
    if (g >= 1) g = 1;
    if (g <= 0) g = 0;
    x-> gain = g;
}
