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

#include "PvZ/Lawn/Board/Zombie.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board/Board.h"
#include "PvZ/Lawn/Board/Challenge.h"
#include "PvZ/Lawn/Board/GridItem.h"
#include "PvZ/Lawn/Board/Plant.h"
#include "PvZ/Lawn/Board/Projectile.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics/Graphics.h"
#include "PvZ/Symbols.h"
#include "PvZ/TodLib/Common/TodCommon.h"
#include "PvZ/TodLib/Effect/Attachment.h"
#include "PvZ/TodLib/Effect/Reanimator.h"
#include "PvZ/TodLib/Effect/TodParticle.h"

#include <string.h>

using namespace Sexy;

ZombieDefinition gZombieDefs[NUM_ZOMBIE_TYPES] = {
    {ZOMBIE_NORMAL, REANIM_ZOMBIE, 1, 1, 1, 4000, "ZOMBIE"},
    {ZOMBIE_FLAG, REANIM_ZOMBIE, 1, 1, 1, 0, "FLAG_ZOMBIE"},
    {ZOMBIE_TRAFFIC_CONE, REANIM_ZOMBIE, 2, 3, 1, 4000, "CONEHEAD_ZOMBIE"},
    {ZOMBIE_POLEVAULTER, REANIM_POLEVAULTER, 2, 6, 5, 2000, "POLE_VAULTING_ZOMBIE"},
    {ZOMBIE_PAIL, REANIM_ZOMBIE, 4, 8, 1, 3000, "BUCKETHEAD_ZOMBIE"},
    {ZOMBIE_NEWSPAPER, REANIM_ZOMBIE_NEWSPAPER, 2, 11, 1, 1000, "NEWSPAPER_ZOMBIE"},
    {ZOMBIE_DOOR, REANIM_ZOMBIE, 4, 13, 5, 3500, "SCREEN_DOOR_ZOMBIE"},
    {ZOMBIE_FOOTBALL, REANIM_ZOMBIE_FOOTBALL, 7, 16, 5, 2000, "FOOTBALL_ZOMBIE"},
    {ZOMBIE_DANCER, REANIM_DANCER, 5, 18, 5, 1000, "DANCING_ZOMBIE"},
    {ZOMBIE_BACKUP_DANCER, REANIM_BACKUP_DANCER, 1, 18, 1, 0, "BACKUP_DANCER"},
    {ZOMBIE_DUCKY_TUBE, REANIM_ZOMBIE, 1, 21, 5, 0, "DUCKY_TUBE_ZOMBIE"},
    {ZOMBIE_SNORKEL, REANIM_SNORKEL, 3, 23, 10, 2000, "SNORKEL_ZOMBIE"},
    {ZOMBIE_ZAMBONI, REANIM_ZOMBIE_ZAMBONI, 7, 26, 10, 2000, "ZOMBONI"},
    {ZOMBIE_BOBSLED, REANIM_BOBSLED, 3, 26, 10, 2000, "ZOMBIE_BOBSLED_TEAM"},
    {ZOMBIE_DOLPHIN_RIDER, REANIM_ZOMBIE_DOLPHINRIDER, 3, 28, 10, 1500, "DOLPHIN_RIDER_ZOMBIE"},
    {ZOMBIE_JACK_IN_THE_BOX, REANIM_JACKINTHEBOX, 3, 31, 10, 1000, "JACK_IN_THE_BOX_ZOMBIE"},
    {ZOMBIE_BALLOON, REANIM_BALLOON, 2, 33, 10, 2000, "BALLOON_ZOMBIE"},
    {ZOMBIE_DIGGER, REANIM_DIGGER, 4, 36, 10, 1000, "DIGGER_ZOMBIE"},
    {ZOMBIE_POGO, REANIM_POGO, 4, 38, 10, 1000, "POGO_ZOMBIE"},
    {ZOMBIE_YETI, REANIM_YETI, 4, 40, 1, 1, "ZOMBIE_YETI"},
    {ZOMBIE_BUNGEE, REANIM_BUNGEE, 3, 41, 10, 1000, "BUNGEE_ZOMBIE"},
    {ZOMBIE_LADDER, REANIM_LADDER, 4, 43, 10, 1000, "LADDER_ZOMBIE"},
    {ZOMBIE_CATAPULT, REANIM_CATAPULT, 5, 46, 10, 1500, "CATAPULT_ZOMBIE"},
    {ZOMBIE_GARGANTUAR, REANIM_GARGANTUAR, 10, 48, 15, 1500, "GARGANTUAR"},
    {ZOMBIE_IMP, REANIM_IMP, 10, 48, 1, 0, "IMP"},
    {ZOMBIE_BOSS, REANIM_BOSS, 10, 50, 1, 0, "BOSS"},
    {ZOMBIE_TRASHCAN, REANIM_ZOMBIE, 1, 99, 1, 4000, "TRASHCAN_ZOMBIE"},
    {ZOMBIE_PEA_HEAD, REANIM_ZOMBIE, 1, 99, 1, 4000, "ZOMBIE"},
    {ZOMBIE_WALLNUT_HEAD, REANIM_ZOMBIE, 4, 99, 1, 3000, "ZOMBIE"},
    {ZOMBIE_JALAPENO_HEAD, REANIM_ZOMBIE, 3, 99, 10, 1000, "ZOMBIE"},
    {ZOMBIE_GATLING_HEAD, REANIM_ZOMBIE, 3, 99, 10, 2000, "ZOMBIE"},
    {ZOMBIE_SQUASH_HEAD, REANIM_ZOMBIE, 3, 99, 10, 2000, "ZOMBIE"},
    {ZOMBIE_TALLNUT_HEAD, REANIM_ZOMBIE, 4, 99, 10, 2000, "ZOMBIE"},
    {ZOMBIE_REDEYE_GARGANTUAR, REANIM_GARGANTUAR, 10, 48, 15, 6000, "REDEYED_GARGANTUAR"},
};

ZombieDefinition gNewZombieDefs[] = {
    {ZOMBIE_SUNFLOWER_HEAD, REANIM_ZOMBIE, 1, 99, 1, 4000, "ZOMBIE"},
    {ZOMBIE_TORCHWOOD_HEAD, REANIM_ZOMBIE, 1, 99, 1, 4000, "ZOMBIE"},
    {ZOMBIE_EXPLODE_O_NUT_HEAD, REANIM_ZOMBIE, 4, 99, 1, 3000, "ZOMBIE"},
    {ZOMBIE_GIGA_FOOTBALL, REANIM_GIGA_FOOTBALL, 7, 16, 5, 2000, "FOOTBALL_ZOMBIE"},
    {ZOMBIE_SUPER_FAN_IMP, REANIM_SUPER_FAN_IMP, 10, 48, 1, 0, "IMP"},
    {ZOMBIE_JACKSON, REANIM_JACKSON, 5, 18, 5, 1000, "DANCING_ZOMBIE"},
    {ZOMBIE_BACKUP_DANCER2, REANIM_BACKUP_DANCER2, 1, 18, 1, 0, "BACKUP_DANCER"},
};

ZombieDefinition &GetZombieDefinition(ZombieType theZombieType) {
    if (theZombieType == ZOMBIE_TRASHCAN) {
        return gZombieTrashBinDef;
    }

    if (theZombieType > NUM_CACHED_ZOMBIE_TYPES) {
        return gNewZombieDefs[theZombieType - NUM_CACHED_ZOMBIE_TYPES - 1];
    } else {
        return gZombieDefs[theZombieType];
    }
}

void Zombie::ZombieInitialize(int theRow, ZombieType theType, bool theVariant, Zombie *theParentZombie, int theFromWave, bool isVisible) {
    old_Zombie_ZombieInitialize(this, theRow, theType, theVariant, theParentZombie, theFromWave, isVisible);

    mSquashHeadCol = -1;
    mIsRevived = false;

    if (zombieSetScale != 0 && mZombieType != ZombieType::ZOMBIE_BOSS) {
        mScaleZombie = 0.2 * zombieSetScale;
        UpdateAnimSpeed();
        float theRatio = mScaleZombie * mScaleZombie;
        mBodyHealth *= theRatio;
        mHelmHealth *= theRatio;
        mShieldHealth *= theRatio;
        mFlyingHealth *= theRatio;
        mBodyMaxHealth = mBodyHealth;
        mHelmMaxHealth = mHelmHealth;
        mShieldMaxHealth = mShieldHealth;
        mFlyingMaxHealth = mFlyingHealth;
    }

    if (IsZombatarZombie(theType) && theFromWave != -3) {
        SetZombatarReanim();
    }

    switch (theType) {
        case ZombieType::ZOMBIE_SUNFLOWER_HEAD: {
            LoadPlainZombieReanim();
            ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("anim_head", RENDER_GROUP_HIDDEN);

            Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
            ReanimatorTrackInstance *aTrackInstance = aBodyReanim->GetTrackInstanceByName("Zombie_body");
            Reanimation *aHeadReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_SUNFLOWER);
            aHeadReanim->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
            mSpecialHeadReanimID = mApp->ReanimationGetID(aHeadReanim);
            AttachEffect *aAttachEffect = AttachReanim(aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
            aBodyReanim->mFrameBasePose = 0;
            TodScaleRotateTransformMatrix(aAttachEffect->mOffset, 65.0f, -10.0f, 0.2f, -1.0f, 1.0f);

            aHeadReanim->AssignRenderGroupToTrack("frontleaf_left_tip", RENDER_GROUP_HIDDEN);
            aHeadReanim->AssignRenderGroupToTrack("frontleaf_right_tip", RENDER_GROUP_HIDDEN);
            aHeadReanim->AssignRenderGroupToTrack("frontleaf", RENDER_GROUP_HIDDEN);
            aHeadReanim->AssignRenderGroupToTrack("stalk_bottom", RENDER_GROUP_HIDDEN);
            aHeadReanim->AssignRenderGroupToTrack("backleaf_right_tip", RENDER_GROUP_HIDDEN);
            aHeadReanim->AssignRenderGroupToTrack("backleaf_left_tip", RENDER_GROUP_HIDDEN);
            aHeadReanim->AssignRenderGroupToTrack("backleaf", RENDER_GROUP_HIDDEN);

            mBodyHealth = 500;
            mVariant = false;
            break;
        }

        case ZombieType::ZOMBIE_TORCHWOOD_HEAD: {
            LoadPlainZombieReanim();
            ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("anim_head", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("Zombie_tie", RENDER_GROUP_HIDDEN);

            Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
            ReanimatorTrackInstance *aTrackInstance = aBodyReanim->GetTrackInstanceByName("Zombie_body");
            Reanimation *aHeadReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_TORCHWOOD);
            aHeadReanim->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
            mSpecialHeadReanimID = mApp->ReanimationGetID(aHeadReanim);
            AttachEffect *aAttachEffect = AttachReanim(aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
            aBodyReanim->mFrameBasePose = 0;
            TodScaleRotateTransformMatrix(aAttachEffect->mOffset, 65.0f, -10.0f, 0.2f, -1.0f, 0.8f);

            mBodyHealth = 500;
            mVariant = false;
            mHasObject = true; // 可点燃植物和僵尸豌豆
            break;
        }

        case ZombieType::ZOMBIE_EXPLODE_O_NUT_HEAD: {
            LoadPlainZombieReanim();
            ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("anim_head", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("Zombie_tie", RENDER_GROUP_HIDDEN);

            Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
            ReanimatorTrackInstance *aTrackInstance = aBodyReanim->GetTrackInstanceByName("Zombie_body");
            Reanimation *aHeadReanim = mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_WALLNUT);
            aHeadReanim->mColorOverride = Color(255, 64, 64);
            aHeadReanim->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
            mSpecialHeadReanimID = mApp->ReanimationGetID(aHeadReanim);
            AttachEffect *aAttachEffect = AttachReanim(aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
            aBodyReanim->mFrameBasePose = 0;
            TodScaleRotateTransformMatrix(aAttachEffect->mOffset, 50.0f, 0.0f, 0.2f, -0.8f, 0.8f);

            mHelmType = HelmType::HELMTYPE_WALLNUT;
            mHelmHealth = 1100;
            mVariant = false;
            break;
        }

        case ZombieType::ZOMBIE_JACKSON:
            if (!IsOnBoard()) {
                PlayZombieReanim("anim_moonwalk", ReanimLoopType::REANIM_LOOP, 0, 12.0f);
            } else {
                mZombiePhase = ZombiePhase::PHASE_DANCER_DANCING_IN;
                mVelX = 0.5f;
                mPhaseCounter = 300 + Rand(12);
                PlayZombieReanim("anim_moonwalk", ReanimLoopType::REANIM_LOOP, 0, 24.0f);
            }
            mBodyHealth = 500;
            mVariant = false;
            break;

        case ZombieType::ZOMBIE_BACKUP_DANCER2:
            if (!IsOnBoard()) {
                PlayZombieReanim("anim_armraise", ReanimLoopType::REANIM_LOOP, 0, 12.0f);
            }
            mZombiePhase = ZombiePhase::PHASE_DANCER_DANCING_LEFT;
            mVariant = false;
            break;

        case ZombieType::ZOMBIE_GIGA_FOOTBALL:
            mZombieRect = Rect(50, 0, 57, 115);
            ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
            mHelmType = HelmType::HELMTYPE_FOOTBALL;
            mHelmHealth = 1400;
            mAnimTicksPerFrame = 6;
            mVariant = false;
            mZombiePhase = ZombiePhase::PHASE_FOOTBALL_PRE_CHARGING;
            break;

        case ZombieType::ZOMBIE_SUPER_FAN_IMP:
            if (!IsOnBoard()) {
                PlayZombieReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 12.0f);
            }
            break;

        case ZombieType::ZOMBIE_BALLOON:
            if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
                mAltitude = 0;
                mFlyingHealth = 150;
                PickRandomSpeed();
            }
            break;

        case ZombieType::ZOMBIE_IMP:
//            if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
//                mBodyHealth = 70;
//            }
            break;

        case ZombieType::ZOMBIE_TRASHCAN:
            if (gVSBalanceAdjustment) {
                mShieldHealth = 1100; // 800 -> 1100
            }
            break;

        default:
            break;
    }
    mBodyMaxHealth = mBodyHealth;
    mHelmMaxHealth = mHelmHealth;
    mShieldMaxHealth = mShieldHealth;
    mFlyingMaxHealth = mFlyingHealth;
}

void Zombie::CheckIfPreyCaught() {
    if (mZombieType == ZombieType::ZOMBIE_BUNGEE || mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_ZAMBONI
        || mZombieType == ZombieType::ZOMBIE_CATAPULT || mZombieType == ZombieType::ZOMBIE_BOSS || IsBouncingPogo() || IsBobsledTeamWithSled()
        || mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT || mZombiePhase == ZombiePhase::PHASE_NEWSPAPER_MADDENING
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISING || mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISE_WITHOUT_AXE
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_STUNNED || mZombiePhase == ZombiePhase::PHASE_RISING_FROM_GRAVE || mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_THROWN
        || mZombiePhase == ZombiePhase::PHASE_IMP_LANDING || mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_TACKLE || mZombiePhase == ZombiePhase::PHASE_DANCER_RISING || mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS
        || mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT || mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_HOLD
        || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_WITHOUT_DOLPHIN || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_INTO_POOL
        || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_RIDING || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_IN_JUMP || mZombiePhase == ZombiePhase::PHASE_SNORKEL_INTO_POOL
        || mZombiePhase == ZombiePhase::PHASE_SNORKEL_WALKING || mZombiePhase == ZombiePhase::PHASE_LADDER_PLACING || mZombiePhase == ZombiePhase::PHASE_FOOTBALL_CHARGING || mZombiePhase == ZombiePhase::PHASE_FOOTBALL_TACKLE
        || mZombiePhase == ZombiePhase::PHASE_IMP_POPPING || mZombieHeight == ZombieHeight::HEIGHT_GETTING_BUNGEE_DROPPED || mZombieHeight == ZombieHeight::HEIGHT_UP_LADDER
        || mZombieHeight == ZombieHeight::HEIGHT_IN_TO_POOL || mZombieHeight == ZombieHeight::HEIGHT_OUT_OF_POOL || IsTangleKelpTarget() || mZombieHeight == ZombieHeight::HEIGHT_FALLING || !mHasHead
        || IsFlying())
        return;

    int aTicksBetweenEats = TICKS_BETWEEN_EATS;
    if (mChilledCounter > 0) {
        aTicksBetweenEats *= 2;
    }
    if (mZombieAge % aTicksBetweenEats != 0) {
        return;
    }

    Zombie *aZombie = FindZombieTarget();
    if (aZombie) {
        EatZombie(aZombie);
        return;
    }

    if (!mMindControlled) {
        Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
        if (aPlant) {
            EatPlant(aPlant);
            return;
        }
    }

    if (mApp->IsIZombieLevel() && mBoard->mChallenge->IZombieEatBrain(this)) {
        return;
    }

    if (mIsEating) {
        StopEating();
    }
}

bool Zombie::IsOnBoard() {
    if (mFromWave == Zombie::ZOMBIE_WAVE_CUTSCENE || mFromWave == Zombie::ZOMBIE_WAVE_UI) {
        return false;
    }

    return true;
}

void Zombie::Update() {
    if (zombieBloated) {
        // 如果开启了“普僵必噎死”
        mBloated = mZombieType == ZombieType::ZOMBIE_NORMAL && !mInPool;
    }

    if (requestPause) {
        // 如果开了高级暂停
        return;
    }

    if (mZombieType == ZombieType::ZOMBIE_FLAG && mBossFireBallReanimID != 0) {
        Reanimation *reanimation = mApp->ReanimationTryToGet(mBossFireBallReanimID);
        if (reanimation != nullptr)
            reanimation->Update();
    }

    return old_Zombie_Update(this);
}

void Zombie::UpdateActions() {
    old_Zombie_UpdateActions(this);

    // UpdateZombieType类函数在此处添加
    if (mZombieType == ZombieType::ZOMBIE_GIGA_FOOTBALL) {
        UpdateZombieGigaFootball();
    }
    if (mZombieType == ZombieType::ZOMBIE_SUPER_FAN_IMP) {
        UpdateZombieImp();
    }
    if (mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
        UpdateZombieBackupDancer();
    }
    if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
        UpdateZombieJackson();
    }
    if (mZombieType == ZombieType::ZOMBIE_SUNFLOWER_HEAD) {
        UpdateZombieSunflowerHead();
    }
    if (mZombieType == ZombieType::ZOMBIE_TORCHWOOD_HEAD) {
        UpdateZombieTorchwoodHead();
    }
}

void Zombie::DoSpecial() {
    switch (mZombieType) {
        case ZombieType::ZOMBIE_GIGA_FOOTBALL: {
            // 刷新冲锋状态
            mZombiePhase = ZombiePhase::PHASE_FOOTBALL_WALKING;
            mPhaseCounter = 10;

            Zombie *aZombieImp = mBoard->AddZombie(ZombieType::ZOMBIE_SUPER_FAN_IMP, mFromWave, false);
            if (aZombieImp == nullptr)
                return;

            aZombieImp->mPosX = mPosX - 50.0f;
            aZombieImp->mPosY = GetPosYBasedOnRow(mRow);
            aZombieImp->SetRow(mRow);
            aZombieImp->mVariant = false;
            aZombieImp->mAltitude = 44.0f;
            aZombieImp->mRenderOrder = mRenderOrder + 1;
            aZombieImp->mScaleZombie = mScaleZombie;
            aZombieImp->mBodyHealth *= mScaleZombie * mScaleZombie;
            aZombieImp->mBodyMaxHealth *= mScaleZombie * mScaleZombie;
            aZombieImp->mChilledCounter = mChilledCounter;
            aZombieImp->DoSpecial();
            break;
        }
        case ZombieType::ZOMBIE_SUPER_FAN_IMP: {
            float aTacklingDistance = mPosX - 360.0f;
            mApp->PlayFoley(FoleyType::FOLEY_SWING);

            float aMinDistancce = 40.0f;
            if (mBoard->StageHasRoof()) {
                aTacklingDistance -= 180.0f;
                aMinDistancce = -140.0f;
            }
            if (aTacklingDistance < aMinDistancce) {
                aTacklingDistance = aMinDistancce;
            } else if (aTacklingDistance > 140.0f) {
                aTacklingDistance -= RandRangeFloat(0.0f, 100.0f);
            }

            mZombiePhase = ZombiePhase::PHASE_IMP_GETTING_TACKLE;
            mVelX = 3.0f / mScaleZombie;
            mVelZ = 0.5f * (aTacklingDistance / mVelX) * 0.05f;
            PlayZombieReanim("anim_thrown", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 18.0f);
            UpdateReanim();
            mApp->PlayFoley(FoleyType::FOLEY_IMP);
            break;
        }
        case ZombieType::ZOMBIE_JACKSON: {
            mZombiePhase = ZombiePhase::PHASE_JACKSON_SNAPPING_FINGERS;
            PlayZombieReanim("anim_point", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
            //        mApp->PlayFoley(FoleyType::FOLEY_THRILLER);
            mApp->PlaySample(addonSounds.thriller); // PlayFoley仅第一次播放生效，故暂时采用PlaySample

            pvzstl::string str = StrFormat("[RAISE_DEAD]");
            mBoard->DisplayAdviceAgain(str, MessageStyle::MESSAGE_STYLE_HUGE_WAVE, AdviceType::ADVICE_HUGE_WAVE);

            SummonBackupDancers();
            RaiseDeadZombies();
            break;
        }
        case ZombieType::ZOMBIE_EXPLODE_O_NUT_HEAD: {
            mApp->PlayFoley(FoleyType::FOLEY_CHERRYBOMB);

            int aPosX = mX + mWidth / 2;
            int aPosY = mY + mHeight / 2;
            if (mMindControlled) {
                mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, JackInTheBoxZombieRadius, 1, true, 127);
            } else {
                mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, JackInTheBoxZombieRadius, 1, true, 255);
                mBoard->KillAllPlantsInRadius(aPosX, aPosY, JackInTheBoxPlantRadius);
            }

            mApp->AddTodParticle(aPosX, aPosY, Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_TOP, 0, 0), ParticleEffect::PARTICLE_POWIE);
            mBoard->ShakeBoard(3, -4);
            DieNoLoot();
            break;
        }
        default:
            break;
    }
}

