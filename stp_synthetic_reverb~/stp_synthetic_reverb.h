#ifndef stp_synthetic_reverb_h
#define stp_synthetic_reverb_h

#define STP_INPUTVECTOR_USE_FLOAT
#define STP_OUTPUTVECTOR_USE_FLOAT

#include <stdio.h>
#include <stdlib.h>
#include "stp_defines.h"
#include "stp_comb_filter.h"
#include "stp_all_pass_filter.h"


typedef struct stp_synthetic_reverb
{
    stp_comb_filter* comb_1;
    stp_comb_filter* comb_2;
    stp_comb_filter* comb_3;
    stp_comb_filter* comb_4;
    stp_comb_filter* comb_5;
    stp_comb_filter* comb_6;
    stp_comb_filter* comb_7;
    stp_comb_filter* comb_8;
    
    stp_all_pass_filter* ap_1;
    stp_all_pass_filter* ap_2;
    stp_all_pass_filter* ap_3;
    stp_all_pass_filter* ap_4;
    
    float* comb_buffer_1;
    float* comb_buffer_2;
    float* comb_buffer_3;
    float* comb_buffer_4;
    float* comb_buffer_5;
    float* comb_buffer_6;
    float* comb_buffer_7;
    float* comb_buffer_8;
    
    float* ap_buffer_1;
    float* ap_buffer_2;
    float* ap_buffer_3;
    float* ap_buffer_4;

    float* comb_sum_buffer;
    
    long buffer_size;
} stp_synthetic_reverb;

stp_synthetic_reverb *stp_synthetic_reverb_new();

void stp_synthetic_reverb_free(stp_synthetic_reverb *x);

void stp_synthetic_reverb_perform(stp_synthetic_reverb *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vector_size);

void stp_synthetic_reverb_comb_filter_sum_up(stp_synthetic_reverb *x, int vector_size);

void stp_synthetic_reverb_allocate_temp_buffer(stp_synthetic_reverb *x, int vector_size);

void stp_synthetic_reverb_set_feedback(stp_synthetic_reverb *x, float _feedback);

void stp_synthetic_reverb_set_damping(stp_synthetic_reverb *x, float _damping);

#endif /* stp_synthetic_reverb_h */
