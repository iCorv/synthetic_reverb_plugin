/**
 * @file stp_defines.h
 * @author C.Jaedicke, A.Monciero, P.Schuhladen, F.Müller <br>
 * Definitions <br>
 * <br>
 * @brief Constant values used in the synthetic reverb plug-in <br>
 * <br>
 * Constant values used in the synthetic reverb plug-in <br>
 * <br>
 */


#ifndef stp_defines_h
#define stp_defines_h

/**
 * Delay constants for the comb filters.
 */
#define COMB1_DELAY 1116.171
#define COMB2_DELAY COMB1_DELAY + 71.83
#define COMB3_DELAY COMB1_DELAY + 160.965
#define COMB4_DELAY COMB1_DELAY + 239.904
#define COMB5_DELAY COMB1_DELAY + 305.613
#define COMB6_DELAY COMB1_DELAY + 374.85
#define COMB7_DELAY COMB1_DELAY + 441
#define COMB8_DELAY COMB1_DELAY + 500.976

/**
 * Allpass gain value
 */
#define AP_GAIN 0.5

/**
 * Delay constants for the allpass filters.
 */
#define AP_1_DELAY 556.101
#define AP_2_DELAY 441
#define AP_3_DELAY 340.893
#define AP_4_DELAY 224.91

/**
 * Enough buffer for most applications.
 */
#define STANDARD_BUFFER_SIZE 44100


/**
 * Choose floating point or double precision for i/o vectors.
 */
#ifdef STP_INPUTVECTOR_USE_FLOAT
typedef float STP_INPUTVECTOR;
#else
typedef double STP_INPUTVECTOR;
#endif

/**
 * Choose floating point or double precision for i/o vectors.
 */
#ifdef STP_OUTPUTVECTOR_USE_FLOAT
typedef float STP_OUTPUTVECTOR;
#else
typedef double STP_OUTPUTVECTOR;
#endif

#endif /* stp_defines_h */
