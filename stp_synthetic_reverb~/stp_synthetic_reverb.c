#include "stp_synthetic_reverb.h"

stp_synthetic_reverb *stp_synthetic_reverb_new()
{
    stp_synthetic_reverb *x = (stp_synthetic_reverb *)malloc(sizeof(stp_synthetic_reverb));
    return x;
}

void stp_synthetic_reverb_free(stp_synthetic_reverb *x)
{
    free(x);
}

void stp_synthetic_reverb_perform(stp_synthetic_reverb *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize)
{

}
