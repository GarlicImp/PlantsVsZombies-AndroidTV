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

#include "PvZ/Lawn/System/ReanimationLawn.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board/Zombie.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics/Graphics.h"
#include "PvZ/SexyAppFramework/Graphics/MemoryImage.h"
#include "PvZ/TodLib/Effect/Reanimator.h"

using namespace Sexy;

void ReanimatorCache::LoadCachedImages() {
    // 此时尚未加载AddonImages！不可在此处替换贴图们
    old_ReanimatorCache_LoadCachedImages(this);
}

void ReanimatorCache::UpdateReanimationForVariation(Reanimation *theReanim, DrawVariation theDrawVariation) {
    // 修复商店花盆不显示、修复花园花盆不显示、修复花园手套和推车预览不显示。原理就是Reanimation::Update。
    old_ReanimatorCache_UpdateReanimationForVariation(this, theReanim, theDrawVariation);
    //    Reanimation_SetAnimRate(theReanim, 0.0f);
    theReanim->Update();
    //    Reanimation_SetAnimRate(theReanim, tmp);
}

void ReanimatorCache::GetPlantImageSize(SeedType theSeedType, int &theOffsetX, int &theOffsetY, int &theWidth, int &theHeight) {
    theOffsetX = -20;
    theOffsetY = -20;
    theWidth = 120;
    theHeight = 120;

    if (theSeedType == SeedType::SEED_TALLNUT) {
        theOffsetY = -40;
        theHeight += 40;
    } else if (theSeedType == SeedType::SEED_MELONPULT || theSeedType == SeedType::SEED_WINTERMELON) {
        theOffsetX = -40;
        theWidth += 40;
    } else if (theSeedType == SeedType::SEED_COBCANNON) {
        theWidth += 80;
    }
}

void ReanimatorCache::ReanimatorCacheInitialize() {
    mApp = (LawnApp *)*Sexy_gSexyAppBase_Addr;
    for (int i = 0; i < SeedType::NUM_SEED_TYPES; i++)
        mPlantImages[i] = nullptr;
    for (int i = 0; i < LawnMowerType::NUM_MOWER_TYPES; i++)
        mLawnMowers[i] = nullptr;
    for (int i = 0; i < ZombieType::NUM_ZOMBIE_TYPES; i++)
        mZombieImages[i] = nullptr;

    for (int i = 0; i < ZombieType::NUM_NEW_ZOMBIE_TYPES - NUM_CACHED_ZOMBIE_TYPES; i++)
        gNewZombieImages[i] = nullptr;
}

void ReanimatorCache::ReanimatorCacheDispose() {
    for (int i = 0; i < SeedType::NUM_SEED_TYPES; i++)
        delete mPlantImages[i];
    while (mImageVariationList.mSize != 0) {
        ReanimCacheImageVariation aImageVariation = mImageVariationList.RemoveHead();
        if (aImageVariation.mImage != nullptr)
            delete aImageVariation.mImage;
    }
    for (int i = 0; i < LawnMowerType::NUM_MOWER_TYPES; i++)
        delete mLawnMowers[i];
    for (int i = 0; i < ZombieType::NUM_ZOMBIE_TYPES; i++)
        delete mZombieImages[i];

    for (int i = 0; i < ZombieType::NUM_NEW_ZOMBIE_TYPES - NUM_CACHED_ZOMBIE_TYPES; i++)
        delete gNewZombieImages[i];
}

void ReanimatorCache::DrawCachedPlant(Graphics *graphics, float thePosX, float thePosY, SeedType theSeedType, DrawVariation theDrawVariation) {
    if (theDrawVariation == DrawVariation::VARIATION_IMITATER_LESS || theDrawVariation == DrawVariation::VARIATION_IMITATER || theDrawVariation == DrawVariation::VARIATION_NORMAL) {
        Image *image = (Image *)mPlantImages[theSeedType];
        if (image == nullptr) {
            return;
        }
        if (theDrawVariation == DrawVariation::VARIATION_IMITATER) {
            image = FilterEffectGetImage(image, FilterEffect::FILTEREFFECT_WASHED_OUT);
        } else if (theDrawVariation == DrawVariation::VARIATION_IMITATER_LESS) {
            image = FilterEffectGetImage(image, FilterEffect::FILTEREFFECT_LESS_WASHED_OUT);
        }
        int a, b, c, d;
        GetPlantImageSize(theSeedType, a, b, c, d);
        float xScaled = graphics->mScaleX;
        float yScaled = graphics->mScaleY;
        // 修复关闭3D加速后SeedPacket上不显示植物
        //        if (Sexy_SexyAppBase_Is3DAccelerated(a1->mApp)) {
        TodDrawImageScaledF(graphics, image, thePosX + xScaled * a, thePosY + yScaled * b, xScaled, yScaled);
        //        } else {
        //            if (xScaled == 1.0 && yScaled == 1.0) {
        //                DrawImage(graphics, image, thePosX + a, thePosY + b);
        //                return;
        //            }
        //        }
    } else {
        return old_ReanimatorCache_DrawCachedPlant(this, graphics, thePosX, thePosY, theSeedType, theDrawVariation);
    }
}

