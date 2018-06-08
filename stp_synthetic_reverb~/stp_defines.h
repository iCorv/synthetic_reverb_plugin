//
//  stp_defines.h
//  stp_gain~
//
//  Created by Admin on 02.06.18.
//  Copyright © 2018 Intrinsic Audio. All rights reserved.
//

#ifndef stp_defines_h
#define stp_defines_h

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
