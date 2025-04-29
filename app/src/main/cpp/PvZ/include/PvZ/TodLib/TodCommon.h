//
// Created by 28636 on 2025/4/28.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_TODCOMMON_H
#define PLANTSVSZOMBIES_ANDROIDTV_TODCOMMON_H

#include "PvZ/Enums.h"

inline void SetBit(uint& theNum, int theIdx, bool theValue = true) {
    if (theValue)
        theNum |= 1 << theIdx;
    else
        theNum &= ~(1 << theIdx);
}
inline bool TestBit(uint theNum, int theIdx) {
    return theNum & (1 << theIdx);
}

#endif // PLANTSVSZOMBIES_ANDROIDTV_TODCOMMON_H