void ReanimatorCache::DrawCachedZombie(Graphics *g, float thePosX, float thePosY, ZombieType theZombieType) {
    if (theZombieType < NUM_CACHED_ZOMBIE_TYPES) {
        if (mZombieImages[(int)theZombieType] == nullptr)
            mZombieImages[(int)theZombieType] = MakeCachedZombieFrame(theZombieType);
        TodDrawImageScaledF(g, (Image *)mZombieImages[(int)theZombieType], thePosX, thePosY, g->mScaleX, g->mScaleY);
    } else {
        if (gNewZombieImages[(int)theZombieType - NUM_CACHED_ZOMBIE_TYPES - 1] == nullptr)
            gNewZombieImages[(int)theZombieType - NUM_CACHED_ZOMBIE_TYPES - 1] = MakeCachedZombieFrame(theZombieType);
        TodDrawImageScaledF(g, (Image *)gNewZombieImages[(int)theZombieType - NUM_CACHED_ZOMBIE_TYPES - 1], thePosX, thePosY, g->mScaleX, g->mScaleY);
    }
}

MemoryImage*ReanimatorCache::MakeBlankMemoryImage(int theWidth, int theHeight) {
    MemoryImage *aImage = new MemoryImage();

    int aBitsCount = theWidth * theHeight;
    aImage->mBits = new unsigned long[aBitsCount + 1];
    aImage->mWidth = theWidth;
    aImage->mHeight = theHeight;
    aImage->mHasTrans = true;
    aImage->mHasAlpha = true;
    memset(aImage->mBits, 0, aBitsCount * 4);
    aImage->mBits[aBitsCount] = Sexy::MEMORYCHECK_ID;
    return aImage;
}

// 为红眼巨人增加SeedPacket图标
Sexy::MemoryImage *ReanimatorCache::MakeCachedZombieFrame(ZombieType theZombieType) {
    if (theZombieType > ZombieType::NUM_CACHED_ZOMBIE_TYPES) {
    int maxWidth = 200;
    int maxHeight = 210;

//    MemoryImage *aMemoryImage = MakeBlankMemoryImage(maxWidth, maxHeight);
    MemoryImage *aMemoryImage = MakeBlankCanvasImage(maxWidth, maxHeight);
    Graphics aMemoryGraphics((Image *)aMemoryImage);
    aMemoryGraphics.SetLinearBlend(true);

    ZombieType aUseZombieType = theZombieType;
    ZombieDefinition &aZombieDef = GetZombieDefinition(aUseZombieType);

    float aPosX = 40.0f, aPosY = 40.0f;
    if (theZombieType == ZombieType::ZOMBIE_JACKSON) {
        Reanimation aReanim;
//        aReanim.OverrideScale(0.79872f, 0.79872f);
//        aPosX += 8;
//        aPosY += 32;

        aReanim.ReanimationInitializeType(aPosX, aPosY, aZombieDef.mReanimationType);
        aReanim.PlayReanim("anim_moonwalk", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
        aReanim.Update();
        aReanim.Draw(&aMemoryGraphics);
        gNewZombieImages[theZombieType - NUM_CACHED_ZOMBIE_TYPES - 1] = aMemoryImage;
    } else if (theZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
        Reanimation aReanim;
//        aReanim.OverrideScale(0.79872f, 0.79872f);
//        aPosX += 8;
//        aPosY += 32;

        aReanim.ReanimationInitializeType(aPosX, aPosY, aZombieDef.mReanimationType);
        aReanim.PlayReanim("anim_armraise", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
        aReanim.mAnimTime = 0.5f;
        aReanim.Update();
        aReanim.Draw(&aMemoryGraphics);
        gNewZombieImages[theZombieType - NUM_CACHED_ZOMBIE_TYPES - 1] = aMemoryImage;
    }
    return aMemoryImage;
}

    switch (theZombieType) {
        case ZOMBIE_REDEYE_GARGANTUAR: {
            mZombieImages[theZombieType]->~MemoryImage();
            mZombieImages[theZombieType] = nullptr;

            Sexy::MemoryImage *BlankCanvasImage = MakeBlankCanvasImage((theZombieType == ZombieType::ZOMBIE_ZAMBONI ? 512 : 256), 256);
            Graphics *graphics = new Graphics((Image *)BlankCanvasImage);
            graphics->SetLinearBlend(true);
            ZombieType zombieType_reanim = theZombieType != ZombieType::ZOMBIE_CACHED_POLEVAULTER_WITH_POLE ? theZombieType : ZombieType::ZOMBIE_POLEVAULTER;
            ReanimationType reanimationType = GetZombieDefinition(zombieType_reanim).mReanimationType;
            float x = 40;
            float y = 60;
            Reanimation reanimation;
            reanimation.ReanimationInitializeType(x, y, reanimationType);
            reanimation.SetFramesForLayer("anim_idle");
            Zombie::SetupReanimLayers(&reanimation, zombieType_reanim);
            reanimation.SetImageOverride("anim_head1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_Addr);
            reanimation.Update();
            reanimation.Draw(graphics);
            mZombieImages[theZombieType] = BlankCanvasImage;
            delete graphics;
            return BlankCanvasImage;
        }
            // TODO:植物僵尸缓存动画
            // 暂时用P的图代替
            //        case ZOMBIE_PEA_HEAD: {
            //
            //        }
        default:
            return old_ReanimatorCache_MakeCachedZombieFrame(this, theZombieType);
    }
}