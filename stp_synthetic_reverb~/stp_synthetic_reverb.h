#ifndef stp_synthetic_reverb_h
#define stp_synthetic_reverb_h

#include <stdio.h>
#include <stdlib.h>
#include "stp_defines.h"
#include "stp_delay.h"


typedef struct stp_synthetic_reverb
{
    //stp_delay *delay;

} stp_synthetic_reverb;

stp_synthetic_reverb *stp_synthetic_reverb_new();

void stp_synthetic_reverb_free(stp_synthetic_reverb *x);

void stp_synthetic_reverb_perform(stp_synthetic_reverb *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize);

#endif /* stp_synthetic_reverb_h */