void Zombie::UpdateZombieGigaFootball() {
    if (!mHasHead || IsDeadOrDying())
        return;

    if (mZombiePhase == ZombiePhase::PHASE_FOOTBALL_PRE_CHARGING) {
        mApp->PlaySample(addonSounds.whistle);
        mZombiePhase = ZombiePhase::PHASE_FOOTBALL_CHARGING;
        PickRandomSpeed();
    }

    //黄油、冻结打断冲锋
    if (mZombiePhase == ZombiePhase::PHASE_FOOTBALL_CHARGING) {
        if (mButteredCounter > 0 || mIceTrapCounter > 0) {
            mZombiePhase = ZombiePhase::PHASE_FOOTBALL_WALKING;
            mPhaseCounter = RandRangeInt(1000, 1500) / 2;
        }
    }

    float aScaleSquare = mScaleZombie * mScaleZombie;
    int aMindCtrlIndex = mMindControlled ? -1 : 1;

    if (mZombiePhase == ZombiePhase::PHASE_FOOTBALL_CHARGING) {
        Zombie *aZombie = FindZombieTarget();
        if (aZombie) {
            aZombie->TakeDamage(1500, 0U);
        }

        Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
        if (aPlant) {
            if (mBoard->GetLadderAt(aPlant->mPlantCol, aPlant->mRow)) {
                float aPlantX = mBoard->GridToPixelX(aPlant->mPlantCol, aPlant->mRow) + 40;
                if (aPlantX > mPosX && mZombieHeight == ZombieHeight::HEIGHT_ZOMBIE_NORMAL && mUseLadderCol != aPlant->mPlantCol) {
                    mZombieHeight = ZombieHeight::HEIGHT_UP_LADDER;
                    mUseLadderCol = aPlant->mPlantCol;
                }
                return;
            }

            SeedType aSeedType = aPlant->mSeedType;
            // 不撞一次性植物植物
            if (aSeedType == SEED_CHERRYBOMB || ((aSeedType == SEED_ICESHROOM || aSeedType == SEED_DOOMSHROOM) && !aPlant->mIsAsleep) ||
                aSeedType == SEED_SQUASH || aSeedType == SEED_JALAPENO || aSeedType == SEED_BLOVER)
                return;

            int aGridX = aPlant->mPlantCol;
            int aGridY = aPlant->mRow;
            Plant* aPot = mBoard->GetFlowerPotAt(aGridX, aGridY);
            Plant* aPumpkin = mBoard->GetPumpkinAt(aGridX, aGridY);
            if (aPlant->mPlantHealth < 4500) {
                if (aPot && aSeedType != SEED_FLOWERPOT) {
                    aPot->mPlantHealth -= 4500 - aPlant->mPlantHealth;
                }
                Plant *aUnderPlant = nullptr;
                while (mBoard->IteratePlants(aUnderPlant)) {
                    if (aSeedType == SeedType::SEED_PUMPKINSHELL && aUnderPlant->mRow == aGridY &&
                        aUnderPlant->mPlantCol == aGridX && !aPlant->NotOnGround()) {
                        aUnderPlant->mPlantHealth -= 4500 - aPlant->mPlantHealth;
                    }
                }
            }
            aPlant->mPlantHealth -= 4500;
        }
    } else if (mZombiePhase == ZombiePhase::PHASE_FOOTBALL_TACKLE) {
        mVelX = 0.0f;
        UpdateAnimSpeed();
        if (mPhaseCounter >= 75) {
            mPosX += aScaleSquare * aMindCtrlIndex;
            mAltitude += aScaleSquare;
        }
        if (mPhaseCounter == 75) {
            PlayZombieReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 12.0f);
        }

        if (mPhaseCounter == 0) {
            mZombiePhase = ZombiePhase::PHASE_FOOTBALL_WALKING;
            mPhaseCounter = RandRangeInt(1000, 1500);
            Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
            if (!aPlant) {
                StartWalkAnim(0);
            }
        }
    } else if (mZombiePhase == ZombiePhase::PHASE_FOOTBALL_WALKING) {
        //啃咬时冲锋不冷却
        if (mIsEating)
            mPhaseCounter++;

        if (mPhaseCounter == 0) {
            mApp->PlaySample(addonSounds.whistle);
            mZombiePhase = ZombiePhase::PHASE_FOOTBALL_CHARGING;
            PickRandomSpeed();

            Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
            if (!aPlant) {
                StartWalkAnim(0);
            }
        }
    }

    Zombie *aZombie = FindZombieTarget();
    Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
    bool doCrash = false;
    if (mZombiePhase == ZombiePhase::PHASE_FOOTBALL_CHARGING) {
        if (aZombie || aPlant) {
            doCrash = true;
            mApp->PlaySample(addonSounds.allstardbl);
            mApp->AddTodParticle(mPosX + 60, mPosY - 20, mRenderOrder + 1, ParticleEffect::PARTICLE_TALL_NUT_BLOCK);
        }
    }
    if (doCrash) {
        mZombiePhase = ZombiePhase::PHASE_FOOTBALL_TACKLE;
        mPhaseCounter = 100;

        float aOffsetX = mMindControlled ? 80 : 0;
        mApp->AddTodParticle(mPosX + aOffsetX, mPosY + 100, RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_POW);
        mBoard->ShakeBoard(-4 * aMindCtrlIndex, 1);
        mPosX -= 25 * aScaleSquare * aMindCtrlIndex;
        mAltitude -= 25 * aScaleSquare;
        PlayZombieReanim("anim_walk", ReanimLoopType::REANIM_PLAY_ONCE, 0, 0.0f); //用walk的第一帧模拟撞击动画
    }
}

void Zombie::UpdateZombieBackupDancer() {
    if (mIsEating)
        return;

    if (mZombiePhase == ZombiePhase::PHASE_DANCER_RISING) {
        mAltitude = TodAnimateCurve(150, 0, mPhaseCounter, ZOMBIE_BACKUP_DANCER_RISE_HEIGHT, 0, TodCurves::CURVE_LINEAR);

        if (mPhaseCounter != 0)
            return;

        if (IsOnHighGround()) {
            mAltitude = HIGH_GROUND_HEIGHT;
        }
    }

    ZombiePhase aDancerPhase = GetDancerPhase();
    if (aDancerPhase != mZombiePhase) {
        switch (aDancerPhase) {
            case ZombiePhase::PHASE_DANCER_DANCING_LEFT: {
                mZombiePhase = aDancerPhase;
                PlayZombieReanim("anim_walk", ReanimLoopType::REANIM_LOOP, 10, 18.0f);
                break;
            }
            case ZombiePhase::PHASE_DANCER_WALK_TO_RAISE:
                mZombiePhase = aDancerPhase;
                PlayZombieReanim("anim_armraise", ReanimLoopType::REANIM_LOOP, 10, 18.0f);
                mApp->ReanimationTryToGet(mBodyReanimID)->mAnimTime = 0.6f;
                break;
            case ZombiePhase::PHASE_DANCER_RAISE_RIGHT_1:
            case ZombiePhase::PHASE_DANCER_RAISE_LEFT_2:
                mZombiePhase = aDancerPhase;
                PlayZombieReanim("anim_armraise", ReanimLoopType::REANIM_LOOP, 10, 18.0f);
                break;
            default:
                break;
        }
    }
}

void Zombie::UpdateZombieJackson() {
    if (mBoard->mDanceMode) {
        gSetRowCount++;
    }
    if (gSetRowCount >= 750) {
        Zombie *aZombie = nullptr;
        while (mBoard->IterateZombies(aZombie)) {
            if (aZombie)
                aZombie->SetDanceRow();
        }
        gSetRowCount = 0;
    }

    if (mZombiePhase == ZombiePhase::PHASE_JACKSON_SNAPPING_FINGERS) {
        Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        if (aBodyReanim->mLoopCount > 0) {
            mIsEating = false;
            mZombiePhase = ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_HOLD;
            mPhaseCounter = 200;
        }
        return;
    }

    if (mIsEating)
        return;

    if (mSummonCounter > 0) {
        mSummonCounter--;
        if (mSummonCounter == 0) {
            if (GetDancerFrame() == 12 && mHasHead && mPosX < 700.0f) {
                mZombiePhase = ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT;
                PlayZombieReanim("anim_point", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
            } else {
                mSummonCounter = 1;
            }
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_DANCER_DANCING_IN) {
        if (mHasHead && mPhaseCounter == 0) {
            mZombiePhase = ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS;
            PlayZombieReanim("anim_point", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
            PickRandomSpeed();
        }
    } else if (mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS || mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT) {
        Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        if (aBodyReanim->mLoopCount > 0) {
            if (mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS && mBoard->CountZombiesOnScreen() <= 15) {
                mApp->PlayFoley(FoleyType::FOLEY_DANCER);
            }

            SummonBackupDancers();
            mBoard->SetDanceMode(true);
            mZombiePhase = ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_HOLD;
            mPhaseCounter = 200;
        }
    } else {
        if (mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_HOLD) {
            if (mPhaseCounter != 0)
                return;

            PlayZombieReanim("anim_walk", ReanimLoopType::REANIM_LOOP, 20, 18.0f);
            mZombiePhase = ZombiePhase::PHASE_DANCER_DANCING_LEFT;
            UpdateAnimSpeed();

            for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
                Zombie *aDancer = mBoard->ZombieTryToGet(mFollowerZombieID[i]);

                if (aDancer && !aDancer->IsDeadOrDying() && !aDancer->IsImmobilizied() && !aDancer->mIsEating) {
                    aDancer->PlayZombieReanim("anim_walk", ReanimLoopType::REANIM_LOOP, 20, 18.0f);
                    aDancer->mZombiePhase = ZombiePhase::PHASE_DANCER_DANCING_LEFT;
                    UpdateAnimSpeed();
                }
            }
        }

        ZombiePhase aDancerPhase = GetDancerPhase();
        if (aDancerPhase != mZombiePhase) {
            switch (aDancerPhase) {
                case ZombiePhase::PHASE_DANCER_DANCING_LEFT: {
                    mZombiePhase = aDancerPhase;
                    PlayZombieReanim("anim_walk", ReanimLoopType::REANIM_LOOP, 10, 18.0f);
                    break;
                }
                case ZombiePhase::PHASE_DANCER_WALK_TO_RAISE:
                    mZombiePhase = aDancerPhase;
                    PlayZombieReanim("anim_armraise", ReanimLoopType::REANIM_LOOP, 10, 18.0f);
                    mApp->ReanimationTryToGet(mBodyReanimID)->mAnimTime = 0.6f;
                    break;

                case ZombiePhase::PHASE_DANCER_RAISE_RIGHT_1:
                case ZombiePhase::PHASE_DANCER_RAISE_LEFT_2:
                    mZombiePhase = aDancerPhase;
                    PlayZombieReanim("anim_armraise", ReanimLoopType::REANIM_LOOP, 10, 18.0f);
                    break;
                default:
                    break;
            }
        }

        if (mHasHead && mSummonCounter == 0 && NeedsMoreBackupDancers()) {
            mSummonCounter = 100;
        }
    }
}

void Zombie::LandFlyer(unsigned int theDamageFlags) {
    if (!TestBit(theDamageFlags, (int)DamageFlags::DAMAGE_DOESNT_LEAVE_BODY) && mZombiePhase == ZombiePhase::PHASE_BALLOON_FLYING) {
        mApp->PlaySample(*SOUND_BALLOON_POP);
        mZombiePhase = ZombiePhase::PHASE_BALLOON_POPPING;
        PlayZombieReanim("anim_pop", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
    }

    if (mBoard->mPlantRow[mRow] == PlantRowType::PLANTROW_POOL) {
        DieWithLoot();
    } else {
        mZombieHeight = ZombieHeight::HEIGHT_FALLING;
    }
}

void Zombie::UpdateZombieFlyer() {
    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HIGH_GRAVITY && mPosX < 720.0f) {
        mAltitude -= 0.1f;
        if (mAltitude < -35.0f) {
            LandFlyer(0U);
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_BALLOON_POPPING) {
        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->mLoopCount > 0) {
            mZombiePhase = ZombiePhase::PHASE_BALLOON_WALKING;
            StartWalkAnim(0);
        }
    }

    if (mApp->IsIZombieLevel() && mZombiePhase == ZombiePhase::PHASE_BALLOON_FLYING && mBoard->mChallenge->IZombieGetBrainTarget(this)) {
        LandFlyer(0U);
    }

    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
        float aMaxAltitude = 50.0f;
        if (mZombiePhase == ZombiePhase::PHASE_BALLOON_FLYING) {
            Plant* aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
            if (aPlant) {
                if (aPlant->mSeedType == SeedType::SEED_TALLNUT) {
                    LandFlyer(0U);
                    return;
                }
                if (mAltitude < aMaxAltitude) {
                    if (mAltitude == 0) {
                        mApp->PlayFoley(FoleyType::FOLEY_BALLOONINFLATE);
                    }
                    mAltitude++;
                    mVelX = 0;
                    UpdateAnimSpeed();
                } else {
                    mPhaseCounter = 50;
                    PickRandomSpeed();
                }
            } else {
                if (mPhaseCounter <= 0 && mAltitude > 0) {
                    mAltitude--;
                }
            }

            if (mAltitude > aMaxAltitude / 2) {
                mHasObject = true;
            } else {
                mHasObject = false;
            }
        }
    }
}

void Zombie::UpdateYeti() {
    if (mMindControlled || !mHasHead || IsDeadOrDying())
        return;

    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) { // 修复对战雪人露头就逃跑
        if (mZombiePhase == PHASE_YETI_PRE_RUN) {
            mPhaseCounter = RandRangeInt(1500, 2000);
            mHasObject = true;
            mZombiePhase = PHASE_ZOMBIE_NORMAL;
            return;
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_NORMAL && mPhaseCounter == 0) {
        mZombiePhase = ZombiePhase::PHASE_YETI_RUNNING;
        mHasObject = false;
        PickRandomSpeed();
    }
}

void Zombie::UpdateZombieImp() {
    if (mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_THROWN || mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_TACKLE) {
        mVelZ -= THOWN_ZOMBIE_GRAVITY;
        mAltitude += mVelZ;
        mPosX -= mVelX;

        float aDiffY = GetPosYBasedOnRow(mRow) - mPosY;
        mPosY += aDiffY;
        mAltitude += aDiffY;
        if (mAltitude <= 0.0f) {
            mAltitude = 0.0f;
            mZombiePhase = ZombiePhase::PHASE_IMP_LANDING;
            PlayZombieReanim("anim_land", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
        }
    } else if (mZombiePhase == ZombiePhase::PHASE_IMP_LANDING) {
        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->mLoopCount > 0) {
            mZombiePhase = ZombiePhase::PHASE_ZOMBIE_NORMAL;
            StartWalkAnim(0);
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_IMP_PRE_RUN) {
        mZombiePhase = PHASE_IMP_RUNNING;
        PickRandomSpeed();
    }

    if (mZombieType == ZombieType::ZOMBIE_SUPER_FAN_IMP) {
        UpdateImpGettingTackle();

        Zombie *aZombie = FindZombieGigaFootball();
        if (aZombie) {
            DoSpecial();
        }

        Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);

        if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_NORMAL) {
            if ((aPlant && mX < 240) || mX < 40) {
                mPhaseCounter = 110;
                mZombiePhase = ZombiePhase::PHASE_IMP_POPPING;
            }
        }

        if (mZombiePhase == ZombiePhase::PHASE_IMP_POPPING) {
            if (mPhaseCounter == 80) {
                PlayZombieReanim("anim_thrown", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
            }
            
            if (mPhaseCounter <= 0) {
                mApp->PlayFoley(FoleyType::FOLEY_EXPLOSION);

                int aPosX = mX + mWidth / 2;
                int aPosY = mY + mHeight / 2;
                if (mMindControlled) {
                    mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, SuperFanImpZombieRadius, 1, true, 127);
                } else {
                    mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, SuperFanImpZombieRadius, 1, true, 255);
                    mBoard->KillAllPlantsInRadius(aPosX, aPosY, SuperFanImpPlantRadius);
                }

                mApp->AddTodParticle(aPosX, aPosY, Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_TOP, 0, 0), ParticleEffect::PARTICLE_JACKEXPLODE);
                mBoard->ShakeBoard(4, -6);
                ApplyBurn();
            }
        }
    }
}

void Zombie::UpdateImpGettingTackle() {
    if (mZombiePhase != ZombiePhase::PHASE_IMP_GETTING_TACKLE)
        return;

    if (!mHasHead || IsDeadOrDying())
        return;

    if (mX < 40) {
        mZombiePhase = ZombiePhase::PHASE_IMP_LANDING;
        mZombieHeight = ZombieHeight::HEIGHT_FALLING;
    }

    Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
    if (aPlant && aPlant->mSeedType == SeedType::SEED_TALLNUT) {
        mApp->PlayFoley(FoleyType::FOLEY_BONK);
        mApp->AddTodParticle(aPlant->mX + 60, aPlant->mY - 20, mRenderOrder + 1, ParticleEffect::PARTICLE_TALL_NUT_BLOCK);

        mZombiePhase = ZombiePhase::PHASE_IMP_LANDING;
        mZombieHeight = ZombieHeight::HEIGHT_FALLING;
        mPosX = aPlant->mX;
    }
}

void Zombie::SquishAllInSquare(int theX, int theY, ZombieAttackType theAttackType) {
    return old_Zombie_SquishAllInSquare(this, theX, theY, theAttackType);
}

void Zombie::UpdateZombieJackInTheBox() {
    if (mZombiePhase == ZombiePhase::PHASE_JACK_IN_THE_BOX_PRE_RUN) {
        int aDistance = 450 + Rand(300);
        if (Rand(20) == 0)  // 早爆的概率
        {
            aDistance /= 3;
        }
        mPhaseCounter = (int)(aDistance / mVelX) * ZOMBIE_LIMP_SPEED_FACTOR;
        mZombiePhase = ZombiePhase::PHASE_JACK_IN_THE_BOX_RUNNING;
    }

    if (mZombiePhase == ZombiePhase::PHASE_JACK_IN_THE_BOX_RUNNING) {
        if (mHasHead) {
            if ((mApp->mGameMode != GameMode::GAMEMODE_MP_VS && mPhaseCounter <= 0) || mIsEating) {
                mPhaseCounter = 110;
                mZombiePhase = ZombiePhase::PHASE_JACK_IN_THE_BOX_POPPING;

                StopZombieSound();
                mApp->PlaySample(*SOUND_BOING);
                PlayZombieReanim("anim_pop", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 28.0f);
            }
        }

    } else if (mZombiePhase == ZombiePhase::PHASE_JACK_IN_THE_BOX_POPPING) {
        if (mPhaseCounter == 80) {
            mApp->PlayFoley(FoleyType::FOLEY_JACK_SURPRISE);
        }

        if (mPhaseCounter <= 0) {
            mApp->PlayFoley(FoleyType::FOLEY_EXPLOSION);

            int aPosX = mX + mWidth / 2;
            int aPosY = mY + mHeight / 2;
            if (mMindControlled) {
                mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, JackInTheBoxZombieRadius, 1, true, 127);
            } else {
                mBoard->KillAllZombiesInRadius(mRow, aPosX, aPosY, JackInTheBoxZombieRadius, 1, true, 255);
                mBoard->KillAllPlantsInRadius(aPosX, aPosY, JackInTheBoxPlantRadius);
            }

            mApp->AddTodParticle(aPosX, aPosY, Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_TOP, 0, 0), ParticleEffect::PARTICLE_JACKEXPLODE);
            mBoard->ShakeBoard(4, -6);
            DieNoLoot();

            if (mApp->IsScaryPotterLevel()) {
                mBoard->mChallenge->ScaryPotterJackExplode(aPosX, aPosY);
            }
        }
    }
}

