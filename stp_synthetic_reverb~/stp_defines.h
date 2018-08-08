//
//  stp_defines.h
//  stp_gain~
//
//  Created by Admin on 02.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#ifndef stp_defines_h
#define stp_defines_h

#define COMB1_DELAY 1116.171
#define COMB2_DELAY COMB1_DELAY + 71.83
#define COMB3_DELAY COMB1_DELAY + 160.965
#define COMB4_DELAY COMB1_DELAY + 239.904
#define COMB5_DELAY COMB1_DELAY + 305.613
#define COMB6_DELAY COMB1_DELAY + 374.85
#define COMB7_DELAY COMB1_DELAY + 441
#define COMB8_DELAY COMB1_DELAY + 500.976

#define AP_GAIN 0.5
#define AP_1_DELAY 556.101
#define AP_2_DELAY 441
#define AP_3_DELAY 340.893
#define AP_4_DELAY 224.91



#ifdef STP_INPUTVECTOR_USE_FLOAT
typedef float STP_INPUTVECTOR;
#else
typedef double STP_INPUTVECTOR;
#endif

#ifdef STP_OUTPUTVECTOR_USE_FLOAT
typedef float STP_OUTPUTVECTOR;
#else
typedef double STP_OUTPUTVECTOR;
#endif

#endif /* stp_defines_h */
