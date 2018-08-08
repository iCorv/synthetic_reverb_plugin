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
    x->delay_line1 = stp_delay_new(STANDARD_BUFFER_SIZE);
    x->delay_line2 = stp_delay_new(STANDARD_BUFFER_SIZE);

    return (void *)x;
}
void stp_all_pass_filter_free(stp_all_pass_filter *x)
{
    free(x-> delay_line_out1);
    free(x-> delay_line_out2);
    stp_delay_free(x-> delay_line1);
    stp_delay_free(x-> delay_line2);
    free(x);
}
void stp_all_pass_filter_perform(stp_all_pass_filter *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize)
{
    
    for (int i=0; i<vectorSize; i++){
        out[i] = ((1+x->gain) * (x->delay_line_out1[i])) - in[i] + x->delay_line_out2[i] * x->gain;
    }
    stp_delay_perform(x->delay_line1, in, x->delay_line_out1, vectorSize);
    stp_delay_perform(x->delay_line2, out, x->delay_line_out2, vectorSize);
    
}
void stp_all_pass_filter_set_delay(stp_all_pass_filter *x, float _delay_in_samples)
{
    stp_delay_set_delay(x->delay_line1, _delay_in_samples);
    stp_delay_set_delay(x->delay_line2, _delay_in_samples);
}
void stp_all_pass_filter_set_gain(stp_all_pass_filter *x, float _gain)
{
    if (_gain >= 1) _gain = 1;
    if (_gain <= 0) _gain = 0;
    x-> gain = _gain;
}

void stp_all_pass_filter_allocate_temp_buffer(stp_all_pass_filter *x, int vector_size) {
	
    x->delay_line_out1 = (float *) calloc (vector_size, sizeof(float));
    x->delay_line_out2 = (float *) calloc (vector_size, sizeof(float));
}