void Zombie::UpdateZombieGargantuar() {
    // 修复巨人不索敌敌方僵尸的BUG
    if (mZombiePhase == ZombiePhase::PHASE_GARGANTUAR_SMASHING) {
        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->ShouldTriggerTimedEvent(0.64f)) {
            Zombie *aZombie = FindZombieTarget();
            if (aZombie) {
                aZombie->TakeDamage(1500, 0U);
            }

            Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
            if (aPlant) {
                if (aPlant->mSeedType == SeedType::SEED_SPIKEROCK) {
                    TakeDamage(20, 32U);
                    aPlant->SpikeRockTakeDamage();
                    if (aPlant->mPlantHealth <= 0) {
                        SquishAllInSquare(aPlant->mPlantCol, aPlant->mRow, ZombieAttackType::ATTACKTYPE_CHEW);
                    }
                } else {
                    SquishAllInSquare(aPlant->mPlantCol, aPlant->mRow, ZombieAttackType::ATTACKTYPE_CHEW);
                }
            }

            if (mApp->IsScaryPotterLevel()) {
                int aGridX = mBoard->PixelToGridX(mPosX, mPosY);
                GridItem *aScaryPot = mBoard->GetScaryPotAt(aGridX, mRow);
                if (aScaryPot) {
                    mBoard->mChallenge->ScaryPotterOpenPot(aScaryPot);
                }
            }

            if (mApp->IsIZombieLevel()) {
                GridItem *aBrain = mBoard->mChallenge->IZombieGetBrainTarget(this);
                if (aBrain) {
                    mBoard->mChallenge->IZombieSquishBrain(aBrain);
                }
            }

            mApp->PlayFoley(FoleyType::FOLEY_THUMP);
            mBoard->ShakeBoard(0, 3);
        }

        if (aBodyReanim->mLoopCount > 0) {
            mZombiePhase = ZombiePhase::PHASE_ZOMBIE_NORMAL;
            StartWalkAnim(20);
        }

        return;
    }

    float aThrowingDistance = mPosX - 360.0f;
    if (mZombiePhase == ZombiePhase::PHASE_GARGANTUAR_THROWING) {
        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (aBodyReanim->ShouldTriggerTimedEvent(0.74f)) {
            mHasObject = false;
            ReanimShowPrefix("Zombie_imp", RENDER_GROUP_HIDDEN);
            ReanimShowTrack("Zombie_gargantuar_whiterope", RENDER_GROUP_HIDDEN);
            mApp->PlayFoley(FoleyType::FOLEY_SWING);

            Zombie *aZombieImp = mBoard->AddZombie(ZombieType::ZOMBIE_IMP, mFromWave, false);
            if (aZombieImp == nullptr)
                return;

            float aMinThrowDistance = 40.0f;
            if (mBoard->StageHasRoof()) {
                aThrowingDistance -= 180.0f;
                aMinThrowDistance = -140.0f;
            }
            if (aThrowingDistance < aMinThrowDistance) {
                aThrowingDistance = aMinThrowDistance;
            } else if (aThrowingDistance > 140.0f) {
                aThrowingDistance -= RandRangeFloat(0.0f, 100.0f);
            }

            aZombieImp->mPosX = mPosX - 133.0f;
            aZombieImp->mPosY = GetPosYBasedOnRow(mRow);
            aZombieImp->SetRow(mRow);
            aZombieImp->mVariant = false;
            aZombieImp->mAltitude = 88.0f;
            aZombieImp->mRenderOrder = mRenderOrder + 1;
            aZombieImp->mZombiePhase = ZombiePhase::PHASE_IMP_GETTING_THROWN;
            // 修复魅惑巨人不投掷魅惑小鬼的BUG
            aZombieImp->mScaleZombie = mScaleZombie;
            aZombieImp->mBodyHealth *= mScaleZombie * mScaleZombie;
            aZombieImp->mBodyMaxHealth *= mScaleZombie * mScaleZombie;

            if (mMindControlled) {
                aZombieImp->mPosX = mPosX + mWidth;
                aZombieImp->StartMindControlled();
                aZombieImp->mVelX = -3.0f;
            } else {
                aZombieImp->mVelX = 3.0f;
            }
            aZombieImp->mChilledCounter = mChilledCounter;
            aZombieImp->mVelZ = 0.5f * (aThrowingDistance / aZombieImp->mVelX) * THOWN_ZOMBIE_GRAVITY;
            aZombieImp->PlayZombieReanim("anim_thrown", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 18.0f);
            aZombieImp->UpdateReanim();
            mApp->PlayFoley(FoleyType::FOLEY_IMP);
        }

        if (aBodyReanim->mLoopCount > 0) {
            mZombiePhase = ZombiePhase::PHASE_ZOMBIE_NORMAL;
            StartWalkAnim(20);
        }

        return;
    }

    if (IsImmobilizied() || !mHasHead)
        return;

    if (mHasObject && mBodyHealth < mBodyMaxHealth / 2 && aThrowingDistance > 40.0f) {
        mZombiePhase = ZombiePhase::PHASE_GARGANTUAR_THROWING;
        PlayZombieReanim("anim_throw", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
        return;
    }

    bool doSmash = false;
    if (FindZombieTarget() || FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW)) {
        doSmash = true;
    } else if (mApp->IsScaryPotterLevel()) {
        int aGridX = mBoard->PixelToGridX(mPosX, mPosY);
        if (mBoard->GetScaryPotAt(aGridX, mRow)) {
            doSmash = true;
        }
    } else if (mApp->IsIZombieLevel()) {
        if (mBoard->mChallenge->IZombieGetBrainTarget(this)) {
            doSmash = true;
        }
    }

    if (doSmash) {
        mZombiePhase = ZombiePhase::PHASE_GARGANTUAR_SMASHING;
        mApp->PlayFoley(FoleyType::FOLEY_LOW_GROAN);
        PlayZombieReanim("anim_smash", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 16.0f);
    }
}

void Zombie::UpdateZombiePeaHead() {
    // 用于修复豌豆僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG、啃食时不发射子弹的BUG
    // 游戏原版逻辑是判断是否hasHead 且 是否isEating。这里去除对吃植物的判断

    if (!mHasHead)
        return;

    if (mPhaseCounter == 35) {
        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        aHeadReanim->PlayReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 35.0f);
    } else if (mPhaseCounter <= 0) {
        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        aHeadReanim->PlayReanim("anim_head_idle", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 15.0f);
        mApp->PlayFoley(FoleyType::FOLEY_THROW);

        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        int index = aBodyReanim->FindTrackIndexById(*ReanimTrackId_anim_head1_Addr);
        ReanimatorTransform aTransForm = ReanimatorTransform();
        aBodyReanim->GetCurrentTransform(index, &aTransForm);

        float aOriginX = mPosX + aTransForm.mTransX - 9.0f;
        float aOriginY = mPosY + aTransForm.mTransY + 6.0f - mAltitude;

        if (mMindControlled) // 魅惑修复
        {
            aOriginX += 90.0f * mScaleZombie;
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_PEA);
            aProjectile->mDamageRangeFlags = 1;
        } else {
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_ZOMBIE_PEA);
            aProjectile->mMotionType = ProjectileMotion::MOTION_BACKWARDS;
        }

        mPhaseCounter = 150;
    }
}

void Zombie::UpdateZombieGatlingHead() {
    // 用于修复加特林僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG、啃食时不发射子弹的BUG
    // 游戏原版逻辑是判断是否hasHead 且 是否isEating。这里去除对吃植物的判断

    if (!mHasHead)
        return;

    if (mPhaseCounter == 100) {
        Reanimation *mSpecialHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        mSpecialHeadReanim->PlayReanim("anim_shooting", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 35.0f);
    } else if (mPhaseCounter == 18 || mPhaseCounter == 35 || mPhaseCounter == 51 || mPhaseCounter == 68) {
        mApp->PlayFoley(FoleyType::FOLEY_THROW);

        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        int aTrackIndex = aBodyReanim->FindTrackIndexById(*ReanimTrackId_anim_head1_Addr);
        ReanimatorTransform aTransForm = ReanimatorTransform();
        aBodyReanim->GetCurrentTransform(aTrackIndex, &aTransForm);

        float aOriginX = mPosX + aTransForm.mTransX - 9.0f;
        float aOriginY = mPosY + aTransForm.mTransY + 6.0f - mAltitude;

        if (mMindControlled) // 魅惑修复
        {
            aOriginX += 90.0f * mScaleZombie;
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_PEA);
            aProjectile->mDamageRangeFlags = 1;
        } else {
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_ZOMBIE_PEA);
            aProjectile->mMotionType = ProjectileMotion::MOTION_BACKWARDS;
        }
    } else if (mPhaseCounter <= 0) {
        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        aHeadReanim->PlayReanim("anim_head_idle", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 15.0f);
        mPhaseCounter = 150;
    }
}

void Zombie::BossDestroyIceballInRow(int theRow) {
    if (theRow != mFireballRow)
        return;

    Reanimation *aFireBallReanim = mApp->ReanimationTryToGet(mBossFireBallReanimID);
    if (aFireBallReanim && !mIsFireBall) {
        mApp->AddTodParticle(mPosX + 80.0, mAnimCounter + 80.0, 400000, ParticleEffect::PARTICLE_ICEBALL_DEATH);

        aFireBallReanim->ReanimationDie();
        mBossFireBallReanimID = ReanimationID::REANIMATIONID_NULL;
        mBoard->RemoveParticleByType(ParticleEffect::PARTICLE_ICEBALL_TRAIL);
    }
}

void Zombie::BurnRow(int theRow) {
    // 辣椒僵尸被魅惑后的爆炸函数

    Zombie *aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie)) {
        if ((aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mRow == theRow) && aZombie->EffectedByDamage(127)) {
            aZombie->RemoveColdEffects();
            aZombie->ApplyBurn();
        }
    }

    GridItem *aGridItem = nullptr;
    while (mBoard->IterateGridItems(aGridItem)) {
        if (aGridItem->mGridY == theRow && aGridItem->mGridItemType == GridItemType::GRIDITEM_LADDER) {
            aGridItem->GridItemDie();
        }
    }

    Zombie *aBossZombie = mBoard->GetBossZombie();
    if (aBossZombie && aBossZombie->mFireballRow == theRow) {
        aBossZombie->BossDestroyIceballInRow(theRow);
    }
}

void Zombie::UpdateZombieJalapenoHead() {
    // 修复辣椒僵尸被魅惑后爆炸依然伤害植物的BUG

    if (!mHasHead)
        return;

    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) { // 修复对战辣椒瞬爆
        if (mZombiePhase == PHASE_ZOMBIE_NORMAL) {
            int aDistance = 275 + Rand(175);
            mPhaseCounter = (int)(aDistance / mVelX) * ZOMBIE_LIMP_SPEED_FACTOR;
            mZombiePhase = PHASE_JALAPENO_PRE_BURN;
            return;
        }
    }

    if (mPhaseCounter == 0) {
        mApp->PlayFoley(FoleyType::FOLEY_JALAPENO_IGNITE);
        mApp->PlayFoley(FoleyType::FOLEY_JUICY);
        mBoard->DoFwoosh(mRow);
        mBoard->ShakeBoard(3, -4);

        if (mMindControlled) // 魅惑修复
        {
            BurnRow(mRow);
        } else {
            Plant *aPlant = nullptr;
            while (mBoard->IteratePlants(aPlant)) {
//                Rect aPlantRect = aPlant->GetPlantRect(); // 原版代码遗留，但该变量并未被使用，故注释
                if (aPlant->mRow == mRow && !aPlant->NotOnGround()) {
                    mBoard->mPlantsEaten++;
                    aPlant->Die();
                }
            }
        }
        DieNoLoot();
    }
}

void Zombie::UpdateZombieSquashHead() {
    if (mHasHead && mIsEating && mZombiePhase == ZombiePhase::PHASE_SQUASH_PRE_LAUNCH) {
        StopEating();
        PlayZombieReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 20, 12.0f);
        mHasHead = false;

        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        aHeadReanim->PlayReanim("anim_jumpup", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
        aHeadReanim->mRenderOrder = mRenderOrder + 1;
        aHeadReanim->SetPosition(mPosX + 6.0f, mPosY - 21.0f);

        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        ReanimatorTrackInstance *aTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
        AttachmentDetach(aTrackInstance->mAttachmentID);
        aHeadReanim->OverrideScale(0.75f, 0.75f);
        aHeadReanim->mOverlayMatrix.m10 = 0.0f;

        mZombiePhase = ZombiePhase::PHASE_SQUASH_RISING;
        mPhaseCounter = 95;
    }

    if (mZombiePhase == ZombiePhase::PHASE_SQUASH_RISING) {
        int aDestX = mBoard->GridToPixelX(mBoard->PixelToGridXKeepOnBoard(mX, mY), mRow);

        if (mMindControlled) {
            Zombie *aZombie = FindZombieTarget();
            if (aZombie) {
                aDestX = aZombie->ZombieTargetLeadX(0.0f);
            } else {
                aDestX += 90.0f * mScaleZombie;
            }
        }

        if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
            if (mSquashHeadCol == -1) { // 空压修复
                Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
                if (aPlant) {
                    mSquashHeadCol = aPlant->mPlantCol;
                }
                aDestX = mBoard->GridToPixelX(mSquashHeadCol, mRow);
            } else {
                aDestX = mBoard->GridToPixelX(mSquashHeadCol, mRow);
            }
        }

        int aPosX = TodAnimateCurve(50, 20, mPhaseCounter, 0, aDestX - mPosX, TodCurves::CURVE_EASE_IN_OUT);
        int aPosY = TodAnimateCurve(50, 20, mPhaseCounter, 0, -20, TodCurves::CURVE_EASE_IN_OUT);

        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        aHeadReanim->SetPosition(mPosX + aPosX + 6.0f, mPosY + aPosY - 21.0f);

        if (mPhaseCounter == 0) {
            aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
            aHeadReanim->PlayReanim("anim_jumpdown", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 60.0f);
            mZombiePhase = ZombiePhase::PHASE_SQUASH_FALLING;
            mPhaseCounter = 10;
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_SQUASH_FALLING) {
        int aPosY = TodAnimateCurve(10, 0, mPhaseCounter, -20, 74, TodCurves::CURVE_LINEAR);
        int aDestX = mBoard->GridToPixelX(mBoard->PixelToGridXKeepOnBoard(mX, mY), mRow);

        if (mMindControlled) {
            Zombie *aZombie = FindZombieTarget();
            if (aZombie) {
                aDestX = aZombie->ZombieTargetLeadX(0.0f);
            } else {
                aDestX += 90.0f * mScaleZombie;
            }
        }

        if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
            if (mSquashHeadCol != -1) {
                aDestX = mBoard->GridToPixelX(mSquashHeadCol, mRow);
            }
        }

        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        aHeadReanim->SetPosition(mPosX + 6.0f + aDestX - mPosX, mPosY - 21.0f + aPosY);

        float aSquashX = mX;
        if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
            aSquashX = mPosX + 6.0f + aDestX - mPosX;
        }

        if (mPhaseCounter == 2) {
            if (mMindControlled) // 魅惑修复
            {
                Rect aAttackRect(aDestX - 73, mPosY + 4, 65, 90); // 具体数值未实测，待定

                Zombie *aZombie = nullptr;
                while (mBoard->IterateZombies(aZombie)) {
                    if ((aZombie->mRow == mRow || aZombie->mZombieType == ZombieType::ZOMBIE_BOSS) && aZombie->EffectedByDamage(13U)) {
                        Rect aZombieRect = aZombie->GetZombieRect();
                        if (GetRectOverlap(aAttackRect, aZombieRect) > (aZombie->mZombieType == ZombieType::ZOMBIE_FOOTBALL ? -20 : 0)) {
                            aZombie->TakeDamage(1800, 18U);
                        }
                    }
                }
            } else {
                SquishAllInSquare(mBoard->PixelToGridXKeepOnBoard(aSquashX, mY), mRow, ZombieAttackType::ATTACKTYPE_CHEW);
            }
        }

        if (mPhaseCounter == 0) {
            mZombiePhase = ZombiePhase::PHASE_SQUASH_DONE_FALLING;
            mPhaseCounter = 100;

            mBoard->ShakeBoard(1, 4);
            mApp->PlayFoley(FoleyType::FOLEY_THUMP);
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_SQUASH_DONE_FALLING && mPhaseCounter == 0) {
        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        aHeadReanim->ReanimationDie();
        mSpecialHeadReanimID = ReanimationID::REANIMATIONID_NULL;

        TakeDamage(1800, 9U);
    }
}

void Zombie::UpdateZombieSunflowerHead() {
    if (!mHasHead)
        return;

    if (mZombiePhase != ZombiePhase::PHASE_SUNFLOWER_HEAD_SPAWNING) {
        if (mPhaseCounter <= 0) {
            mZombiePhase = ZombiePhase::PHASE_SUNFLOWER_HEAD_SPAWNING;
            mPhaseCounter = RandRangeInt(ProductorZombieLaunchRate / 2 - 150, ProductorZombieLaunchRate / 2);
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_SUNFLOWER_HEAD_SPAWNING) {
        if (mMindControlled) {
            return;
        }

        if (mPhaseCounter <= 100) {
            int aFlashCountdown = TodAnimateCurve(100, 0, mPhaseCounter, 0, 100, TodCurves::CURVE_LINEAR);
            mJustGotShotCounter = std::max(mJustGotShotCounter, aFlashCountdown);
        }
        if (mPhaseCounter <= 0) {
            mPhaseCounter = RandRangeInt(ProductorZombieLaunchRate -150, ProductorZombieLaunchRate);
            mApp->PlayFoley(FoleyType::FOLEY_SPAWN_SUN);

            mBoard->AddCoin(mX, mY, CoinType::COIN_SUN, CoinMotion::COIN_MOTION_FROM_FROM_GRAVE);
        }
    }
}

void Zombie::UpdateZombieTorchwoodHead() {
    if (!mHasHead)
        return;

    Reanimation *aHeadReanim = mApp->ReanimationTryToGet(mSpecialHeadReanimID);

    if (mChilledCounter > 0 || mIceTrapCounter > 0) { // 受到寒冰效果火炬熄灭
        mHasObject = false;
    }

    if (mHasObject) {
        if (aHeadReanim)
            aHeadReanim->AssignRenderGroupToTrack("Torchwood_fire1", RENDER_GROUP_NORMAL);

        Rect aAttackRect = GetZombieAttackRect();
        Projectile *aProjectile = nullptr;
        while (mBoard->IterateProjectiles(aProjectile)) {
            if (aProjectile->mRow == mRow) {
                Rect aProjectileRect = aProjectile->GetProjectileRect();
                if (GetRectOverlap(aAttackRect, aProjectileRect) >= 10) {
                    if (mMindControlled) {
                        int aGridX = mBoard->PixelToGridX(mX, mY);
                        if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_PEA) {
                            aProjectile->ConvertToFireball(aGridX);
                        } else if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_SNOWPEA) {
                            aProjectile->ConvertToPea(aGridX);
                        }
                    } else {
                        if (aProjectile->mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA) {
                            aProjectile->ConvertToZombieFireball();
                        }
                    }
                }
            }
        }

        Plant *aPlant = FindPlantTarget(ZombieAttackType::ATTACKTYPE_CHEW);
        if (aPlant) {
            SeedType aSeedType = aPlant->mSeedType;
            if (aSeedType == SEED_CHERRYBOMB || (aSeedType == SEED_POTATOMINE && aPlant->mState == STATE_POTATO_ARMED)
                || ((aSeedType == SEED_ICESHROOM || aSeedType == SEED_DOOMSHROOM) && !aPlant->mIsAsleep) || aSeedType == SEED_SQUASH || aSeedType == SEED_JALAPENO || aSeedType == SEED_BLOVER)
                return;

            mApp->PlayFoley(FoleyType::FOLEY_JALAPENO_IGNITE);
            mApp->PlayFoley(FoleyType::FOLEY_JUICY);
            int aRenderOrder = mBoard->MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, mRow, 1);
            Reanimation *aOriReanim = mApp->ReanimationTryToGet(mBoard->mFwooshID[mRow][aPlant->mRow]);
            if (aOriReanim) {
                aOriReanim->ReanimationDie();
            }

            float aPosX = mBoard->GridToPixelX(aPlant->mPlantCol, aPlant->mRow) + 40.0f;
            float aPosY = mBoard->GridToPixelY(aPlant->mPlantCol, aPlant->mRow);
            Reanimation *aFwoosh = mApp->AddReanimation(aPosX, aPosY, aRenderOrder, ReanimationType::REANIM_JALAPENO_FIRE);
            aFwoosh->SetFramesForLayer("anim_flame");
            aFwoosh->mLoopType = ReanimLoopType::REANIM_LOOP_FULL_LAST_FRAME;
            aFwoosh->mAnimRate *= RandRangeFloat(0.7f, 1.3f);

            float aScale = RandRangeFloat(0.9f, 1.1f);
            float aFlip = Rand(2) ? 1.0f : -1.0f;
            aFwoosh->OverrideScale(aScale * aFlip, 1);

            mBoard->mFwooshID[mRow][aPlant->mRow] = mApp->ReanimationGetID(aFwoosh);
            mBoard->mFwooshCountDown = 100;
            aPlant->Die();
        }

        Zombie *aZombie = FindZombieTarget();
        if (aZombie) {
            aZombie->TakeDamage(10, 0U);
            if (aZombie->mBodyHealth < 10) {
                aZombie->ApplyBurn();
            }
        }
    } else {
        if (aHeadReanim)
            aHeadReanim->AssignRenderGroupToTrack("Torchwood_fire1", RENDER_GROUP_HIDDEN);
    }
}

