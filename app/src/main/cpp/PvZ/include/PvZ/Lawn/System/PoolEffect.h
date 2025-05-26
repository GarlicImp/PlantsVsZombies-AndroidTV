//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_POOLEFFECT_H
#define PLANTSVSZOMBIES_ANDROIDTV_POOLEFFECT_H

#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/SexyAppFramework/Graphics/Image.h"

constexpr const int CAUSTIC_IMAGE_WIDTH = 128;
constexpr const int CAUSTIC_IMAGE_HEIGHT = 64;

namespace Sexy
{
class MemoryImage;
class Graphics;
};

class LawnApp;
class PoolEffect {
public:
    CausticEffect *mCausticGrayscaleImage; // 0
    Sexy::Image *mCausticImage;            // 1
    LawnApp *mApp;                         // 2
    int mPoolCounter;                      // 3
}; // 大小4个整数

inline unsigned int (*PoolEffect_BilinearLookupFixedPoint)(PoolEffect *, unsigned int, unsigned int);

void PoolEffect_PoolEffectDraw(PoolEffect *poolEffect, Sexy::Graphics *graphics, bool theIsNight);

#endif // PLANTSVSZOMBIES_ANDROIDTV_POOLEFFECT_H
