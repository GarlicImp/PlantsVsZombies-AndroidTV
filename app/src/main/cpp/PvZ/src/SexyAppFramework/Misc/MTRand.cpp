/*
* Copyright (C) 2023-2025  PvZ TV Touch Team
*
* This file is part of PlantsVsZombies-AndroidTV.
*
* PlantsVsZombies-AndroidTV is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or (at your
* option) any later version.
*
* PlantsVsZombies-AndroidTV is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* PlantsVsZombies-AndroidTV.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "PvZ/SexyAppFramework/Misc/MTRand.h"

using namespace Sexy;

///* Period parameters */
// constexpr int MTRAND_M = 397;
// constexpr int MATRIX_A = 0x9908b0dfUL;   /* constant vector a */
// constexpr int UPPER_MASK = 0x80000000UL; /* most significant w-r bits */
// constexpr int LOWER_MASK = 0x7fffffffUL; /* least significant r bits */
//
///* Tempering parameters */
// constexpr int TEMPERING_MASK_B = 0x9d2c5680;
// constexpr int TEMPERING_MASK_C = 0xefc60000;
// #define TEMPERING_SHIFT_U(y)  (y >> 11)
// #define TEMPERING_SHIFT_S(y)  (y << 7)
// #define TEMPERING_SHIFT_T(y)  (y << 15)
// #define TEMPERING_SHIFT_L(y)  (y >> 18)
//
//
MTRand::MTRand(const std::string &theSerialData) {
    SRand(theSerialData);
    mti = MTRAND_N + 1; /* mti==MTRAND_N+1 means mt[MTRAND_N] is not initialized */
}

MTRand::MTRand(unsigned long seed) {
    SRand(seed);
}

MTRand::MTRand() {
    SRand(4357);
}

// static int gRandAllowed = 0;
// void MTRand::SetRandAllowed(bool allowed)
//{
//    if (allowed)
//    {
//        if (gRandAllowed>0)
//            gRandAllowed--;
//    }
//    else
//        gRandAllowed++;
//}
//
void MTRand::SRand(const std::string &theSerialData) {
    if (theSerialData.size() == MTRAND_N * 4) {
        memcpy(mt, theSerialData.c_str(), MTRAND_N * 4);
    } else
        SRand(4357);
}

void MTRand::SRand(unsigned long seed) {
    if (seed == 0)
        seed = 4357;

    /* setting initial seeds to mt[MTRAND_N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0] = seed & 0xffffffffUL;
    for (mti = 1; mti < MTRAND_N; mti++) {
        mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

// unsigned long MTRand::Next()
//{
//    return NextNoAssert();
//}
//
// unsigned long MTRand::NextNoAssert()
//{
//    unsigned long y;
//    static unsigned long mag01[2]={0x0, MATRIX_A};
//    /* mag01[x] = x * MATRIX_A  for x=0,1 */
//
//    if (mti >= MTRAND_N) { /* generate MTRAND_N words at one time */
//        int kk;
//
//        for (kk=0;kk<MTRAND_N-MTRAND_M;kk++) {
//            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
//            mt[kk] = mt[kk+MTRAND_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
//        }
//        for (;kk<MTRAND_N-1;kk++) {
//            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
//            mt[kk] = mt[kk+(MTRAND_M-MTRAND_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
//        }
//        y = (mt[MTRAND_N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
//        mt[MTRAND_N-1] = mt[MTRAND_M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];
//
//        mti = 0;
//    }
//
//    y = mt[mti++];
//    y ^= TEMPERING_SHIFT_U(y);
//    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
//    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
//    y ^= TEMPERING_SHIFT_L(y);
//
//    y &= 0x7FFFFFFF;
//
//    /*char aStr[256];
//    sprintf(aStr, "Rand=%d\r\n", y);
//    OutputDebugString(aStr);*/
//
//    return y;
//}
//
// unsigned long MTRand::NextNoAssert(unsigned long range)
//{
//    return NextNoAssert() % range;
//}
//
// unsigned long MTRand::Next(unsigned long range)
//{
//    return NextNoAssert( range );
//}
//
// float MTRand::NextNoAssert(float range)
//{
//    return (float) ((double)NextNoAssert() / (double)0x7FFFFFFF * range);
//}
//
// float MTRand::Next(float range)
//{
//    return NextNoAssert(range);
//}
//
// std::string MTRand::Serialize()
//{
//    std::string aString;
//
//    aString.resize(MTRAND_N*4);
//    memcpy((char*) aString.c_str(), mt, MTRAND_N*4);
//
//    return aString;
//}