void Zombie::UpdateZombieRiseFromGrave() {
    if (mInPool) {
        mAltitude = TodAnimateCurve(50, 0, mPhaseCounter, -150, -40, TodCurves::CURVE_LINEAR) * mScaleZombie;
    } else {
        mAltitude = TodAnimateCurve(50, 0, mPhaseCounter, -200, 0, TodCurves::CURVE_LINEAR);
    }

    if (mPhaseCounter == 0) {
        switch (mZombieType) {
            case ZOMBIE_POLEVAULTER:
                mZombiePhase = PHASE_POLEVAULTER_PRE_VAULT;
                break;
            case ZOMBIE_NEWSPAPER:
                mZombiePhase = PHASE_NEWSPAPER_READING;
                break;
            case ZOMBIE_DANCER:
                mZombiePhase = PHASE_DANCER_DANCING_IN;
                break;
            case ZOMBIE_POGO:
                mZombiePhase = PHASE_POGO_BOUNCING;
                break;
            case ZOMBIE_LADDER:
                mZombiePhase = PHASE_LADDER_CARRYING;
                break;
            // 对战模式修复
            case ZOMBIE_JACK_IN_THE_BOX:
                mZombiePhase = PHASE_JACK_IN_THE_BOX_PRE_RUN;
                break;
            case ZOMBIE_YETI:
                mZombiePhase = PHASE_YETI_PRE_RUN;
                break;
            case ZOMBIE_SQUASH_HEAD: // 修复窝瓜僵尸不起跳
                mZombiePhase = PHASE_SQUASH_PRE_LAUNCH;
                break;
            case ZOMBIE_IMP:
            case ZOMBIE_SUPER_FAN_IMP:
                mZombiePhase = PHASE_IMP_PRE_RUN;
                break;
            case ZOMBIE_GIGA_FOOTBALL:
                mZombiePhase = PHASE_FOOTBALL_PRE_CHARGING;
                break;
            default:
                mZombiePhase = PHASE_ZOMBIE_NORMAL;
                break;
        }

        if (IsOnHighGround()) {
            mAltitude = HIGH_GROUND_HEIGHT;
        }

        if (mInPool) {
            ReanimIgnoreClipRect("Zombie_duckytube", true);
            ReanimIgnoreClipRect("Zombie_whitewater", true);
            ReanimIgnoreClipRect("Zombie_outerarm_hand", true);
            ReanimIgnoreClipRect("Zombie_innerarm3", true);
        }
    }
}

void Zombie::UpdateDamageStates(unsigned int theDamageFlags) {
    if (!CanLoseBodyParts())
        return;

    if (mHasArm && mBodyHealth < 2 * mBodyMaxHealth / 3 && mBodyHealth > 0) {
        DropArm(theDamageFlags);
    }

    if (mHasHead && mBodyHealth < mBodyMaxHealth / 3) {
        DropHead(theDamageFlags);
        DropLoot();
        StopZombieSound();

        if (mBoard->HasLevelAwardDropped()) {
            PlayDeathAnim(theDamageFlags);
        }

        if (mZombiePhase == ZombiePhase::PHASE_SNORKEL_WALKING_IN_POOL) {
            DieNoLoot();
        }

        if (mZombieType == ZombieType::ZOMBIE_EXPLODE_O_NUT_HEAD) {
            DoSpecial();
        }
    }
}

void Zombie::Draw(Sexy::Graphics *g) {
    // 根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_Draw函数执行完后额外绘制血量文本。
    old_Zombie_Draw(this, g);
    int drawHeightOffset = 0;
    pvzstl::string str;
    if (showZombieBodyHealth || (showGargantuarHealth && (mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR))) { // 如果玩家开了"僵尸显血"
        str = StrFormat("%d/%d", mBodyHealth, mBodyMaxHealth);
        g->SetColor(white);
        g->SetFont(*Sexy_FONT_DWARVENTODCRAFT18_Addr);
        if (mZombieType == ZombieType::ZOMBIE_BOSS) {
            // 如果是僵王,将血量绘制到僵王头顶。从而修复图鉴中僵王血量绘制位置不正确。
            // 此处仅在图鉴中生效,实战中僵王绘制不走Zombie_Draw()，走Zombie_DrawBossPart()
            g->mTransX = 780.0f;
            g->mTransY = 240.0f;
        }
        g->DrawString(str, 0, drawHeightOffset);
        g->SetFont(nullptr);
        drawHeightOffset += 20;
    }
    if (showHelmAndShieldHealth) {
        if (mHelmHealth > 0) { // 如果有头盔，绘制头盔血量
            str = StrFormat("%d/%d", mHelmHealth, mHelmMaxHealth);
            g->SetColor(yellow);
            g->SetFont(*Sexy_FONT_DWARVENTODCRAFT18_Addr);
            g->DrawString(str, 0, drawHeightOffset);
            g->SetFont(nullptr);
            drawHeightOffset += 20;
        }
        if (mShieldHealth > 0) { // 如果有盾牌，绘制盾牌血量
            str = StrFormat("%d/%d", mShieldHealth, mShieldMaxHealth);
            g->SetColor(blue);
            g->SetFont(*Sexy_FONT_DWARVENTODCRAFT18_Addr);
            g->DrawString(str, 0, drawHeightOffset);
            g->SetFont(nullptr);
        }
    }
}

void Zombie::DrawBossPart(Sexy::Graphics *g, int theBossPart) {
    // 根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_DrawBossPart函数执行完后额外绘制血量文本。
    old_Zombie_DrawBossPart(this, g, theBossPart);
    if (theBossPart == 3) {
        // 每次绘制Boss都会调用四次本函数，且theBossPart从0到3依次增加，代表绘制Boss的不同Part。
        // 我们只在theBossPart==3时(绘制最后一个部分时)绘制一次血量，免去每次都绘制。
        if (showZombieBodyHealth) { // 如果玩家开了"僵尸显血"
            pvzstl::string str = StrFormat("%d/%d", mBodyHealth, mBodyMaxHealth);
            g->SetColor(white);
            g->SetFont(*Sexy_FONT_DWARVENTODCRAFT18_Addr);
            float tmpTransX = g->mTransX;
            float tmpTransY = g->mTransY;
            g->mTransX = 800.0f;
            g->mTransY = 200.0f;
            g->DrawString(str, 0, 0);
            g->mTransX = tmpTransX;
            g->mTransY = tmpTransY;
            g->SetFont(nullptr);
        }
    }
}

int Zombie::GetDancerFrame() {
    if (mFromWave == -3 || IsImmobilizied())
        return 0;

    // 女仆秘籍
    switch (maidCheats) {
        case 1:
            return 11; // 保持前进 (DancerDancingLeft)
        case 2:
            return 18; // 跳舞 (DancerRaiseLeft1)
        case 3:
            return 12; // 召唤舞伴 (DancerWalkToRaise)
        default:
            break;
    }

    // 修复女仆秘籍问题、修复舞王和舞者的跳舞时间不吃高级暂停也不吃倍速
    // 关键就是用mBoard.mMainCounter代替mApp.mAppCounter做计时
    int num1 = mZombiePhase == ZombiePhase::PHASE_DANCER_DANCING_IN ? 10 : 20;
    int num2 = mZombiePhase == ZombiePhase::PHASE_DANCER_DANCING_IN ? 110 : 460;
    return mBoard->mMainCounter % num2 / num1;
    // return *(uint32_t *) (lawnApp + 2368) % num2 / num1;
}

bool Zombie::IsZombotany(ZombieType theZombieType) {
    return theZombieType == ZombieType::ZOMBIE_PEA_HEAD || theZombieType == ZombieType::ZOMBIE_WALLNUT_HEAD || theZombieType == ZombieType::ZOMBIE_TALLNUT_HEAD
        || theZombieType == ZombieType::ZOMBIE_JALAPENO_HEAD || theZombieType == ZombieType::ZOMBIE_GATLING_HEAD || theZombieType == ZombieType::ZOMBIE_SQUASH_HEAD
        || theZombieType == ZombieType::ZOMBIE_SUNFLOWER_HEAD || theZombieType == ZombieType::ZOMBIE_TORCHWOOD_HEAD || theZombieType == ZombieType::ZOMBIE_EXPLODE_O_NUT_HEAD;
}

bool Zombie::ZombieTypeCanGoInPool(ZombieType theZombieType) {
    // 修复泳池对战的僵尸们走水路时不攻击植物
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_MP_VS && (VSBackGround == 3 || VSBackGround == 4 || VSBackGround == 9)) {
        return true;
    }

    return old_ZombieTypeCanGoInPool(theZombieType);
}

Rect Zombie::GetZombieRect() {
    Rect aZombieRect = mZombieRect;
    if (IsWalkingBackwards()) {
        aZombieRect.mX = mWidth - aZombieRect.mX - aZombieRect.mWidth;
    }

    ZombieDrawPosition aDrawPos;
    GetDrawPos(aDrawPos);
    aZombieRect.Offset(mX, mY + aDrawPos.mBodyY);
    if (aDrawPos.mClipHeight > CLIP_HEIGHT_LIMIT) {
        aZombieRect.mHeight -= aDrawPos.mClipHeight;
    }

    return aZombieRect;
}

void Zombie::RiseFromGrave(int theGridX, int theGridY) {
    // 修复对战切换场地为泳池后的闪退BUG。但是仅仅是修复闪退，泳池对战还谈不上能玩的程度
    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
        if (mBoard->mPlantRow[theGridY] == PlantRowType::PLANTROW_POOL) {
            //                if (old_ZombieTypeCanGoInPool(mZombieType)) {
            DieNoLoot();
            mBoard->AddZombieInRow(mZombieType, theGridY, mBoard->mCurrentWave, 1);
            return;
            //                }
        }

        BackgroundType tmp = mBoard->mBackground;
        mBoard->mBackground = BackgroundType::BACKGROUND_1_DAY;
        old_Zombie_RiseFromGrave(this, theGridX, theGridY);
        mBoard->mBackground = tmp;
        return;
    }
    old_Zombie_RiseFromGrave(this, theGridX, theGridY);
}

void Zombie::CheckForBoardEdge() {
    // 修复僵尸正常进家、支持调整僵尸进家线
    if (IsWalkingBackwards() && mPosX > 850.0f) {
        DieNoLoot();
        return;
    }
    int boardEdge;
    if (mZombieType == ZombieType::ZOMBIE_POLEVAULTER || mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR) {
        // 如果是撑杆、巨人、红眼巨人
        boardEdge = -100;
    } else if (mZombieType == ZombieType::ZOMBIE_FOOTBALL || mZombieType == ZombieType::ZOMBIE_ZAMBONI || mZombieType == ZombieType::ZOMBIE_CATAPULT) {
        // 如果是橄榄球、冰车、篮球
        boardEdge = -125;
    } else if (mZombieType == ZombieType::ZOMBIE_DANCER || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER || mZombieType == ZombieType::ZOMBIE_SNORKEL) {
        // 如果是舞王、伴舞、潜水
        boardEdge = -80;
    } else {
        // 如果是除上述僵尸外的僵尸
        boardEdge = -50;
    }
    boardEdge -= boardEdgeAdjust; // 支持任意调整进家线
    if (mX <= boardEdge && mHasHead) {
        if (mApp->IsIZombieLevel()) {
            DieNoLoot();
        } else {
            mBoard->ZombiesWon(this);
        }
    }
    if (mX <= boardEdge + 70 && !mHasHead) {
        TakeDamage(1800, 9u);
    }
}

void Zombie::SetupDoorArms(Reanimation *aReanim, bool theShow) {
    int aArmGroup = RENDER_GROUP_NORMAL;
    int aDoorGroup = RENDER_GROUP_HIDDEN;
    if (theShow) {
        aArmGroup = RENDER_GROUP_HIDDEN;
        aDoorGroup = RENDER_GROUP_NORMAL;
    }

    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_hand", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_lower", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_upper", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("anim_innerarm", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_screendoor", aDoorGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor", aDoorGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor_hand", aDoorGroup);
}

void Zombie::ShowDoorArms(bool theShow) {
    Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (aBodyReanim) {
        SetupDoorArms(aBodyReanim, theShow);
        if (!mHasArm) {
            ReanimShowPrefix("Zombie_outerarm_lower", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("Zombie_outerarm_hand", RENDER_GROUP_HIDDEN);
        }
    }
}

void Zombie::StopEating() {
    if (!mIsEating)
        return;

    mIsEating = false;
    Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);

    if (mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING)
        return;

    if (aBodyReanim && mZombieType != ZombieType::ZOMBIE_SNORKEL) {
        StartWalkAnim(20);
    }

    if (mShieldType == ShieldType::SHIELDTYPE_DOOR) {
        ShowDoorArms(true);
    }

    UpdateAnimSpeed();
}

void Zombie::EatPlant(Plant *thePlant) {
    // 修复正向出土的矿工不上梯子
    if (mZombiePhase == ZombiePhase::PHASE_DANCER_DANCING_IN) {
        mPhaseCounter = 1;
        return;
    }
    if (mYuckyFace) {
        return;
    }
    int aPlantCol = thePlant->mPlantCol;
    int aRow = thePlant->mRow;
    if (mBoard->GetLadderAt(aPlantCol, aRow) != nullptr && mZombieType == ZombieType::ZOMBIE_DIGGER && mZombiePhase == ZombiePhase::PHASE_DIGGER_WALKING_WITHOUT_AXE && !IsWalkingBackwards()) {
        StopEating();
        if (mZombieHeight == ZombieHeight::HEIGHT_ZOMBIE_NORMAL && mUseLadderCol != aPlantCol) {
            mZombieHeight = ZombieHeight::HEIGHT_UP_LADDER;
            mUseLadderCol = aPlantCol;
        }
        return;
    }
    return old_Zombie_EatPlant(this, thePlant);
}

void Zombie::DetachShield() {
    // 修复梯子僵尸断手后掉梯子时手会恢复的BUG。
    old_Zombie_DetachShield(this);
    if (mShieldType == ShieldType::SHIELDTYPE_LADDER && !mHasArm) {
        ReanimShowPrefix("Zombie_outerarm", -1);
    }
}

void Zombie::BossSpawnAttack() {
    // 修复泳池僵王为六路放僵尸时闪退
    RemoveColdEffects();
    mZombiePhase = ZombiePhase::PHASE_BOSS_SPAWNING;
    if (mBossMode == 0) {
        mSummonCounter = RandRangeInt(450, 550);
    } else if (mBossMode == 1) {
        mSummonCounter = RandRangeInt(350, 450);
    } else if (mBossMode == 2) {
        mSummonCounter = RandRangeInt(150, 250);
    }
    mTargetRow = mBoard->PickRowForNewZombie(ZombieType::ZOMBIE_NORMAL);
    switch (mTargetRow) {
        case 0:
            PlayZombieReanim("anim_spawn_1", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0);
            break;
        case 1:
            PlayZombieReanim("anim_spawn_2", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0);
            break;
        case 2:
            PlayZombieReanim("anim_spawn_3", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0);
            break;
        case 3:
            PlayZombieReanim("anim_spawn_4", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0);
            break;
        default:
            PlayZombieReanim("anim_spawn_5", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 12.0);
            break;
    }

    mApp->PlayFoley(FoleyType::FOLEY_HYDRAULIC_SHORT);
}

bool Zombie::IsBouncingPogo() {
    return mZombiePhase >= ZombiePhase::PHASE_POGO_BOUNCING && mZombiePhase <= ZombiePhase::PHASE_POGO_FORWARD_BOUNCE_7;
}

bool Zombie::IsFlying() {
    return mZombiePhase == ZombiePhase::PHASE_BALLOON_FLYING || mZombiePhase == ZombiePhase::PHASE_BALLOON_POPPING;
}

int Zombie::GetBobsledPosition() {
    return old_Zombie_GetBobsledPosition(this);
}

bool Zombie::IsBobsledTeamWithSled() {
    return GetBobsledPosition() != -1;
}

bool Zombie::IsDeadOrDying() {
    return mDead || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_DYING || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_BURNED || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_MOWERED;
}

bool Zombie::CanBeChilled() {
    if (mZombieType == ZombieType::ZOMBIE_ZAMBONI || IsBobsledTeamWithSled())
        return false;

    if (IsDeadOrDying())
        return false;

    if (mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISING || mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISE_WITHOUT_AXE || mZombiePhase == ZombiePhase::PHASE_RISING_FROM_GRAVE || mZombiePhase == ZombiePhase::PHASE_DANCER_RISING)
        return false;

    if (mMindControlled)
        return false;

    return mZombieType != ZombieType::ZOMBIE_BOSS || mZombiePhase == ZombiePhase::PHASE_BOSS_HEAD_IDLE_BEFORE_SPIT || mZombiePhase == ZombiePhase::PHASE_BOSS_HEAD_IDLE_AFTER_SPIT
        || mZombiePhase == ZombiePhase::PHASE_BOSS_HEAD_SPIT;
}

bool Zombie::CanBeFrozen() {
    if (!CanBeChilled())
        return false;

    if (mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_INTO_POOL || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_IN_JUMP
        || mZombiePhase == ZombiePhase::PHASE_SNORKEL_INTO_POOL || IsFlying() || mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_THROWN || mZombiePhase == ZombiePhase::PHASE_IMP_LANDING
        || mZombiePhase == ZombiePhase::PHASE_BOBSLED_CRASHING || mZombiePhase == ZombiePhase::PHASE_JACK_IN_THE_BOX_POPPING || mZombiePhase == ZombiePhase::PHASE_SQUASH_RISING
        || mZombiePhase == ZombiePhase::PHASE_SQUASH_FALLING || mZombiePhase == ZombiePhase::PHASE_SQUASH_DONE_FALLING || IsBouncingPogo())
        return false;

    return mZombieType != ZombieType::ZOMBIE_BUNGEE || mZombiePhase == ZombiePhase::PHASE_BUNGEE_AT_BOTTOM;
}

