//
//  stp_defines.h
//  stp_gain~
//
//  Created by Admin on 02.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#ifndef stp_defines_h
#define stp_defines_h

#define comb1_delay 1116.171
#define comb2_delay comb1_delay + 71.83
#define comb3_delay comb1_delay + 160.965
#define comb4_delay comb1_delay + 239.904
#define comb5_delay comb1_delay +305.613
#define comb6_delay comb1_delay + 374.85
#define comb7_delay comb1_delay + 441
#define comb8_delay comb1_delay + 500.976

#define ap_gain 0.5
#define ap_1_delay 556.101
#define ap_2_delay 441
#define ap_3_delay 340.893
#define ap_4_delay 224.91



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
