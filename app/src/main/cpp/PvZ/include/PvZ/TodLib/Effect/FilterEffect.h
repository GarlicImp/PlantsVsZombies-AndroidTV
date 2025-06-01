//
// Created by 28636 on 2025/5/27.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_FILTEREFFECT_H
#define PLANTSVSZOMBIES_ANDROIDTV_FILTEREFFECT_H

#include "PvZ/Lawn/Common/ConstEnums.h"

namespace Sexy
{
class Image;
class MemoryImage;
}

enum FilterEffect {
    FILTEREFFECT_NONE = -1,
    FILTEREFFECT_WASHED_OUT = 0,
    FILTEREFFECT_LESS_WASHED_OUT = 1,
    FILTEREFFECT_WHITE = 2,
    FILTEREFFECT_CUSTOM = 3,
    NUM_FILTEREFFECT
};

Sexy::Image *FilterEffectCreateImage(Sexy::Image *image, FilterEffect);

Sexy::Image *FilterEffectGetImage(Sexy::Image *image, FilterEffect);

FilterEffect GetFilterEffectTypeBySeedType(SeedType mSeedType);

#endif // PLANTSVSZOMBIES_ANDROIDTV_FILTEREFFECT_H