bool Zombie::EffectedByDamage(unsigned int theDamageRangeFlags) {
    if (!TestBit(theDamageRangeFlags, (int)DamageRangeFlags::DAMAGES_DYING) && IsDeadOrDying()) {
        return false;
    }

    if (TestBit(theDamageRangeFlags, (int)DamageRangeFlags::DAMAGES_ONLY_MINDCONTROLLED)) {
        if (!mMindControlled) {
            return false;
        }
    } else if (mMindControlled) {
        return false;
    }

    if (mZombieType == ZombieType::ZOMBIE_BUNGEE && mZombiePhase != ZombiePhase::PHASE_BUNGEE_AT_BOTTOM && mZombiePhase != ZombiePhase::PHASE_BUNGEE_GRABBING) {
        return false; // 蹦极僵尸只有在停留时才会受到攻击
    }

    if (mZombieHeight == ZombieHeight::HEIGHT_GETTING_BUNGEE_DROPPED) {
        return false; // 被空投的过程中不会受到攻击
    }

    if (mZombieType == ZombieType::ZOMBIE_BOSS) {
        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        if (mZombiePhase == ZombiePhase::PHASE_BOSS_HEAD_ENTER && aBodyReanim->mAnimTime < 0.5f) {
            return false;
        }
        if (mZombiePhase == ZombiePhase::PHASE_BOSS_HEAD_LEAVE && aBodyReanim->mAnimTime > 0.5f) {
            return false;
        }

        if (mZombiePhase != ZombiePhase::PHASE_BOSS_HEAD_IDLE_BEFORE_SPIT && mZombiePhase != ZombiePhase::PHASE_BOSS_HEAD_IDLE_AFTER_SPIT && mZombiePhase != ZombiePhase::PHASE_BOSS_HEAD_SPIT) {
            return false; // 僵王博士只有在低头状态下才会受到攻击
        }
    }

    if (mZombieType == ZombieType::ZOMBIE_BOBSLED && GetBobsledPosition() > 0) {
        return false; // 存在雪橇时，只有领头僵尸会受到攻击
    }

    if (mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_THROWN || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISING
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISE_WITHOUT_AXE || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_INTO_POOL
        || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_IN_JUMP || mZombiePhase == ZombiePhase::PHASE_SNORKEL_INTO_POOL || mZombiePhase == ZombiePhase::PHASE_BALLOON_POPPING
        || mZombiePhase == ZombiePhase::PHASE_RISING_FROM_GRAVE || mZombiePhase == ZombiePhase::PHASE_BOBSLED_CRASHING || mZombiePhase == ZombiePhase::PHASE_DANCER_RISING) {
        return TestBit(theDamageRangeFlags, (int)DamageRangeFlags::DAMAGES_OFF_GROUND);
    }

    if (mZombieType != ZombieType::ZOMBIE_BOBSLED && GetZombieRect().mX > WIDE_BOARD_WIDTH) {
        return false; // 除雪橇僵尸小队外，场外的僵尸不会受到攻击
    }

    bool submerged = mZombieType == ZombieType::ZOMBIE_SNORKEL && mInPool && !mIsEating;
    if (TestBit(theDamageRangeFlags, (int)DamageRangeFlags::DAMAGES_SUBMERGED) && submerged) {
        return true;
    }

    bool underground = mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING;
    if (TestBit(theDamageRangeFlags, (int)DamageRangeFlags::DAMAGES_UNDERGROUND) && underground) {
        return true;
    }

    if (TestBit(theDamageRangeFlags, (int)DamageRangeFlags::DAMAGES_FLYING) && IsFlying()) {
        return true;
    }

    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
        if (IsFlying() && !mHasObject) { // 对战气球低空飞行时会受到攻击
            return true;
        }
    }

    return TestBit(theDamageRangeFlags, (int)DamageRangeFlags::DAMAGES_GROUND) && !IsFlying() && !submerged && !underground;
}

void Zombie::AddButter() {
    if (CanBeFrozen() && mZombieType != ZombieType::ZOMBIE_BOSS) {
        // Ban冰车 跳跳 僵王 飞翔的气球 跳跃的撑杆 即将跳水的潜水 等等
        if (mButteredCounter <= 100) {
            if (mButteredCounter == 0) {
                mApp->PlayFoley(FoleyType::FOLEY_BUTTER);
            }
            ApplyButter();
        }
    }
}

bool Zombie::IsWalkingBackwards() {
    if (mMindControlled)
        return true;

    if (mZombieHeight == ZombieHeight::HEIGHT_ZOMBIQUARIUM) {
        if (mVelZ < 1.5707964f || mVelZ > 4.712389f) {
            return true;
        }
    }

    if (mZombieType == ZombieType::ZOMBIE_DIGGER) {
        if (mZombiePhase == ZombiePhase::PHASE_DIGGER_RISING || mZombiePhase == ZombiePhase::PHASE_DIGGER_STUNNED || mZombiePhase == ZombiePhase::PHASE_DIGGER_WALKING) {
            return true;
        } else if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_DYING || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_BURNED || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_MOWERED) {
            return mHasObject;
        }

        return false;
    }

    return mZombieType == ZombieType::ZOMBIE_YETI && !mHasObject;
}

void Zombie::SetZombatarReanim() {
    DefaultPlayerInfo *aPlayerInfo = mApp->mPlayerInfo;
    if (!aPlayerInfo->mZombatarEnabled)
        return;
    Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    ReanimatorTrackInstance *aHeadTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
    aHeadTrackInstance->mImageOverride = *IMAGE_BLANK;
    Reanimation *aZombatarHeadReanim = mApp->AddReanimation(0, 0, 0, ReanimationType::REANIM_ZOMBATAR_HEAD);
    Reanimation_SetZombatarHats(aZombatarHeadReanim, aPlayerInfo->mZombatarHat, aPlayerInfo->mZombatarHatColor);
    Reanimation_SetZombatarHair(aZombatarHeadReanim, aPlayerInfo->mZombatarHair, aPlayerInfo->mZombatarHairColor);
    Reanimation_SetZombatarFHair(aZombatarHeadReanim, aPlayerInfo->mZombatarFacialHair, aPlayerInfo->mZombatarFacialHairColor);
    Reanimation_SetZombatarAccessories(aZombatarHeadReanim, aPlayerInfo->mZombatarAccessory, aPlayerInfo->mZombatarAccessoryColor);
    Reanimation_SetZombatarEyeWear(aZombatarHeadReanim, aPlayerInfo->mZombatarEyeWear, aPlayerInfo->mZombatarEyeWearColor);
    Reanimation_SetZombatarTidBits(aZombatarHeadReanim, aPlayerInfo->mZombatarTidBit, aPlayerInfo->mZombatarTidBitColor);
    aZombatarHeadReanim->PlayReanim("anim_head_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0);
    aZombatarHeadReanim->AssignRenderGroupToTrack("anim_hair", -1);
    mBossFireBallReanimID = mApp->ReanimationGetID(aZombatarHeadReanim);
    AttachEffect *attachEffect = AttachReanim(aHeadTrackInstance->mAttachmentID, aZombatarHeadReanim, 0.0f, 0.0f);
    TodScaleRotateTransformMatrix((SexyMatrix3 &)attachEffect->mOffset, -20.0, -1.0, 0.2, 1.0, 1.0);
    ReanimShowPrefix("anim_hair", -1);
    ReanimShowPrefix("anim_head2", -1);
}

bool Zombie::IsZombatarZombie(ZombieType theType) {
    // return type == ZombieType::ZOMBIE_FLAG || type == ZombieType::ZOMBIE_NORMAL || type == ZombieType::ZOMBIE_TRAFFIC_CONE || type == ZombieType::ZOMBIE_DOOR || type == ZombieType::ZOMBIE_TRASHCAN
    // || type == ZombieType::ZOMBIE_PAIL || type
    // == ZombieType::ZOMBIE_DUCKY_TUBE;
    return theType == ZombieType::ZOMBIE_FLAG;
}

void Zombie::DieWithLoot() {
    DieNoLoot();
    DropLoot();
}

void Zombie::DieNoLoot() {
    if (mZombieType == ZombieType::ZOMBIE_GARGANTUAR && mBoard != nullptr && mApp->mGameScene == GameScenes::SCENE_PLAYING) {
        mBoard->GrantAchievement(AchievementId::ACHIEVEMENT_GARG, true);
    }

    if (IsZombatarZombie(mZombieType)) {
        // 大头贴
        mApp->RemoveReanimation(mBossFireBallReanimID);
    }

    DropSoul();

    if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
        JacksonDie();
    }

    old_Zombie_DieNoLoot(this);
}

void Zombie::StopZombieSound() {
    if (mZombieType == ZombieType::ZOMBIE_DANCER || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER) {
        bool aStopSound = false;

        if (mBoard) {
            Zombie *aZombie = nullptr;
            while (mBoard->IterateZombies(aZombie)) {
                if (aZombie->mHasHead && !aZombie->IsDeadOrDying() && aZombie->IsOnBoard()
                    && (aZombie->mZombieType == ZombieType::ZOMBIE_DANCER || aZombie->mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER)) {
                    aStopSound = true;
                    break;
                }
            }
        }

        if (aStopSound) {
            mApp->mSoundSystem->StopFoley(FoleyType::FOLEY_DANCER);
        }
    }

    if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
        bool aStopSound = false;

        if (mBoard) {
            Zombie *aZombie = nullptr;
            while (mBoard->IterateZombies(aZombie)) {
                if (aZombie->mHasHead && !aZombie->IsDeadOrDying() && aZombie->IsOnBoard() && aZombie->mZombieType == ZombieType::ZOMBIE_JACKSON) {
                    aStopSound = true;
                    break;
                }
            }
        }

        if (aStopSound) {
            mApp->mSoundSystem->StopFoley(FoleyType::FOLEY_THRILLER);
        }
    }

    if (mPlayingSong) {
        mPlayingSong = false;

        if (mZombieType == ZombieType::ZOMBIE_JACK_IN_THE_BOX) {
            mApp->mSoundSystem->StopFoley(FoleyType::FOLEY_JACKINTHEBOX);
        } else if (mZombieType == ZombieType::ZOMBIE_DIGGER) {
            mApp->mSoundSystem->StopFoley(FoleyType::FOLEY_DIGGER);
        }
    }
}

void Zombie::DrawBungeeCord(Sexy::Graphics *g, int theOffsetX, int theOffsetY) {
    // 修复在Boss关的蹦极绳子不绑在Boss手上
    int aCordCelHeight = (*Sexy_IMAGE_BUNGEECORD_Addr)->GetCelHeight() * mScaleZombie;
    float aPosX = 0.0f;
    float aPosY = 0.0f;
    GetTrackPosition("Zombie_bungi_body", aPosX, aPosY);
    bool aSetClip = false;
    if (IsOnBoard() && mApp->IsFinalBossLevel()) {
        Zombie *aBossZombie = mBoard->GetBossZombie();
        int aClipAmount = 55;
        if (aBossZombie->mZombiePhase == ZombiePhase::PHASE_BOSS_BUNGEES_LEAVE) {
            Reanimation *reanimation = mApp->ReanimationGet(aBossZombie->mBodyReanimID);
            aClipAmount = TodAnimateCurveFloatTime(0.0f, 0.2f, reanimation->mAnimTime, 55.0f, 0.0f, TodCurves::CURVE_LINEAR);
        }
        if (mTargetCol >= aBossZombie->mTargetCol) { // ">" ------ > ">="，修复第一根手指蹦极不绑在手上
            if (mTargetCol > aBossZombie->mTargetCol) {
                aClipAmount += 60; // 55 ---- > 115，修复第2、3根手指蹦极不绑在手上
            }
            g->SetClipRect(-g->mTransX, aClipAmount - g->mTransY, 800, 600);
            aSetClip = true;
        }
    }

    for (float y = aPosY - aCordCelHeight; y > -60 - aCordCelHeight; y -= aCordCelHeight) {
        float thePosX = theOffsetX + 61.0f - 4.0f / mScaleZombie;
        float thePosY = y - mPosY;
        TodDrawImageScaledF(g, *Sexy_IMAGE_BUNGEECORD_Addr, thePosX, thePosY, mScaleZombie, mScaleZombie);
    }
    if (aSetClip) {
        g->ClearClipRect();
    }
}

void Zombie::GetDrawPos(ZombieDrawPosition &theDrawPos) {
    theDrawPos.mImageOffsetX = mPosX - mX;
    theDrawPos.mImageOffsetY = mPosY - mY;

    if (mIsEating) {
        theDrawPos.mHeadX = 47;
        theDrawPos.mHeadY = 4;
    } else {
        switch (mFrame) {
            case 0:
                theDrawPos.mHeadX = 50;
                theDrawPos.mHeadY = 2;
                break;
            case 1:
                theDrawPos.mHeadX = 49;
                theDrawPos.mHeadY = 1;
                break;
            case 2:
                theDrawPos.mHeadX = 49;
                theDrawPos.mHeadY = 2;
                break;
            case 3:
                theDrawPos.mHeadX = 48;
                theDrawPos.mHeadY = 4;
                break;
            case 4:
                theDrawPos.mHeadX = 48;
                theDrawPos.mHeadY = 5;
                break;
            case 5:
                theDrawPos.mHeadX = 48;
                theDrawPos.mHeadY = 4;
                break;
            case 6:
                theDrawPos.mHeadX = 48;
                theDrawPos.mHeadY = 2;
                break;
            case 7:
                theDrawPos.mHeadX = 49;
                theDrawPos.mHeadY = 1;
                break;
            case 8:
                theDrawPos.mHeadX = 49;
                theDrawPos.mHeadY = 2;
                break;
            case 9:
                theDrawPos.mHeadX = 50;
                theDrawPos.mHeadY = 4;
                break;
            case 10:
                theDrawPos.mHeadX = 50;
                theDrawPos.mHeadY = 5;
                break;
            default:
                theDrawPos.mHeadX = 50;
                theDrawPos.mHeadY = 4;
                break;
        }
    }

    theDrawPos.mArmY = theDrawPos.mHeadY / 2;

    switch (mZombieType) {
        case ZombieType::ZOMBIE_FOOTBALL:
            theDrawPos.mImageOffsetY -= 16.0f;
            break;
        case ZombieType::ZOMBIE_YETI:
            theDrawPos.mImageOffsetY -= 20.0f;
            break;
        case ZombieType::ZOMBIE_CATAPULT:
            theDrawPos.mImageOffsetX -= 25.0f;
            theDrawPos.mImageOffsetY -= 18.0f;
            break;
        case ZombieType::ZOMBIE_POGO:
            theDrawPos.mImageOffsetY += 16.0f;
            break;
        case ZombieType::ZOMBIE_BALLOON:
            theDrawPos.mImageOffsetY += 17.0f;
            break;
        case ZombieType::ZOMBIE_POLEVAULTER:
            theDrawPos.mImageOffsetX -= 6.0f;
            theDrawPos.mImageOffsetY -= 11.0f;
            break;
        case ZombieType::ZOMBIE_ZAMBONI:
            theDrawPos.mImageOffsetX += 68.0f;
            theDrawPos.mImageOffsetY -= 23.0f;
            break;
        case ZombieType::ZOMBIE_GARGANTUAR:
        case ZombieType::ZOMBIE_REDEYE_GARGANTUAR:
            theDrawPos.mImageOffsetY -= 8.0f;
            break;
        case ZombieType::ZOMBIE_BOBSLED:
            theDrawPos.mImageOffsetY -= 12.0f;
            break;
        default:
            break;
    }

    if (mZombiePhase == ZombiePhase::PHASE_RISING_FROM_GRAVE) {
        theDrawPos.mBodyY = -mAltitude;

        if (mInPool) {
            theDrawPos.mClipHeight = theDrawPos.mBodyY;
        } else {
            float aHeightLimit = std::min(mPhaseCounter, 40);
            theDrawPos.mClipHeight = theDrawPos.mBodyY + aHeightLimit;
        }

        if (IsOnHighGround()) {
            theDrawPos.mBodyY -= HIGH_GROUND_HEIGHT;
        }

        return;
    }

    if (mZombieType == ZombieType::ZOMBIE_DOLPHIN_RIDER) {
        theDrawPos.mBodyY = -mAltitude;
        theDrawPos.mClipHeight = CLIP_HEIGHT_OFF;

        if (mZombiePhase == ZombiePhase::PHASE_DOLPHIN_INTO_POOL) {
            Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);

            if (aBodyReanim->mAnimTime >= 0.56f && aBodyReanim->mAnimTime <= 0.65f) // 跳上海豚的起跳过程
            {
                theDrawPos.mClipHeight = 0.0f;
            } else if (aBodyReanim->mAnimTime >= 0.75f) // 跳上海豚的下落过程
            {
                theDrawPos.mClipHeight = -mAltitude - 10.0f;
            }
        } else if (mZombiePhase == ZombiePhase::PHASE_DOLPHIN_RIDING) {
            theDrawPos.mImageOffsetX += 70.0f; // 额外 70 像素的横坐标偏移用于弥补跳上海豚后的 mPosX -= 70.0f

            if (mZombieHeight == ZombieHeight::HEIGHT_DRAGGED_UNDER) {
                theDrawPos.mClipHeight = -mAltitude - 15.0f;
            } else {
                theDrawPos.mClipHeight = -mAltitude - 10.0f;
            }
        } else if (mZombiePhase == ZombiePhase::PHASE_DOLPHIN_IN_JUMP) {
            theDrawPos.mImageOffsetX += 70.0f + mAltitude;

            Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
            if (aBodyReanim->mAnimTime <= 0.06f) // 起跳出水之前
            {
                theDrawPos.mClipHeight = -mAltitude - 10.0f;
            } else if (aBodyReanim->mAnimTime >= 0.5f && aBodyReanim->mAnimTime <= 0.76f) // 起跳过程中（脱离水面后至重新入水前）
            {
                theDrawPos.mClipHeight = -13.0f;
            }
        } else if (mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_IN_POOL || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_DYING) {
            theDrawPos.mImageOffsetY += 50.0f; // 额外 50 像素的横坐标偏移用于弥补跳跃过程中前进的距离

            if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_DYING) {
                theDrawPos.mClipHeight = -mAltitude + 44.0f;
            } else if (mZombieHeight == ZombieHeight::HEIGHT_DRAGGED_UNDER) {
                theDrawPos.mClipHeight = -mAltitude + 36.0f;
            }
        } else if (mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING && mZombieHeight == ZombieHeight::HEIGHT_OUT_OF_POOL) {
            theDrawPos.mClipHeight = -mAltitude;
        } else if (mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_WITHOUT_DOLPHIN && mZombieHeight == ZombieHeight::HEIGHT_OUT_OF_POOL) {
            theDrawPos.mClipHeight = -mAltitude;
        }
    } else if (mZombieType == ZombieType::ZOMBIE_SNORKEL) {
        theDrawPos.mBodyY = -mAltitude;
        theDrawPos.mClipHeight = CLIP_HEIGHT_OFF;

        if (mZombiePhase == ZombiePhase::PHASE_SNORKEL_INTO_POOL) {
            Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
            if (aBodyReanim->mAnimTime >= 0.8f) // 入水后
            {
                theDrawPos.mClipHeight = -10.0f;
            }
        } else if (mInPool) {
            theDrawPos.mClipHeight = -mAltitude - 5.0f;
            theDrawPos.mClipHeight += 20.0f - 20.0f * mScaleZombie;
        }
    } else if (mInPool) {
        theDrawPos.mBodyY = -mAltitude;
        theDrawPos.mClipHeight = -mAltitude - 7.0f;
        theDrawPos.mClipHeight += 10.0f - 10.0f * mScaleZombie;

        if (mIsEating) {
            theDrawPos.mClipHeight += 7.0f;
        }
    } else if (mZombiePhase == ZombiePhase::PHASE_DANCER_RISING) {
        theDrawPos.mBodyY = -mAltitude;
        theDrawPos.mClipHeight = -mAltitude;

        if (IsOnHighGround()) {
            theDrawPos.mBodyY -= HIGH_GROUND_HEIGHT;
        }
    } else if (mZombiePhase == ZombiePhase::PHASE_DIGGER_RISING || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISE_WITHOUT_AXE) {
        theDrawPos.mBodyY = -mAltitude;

        if (mPhaseCounter > 20) {
            theDrawPos.mClipHeight = -mAltitude;
        } else {
            theDrawPos.mClipHeight = CLIP_HEIGHT_OFF;
        }
    } else if (mZombieType == ZombieType::ZOMBIE_BUNGEE) {
        theDrawPos.mBodyY = -mAltitude;
        theDrawPos.mImageOffsetX -= 18.0f;

        if (IsOnHighGround()) {
            theDrawPos.mBodyY -= HIGH_GROUND_HEIGHT;
        }

        theDrawPos.mClipHeight = CLIP_HEIGHT_OFF;
    } else {
        theDrawPos.mBodyY = -mAltitude;
        theDrawPos.mClipHeight = CLIP_HEIGHT_OFF;
    }
}

bool Zombie::IsOnHighGround() {
    return IsOnBoard() && mBoard->mGridSquareType[mBoard->PixelToGridXKeepOnBoard(mX + 75, mY)][mRow] == GridSquareType::GRIDSQUARE_HIGH_GROUND;
}

bool Zombie::IsTangleKelpTarget() {
    // 修复水草拉僵尸有概率失效

    if (!mBoard->StageHasPool()) {
        return false;
    }
    if (mZombieHeight == ZombieHeight::HEIGHT_DRAGGED_UNDER) {
        return true;
    }
    Plant *aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant)) {
        if (!aPlant->mDead && aPlant->mSeedType == SeedType::SEED_TANGLEKELP && aPlant->mTargetZombieID == mZombieID) {
            return true;
        }
    }
    return false;
}

