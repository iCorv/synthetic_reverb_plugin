/*
 * stp_lowpass.h
 *
 *  Created on: 26.06.2018
 *      Author: Alberto
 */

#ifndef STP_LOWPASS_H_
#define STP_LOWPASS_H_



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stp_defines.h"

typedef struct stp_lowpass
{
	float cutoff;
	float last_sample;

} stp_lowpass;

stp_lowpass* stp_lowpass_new(void);
void stp_lowpass_free(stp_lowpass *x);
void stp_lowpass_setCutoff(stp_lowpass *x, float _delay_in_samples);
void stp_lowpass_perform(stp_lowpass *x, float *in, float *out, int vectorSize);

#endif /* STP_LOWPASS_H_ */
