//
// Created by 28636 on 2025/4/28.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_TODCOMMON_H
#define PLANTSVSZOMBIES_ANDROIDTV_TODCOMMON_H

#include <stdlib.h>
#include "PvZ/Lawn/Common/LawnCommon.h"
#include "PvZ/SexyAppFramework/Misc/Common.h"

inline void (*TodDrawImageCelF)(Sexy::Graphics *, Sexy::Image *, float, float, int, int);

inline int (*TodDrawImageCelCenterScaledF)(Sexy::Graphics *a1, Sexy::Image *a2, float a3, float a4, int a5, float a6, float a7);

inline void (*TodDrawImageScaledF)(Sexy::Graphics *g, Sexy::Image *image, float x, float y, float xScaled, float yScaled);

inline void (*TodDrawImageCelScaledF)(Sexy::Graphics *, Sexy::Image *, float, float, int, int, float, float);

inline void (*TodDrawImageCenterScaledF)(Sexy::Graphics *, Sexy::Image *, float, float, float, float);

inline void (*TodDrawString)(Sexy::Graphics *, int *, int, int, Sexy::Font *, Sexy::Color color, DrawStringJustification);

inline void (*TodScaleTransformMatrix)(int *, float, float, float, float);

inline void (*TodDrawStringMatrix)(Sexy::Graphics *, Sexy::Font *, int *, int *, Sexy::Color *);

inline int (*TodAnimateCurve)(int theTimeStart, int theTimeEnd, int theTimeAge, int thePositionStart, int thePositionEnd, TodCurves theCurve);

inline float (*TodAnimateCurveFloat)(int theTimeStart, int theTimeEnd, int theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve);

inline float (*TodAnimateCurveFloatTime)(float theTimeStart, float theTimeEnd, float theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve);

inline void (*TodDrawStringWrapped)(Sexy::Graphics *graphics, int *text, Sexy::Rect *theRect, Sexy::Font *theFont, Sexy::Color *theColor, DrawStringJustification justification, bool a7);

inline int (*TodDrawStringWrappedHelper)(Sexy::Graphics *pGraphics, int *pInt, Sexy::Rect *pRect, Sexy::Font *pFont, Sexy::Color color, DrawStringJustification justification, bool i1, bool i2);


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