void Zombie::DrawReanim(Sexy::Graphics *g, ZombieDrawPosition &theDrawPos, int theBaseRenderGroup) {
    Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
    if (aBodyReanim == nullptr) {
        return;
    }

    if (theDrawPos.mClipHeight > CLIP_HEIGHT_LIMIT) {
        float aDrawHeight = 120.0f - theDrawPos.mClipHeight + 71.0f;
        g->SetClipRect(theDrawPos.mImageOffsetX - 200.0f, theDrawPos.mImageOffsetY + theDrawPos.mBodyY - 78.0f, 520, aDrawHeight);
    }

    int aFadeAlpha = 255;
    if (mZombieFade >= 0) {
        aFadeAlpha = ClampInt(255 * mZombieFade / 10, 0, 255);
    }

    Color aColorOverride(255, 255, 255, aFadeAlpha);
    Color aExtraAdditiveColor = Color::Black;
    bool aEnableExtraAdditiveDraw = false;
    if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_BURNED) {
        aColorOverride = Color(0, 0, 0, aFadeAlpha);
        aExtraAdditiveColor = Color::Black;
        aEnableExtraAdditiveDraw = false;
    } else if (mZombieType == ZombieType::ZOMBIE_BOSS && mZombiePhase != ZombiePhase::PHASE_ZOMBIE_DYING && mBodyHealth < mBodyMaxHealth / BOSS_FLASH_HEALTH_FRACTION) {
        int aGrayness = TodAnimateCurve(0, 39, mBoard->mMainCounter % 40, 155, 255, TodCurves::CURVE_BOUNCE);
        if (mChilledCounter > 0 || mIceTrapCounter > 0) {
            int aColdColor = TodAnimateCurve(0, 39, mBoard->mMainCounter % 40, 65, 75, TodCurves::CURVE_BOUNCE);
            aColorOverride = Color(aColdColor, aColdColor, aGrayness, aFadeAlpha);
        } else {
            aColorOverride = Color(aGrayness, aGrayness, aGrayness, aFadeAlpha);
        }

        aExtraAdditiveColor = Color::Black;
        aEnableExtraAdditiveDraw = false;
    } else if (mMindControlled) {
        aColorOverride = ZOMBIE_MINDCONTROLLED_COLOR;
        aColorOverride.mAlpha = aFadeAlpha;
        aExtraAdditiveColor = aColorOverride;
        aEnableExtraAdditiveDraw = true;
    } else if (mChilledCounter > 0 || mIceTrapCounter > 0) {
        aColorOverride = Color(75, 75, 255, aFadeAlpha);
        aExtraAdditiveColor = aColorOverride;
        aEnableExtraAdditiveDraw = true;
    } else if (mZombieHeight == ZombieHeight::HEIGHT_ZOMBIQUARIUM && mBodyHealth < 100) {
        aColorOverride = Color(100, 150, 25, aFadeAlpha);
        aExtraAdditiveColor = aColorOverride;
        aEnableExtraAdditiveDraw = true;
    } else if (mIsRevived) {
        aColorOverride = ZOMBIE_REVIVED_COLOR;
        aColorOverride.mAlpha = aFadeAlpha;
        aExtraAdditiveColor = aColorOverride;
        aEnableExtraAdditiveDraw = true;
    }

    if (mJustGotShotCounter > 0 && !IsBobsledTeamWithSled()) {
        int aGrayness = mJustGotShotCounter * 10;
        Color aHighlightColor(aGrayness, aGrayness, aGrayness, 255);
        aExtraAdditiveColor = ColorAdd(aHighlightColor, aExtraAdditiveColor);
        aEnableExtraAdditiveDraw = true;
    }

    aBodyReanim->mColorOverride = aColorOverride;
    aBodyReanim->mExtraAdditiveColor = aExtraAdditiveColor;
    aBodyReanim->mEnableExtraAdditiveDraw = aEnableExtraAdditiveDraw;

    if (mZombieType == ZombieType::ZOMBIE_BOBSLED) {
        DrawBobsledReanim(g, theDrawPos, true);
        aBodyReanim->DrawRenderGroup(g, theBaseRenderGroup);
        DrawBobsledReanim(g, theDrawPos, false);
    } else if (mZombieType == ZombieType::ZOMBIE_BUNGEE) {
        DrawBungeeReanim(g, theDrawPos);
    } else if (mZombieType == ZombieType::ZOMBIE_DANCER || mZombieType == ZombieType::ZOMBIE_JACKSON) {
        DrawDancerReanim(g, theDrawPos);
    } else {
        aBodyReanim->DrawRenderGroup(g, theBaseRenderGroup);

        Reanimation *aHeadReanim = mApp->ReanimationGet(mSpecialHeadReanimID);
        if (aHeadReanim && IsZombotany(mZombieType)) {
            aHeadReanim->mColorOverride = aColorOverride;
            aHeadReanim->mExtraAdditiveColor = aExtraAdditiveColor;
            aHeadReanim->mEnableExtraAdditiveDraw = aEnableExtraAdditiveDraw;
            if (mZombieType == ZombieType::ZOMBIE_EXPLODE_O_NUT_HEAD) {
                aHeadReanim->mColorOverride = Color(255, 64, 64);
                aHeadReanim->DrawRenderGroup(g, theBaseRenderGroup);
            }
            if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_BURNED) {
                aHeadReanim->DrawRenderGroup(g, theBaseRenderGroup);
            }
        }
    }

    if (mShieldType != ShieldType::SHIELDTYPE_NONE) {
        if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_BURNED) {
            aBodyReanim->mColorOverride = Color(0, 0, 0, aFadeAlpha);
            aBodyReanim->mExtraAdditiveColor = Color::Black;
            aBodyReanim->mEnableExtraAdditiveDraw = false;
        } else if (mShieldJustGotShotCounter > 0) {
            int aGrayness = mShieldJustGotShotCounter * 10;
            aBodyReanim->mColorOverride = Color(aGrayness, aGrayness, aGrayness, aFadeAlpha);
            aBodyReanim->mExtraAdditiveColor = Color::White;
            aBodyReanim->mEnableExtraAdditiveDraw = true;
        } else {
            aBodyReanim->mColorOverride = Color(255, 255, 255, aFadeAlpha);
            aBodyReanim->mExtraAdditiveColor = Color::Black;
            aBodyReanim->mEnableExtraAdditiveDraw = false;
        }

        float aShieldHitOffset = 0.0f;
        if (mShieldRecoilCounter > 0) {
            aShieldHitOffset = TodAnimateCurveFloat(12, 0, mShieldRecoilCounter, 3.0f, 0.0f, TodCurves::CURVE_LINEAR);
        }

        g->mTransX += aShieldHitOffset;
        aBodyReanim->DrawRenderGroup(g, RENDER_GROUP_SHIELD);
        g->mTransX -= aShieldHitOffset;
    } else {
        if (aEnableExtraAdditiveDraw) {
            aBodyReanim->PropogateColorToAttachments();
        }
    }

    if (mShieldType == ShieldType::SHIELDTYPE_NEWSPAPER || mShieldType == ShieldType::SHIELDTYPE_DOOR || mShieldType == ShieldType::SHIELDTYPE_LADDER
        || mShieldType == ShieldType::SHIELDTYPE_TRASHCAN) {
        aBodyReanim->mColorOverride = aColorOverride;
        aBodyReanim->mExtraAdditiveColor = aExtraAdditiveColor;
        aBodyReanim->mEnableExtraAdditiveDraw = aEnableExtraAdditiveDraw;
        aBodyReanim->DrawRenderGroup(g, RENDER_GROUP_OVER_SHIELD);
    }

    // 大头贴专门Draw一下
    if (IsZombatarZombie(mZombieType)) {
        Reanimation *aZombatarReanim = mApp->ReanimationTryToGet(mBossFireBallReanimID);
        if (aZombatarReanim) {
            aZombatarReanim->Draw(g);
        }
    }

    g->ClearClipRect();
}

bool Zombie::CanLoseBodyParts() {
    return mZombieType != ZombieType::ZOMBIE_ZAMBONI && mZombieType != ZombieType::ZOMBIE_BUNGEE && mZombieType != ZombieType::ZOMBIE_CATAPULT && mZombieType != ZombieType::ZOMBIE_GARGANTUAR
        && mZombieType != ZombieType::ZOMBIE_REDEYE_GARGANTUAR && mZombieType != ZombieType::ZOMBIE_BOSS && mZombieHeight != ZombieHeight::HEIGHT_ZOMBIQUARIUM && !IsFlying()
        && !IsBobsledTeamWithSled();
}

void Zombie::SetupReanimForLostHead() {
    ReanimShowPrefix("anim_head", RENDER_GROUP_HIDDEN);
    ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
    ReanimShowPrefix("anim_tongue", RENDER_GROUP_HIDDEN);
}

void Zombie::DropHead(unsigned int theDamageFlags) {
    if (mZombieType > ZombieType::NUM_CACHED_ZOMBIE_TYPES) {
        if (!CanLoseBodyParts() || !mHasHead)
            return;

        mHasHead = false;
        SetupReanimForLostHead();
        if (TestBit(theDamageFlags, DamageFlags::DAMAGE_DOESNT_LEAVE_BODY)) {
            return;
        }

        if (Zombie::IsZombotany(mZombieType) && mSpecialHeadReanimID != ReanimationID::REANIMATIONID_NULL) {
            Reanimation *aHeadReanim = mApp->ReanimationTryToGet(mSpecialHeadReanimID);
            if (aHeadReanim)
                aHeadReanim->ReanimationDie();

            mSpecialHeadReanimID = ReanimationID::REANIMATIONID_NULL;
            return;
        }

        int aRenderOrder = mRenderOrder + 1;
        ZombieDrawPosition aDrawPos;
        GetDrawPos(aDrawPos);
        float aPosX = mPosX + aDrawPos.mImageOffsetX + aDrawPos.mHeadX + 11.0f;
        float aPosY = mPosY + aDrawPos.mImageOffsetY + aDrawPos.mHeadY + aDrawPos.mBodyY + 21.0f;
        if (mBodyReanimID != ReanimationID::REANIMATIONID_NULL) {
            GetTrackPosition("anim_head1", aPosX, aPosY);
        }

        ParticleEffect aEffect = ParticleEffect::PARTICLE_ZOMBIE_HEAD;
        if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_MOWERED) {
            aEffect = ParticleEffect::PARTICLE_MOWERED_ZOMBIE_HEAD;
        } else if (mInPool) {
            aEffect = ParticleEffect::PARTICLE_ZOMBIE_HEAD_POOL;
        }
        if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
            aRenderOrder = mRenderOrder - 1;
        }

        TodParticleSystem* aParticle = mApp->AddTodParticle(aPosX, aPosY, aRenderOrder, aEffect);
        if (aParticle) {
            if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
                aParticle->OverrideImage(nullptr, addonImages.IMAGE_ZOMBIEJACKSONHEAD);
            } else if (mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
                aParticle->OverrideImage(nullptr, addonImages.IMAGE_ZOMBIEBACKUPDANCERHEAD2);
            } else if (mZombieType == ZombieType::ZOMBIE_SUPER_FAN_IMP) {
                aParticle->OverrideImage(nullptr, *IMAGE_ZOMBIEIMPHEAD);
            }
        }
    }

    // 负责 大头贴掉头
    // TODO: 大头贴僵尸掉头时掉饰品(掉 hat 和 eyeWear)
    old_Zombie_DropHead(this, theDamageFlags);

    if (IsZombatarZombie(mZombieType)) {
        Reanimation *aHeadReanim = mApp->ReanimationTryToGet(mBossFireBallReanimID);
        if (aHeadReanim != nullptr) {
            int index[2] = {aHeadReanim->GetZombatarHatTrackIndex(), aHeadReanim->GetZombatarEyeWearTrackIndex()};
            for (int i = 0; i < 2; ++i) {
                if (index[i] == -1)
                    continue;
                ReanimatorTrackInstance *aTrackInstance = aHeadReanim->mTrackInstances + index[i];
                ReanimatorTrack *aTrack = aHeadReanim->mDefinition->mTracks + index[i];
                SexyTransform2D aTransform2D;
                aHeadReanim->GetTrackMatrix(index[i], aTransform2D);
                float aPosX = mPosX + aTransform2D.m[0][2];
                float aPosY = mPosY + aTransform2D.m[1][2];
                TodParticleSystem *aParticle = mApp->AddTodParticle(aPosX, aPosY, mRenderOrder + 1, ParticleEffect::PARTICLE_ZOMBIE_HEAD);
                aParticle->OverrideColor(nullptr, aTrackInstance->mTrackColor);
                aParticle->OverrideImage(nullptr, aTrack->mTransforms[0].mImage);
            }
            mApp->RemoveReanimation(mBossFireBallReanimID);
            mBossFireBallReanimID = ReanimationID::REANIMATIONID_NULL;
        }
    }
}

void Zombie::SetupReanimForLostArm(unsigned int theDamageFlags) {
    switch (mZombieType) {
        case ZombieType::ZOMBIE_GIGA_FOOTBALL:
            ReanimShowPrefix("Zombie_football_leftarm_lower", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("Zombie_football_leftarm_hand", RENDER_GROUP_HIDDEN);
            break;
        case ZombieType::ZOMBIE_JACKSON:
            ReanimShowTrack("Zombie_disco_outerarm_lower", RENDER_GROUP_HIDDEN);
            ReanimShowTrack("Zombie_disco_outerhand_point", RENDER_GROUP_HIDDEN);
            break;
        case ZombieType::ZOMBIE_BACKUP_DANCER:
            ReanimShowTrack("Zombie_disco_outerarm_lower", RENDER_GROUP_HIDDEN);
            ReanimShowTrack("Zombie_disco_outerhand", RENDER_GROUP_HIDDEN);
            break;
        default:
            ReanimShowPrefix("Zombie_outerarm_lower", RENDER_GROUP_HIDDEN);
            ReanimShowPrefix("Zombie_outerarm_hand", RENDER_GROUP_HIDDEN);
            break;
    }

    ZombieDrawPosition aDrawPos;
    GetDrawPos(aDrawPos);
    float aPosX = mPosX + aDrawPos.mImageOffsetX + 45.0f;
    float aPosY = mPosY + aDrawPos.mImageOffsetY + aDrawPos.mBodyY + 78.0f;
    if (IsWalkingBackwards()) {
        aPosX += 36.0f;
    }

    Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim) {
        switch (mZombieType) {
            case ZombieType::ZOMBIE_GIGA_FOOTBALL:
                GetTrackPosition("Zombie_football_leftarm_hand", aPosX, aPosY);
                aBodyReanim->SetImageOverride("Zombie_football_leftarm_upper", *IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2);
                break;
            case ZombieType::ZOMBIE_SUPER_FAN_IMP:
                GetTrackPosition("Zombie_outerarm_lower", aPosX, aPosY);
                aBodyReanim->SetImageOverride("Zombie_imp_outerarm_upper", *IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE);
                break;
            case ZombieType::ZOMBIE_JACKSON:
                GetTrackPosition("Zombie_disco_outerarm_lower", aPosX, aPosY);
                aBodyReanim->SetImageOverride("Zombie_disco_outerarm_upper", addonImages.IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_UPPER2);
                break;
            case ZombieType::ZOMBIE_BACKUP_DANCER2:
                GetTrackPosition("Zombie_disco_outerarm_lower", aPosX, aPosY);
                aBodyReanim->SetImageOverride("Zombie_disco_outerarm_upper", addonImages.IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2);
                break;
            default:
                GetTrackPosition("Zombie_outerarm_lower", aPosX, aPosY);
                aBodyReanim->SetImageOverride("Zombie_outerarm_upper", *IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2);
                break;
        }
    }

    if (!mInPool && !TestBit(theDamageFlags, DamageFlags::DAMAGE_DOESNT_LEAVE_BODY)) {
        ParticleEffect aEffect = ParticleEffect::PARTICLE_ZOMBIE_ARM;
        if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_MOWERED) {
            aEffect = ParticleEffect::PARTICLE_MOWERED_ZOMBIE_ARM;
        }

        TodParticleSystem *aParticle = mApp->AddTodParticle(aPosX, aPosY, mRenderOrder + 1, aEffect);

        if (aParticle) {
            switch (mZombieType) {
                case ZombieType::ZOMBIE_GIGA_FOOTBALL:
                    aParticle->OverrideImage(nullptr, *IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND);
                    break;
                case ZombieType::ZOMBIE_SUPER_FAN_IMP:
                    aParticle->OverrideImage(nullptr, *IMAGE_REANIM_ZOMBIE_IMP_ARM2);
                    break;
                case ZombieType::ZOMBIE_JACKSON:
                    ReanimShowTrack("Zombie_disco_outerarm_lower", RENDER_GROUP_HIDDEN);
                    ReanimShowTrack("Zombie_disco_outerhand_point", RENDER_GROUP_HIDDEN);
                    ReanimShowTrack("Zombie_disco_outerhand", RENDER_GROUP_HIDDEN);
                    aParticle->OverrideImage(nullptr, addonImages.IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_HAND);
                    break;
                case ZombieType::ZOMBIE_BACKUP_DANCER2:
                    ReanimShowTrack("Zombie_disco_outerarm_lower", RENDER_GROUP_HIDDEN);
                    ReanimShowTrack("Zombie_disco_outerhand", RENDER_GROUP_HIDDEN);
                    aParticle->OverrideImage(nullptr, addonImages.IMAGE_REANIM_ZOMBIE_DANCER_INNERARM_HAND);
                    break;
                default:
                    break;
            }
        }
    }
}

void Zombie::DropArm(unsigned int theDamageFlags) {
    if (mZombieType > ZombieType::NUM_CACHED_ZOMBIE_TYPES) {
        if (!CanLoseBodyParts()) {
            return;
        }
        if (mShieldType == ShieldType::SHIELDTYPE_DOOR || mShieldType == ShieldType::SHIELDTYPE_TRASHCAN || mShieldType == ShieldType::SHIELDTYPE_NEWSPAPER
            || mZombieType == ZombieType::ZOMBIE_BUNGEE) {
            return;
        }
        if (mZombiePhase == ZombiePhase::PHASE_SNORKEL_INTO_POOL || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_INTO_POOL
            || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_RIDING || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_IN_JUMP || mZombiePhase == ZombiePhase::PHASE_NEWSPAPER_READING) {
            return;
        }
        if (!mHasArm) {
            return;
        }

        mHasArm = false;
        SetupReanimForLostArm(theDamageFlags);
        mApp->PlayFoley(FoleyType::FOLEY_LIMBS_POP);
        return;
    }

    old_Zombie_DropArm(this, theDamageFlags);
}

int Zombie::GetHelmDamageIndex() {
    if (mHelmHealth < mHelmMaxHealth / 3) {
        return 2;
    }

    if (mHelmHealth < mHelmMaxHealth * 2 / 3) {
        return 1;
    }

    return 0;
}

int Zombie::GetBodyDamageIndex() {
    if (mZombieType == ZombieType::ZOMBIE_BOSS) {
        if (mBodyHealth < mBodyMaxHealth / 2) {
            return 2;
        }

        if (mBodyHealth < mBodyMaxHealth * 4 / 5) {
            return 1;
        }

        return 0;
    } else {
        if (mBodyHealth < mBodyMaxHealth / 3) {
            return 2;
        }

        if (mBodyHealth < mBodyMaxHealth * 2 / 3) {
            return 1;
        }

        return 0;
    }
}

int Zombie::GetShieldDamageIndex() {
    if (mShieldHealth < mShieldMaxHealth / 3) {
        return 2;
    }

    if (mShieldHealth < mShieldMaxHealth * 2 / 3) {
        return 1;
    }

    return 0;
}

bool Zombie::IsFireResistant() {
    return mZombieType == ZombieType::ZOMBIE_CATAPULT || mZombieType == ZombieType::ZOMBIE_ZAMBONI || mShieldType == ShieldType::SHIELDTYPE_DOOR || mShieldType == ShieldType::SHIELDTYPE_LADDER
        || mShieldType == ShieldType::SHIELDTYPE_TRASHCAN;
}

Rect Zombie::GetZombieAttackRect() {
    Rect aAttackRect = mZombieAttackRect;
    if (mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_IN_JUMP) {
        aAttackRect = Rect(-40, 0, 100, 115);
    }

    if (IsWalkingBackwards()) {
        aAttackRect.mX = mWidth - aAttackRect.mX - aAttackRect.mWidth;
    }

    ZombieDrawPosition aDrawPos;
    GetDrawPos(aDrawPos);
    aAttackRect.Offset(mX, mY + aDrawPos.mBodyY);
    if (aDrawPos.mClipHeight > CLIP_HEIGHT_LIMIT) {
        aAttackRect.mHeight -= aDrawPos.mClipHeight;
    }

    return aAttackRect;
}

Plant *Zombie::FindPlantTarget(ZombieAttackType theAttackType) {
    if (mMindControlled)
        return nullptr;

    Rect aAttackRect = GetZombieAttackRect();

    Plant *aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant)) {
        if (aPlant->mRow == mRow) {
            Rect aPlantRect = aPlant->GetPlantRect();
            if (GetRectOverlap(aAttackRect, aPlantRect) >= 20 && CanTargetPlant(aPlant, theAttackType)) {
                return aPlant;
            }
        }
    }

    return nullptr;
}

