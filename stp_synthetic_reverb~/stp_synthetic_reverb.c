#include "stp_synthetic_reverb.h"

stp_synthetic_reverb *stp_synthetic_reverb_new(long _buffer_size)
{
    stp_synthetic_reverb *x = (stp_synthetic_reverb *)malloc(sizeof(stp_synthetic_reverb));
    x-> buffer_size = _buffer_size;
    
    x-> comb_1 = stp_comb_filter_new(x-> buffer_size);
    x-> comb_2 = stp_comb_filter_new(x-> buffer_size);
    x-> comb_3 = stp_comb_filter_new(x-> buffer_size);
    x-> comb_4 = stp_comb_filter_new(x-> buffer_size);
    x-> comb_5 = stp_comb_filter_new(x-> buffer_size);
    x-> comb_6 = stp_comb_filter_new(x-> buffer_size);
    x-> comb_7 = stp_comb_filter_new(x-> buffer_size);
    x-> comb_8 = stp_comb_filter_new(x-> buffer_size);
    
    stp_comb_filter_setDelay(x-> comb_1, comb1_delay);
    stp_comb_filter_setDelay(x-> comb_2, comb2_delay);
    stp_comb_filter_setDelay(x-> comb_3, comb3_delay);
    stp_comb_filter_setDelay(x-> comb_4, comb4_delay);
    stp_comb_filter_setDelay(x-> comb_5, comb5_delay);
    stp_comb_filter_setDelay(x-> comb_6, comb6_delay);
    stp_comb_filter_setDelay(x-> comb_7, comb7_delay);
    stp_comb_filter_setDelay(x-> comb_8, comb8_delay);
    
    x-> ap_1 = stp_all_pass_filter_new(x-> buffer_size);
    x-> ap_2 = stp_all_pass_filter_new(x-> buffer_size);
    x-> ap_3 = stp_all_pass_filter_new(x-> buffer_size);
    
    /*
    x-> comb_buffer_1 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> comb_buffer_2 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> comb_buffer_3 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> comb_buffer_4 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> comb_buffer_5 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> comb_buffer_6 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> comb_buffer_7 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> comb_buffer_8 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    
    x-> ap_buffer_1 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> ap_buffer_2 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    x-> ap_buffer_3 = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    
    x-> comb_sum_buffer = (float *) calloc (x-> buffer_size + 1 , sizeof(float));
    */
    return (void *)x;
}

void stp_synthetic_reverb_free(stp_synthetic_reverb *x)
{
    // free buffers
    free(x-> comb_buffer_1);
    free(x-> comb_buffer_2);
    free(x-> comb_buffer_3);
    free(x-> comb_buffer_4);
    free(x-> comb_buffer_5);
    free(x-> comb_buffer_6);
    free(x-> comb_buffer_7);
    free(x-> comb_buffer_8);
    
    free(x-> ap_buffer_1);
    free(x-> ap_buffer_2);
    free(x-> ap_buffer_3);
    
    free(x-> comb_sum_buffer);
    
    // free all pass filter objects
    stp_all_pass_filter_free(x-> ap_1);
    stp_all_pass_filter_free(x-> ap_2);
    stp_all_pass_filter_free(x-> ap_3);
    
    // free comb filter objects
    stp_comb_filter_free(x-> comb_1);
    stp_comb_filter_free(x-> comb_2);
    stp_comb_filter_free(x-> comb_3);
    stp_comb_filter_free(x-> comb_4);
    stp_comb_filter_free(x-> comb_5);
    stp_comb_filter_free(x-> comb_6);
    stp_comb_filter_free(x-> comb_7);
    stp_comb_filter_free(x-> comb_8);
    
    free(x);
}

void stp_synthetic_reverb_perform(stp_synthetic_reverb *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vector_size)
{
    stp_comb_filter_perform(x-> comb_1, in, x-> comb_buffer_1, vector_size);
    stp_comb_filter_perform(x-> comb_2, in, x-> comb_buffer_2, vector_size);
    stp_comb_filter_perform(x-> comb_3, in, x-> comb_buffer_3, vector_size);
    stp_comb_filter_perform(x-> comb_4, in, x-> comb_buffer_4, vector_size);
    stp_comb_filter_perform(x-> comb_5, in, x-> comb_buffer_5, vector_size);
    stp_comb_filter_perform(x-> comb_6, in, x-> comb_buffer_6, vector_size);
    stp_comb_filter_perform(x-> comb_7, in, x-> comb_buffer_7, vector_size);
    stp_comb_filter_perform(x-> comb_8, in, x-> comb_buffer_8, vector_size);
    
    stp_synthetic_reverb_comb_filter_sum_up(x, vector_size);
    
    for(int i = 0; i < vector_size; i++)
    {
        out[i] = x-> comb_sum_buffer[i];
    }
}

void stp_synthetic_reverb_comb_filter_sum_up(stp_synthetic_reverb *x, int vector_size)
{
    for(int i = 0; i < vector_size; i++)
    {
        x-> comb_sum_buffer[i] = (x-> comb_buffer_1[i] + x-> comb_buffer_2[i] + x-> comb_buffer_3[i] + x-> comb_buffer_4[i] + x-> comb_buffer_5[i] + x-> comb_buffer_6[i] + x-> comb_buffer_7[i] + x-> comb_buffer_8[i]) / 8;
    }
}

void stp_synthetic_reverb_allocate_temp_buffer(stp_synthetic_reverb *x, int vector_size)
{
    x-> comb_buffer_1 = (float *) calloc (vector_size, sizeof(float));
    x-> comb_buffer_2 = (float *) calloc (vector_size, sizeof(float));
    x-> comb_buffer_3 = (float *) calloc (vector_size, sizeof(float));
    x-> comb_buffer_4 = (float *) calloc (vector_size, sizeof(float));
    x-> comb_buffer_5 = (float *) calloc (vector_size, sizeof(float));
    x-> comb_buffer_6 = (float *) calloc (vector_size, sizeof(float));
    x-> comb_buffer_7 = (float *) calloc (vector_size, sizeof(float));
    x-> comb_buffer_8 = (float *) calloc (vector_size, sizeof(float));
    
    x-> comb_sum_buffer = (float *) calloc (vector_size, sizeof(float));
    
    x-> ap_buffer_1 = (float *) calloc (vector_size, sizeof(float));
    x-> ap_buffer_2 = (float *) calloc (vector_size, sizeof(float));
    x-> ap_buffer_3 = (float *) calloc (vector_size, sizeof(float));
    
    
    
    // down pass temp buffer size to lower level modules
    stp_comb_filter_allocate_temp_buffer(x->comb_1, vector_size);
    stp_comb_filter_allocate_temp_buffer(x->comb_2, vector_size);
    stp_comb_filter_allocate_temp_buffer(x->comb_3, vector_size);
    stp_comb_filter_allocate_temp_buffer(x->comb_4, vector_size);
    stp_comb_filter_allocate_temp_buffer(x->comb_5, vector_size);
    stp_comb_filter_allocate_temp_buffer(x->comb_6, vector_size);
    stp_comb_filter_allocate_temp_buffer(x->comb_7, vector_size);
    stp_comb_filter_allocate_temp_buffer(x->comb_8, vector_size);
    
    stp_all_pass_filter_allocate_temp_buffer(x->ap_1, vector_size);
    stp_all_pass_filter_allocate_temp_buffer(x->ap_2, vector_size);
    stp_all_pass_filter_allocate_temp_buffer(x->ap_3, vector_size);
}







