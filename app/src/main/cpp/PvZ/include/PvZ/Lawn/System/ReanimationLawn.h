//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_REANIMATONLAWN_H
#define PLANTSVSZOMBIES_ANDROIDTV_REANIMATONLAWN_H

#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/TodLib/Common/TodList.h"

namespace Sexy
{
class Graphics;
class MemoryImage;
};
//using namespace Sexy;

class LawnApp;
class ReanimCacheImageVariation {
public:
    SeedType mSeedType;
    DrawVariation mDrawVariation;
    Sexy::MemoryImage *mImage;
};
typedef TodList<ReanimCacheImageVariation> ImageVariationList;

class Reanimation;
class ReanimatorCache {
public:
    ImageVariationList mImageVariationList;
    Sexy::MemoryImage *mPlantImages[SeedType::NUM_SEED_TYPES];             // 4 ~ 57
    Sexy::MemoryImage *mLawnMowers[LawnMowerType::NUM_MOWER_TYPES];        // 58 ~ 61
    Sexy::MemoryImage *mZombieImages[ZombieType::NUM_CACHED_ZOMBIE_TYPES]; // 62 ~ 97
    LawnApp *mApp;                                                         // 98
    // 大小99个整数

    void GetPlantImageSize(SeedType theSeedType, int& theOffsetX, int& theOffsetY, int& theWidth, int& theHeight);
    void UpdateReanimationForVariation(Reanimation *theReanim, DrawVariation theDrawVariation);
    void LoadCachedImages();
    Sexy::MemoryImage *MakeCachedZombieFrame(ZombieType theZombieType);
    void DrawCachedPlant(Sexy::Graphics* g, float thePosX, float thePosY, SeedType theSeedType, DrawVariation theDrawVariation);
};

inline void (*old_ReanimatorCache_LoadCachedImages)(ReanimatorCache *a1);

inline void (*old_ReanimatorCache_UpdateReanimationForVariation)(ReanimatorCache *a1, Reanimation *a, DrawVariation theDrawVariation);

inline void (*old_ReanimatorCache_DrawCachedPlant)(ReanimatorCache *a1, Sexy::Graphics *graphics, float thePosX, float thePosY, SeedType theSeedType, DrawVariation drawVariation);

inline Sexy::MemoryImage *(*old_ReanimatorCache_MakeCachedZombieFrame)(ReanimatorCache *reanimatorCache, ZombieType zombieType);

inline Sexy::MemoryImage *(*ReanimatorCache_MakeBlankCanvasImage)(ReanimatorCache *, int, int);

#endif // PLANTSVSZOMBIES_ANDROIDTV_REANIMATONLAWN_H
