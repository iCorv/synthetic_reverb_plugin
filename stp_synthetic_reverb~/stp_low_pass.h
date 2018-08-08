/**
 * @file stp_low_pass.h
 * @author C.Jaedicke, A.Monciero, P.Schuhladen, F.Müller <br>
 * A single pole lowpass filter class <br>
 * <br>
 * @brief Audio Object for lowpass filtering the input <br>
 * <br>
 * stp_low_pass allows for lowas filtering <br>
 * any incoming audio signal. <br>
 * <br>
 */

#ifndef stp_low_pass_h
#define stp_low_pass_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

/**
 * @struct stp_low_pass
 * @brief A structure for a lowpass filter object <br>
 * @var stp::cutoff The cut off frequency of the filter <br>
 * @var stp::last_sample Saves the last output sample for the recursive structure <br>
 */
typedef struct stp_low_pass
{
    float cutoff;
    float last_sample;
    
} stp_low_pass;

/**
 * @related stp_low_pass
 * @brief Creates a new lowpass object<br>
 * The function sets the buffer size and delay parameter of <br>
 * the delay class
 * @return a pointer to the newly created stp_delay object <br>
 */
stp_low_pass* stp_low_pass_new(void);
void stp_low_pass_free(stp_low_pass *x);
void stp_low_pass_setCutoff(stp_low_pass *x, float _delay_in_samples);
void stp_low_pass_perform(stp_low_pass *x, float *in, float *out, int vectorSize);

#endif /* stp_low_pass_h */