Plant* Zombie::FindPlantTargetInNextGrid(ZombieAttackType theAttackType) {
    Rect aAttackRect = GetZombieAttackRect();
    int aPosX = mX + mWidth / 2;
    int aNextGridX = mBoard->PixelToGridX(mX, mY) - 1;
    int aDistance = aPosX - mBoard->GridToPixelX(aNextGridX, 0);

    Plant *aPlant = nullptr;
    while (mBoard->IteratePlants(aPlant)) {
        if (aPlant->mRow == mRow) {
            if (aPosX - aPlant->mX >= aDistance && CanTargetPlant(aPlant, theAttackType)) {
                return aPlant;
            }
        }
    }

    return nullptr;
}

Zombie *Zombie::FindZombieGigaFootball() {
    Rect aAttackRect = GetZombieAttackRect();

    Zombie *aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie)) {
        if (mMindControlled == aZombie->mMindControlled && mZombiePhase != ZombiePhase::PHASE_IMP_GETTING_THROWN && mZombiePhase != ZombiePhase::PHASE_RISING_FROM_GRAVE
            && aZombie->mZombiePhase != ZombiePhase::PHASE_RISING_FROM_GRAVE && aZombie->mZombieType == ZombieType::ZOMBIE_GIGA_FOOTBALL
            && aZombie->mZombiePhase == ZombiePhase::PHASE_FOOTBALL_CHARGING && !aZombie->IsDeadOrDying() && aZombie->mRow == mRow) {
            float aTacklingDistance = mPosX - 360.0f;
            if (aTacklingDistance > 40.0f) {
                Rect aZombieRect = aZombie->GetZombieRect();
                int aOverlap = GetRectOverlap(aAttackRect, aZombieRect);
                if (aOverlap > 0) {
                    return aZombie;
                }
            }
        }
    }

    return nullptr;
}

bool Zombie::CanTargetPlant(Plant *thePlant, ZombieAttackType theAttackType) {
    if (mApp->IsWallnutBowlingLevel() && theAttackType != ZombieAttackType::ATTACKTYPE_VAULT)
        return false;

    if (thePlant->NotOnGround() || thePlant->mSeedType == SeedType::SEED_TANGLEKELP)
        return false;

    if (!mInPool && mBoard->IsPoolSquare(thePlant->mPlantCol, thePlant->mRow))
        return false;

    if (mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING) {
        return thePlant->mSeedType == SeedType::SEED_POTATOMINE && thePlant->mState == PlantState::STATE_NOTREADY;
    }

    if (thePlant->IsSpiky()) {
        return mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_ZAMBONI
            || mBoard->IsPoolSquare(thePlant->mPlantCol, thePlant->mRow) || mBoard->GetFlowerPotAt(thePlant->mPlantCol, thePlant->mRow); // 扶梯僵尸给花盆上的地刺/地刺王搭梯的原理
    }

    if (theAttackType == ZombieAttackType::ATTACKTYPE_DRIVE_OVER) {
        if (thePlant->mSeedType == SeedType::SEED_CHERRYBOMB || thePlant->mSeedType == SeedType::SEED_JALAPENO || thePlant->mSeedType == SeedType::SEED_BLOVER
            || thePlant->mSeedType == SeedType::SEED_SQUASH) {
            return false;
        }
        if (thePlant->mSeedType == SeedType::SEED_DOOMSHROOM || thePlant->mSeedType == SeedType::SEED_ICESHROOM) {
            return thePlant->mIsAsleep;
        }
    }

    if (mZombiePhase == ZombiePhase::PHASE_LADDER_CARRYING || mZombiePhase == ZombiePhase::PHASE_LADDER_PLACING) {
        bool aPlaceLadder = false;
        if (thePlant->mSeedType == SeedType::SEED_WALLNUT || thePlant->mSeedType == SeedType::SEED_TALLNUT || thePlant->mSeedType == SeedType::SEED_PUMPKINSHELL) {
            aPlaceLadder = true;
        }

        if (mBoard->GetLadderAt(thePlant->mPlantCol, thePlant->mRow)) {
            aPlaceLadder = false;
        }

        if ((theAttackType == ZombieAttackType::ATTACKTYPE_CHEW && aPlaceLadder) || (theAttackType == ZombieAttackType::ATTACKTYPE_LADDER && !aPlaceLadder)) {
            return false;
        }
    }

    if (theAttackType == ZombieAttackType::ATTACKTYPE_CHEW) {
        Plant *aTopPlant = mBoard->GetTopPlantAt(thePlant->mPlantCol, thePlant->mRow, PlantPriority::TOPPLANT_EATING_ORDER);
        if (aTopPlant != thePlant && aTopPlant && CanTargetPlant(aTopPlant, theAttackType)) {
            return false;
        }
    }

    if (theAttackType == ZombieAttackType::ATTACKTYPE_VAULT) {
        Plant *aTopPlant = mBoard->GetTopPlantAt(thePlant->mPlantCol, thePlant->mRow, PlantPriority::TOPPLANT_ONLY_NORMAL_POSITION);
        if (aTopPlant != thePlant && aTopPlant && CanTargetPlant(aTopPlant, theAttackType)) {
            return false;
        }
    }

    return true;
}

Zombie *Zombie::FindZombieTarget() {
    if (mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING)
        return nullptr;

    Rect aAttackRect = GetZombieAttackRect();

    Zombie *aZombie = nullptr;
    while (mBoard->IterateZombies(aZombie)) {
        if (mMindControlled != aZombie->mMindControlled && !aZombie->IsFlying() && aZombie->mZombiePhase != ZombiePhase::PHASE_DIGGER_TUNNELING
            && aZombie->mZombiePhase != ZombiePhase::PHASE_BUNGEE_DIVING && aZombie->mZombiePhase != ZombiePhase::PHASE_BUNGEE_DIVING_SCREAMING
            && aZombie->mZombiePhase != ZombiePhase::PHASE_BUNGEE_RISING && aZombie->mZombieHeight != ZombieHeight::HEIGHT_GETTING_BUNGEE_DROPPED && !aZombie->IsDeadOrDying()
            && aZombie->mRow == mRow) {
            if (aZombie->mZombieType == ZombieType::ZOMBIE_BOSS && aZombie->mZombiePhase != ZombiePhase::PHASE_BOSS_IDLE) {
                continue;
            }

            Rect aZombieRect = aZombie->GetZombieRect();
            int aOverlap = GetRectOverlap(aAttackRect, aZombieRect);
            if (aOverlap >= 20 || (aOverlap > 0 && aZombie->mIsEating)) {
                return aZombie;
            }
        }
    }

    return nullptr;
}

void Zombie::TakeDamage(int theDamage, unsigned int theDamageFlags) {
    old_Zombie_TakeDamage(this, theDamage, theDamageFlags);
}

int Zombie::TakeHelmDamage(int theDamage, unsigned int theDamageFlags) {
    return old_Zombie_TakeHelmDamage(this, theDamage, theDamageFlags);
}

void Zombie::PlayZombieReanim(const char *theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate) {
    old_Zombie_PlayZombieReanim(this, theTrackName, theLoopType, theBlendTime, theAnimRate);
}

void Zombie::StartWalkAnim(int theBlendTime) {
    old_Zombie_StartWalkAnim(this, theBlendTime);
}

void Zombie::ReanimShowPrefix(const char *theTrackPrefix, int theRenderGroup) {
    old_Zombie_ReanimShowPrefix(this, theTrackPrefix, theRenderGroup);
}

void Zombie::ReanimShowTrack(const char *theTrackName, int theRenderGroup) {
    old_Zombie_ReanimShowTrack(this, theTrackName, theRenderGroup);
}

float Zombie::GetPosYBasedOnRow(int theRow) {
    return old_Zombie_GetPosYBasedOnRow(this, theRow);
}

void Zombie::SetRow(int theRow) {
    old_Zombie_SetRow(this, theRow);
}

void Zombie::StartMindControlled() {
    old_Zombie_StartMindControlled(this);
}

void Zombie::UpdateReanim() {
    old_Zombie_UpdateReanim(this);

    if (mZombieType > ZombieType::NUM_CACHED_ZOMBIE_TYPES) {
        Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        if (aBodyReanim == nullptr || aBodyReanim->mDead)
            return;

        UpdateReanimColor();

        ZombieDrawPosition aDrawPos;
        GetDrawPos(aDrawPos);
        float anOffsetX = aDrawPos.mImageOffsetX + 15.0f;
        float anOffsetY = aDrawPos.mImageOffsetY + aDrawPos.mBodyY - 28.0f + 20.0f;

        bool anOpposite = false;
        if (IsWalkingBackwards()) {
            anOpposite = true;
        }
        if (mZombieType == ZombieType::ZOMBIE_JACKSON || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
            anOpposite = false;

            if (mZombiePhase == ZombiePhase::PHASE_DANCER_DANCING_IN || mZombiePhase == ZombiePhase::PHASE_DANCER_RAISE_RIGHT_1 || mZombiePhase == ZombiePhase::PHASE_DANCER_RAISE_RIGHT_2) {
                if (!mIsEating) {
                    anOpposite = true;
                }
            }

            if (mMindControlled) {
                anOpposite = !anOpposite;
            }
        }
        if (anOpposite) {
            anOffsetX += 90.0f * mScaleZombie;
        }

        aBodyReanim->mOverlayMatrix.m10 = 0.0f;
        aBodyReanim->mOverlayMatrix.m20 = 0.0f;
        aBodyReanim->mOverlayMatrix.m11 = 0.0f;
        aBodyReanim->mOverlayMatrix.m21 = 0.0f;
        float scaleMultiplier = 1.0f;
        float totalScale = mScaleZombie * scaleMultiplier;
        aBodyReanim->OverrideScale(totalScale, totalScale);
        aBodyReanim->SetPosition(anOffsetX + 30.0f - totalScale * 30.0f, anOffsetY + 120.0f - totalScale * 120.0f);
        if (anOpposite) {
            aBodyReanim->mOverlayMatrix.m00 = -totalScale;
        }

        Reanimation* aMoweredReanim = mApp->ReanimationTryToGet(mMoweredReanimID);
        if (aMoweredReanim) {
            aMoweredReanim->Update();

            SexyTransform2D aOverlayMatrix;
            aMoweredReanim->GetAttachmentOverlayMatrix(0, aOverlayMatrix);
            aOverlayMatrix.m00 *= aBodyReanim->mOverlayMatrix.m00;
            aOverlayMatrix.m10 *= aBodyReanim->mOverlayMatrix.m00;
            aOverlayMatrix.m01 *= aBodyReanim->mOverlayMatrix.m11;
            aOverlayMatrix.m11 *= aBodyReanim->mOverlayMatrix.m11;
            aOverlayMatrix.m02 *= aBodyReanim->mOverlayMatrix.m00;
            aOverlayMatrix.m12 *= aBodyReanim->mOverlayMatrix.m11;
            aOverlayMatrix.m02 += aBodyReanim->mOverlayMatrix.m11;
            aOverlayMatrix.m12 += aBodyReanim->mOverlayMatrix.m12;
            aBodyReanim->mOverlayMatrix = aOverlayMatrix;
        }
    }
}

void Zombie::UpdateReanimColor() {
    if (!IsOnBoard())
        return;

    Reanimation *aHeadReanim = mApp->ReanimationTryToGet(mSpecialHeadReanimID);
    if (aHeadReanim == nullptr)
        return;

    Color aColorOverride;
    if (mZombieType == ZombieType::ZOMBIE_EXPLODE_O_NUT_HEAD) {
        aColorOverride = Color(255, 64, 64);
        aHeadReanim->mColorOverride = aColorOverride;
    }
}

bool Zombie::IsImmobilizied() {
    return mIceTrapCounter > 0 || mButteredCounter > 0;
}

