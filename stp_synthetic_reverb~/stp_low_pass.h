//
//  stp_low_pass.h
//  stp_synthetic_reverb~
//
//  Created by C.Jaedicke on 19.07.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#ifndef stp_low_pass_h
#define stp_low_pass_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

typedef struct stp_low_pass
{
    float cutoff;
    float last_sample;
    
} stp_low_pass;

stp_low_pass* stp_lowpass_new();
void stp_low_pass_free(stp_low_pass *x);
void stp_low_pass_setCutoff(stp_low_pass *x, float _delay_in_samples);
void stp_low_pass_perform(stp_low_pass *x, float *in, float *out, int vectorSize);

#endif /* stp_low_pass_h */
