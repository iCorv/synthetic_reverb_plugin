//
//  stp_delay.h
//  stp_synthetic_reverb~
//
//  Created by C.Jaedicke on 07.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#ifndef stp_delay_h
#define stp_delay_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

#define STP_INPUTVECTOR_USE_FLOAT
#define STP_OUTPUTVECTOR_USE_FLOAT


typedef struct stp_delay
{
    // read pointer
    //float rptr;
    // write pointer
    //int wptr;
    // delay buffer
    float* buffer;
    // interpolation factor
    //float alpha;
    // rounded read pointer
    //int rpi;
    // length of delay in samples
    float delay_in_samples;
    // buffer size
    long buffer_size;
    // circular pointer
    float* circ_p;
    int q;
    //
    float s;
} stp_delay;

stp_delay *stp_delay_new(long _buffer_size);

void stp_delay_free(stp_delay *x);

void stp_delay_setDelay(stp_delay *x, float _delay_in_samples);

float tap(long D, float *w, float *p, int i);

float tapi(long D, float d, float *w, float *p);

void wrap(long M, float *w, float **p);

void cdelay(long D, float *w, float **p);
void cdelay2(long D, int *q);
void wrap2(long M, int *q);

void stp_delay_perform(stp_delay *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize);

#endif /* stp_delay_h */