void Zombie::SetupLostArmReanim() {
    switch (mZombieType) {
        case ZombieType::ZOMBIE_FOOTBALL:
            ReanimShowPrefix("Zombie_football_leftarm_lower", -1);
            ReanimShowPrefix("Zombie_football_leftarm_hand", -1);
            break;
        case ZombieType::ZOMBIE_NEWSPAPER:
            ReanimShowTrack("Zombie_paper_hands", -1);
            ReanimShowTrack("Zombie_paper_leftarm_lower", -1);
            break;
        case ZombieType::ZOMBIE_POLEVAULTER:
            ReanimShowTrack("Zombie_polevaulter_outerarm_lower", -1);
            ReanimShowTrack("Zombie_outerarm_hand", -1);
            break;
        case ZombieType::ZOMBIE_DANCER:
            ReanimShowPrefix("Zombie_disco_outerarm_lower", -1);
            ReanimShowPrefix("Zombie_disco_outerhand_point", -1);
            ReanimShowPrefix("Zombie_disco_outerhand", -1);
            ReanimShowPrefix("Zombie_disco_outerarm_upper", -1);
            break;
        case ZombieType::ZOMBIE_BACKUP_DANCER:
            ReanimShowPrefix("Zombie_disco_outerarm_lower", -1);
            ReanimShowPrefix("Zombie_disco_outerhand", -1);
            break;
        case ZombieType::ZOMBIE_JACKSON:
            ReanimShowPrefix("Zombie_disco_outerarm_lower", -1);
            ReanimShowPrefix("Zombie_disco_outerhand_point", -1);
            ReanimShowPrefix("Zombie_disco_outerhand", -1);
            ReanimShowPrefix("Zombie_disco_outerarm_upper", -1);
            break;
        case ZombieType::ZOMBIE_BACKUP_DANCER2:
            ReanimShowPrefix("Zombie_disco_outerarm_lower", -1);
            ReanimShowPrefix("Zombie_disco_outerhand", -1);
            break;
        default:
            ReanimShowPrefix("Zombie_outerarm_lower", -1);
            ReanimShowPrefix("Zombie_outerarm_hand", -1);
            break;
    }
    Reanimation *reanimation = mApp->ReanimationTryToGet(mBodyReanimID);
    if (reanimation != nullptr) {
        switch (mZombieType) {
            case ZombieType::ZOMBIE_FOOTBALL:
                reanimation->SetImageOverride("zombie_football_leftarm_hand", *Sexy_IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_NEWSPAPER:
                reanimation->SetImageOverride("Zombie_paper_leftarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_POLEVAULTER:
                reanimation->SetImageOverride("Zombie_polevaulter_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_BALLOON:
                reanimation->SetImageOverride("zombie_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_IMP:
                reanimation->SetImageOverride("Zombie_imp_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE_Addr);
                break;
            case ZombieType::ZOMBIE_DIGGER:
                reanimation->SetImageOverride("Zombie_digger_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_BOBSLED:
                reanimation->SetImageOverride("Zombie_dolphinrider_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_JACK_IN_THE_BOX:
                reanimation->SetImageOverride("Zombie_jackbox_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2_Addr);
                break;
            case ZombieType::ZOMBIE_SNORKEL:
                reanimation->SetImageOverride("Zombie_snorkle_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_DOLPHIN_RIDER:
                reanimation->SetImageOverride("Zombie_dolphinrider_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_POGO:
                reanimation->SetImageOverride("Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2_Addr);
                reanimation->SetImageOverride("Zombie_pogo_stickhands", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2_Addr);
                reanimation->SetImageOverride("Zombie_pogo_stick", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2_Addr);
                reanimation->SetImageOverride("Zombie_pogo_stick2", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2_Addr);
                break;
            case ZombieType::ZOMBIE_FLAG: {
                reanimation->SetImageOverride("Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_Addr);
                Reanimation *reanimation2 = mApp->ReanimationTryToGet(mSpecialHeadReanimID);
                if (reanimation2 != nullptr) {
                    reanimation2->SetImageOverride("Zombie_flag", *Sexy_IMAGE_REANIM_ZOMBIE_FLAG3_Addr);
                }
                break;
            }
            case ZombieType::ZOMBIE_DANCER:
                reanimation->SetImageOverride("Zombie_disco_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_BACKUP_DANCER:
                reanimation->SetImageOverride("Zombie_disco_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_LADDER:
                reanimation->SetImageOverride("Zombie_ladder_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_YETI:
                reanimation->SetImageOverride("Zombie_yeti_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2_Addr);
                break;
            default:
                reanimation->SetImageOverride("Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_Addr);
                break;
        }
    }
}

void Zombie::PickRandomSpeed() {
    if (mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_IN_POOL) {
        mVelX = 0.3f;
    } else if (mZombiePhase == ZombiePhase::PHASE_DIGGER_WALKING) { // 矿工行走
        if (mApp->IsIZombieLevel()) {
            mVelX = 0.23f; // IZ模式
        } else {
            mVelX = 0.12f; // 一般模式
        }
    } else if (mZombieType == ZombieType::ZOMBIE_IMP && mApp->IsIZombieLevel()) { // IZ小鬼
        mVelX = 0.9f;
    } else if (mZombiePhase == ZombiePhase::PHASE_YETI_RUNNING) {
        mVelX = 0.8f;
    } else if (mZombieType == ZombieType::ZOMBIE_YETI) {
        mVelX = 0.4f;
    } else if (mZombieType == ZombieType::ZOMBIE_DANCER || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER || mZombieType == ZombieType::ZOMBIE_POGO || mZombieType == ZombieType::ZOMBIE_FLAG
               || mZombiePhase == ZombiePhase::PHASE_IMP_RUNNING || mZombieType == ZombieType::ZOMBIE_JACKSON || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
        mVelX = 0.45f;
    } else if (mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING || mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_PRE_VAULT || mZombieType == ZombieType::ZOMBIE_FOOTBALL
               || mZombieType == ZombieType::ZOMBIE_SNORKEL || mZombieType == ZombieType::ZOMBIE_JACK_IN_THE_BOX) {
        mVelX = RandRangeFloat(0.66f, 0.68f);
    } else if (mZombiePhase == ZombiePhase::PHASE_LADDER_CARRYING || mZombieType == ZombieType::ZOMBIE_SQUASH_HEAD) {
        mVelX = RandRangeFloat(0.79f, 0.81f);
    } else if (mZombiePhase == ZombiePhase::PHASE_NEWSPAPER_MAD || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_WITHOUT_DOLPHIN
               || mZombiePhase == ZombiePhase::PHASE_FOOTBALL_CHARGING) {
        mVelX = RandRangeFloat(0.89f, 0.91f);
    } else if (IsFlying()) {
        if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
            mVelX = 0.3f;
        }
    } else {
        mVelX = RandRangeFloat(0.23f, 0.37f); // 普僵
        if (mVelX < 0.3f) {
            mAnimTicksPerFrame = 12;
        } else {
            mAnimTicksPerFrame = 15;
        }
    }

    UpdateAnimSpeed();
}

float Zombie::ZombieTargetLeadX(float theTime) {
    float aSpeed = mVelX;
    if (mChilledCounter > 0) {
        aSpeed *= CHILLED_SPEED_FACTOR;
    }
    if (IsWalkingBackwards()) {
        aSpeed = -aSpeed;
    }
    if (ZombieNotWalking()) {
        aSpeed = 0.0f;
    }

    Rect aZombieRect = GetZombieRect();
    float aCurrentPosX = aZombieRect.mX + aZombieRect.mWidth / 2;
    float aDisplacementX = aSpeed * theTime;
    return aCurrentPosX - aDisplacementX;
}

void Zombie::ApplyBurn() {
    if (mDead || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_BURNED)
        return;

    if (mBodyHealth >= 1800 || mZombieType == ZombieType::ZOMBIE_BOSS) {
        TakeDamage(1800, 18U);
        return;
    }

    if (mZombieType == ZombieType::ZOMBIE_SQUASH_HEAD && !mHasHead) {
        mApp->RemoveReanimation(mSpecialHeadReanimID);
        mSpecialHeadReanimID = ReanimationID::REANIMATIONID_NULL;
    }

    if (mIceTrapCounter > 0) {
        RemoveIceTrap();
    }
    if (mButteredCounter > 0) {
        mButteredCounter = 0;
    }

    AttachmentDetachCrossFadeParticleType(mAttachmentID, ParticleEffect::PARTICLE_ZAMBONI_SMOKE, nullptr);
    BungeeDropPlant();

    if (mZombiePhase == ZombiePhase::PHASE_ZOMBIE_DYING || mZombiePhase == ZombiePhase::PHASE_POLEVAULTER_IN_VAULT || mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_THROWN
        || mZombiePhase == ZombiePhase::PHASE_RISING_FROM_GRAVE || mZombiePhase == ZombiePhase::PHASE_DANCER_RISING || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_INTO_POOL
        || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_IN_JUMP || mZombiePhase == ZombiePhase::PHASE_DOLPHIN_RIDING || mZombiePhase == ZombiePhase::PHASE_SNORKEL_INTO_POOL
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING || mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISING
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISE_WITHOUT_AXE || mZombiePhase == ZombiePhase::PHASE_ZOMBIE_MOWERED || mInPool) {
        DieWithLoot();
    } else if (mZombieType == ZOMBIE_BUNGEE || mZombieType == ZOMBIE_YETI || Zombie::IsZombotany(mZombieType) || IsBobsledTeamWithSled() || IsFlying() || !mHasHead) {
        SetAnimRate(0.0f);
        Reanimation *aHeadReanim = mApp->ReanimationTryToGet(mSpecialHeadReanimID);
        if (aHeadReanim) {
            aHeadReanim->mAnimRate = 0.0f;
        }

        mZombiePhase = ZombiePhase::PHASE_ZOMBIE_BURNED;
        mPhaseCounter = 300;
        mJustGotShotCounter = 0;
        DropLoot();

        if (mZombieType == ZombieType::ZOMBIE_BALLOON) {
            BalloonPropellerHatSpin(false);
        }
    } else {
        ReanimationType aReanimType = ReanimationType::REANIM_ZOMBIE_CHARRED;
        float aCharredPosX = mPosX + 22.0f;
        float aCharredPosY = mPosY - 10.0f;
        if (mZombieType == ZombieType::ZOMBIE_BALLOON) {
            aCharredPosY += 31.0f;
        }
        if (mZombieType == ZombieType::ZOMBIE_IMP || mZombieType == ZombieType::ZOMBIE_SUPER_FAN_IMP) {
            aCharredPosX -= 6.0f;
            aReanimType = ReanimationType::REANIM_ZOMBIE_CHARRED_IMP;
        }
        if (mZombieType == ZombieType::ZOMBIE_DIGGER) {
            if (IsWalkingBackwards()) {
                aCharredPosX += 14.0f;
            }
            aReanimType = ReanimationType::REANIM_ZOMBIE_CHARRED_DIGGER;
        }
        if (mZombieType == ZombieType::ZOMBIE_ZAMBONI) {
            aReanimType = ReanimationType::REANIM_ZOMBIE_CHARRED_ZAMBONI;
            aCharredPosX += 61.0f;
            aCharredPosY -= 16.0f;
        }
        if (mZombieType == ZombieType::ZOMBIE_CATAPULT) {
            aReanimType = ReanimationType::REANIM_ZOMBIE_CHARRED_CATAPULT;
            aCharredPosX -= 36.0f;
            aCharredPosY -= 20.0f;
        }
        if (mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR) {
            aReanimType = ReanimationType::REANIM_ZOMBIE_CHARRED_GARGANTUAR;
            aCharredPosX -= 15.0f;
            aCharredPosY -= 10.0f;
        }

        Reanimation *aCharredReanim = mApp->AddReanimation(aCharredPosX, aCharredPosY, mRenderOrder, aReanimType);
        aCharredReanim->mAnimRate *= RandRangeFloat(0.9f, 1.1f);
        if (mZombiePhase == ZombiePhase::PHASE_DIGGER_WALKING_WITHOUT_AXE) {
            aCharredReanim->SetFramesForLayer("anim_crumble_noaxe");
        } else if (mZombieType == ZombieType::ZOMBIE_DIGGER) {
            aCharredReanim->SetFramesForLayer("anim_crumble");
        } else if ((mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR) && !mHasObject) {
            aCharredReanim->SetImageOverride("impblink", *IMAGE_BLANK);
            aCharredReanim->SetImageOverride("imphead", *IMAGE_BLANK);
        }

        if (mScaleZombie != 1.0f) {
            aCharredReanim->mOverlayMatrix.m00 = mScaleZombie;
            aCharredReanim->mOverlayMatrix.m11 = mScaleZombie;
            aCharredReanim->mOverlayMatrix.m02 += 20.0f - mScaleZombie * 20.0f;
            aCharredReanim->mOverlayMatrix.m12 += 120.0f - mScaleZombie * 120.0f;
            aCharredReanim->OverrideScale(mScaleZombie, mScaleZombie);
        }

        if (IsWalkingBackwards()) {
            aCharredReanim->OverrideScale(-mScaleZombie, mScaleZombie);
            aCharredReanim->mOverlayMatrix.m02 += 60.0f * mScaleZombie;
        }

        DieWithLoot();
    }

    if (mZombieType == ZombieType::ZOMBIE_BOBSLED) {
        BobsledBurn();
    }
}

bool Zombie::ZombieNotWalking() {
    if (mIsEating || IsImmobilizied()) {
        return true;
    }

    if (mZombiePhase == ZombiePhase::PHASE_JACK_IN_THE_BOX_POPPING || mZombiePhase == ZombiePhase::PHASE_NEWSPAPER_MADDENING || mZombiePhase == ZombiePhase::PHASE_GARGANTUAR_THROWING
        || mZombiePhase == ZombiePhase::PHASE_GARGANTUAR_SMASHING || mZombiePhase == ZombiePhase::PHASE_CATAPULT_LAUNCHING || mZombiePhase == ZombiePhase::PHASE_CATAPULT_RELOADING
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISING || mZombiePhase == ZombiePhase::PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE || mZombiePhase == ZombiePhase::PHASE_DIGGER_RISE_WITHOUT_AXE
        || mZombiePhase == ZombiePhase::PHASE_DIGGER_STUNNED || mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS || mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT
        || mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_HOLD || mZombiePhase == ZombiePhase::PHASE_DANCER_RISING || mZombiePhase == ZombiePhase::PHASE_IMP_GETTING_THROWN
        || mZombiePhase == ZombiePhase::PHASE_IMP_LANDING || mZombiePhase == ZombiePhase::PHASE_LADDER_PLACING || mZombieHeight == ZombieHeight::HEIGHT_IN_TO_CHIMNEY
        || mZombieHeight == ZombieHeight::HEIGHT_GETTING_BUNGEE_DROPPED || mZombieHeight == ZombieHeight::HEIGHT_ZOMBIQUARIUM || mZombieType == ZombieType::ZOMBIE_BUNGEE
        || mZombieType == ZombieType::ZOMBIE_BOSS || mZombiePhase == ZombiePhase::PHASE_DANCER_RAISE_LEFT_1 || mZombiePhase == ZombiePhase::PHASE_DANCER_WALK_TO_RAISE
        || mZombiePhase == ZombiePhase::PHASE_DANCER_RAISE_RIGHT_1 || mZombiePhase == ZombiePhase::PHASE_DANCER_RAISE_LEFT_2 || mZombiePhase == ZombiePhase::PHASE_DANCER_RAISE_RIGHT_2) {
        return true;
    }

    if (mZombieType == ZombieType::ZOMBIE_DANCER || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER) {
        Zombie *aLeader = nullptr;
        if (mZombieType == ZombieType::ZOMBIE_DANCER) {
            aLeader = this;
        } else {
            aLeader = mBoard->ZombieTryToGet(mRelatedZombieID);
        }

        if (aLeader) {
            if (aLeader->IsImmobilizied() || aLeader->mIsEating) {
                return true;
            }

            for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
                Zombie *aDancer = mBoard->ZombieTryToGet(aLeader->mFollowerZombieID[i]);
                if (aDancer && (aDancer->IsImmobilizied() || aDancer->mIsEating)) {
                    return true;
                }
            }
        }
    }

    if (mZombieType == ZombieType::ZOMBIE_JACKSON || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
        Zombie *aLeader = nullptr;
        if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
            aLeader = this;
        } else {
            aLeader = mBoard->ZombieTryToGet(mRelatedZombieID);
        }

        if (aLeader) {
            if (aLeader->IsImmobilizied() || aLeader->mIsEating) {
                return true;
            }

            for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
                Zombie *aDancer = mBoard->ZombieTryToGet(aLeader->mFollowerZombieID[i]);
                if (aDancer && (aDancer->IsImmobilizied() || aDancer->mIsEating)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Zombie::IsMovingAtChilledSpeed() {
    if (mChilledCounter > 0)
        return true;

    if (mZombieType == ZombieType::ZOMBIE_DANCER || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER) {
        Zombie *aLeader;
        if (mZombieType == ZombieType::ZOMBIE_DANCER) {
            aLeader = this;
        } else {
            aLeader = mBoard->ZombieTryToGet(mRelatedZombieID);
        }

        if (aLeader && !aLeader->IsDeadOrDying()) {
            if (aLeader->mChilledCounter > 0) {
                return true;
            }

            for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
                Zombie *aDancer = mBoard->ZombieTryToGet(aLeader->mFollowerZombieID[i]);
                if (aDancer && !aDancer->IsDeadOrDying() && aDancer->mChilledCounter > 0) {
                    return true;
                }
            }
        }
    }

    if (mZombieType == ZombieType::ZOMBIE_JACKSON || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
        Zombie *aLeader;
        if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
            aLeader = this;
        } else {
            aLeader = mBoard->ZombieTryToGet(mRelatedZombieID);
        }

        if (aLeader && !aLeader->IsDeadOrDying()) {
            if (aLeader->mChilledCounter > 0) {
                return true;
            }

            for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
                Zombie *aDancer = mBoard->ZombieTryToGet(aLeader->mFollowerZombieID[i]);
                if (aDancer && !aDancer->IsDeadOrDying() && aDancer->mChilledCounter > 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Zombie::UpdateZombieWalking() {
    if (mZombieType > ZombieType::NUM_ZOMBIE_TYPES) {
        if (ZombieNotWalking())
            return;

        Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);

        if (aBodyReanim) {
            float aSpeed;
            aSpeed = mVelX;
            if (IsMovingAtChilledSpeed())
            {
                aSpeed *= CHILLED_SPEED_FACTOR;
            }

            if (mZombieType == ZombieType::ZOMBIE_JACKSON || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER2) {
                Zombie *aLeader;
                if (mZombieType == ZombieType::ZOMBIE_JACKSON) {
                    aLeader = this;
                } else {
                    aLeader = mBoard->ZombieTryToGet(mRelatedZombieID);
                }

                if (aLeader && !aLeader->IsDeadOrDying()) {
                    if (aLeader->IsImmobilizied() || aLeader->mIsEating || aLeader->mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS
                        || aLeader->mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT || aLeader->mZombiePhase == ZombiePhase::PHASE_DANCER_SNAPPING_FINGERS_HOLD) {
                        aSpeed = 0;
                    }

                    for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
                        Zombie *aDancer = mBoard->ZombieTryToGet(aLeader->mFollowerZombieID[i]);
                        if (aDancer && aDancer != this && !aDancer->IsDeadOrDying()) {
                            if (aDancer->ZombieNotWalking())
                                aSpeed = 0;
                        }
                    }
                }
            }

            if (aSpeed == 0) {
                if (IsWalkingBackwards()) {
                    mPosX += aSpeed;
                } else {
                    mPosX -= aSpeed;
                }
                return;
            }
        }
    }

    old_Zombie_UpdateZombieWalking(this);
}

ZombiePhase Zombie::GetDancerPhase() {
    int aFrame = GetDancerFrame();

    return aFrame <= 11 || aFrame > 21 ? ZombiePhase::PHASE_DANCER_DANCING_LEFT
        : aFrame <= 12                 ? ZombiePhase::PHASE_DANCER_WALK_TO_RAISE
        : aFrame <= 15                 ? ZombiePhase::PHASE_DANCER_RAISE_RIGHT_1
        : aFrame <= 18                 ? ZombiePhase::PHASE_DANCER_RAISE_LEFT_1
        : aFrame <= 21                 ? ZombiePhase::PHASE_DANCER_RAISE_RIGHT_2
                                       : ZombiePhase::PHASE_DANCER_RAISE_LEFT_2;
}

ZombieID Zombie::SummonBackupDancer(int theRow, int thePosX) {
    if (!mBoard->RowCanHaveZombieType(theRow, ZombieType::ZOMBIE_BACKUP_DANCER2))
        return ZombieID::ZOMBIEID_NULL;

    Zombie *aZombie = mBoard->AddZombie(ZombieType::ZOMBIE_BACKUP_DANCER2, mFromWave, false);
    if (aZombie == nullptr)
        return ZombieID::ZOMBIEID_NULL;

    aZombie->mPosX = thePosX;
    aZombie->mPosY = GetPosYBasedOnRow(theRow);
    aZombie->SetRow(theRow);
    aZombie->mX = (int)aZombie->mPosX;
    aZombie->mY = (int)aZombie->mPosY;

    aZombie->mAltitude = ZOMBIE_BACKUP_DANCER_RISE_HEIGHT;
    aZombie->mZombiePhase = ZombiePhase::PHASE_DANCER_RISING;
    aZombie->mPhaseCounter = 150;
    aZombie->mRelatedZombieID = mBoard->ZombieGetID(this);

    aZombie->SetAnimRate(0.0f);
    aZombie->mMindControlled = mMindControlled;

    int aParticleX = (int)aZombie->mPosX + 60;
    int aParticleY = (int)aZombie->mPosY + 110;
    if (aZombie->IsOnHighGround()) {
        aParticleY -= HIGH_GROUND_HEIGHT;
    }
    int aRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_PARTICLE, theRow, 0);
    mApp->AddTodParticle(aParticleX, aParticleY, aRenderOrder, ParticleEffect::PARTICLE_DANCER_RISE);
    mApp->PlayFoley(FoleyType::FOLEY_GRAVESTONE_RUMBLE);

    return mBoard->ZombieGetID(aZombie);
}

void Zombie::SummonBackupDancers() {
    if (!mHasHead)
        return;

    for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
        Zombie *aZombie = mBoard->ZombieTryToGet(mFollowerZombieID[i]);
        if (aZombie == nullptr || aZombie && aZombie->IsDeadOrDying()) {
            int aRow, aPosX;
            switch (i) {
                case 0:
                    aRow = mRow - 1;
                    aPosX = mPosX;
                    break;
                case 1:
                    aRow = mRow + 1;
                    aPosX = mPosX;
                    break;
                case 2:
                    aRow = mRow;
                    aPosX = mPosX - 100;
                    break;
                case 3:
                    aRow = mRow;
                    aPosX = mPosX + 100;
                    break;
                default:
                    break;
            }

            mFollowerZombieID[i] = SummonBackupDancer(aRow, aPosX);
        }
    }
}

void Zombie::RaiseDeadZombie(ZombieType theZombieType, int theRow, int thePosX) {
    if (!mBoard->RowCanHaveZombieType(theRow, theZombieType))
        return;

    int aGridX = mBoard->PixelToGridXKeepOnBoard((int)thePosX, (int)theRow);
    Zombie *aZombie = mBoard->AddZombie(theZombieType, mFromWave, false);
    if (aZombie == nullptr)
        return;

    aZombie->RiseFromGrave(aGridX, theRow);
    aZombie->mBodyHealth = aZombie->mBodyMaxHealth * 2 / 3;
    if (aZombie->mHelmHealth > 0) {
        aZombie->TakeHelmDamage(aZombie->mHelmMaxHealth * 2 / 3 + 2, 0U);
    }
    if (aZombie->mShieldHealth > 0) {
        aZombie->TakeShieldDamage(aZombie->mShieldMaxHealth * 2 / 3 + 2, 0U);
    }
    aZombie->mIsRevived = true;
    aZombie->mHasArm = false;
    aZombie->SetupLostArmReanim();
}

void Zombie::RaiseDeadZombies() {
    for (int i = 0; i < gDeadFollowers.size(); i++) {
        if (!gDeadFollowers.empty()) {
            int aRow, aPosX;
            if (i < 5) {
                aRow = i;
                aPosX = mPosX;
            } else if (i < 10) {
                aRow = i - 5;
                aPosX = mPosX + 100;
            } else {
                aRow = i - 10;
                aPosX = mPosX + 200;
            }

            RaiseDeadZombie(gDeadFollowers[i], aRow, aPosX);
        }
    }
    gDeadFollowers.clear();

    Projectile *aProjectile = nullptr;
    while (mBoard->IterateProjectiles(aProjectile)) {
        if (aProjectile->mProjectileType == ProjectileType::PROJCTILE_ZOMBIE_SOUL) {
            aProjectile->mTargetZombieID = ZOMBIEID_NULL;
        }
    }
}

bool Zombie::NeedsMoreBackupDancers() {
    for (int i = 0; i < NUM_BACKUP_DANCERS; i++) {
        Zombie *aZombie = mBoard->ZombieTryToGet(mFollowerZombieID[i]);
        if (aZombie == nullptr) {
            if (i == 0 && !mBoard->RowCanHaveZombieType(mRow - 1, ZombieType::ZOMBIE_BACKUP_DANCER2)) {
                continue;
            }

            if (i == 1 && !mBoard->RowCanHaveZombieType(mRow + 1, ZombieType::ZOMBIE_BACKUP_DANCER2)) {
                continue;
            }

            if (i == 2 && mX < 100) {
                continue;
            }

            if (i == 3 && mMindControlled && mX > 700) {
                continue;
            }

            return true;
        }
    }

    return false;
}

void Zombie::DropLoot() {
    old_Zombie_DropLoot(this);
}

bool Zombie::CanDropSoul() {
    if (mIsRevived) // 复生的僵尸不掉落灵魂
        return false;

    return mZombieType != ZombieType::ZOMBIE_JACKSON &&  mZombieType != ZombieType::ZOMBIE_DANCER && mZombieType != ZombieType::ZOMBIE_ZAMBONI && mZombieType != ZombieType::ZOMBIE_CATAPULT
        && mZombieType != ZombieType::ZOMBIE_GARGANTUAR && mZombieType != ZombieType::ZOMBIE_REDEYE_GARGANTUAR && mZombieType != ZombieType::ZOMBIE_BALLOON && mZombieType != ZombieType::ZOMBIE_BUNGEE
        && mZombieType != ZombieType::ZOMBIE_DIGGER;
}

void Zombie::DropSoul() {
    if (!IsOnBoard() || !CanDropSoul())
        return;

    Zombie *aZombie = mBoard->GetLiveZombieByType(ZombieType::ZOMBIE_JACKSON);
    if (aZombie) {
        Rect aZombieRect = GetZombieRect();
        int aCenterX = aZombieRect.mX + aZombieRect.mWidth / 2;
        int aCenterY = aZombieRect.mY + aZombieRect.mHeight / 4;
        if (gDeadFollowers.size() < MAX_DEAD_FOLLOWERS) {
            Projectile *aSoul = mBoard->AddProjectile(aCenterX, aCenterY, mRenderOrder, mRow, ProjectileType::PROJCTILE_ZOMBIE_SOUL);
            aSoul->mTargetZombieID = mBoard->ZombieGetID(aZombie);
        }

        if (gDeadFollowers.size() < MAX_DEAD_FOLLOWERS) {
            gDeadFollowers.push_back(mZombieType);
        }
    }
}

bool Zombie::IsUpgrade(SeedType theSeedType) {
    return theSeedType == SeedType::SEED_ZOMBIE_GIGA_FOOTBALL || theSeedType == SeedType::SEED_ZOMBIE_SUPER_FAN_IMP || theSeedType == SeedType::SEED_ZOMBIE_JACKSON || theSeedType == SeedType::SEED_ZOMBIE_BACKUP_DANCER2;
}

void Zombie::JacksonDie() {
    if (!IsOnBoard())
        return;

    mBoard->SetDanceMode(false);
    mApp->mSoundSystem->StopFoley(FoleyType::FOLEY_DANCER);

    gDeadFollowers.clear();
}

bool Zombie::CanDance() {
    return mZombieType == ZombieType::ZOMBIE_NORMAL || mZombieType == ZombieType::ZOMBIE_TRAFFIC_CONE || mZombieType == ZombieType::ZOMBIE_PAIL;
}

void Zombie::SetDanceRow() {
    if (!CanDance() || mIsEating)
        return;

    StartWalkAnim(20);

    bool aCanGoUp = true;
    bool aCanGoDown = true;
    bool aIsPool = mBoard->mPlantRow[mRow] == PlantRowType::PLANTROW_POOL;
    if (!mBoard->RowCanHaveZombies(mRow - 1)) {
        aCanGoUp = false;
    } else if (mBoard->mPlantRow[mRow - 1] == PlantRowType::PLANTROW_POOL && !aIsPool) {
        aCanGoUp = false;
    } else if (mBoard->mPlantRow[mRow - 1] != PlantRowType::PLANTROW_POOL && aIsPool) {
        aCanGoUp = false;
    }
    if (!mBoard->RowCanHaveZombies(mRow + 1)) {
        aCanGoDown = false;
    } else if (mBoard->mPlantRow[mRow + 1] == PlantRowType::PLANTROW_POOL && !aIsPool) {
        aCanGoDown = false;
    } else if (mBoard->mPlantRow[mRow + 1] != PlantRowType::PLANTROW_POOL && aIsPool) {
        aCanGoDown = false;
    }

    if (aCanGoDown && !aCanGoUp) {
        SetRow(mRow + 1);
    } else if (!aCanGoDown && aCanGoUp) {
        SetRow(mRow - 1);
    } else if (aCanGoDown && aCanGoUp) {
        SetRow((Rand(2) == 0) ? (mRow + 1) : (mRow - 1));
    }
}