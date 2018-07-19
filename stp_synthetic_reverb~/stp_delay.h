/**
 * @file stp_delay.h
 * @author  <br>
 * An interpolated delay <br>
 * <br>
 * @brief Audio Object for adding delay to the input<br>
 * <br>
 * stp_delay allows for adding delay<br>
 * to any incoming audio signal. <br>
 * <br>
 */

#ifndef stp_delay_h
#define stp_delay_h

#define STP_INPUTVECTOR_USE_FLOAT
#define STP_OUTPUTVECTOR_USE_FLOAT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

/**
 * @struct stp_delay
 * @brief A structure for a delay object <br>
 * @var stp::delay The parameter value for adjusting the <br>
 * delay of the incoming signal
 */

typedef struct stp_delay
{
    float* buffer;              /**< Our delay buffer */
    float delay_in_samples;
    long buffer_size;
    float* circ_p;
    int q;
    float s;
} stp_delay;

/**
 * @related stp_delay
 * @brief Creates a new delay object<br>
 * The function sets the buffer size and delay parameter of <br>
 * the delay class
 * @return a pointer to the newly created stp_delay object <br>
 */

stp_delay *stp_delay_new(int _buffer_size);

/**
 * @related stp_delay
 * @brief Frees a delay object<br>
 * @param x My delay object <br>
 * The function frees the allocated memory<br>
 * of a delay object
 */

void stp_delay_free(stp_delay *x);

/**
 * @related stp_delay
 * @brief Performs the delay in realtime <br>
 * @param x My delay object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function stp_delay_perform performs adds the delay of <br>
 * the incoming signal and copies the result to the output vector <br>
 */

void stp_delay_perform(stp_delay *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize);

void stp_delay_setDelay(stp_delay *x, float _delay_in_samples);

float tap(long D, float *w, float *p, int i);

float tapi(long D, float d, float *w, float *p);

void wrap(long M, float *w, float **p);

void cdelay(long D, float *w, float **p);

#endif /* stp_delay_h */
