#include "PvZ/Lawn/Challenge.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/Android/IntroVideo.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/GridItem.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Plant.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/Zombie.h"
#include "PvZ/Lawn/SeedPacket.h"

#include <cstddef>

Challenge::Challenge() {
    Create();
}


void Challenge::Create() {
    if (requestJumpSurvivalStage) {
        // 如果玩家按了无尽跳关
        if (mSurvivalStage > 0 || mApp->mGameScene == GameScenes::SCENE_PLAYING) {
            // 需要玩家至少已完成选种子，才能跳关。否则有BUG
            mSurvivalStage = targetWavesToJump;
        }
        requestJumpSurvivalStage = false;
    }

    old_Challenge_Challenge(this);
}


void Challenge::Update() {
    if (requestJumpSurvivalStage) {
        // 如果玩家按了无尽跳关
        if (mSurvivalStage > 0 || mApp->mGameScene == GameScenes::SCENE_PLAYING) {
            // 需要玩家至少已完成选种子，才能跳关。否则有BUG
            mSurvivalStage = targetWavesToJump;
        }
        requestJumpSurvivalStage = false;
    }

    GameMode gameMode = mApp->mGameMode;
    if (gameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || gameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) {
        TutorialState mTutorialState = mBoard->mTutorialState;
        if (mTutorialState == TutorialState::TUTORIAL_ZEN_GARDEN_PICKUP_WATER || mTutorialState == TutorialState::TUTORIAL_ZEN_GARDEN_WATER_PLANT
            || mTutorialState == TutorialState::TUTORIAL_ZEN_GARDEN_KEEP_WATERING) {
            mBoardMenuButton->mBtnNoDraw = true;
            mBoardStoreButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = true;
            mBoardMenuButton->mDisabled = true;
        } else if (mApp->mCrazyDaveState != CrazyDaveState::CRAZY_DAVE_OFF) {
            mBoardStoreButton->mBtnNoDraw = true;
            mBoardMenuButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = true;
            mBoardMenuButton->mDisabled = true;
        } else if (mTutorialState == TutorialState::TUTORIAL_ZEN_GARDEN_VISIT_STORE) {
            mBoardStoreButton->mBtnNoDraw = false;
            mBoardMenuButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = false;
            mBoardMenuButton->mDisabled = true;
        } else {
            mBoardStoreButton->mBtnNoDraw = false;
            mBoardMenuButton->mBtnNoDraw = false;
            mBoardStoreButton->mDisabled = false;
            mBoardMenuButton->mDisabled = false;
        }
    }

    if (requestPause) {
        return;
    }

    return old_Challenge_Update(this);
}


void Challenge::HeavyWeaponFire(float a2, float a3) {
    // 设定重型武器子弹的发射角度
    if (a2 == 0 && a3 == 1) {
        a2 = angle1;
        a3 = angle2;
    }
    return old_Challenge_HeavyWeaponFire(this, a2, a3);
}

void Challenge_HeavyWeaponReanimUpdate(Challenge *challenge) {
    Reanimation *heavyWeaponReanim = LawnApp_ReanimationTryToGet(challenge->mApp, challenge->mReanimHeavyWeaponID2);
    if (heavyWeaponReanim == nullptr)
        return;
    SexyTransform2D sexyTransform2D;
    Sexy_SexyTransform2D_SexyTransform2D(&sexyTransform2D);
    Sexy_SexyTransform2D_Translate(&sexyTransform2D, -129.55, -71.45);
    Sexy_SexyTransform2D_RotateRad(&sexyTransform2D, challenge->mHeavyWeaponAngle);
    Sexy_SexyTransform2D_Translate(&sexyTransform2D, challenge->mHeavyWeaponX, challenge->mHeavyWeaponY);
    Sexy_SexyTransform2D_Translate(&sexyTransform2D, 129.55, 71.45);
    Sexy_SexyTransform2D_Translate(&sexyTransform2D, 0.0, -20.0);
    heavyWeaponReanim->mOverlayMatrix = sexyTransform2D;
}

void Challenge::HeavyWeaponUpdate() {
    // 设定重型武器动画的发射角度
    old_Challenge_HeavyWeaponUpdate(this);

    if (angle1 != 0) {
        mHeavyWeaponAngle = acosf(angle1) - 1.5708f;
        Challenge_HeavyWeaponReanimUpdate(this);
    }
}

void Challenge::IZombieDrawPlant(Sexy::Graphics* g, Plant* thePlant) {
    // 参照PC内测版源代码，在IZ模式绘制植物的函数开始前额外绘制纸板效果。

    Reanimation *mBodyReanim = LawnApp_ReanimationTryToGet(mApp, thePlant->mBodyReanimID);
    if (mBodyReanim != nullptr) {
        Challenge_IZombieSetPlantFilterEffect(this, thePlant, FilterEffectType::FILTEREFFECT_WHITE);
        float aOffsetX = g->mTransX;
        float aOffsetY = g->mTransY;
        Color theColor;
        Sexy_Graphics_SetColorizeImages(g, true);

        g->mTransX = aOffsetX + 4.0;
        g->mTransY = aOffsetY + 4.0;
        theColor.mRed = 122;
        theColor.mGreen = 86;
        theColor.mBlue = 58;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(g, &theColor);
        Reanimation_DrawRenderGroup(mBodyReanim, g, 0);

        g->mTransX = aOffsetX + 2.0;
        g->mTransY = aOffsetY + 2.0;
        theColor.mRed = 171;
        theColor.mGreen = 135;
        theColor.mBlue = 107;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(g, &theColor);
        Reanimation_DrawRenderGroup(mBodyReanim, g, 0);

        g->mTransX = aOffsetX - 2.0;
        g->mTransY = aOffsetY - 2.0;
        theColor.mRed = 171;
        theColor.mGreen = 135;
        theColor.mBlue = 107;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(g, &theColor);
        Reanimation_DrawRenderGroup(mBodyReanim, g, 0);

        g->mTransX = aOffsetX;
        g->mTransY = aOffsetY;
        theColor.mRed = 255;
        theColor.mGreen = 201;
        theColor.mBlue = 160;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(g, &theColor);
        Challenge_IZombieSetPlantFilterEffect(this, thePlant, FilterEffectType::FILTEREFFECT_NONE);
        Reanimation_DrawRenderGroup(mBodyReanim, g, 0);

        Challenge_IZombieSetPlantFilterEffect(this, thePlant, FilterEffectType::FILTEREFFECT_NONE);
        Sexy_Graphics_SetDrawMode(g, DrawMode::DRAWMODE_NORMAL);
        Sexy_Graphics_SetColorizeImages(g, false);
    }
}

bool Challenge::IZombieEatBrain(Zombie* theZombie) {
    // 修复IZ脑子血量太高
    GridItem* aBrain = Challenge_IZombieGetBrainTarget(this, theZombie);
    if (aBrain == nullptr)
        return false;

    Zombie_StartEating(theZombie);
    //    int mHealth = aBrain->mGridItemCounter - 1;
    int mHealth = aBrain->mGridItemCounter - 2; // 一次吃掉脑子的两滴血
    aBrain->mGridItemCounter = mHealth;
    if (mHealth <= 0) {
        LawnApp_PlaySample(mApp, *Sexy_SOUND_GULP_Addr);
        GridItem_GridItemDie(aBrain);
        Challenge_IZombieScoreBrain(this, aBrain);
    }
    return true;
}

void Challenge::DrawArtChallenge(Sexy::Graphics* g) {
    // 绘制坚果的两只大眼睛
    Sexy_Graphics_SetColorizeImages(g, true);
    Color theColor = {255, 255, 255, 100};
    Sexy_Graphics_SetColor(g, &theColor);

    for (int theGridY = 0; theGridY < 6; theGridY++) {
        for (int theGridX = 0; theGridX < 9; theGridX++) {
            SeedType ArtChallengeSeed = Challenge_GetArtChallengeSeed(this, theGridX, theGridY);
            if (ArtChallengeSeed != SeedType::SEED_NONE && Board_GetTopPlantAt(mBoard, theGridX, theGridY, PlantPriority::TOPPLANT_ONLY_NORMAL_POSITION) == nullptr) {
                int x = Board_GridToPixelX(mBoard, theGridX, theGridY);
                int y = Board_GridToPixelY(mBoard, theGridX, theGridY);
                Plant::DrawSeedType(g, ArtChallengeSeed, SeedType::SEED_NONE, DrawVariation::VARIATION_NORMAL, x, y);
            }
        }
    }

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT) {
        Color theColor = {255, 255, 255, 255};
        Sexy_Graphics_SetColor(g, &theColor);
        int x1 = Board_GridToPixelX(mBoard, 4, 1);
        int y1 = Board_GridToPixelY(mBoard, 4, 1);
        Sexy_Graphics_DrawImage(g, addonImages.googlyeye, x1, y1);
        int x2 = Board_GridToPixelX(mBoard, 6, 1);
        int y2 = Board_GridToPixelY(mBoard, 6, 1);
        Sexy_Graphics_DrawImage(g, addonImages.googlyeye, x2, y2);
    }

    Sexy_Graphics_SetColorizeImages(g, false);
}

PlantingReason Challenge::CanPlantAt(int theGridX, int theGridY, SeedType theSeedType) {
    // 修复IZ多个蹦极可放置在同一格子内
    GameMode mGameMode = mApp->mGameMode;
    if (LawnApp_IsWallnutBowlingLevel(mApp)) {
        if (theGridX > 2) {
            return PlantingReason::PLANTING_NOT_PASSED_LINE;
        }
    } else if (LawnApp_IsIZombieLevel(mApp)) {
        int num = 6;
        if (mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_2 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_3
            || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_4 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_5) {
            num = 4;
        }
        if (mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_6 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_7 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_8
            || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS) {
            num = 5;
        }
        if (theSeedType == SeedType::SEED_ZOMBIE_BUNGEE) {
            if (theGridX < num) {
                Zombie *zombie = nullptr;
                while (Board_IterateZombies(mBoard, &zombie)) {
                    if (zombie->mZombieType == ZombieType::ZOMBIE_BUNGEE) {
                        int mGridX = Board_PixelToGridX(mBoard, zombie->mX, zombie->mY);
                        if (mGridX == theGridX && zombie->mRow == theGridY) {
                            return PlantingReason::PLANTING_NOT_HERE;
                        }
                    }
                }
                return PlantingReason::PLANTING_OK;
            }
            return PlantingReason::PLANTING_NOT_HERE;
        } else if (Challenge_IsZombieSeedType(theSeedType)) {
            if (theGridX >= num) {
                return PlantingReason::PLANTING_OK;
            }
            return PlantingReason::PLANTING_NOT_HERE;
        }
    } else if (LawnApp_IsArtChallenge(mApp)) {
        SeedType artChallengeSeed = Challenge_GetArtChallengeSeed(this, theGridX, theGridY);
        if (artChallengeSeed != SeedType::SEED_NONE && artChallengeSeed != theSeedType && theSeedType != SeedType::SEED_LILYPAD && theSeedType != SeedType::SEED_PUMPKINSHELL) {
            return PlantingReason::PLANTING_NOT_ON_ART;
        }
        if (mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT) {
            if (theGridX == 4 && theGridY == 1) {
                return PlantingReason::PLANTING_NOT_HERE;
            }
            if (theGridX == 6 && theGridY == 1) {
                return PlantingReason::PLANTING_NOT_HERE;
            }
        }
    } else if (LawnApp_IsFinalBossLevel(mApp) && theGridX >= 8) {
        return PlantingReason::PLANTING_NOT_HERE;
    } else if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS_HIDE || mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        if (Challenge_IsMPSeedType(theSeedType)) {
            if (theGridX > 5 || theSeedType == SeedType::SEED_ZOMBIE_BUNGEE)
                return PlantingReason::PLANTING_OK;
            return PlantingReason::PLANTING_NOT_PASSED_LINE_VS;
        }
        if (theSeedType == SeedType::SEED_GRAVEBUSTER) {
            if (Board_GetGridItemAt(mBoard, GridItemType::GRIDITEM_GRAVESTONE, theGridX, theGridY) == nullptr)
                return PlantingReason::PLANTING_ONLY_ON_GRAVES;
        } else {
            if (theGridX <= 5)
                return PlantingReason::PLANTING_OK;
            return PlantingReason::PLANTING_NOT_PASSED_LINE_VS;
        }
    }
    return PlantingReason::PLANTING_OK;
}

void Challenge::InitLevel() {
    old_Challenge_InitLevel(this);

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        Board_NewPlant(mBoard, 0, 0, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
        Board_NewPlant(mBoard, 0, 1, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
        Board_NewPlant(mBoard, 0, 4, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
        Board_NewPlant(mBoard, 0, 5, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
    }
}

void Challenge::InitZombieWaves() {
    old_Challenge_InitZombieWaves(this);

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        ZombieType zombieList[] = {ZombieType::ZOMBIE_NORMAL,
                                   ZombieType::ZOMBIE_TRAFFIC_CONE,
                                   ZombieType::ZOMBIE_PAIL,
                                   ZombieType::ZOMBIE_DOOR,
                                   ZombieType::ZOMBIE_FOOTBALL,
                                   ZombieType::ZOMBIE_NEWSPAPER,
                                   ZombieType::ZOMBIE_JACK_IN_THE_BOX,
                                   ZombieType::ZOMBIE_POLEVAULTER,
                                   ZombieType::ZOMBIE_DOLPHIN_RIDER,
                                   ZombieType::ZOMBIE_LADDER,
                                   ZombieType::ZOMBIE_GARGANTUAR};
        Challenge_InitZombieWavesFromList(this, zombieList, sizeof(zombieList) / sizeof(zombieList[0]));
    }
}

void Challenge::TreeOfWisdomFertilize() {
    old_Challenge_TreeOfWisdomFertilize(this);

    // 检查智慧树成就
    PlayerInfo *playerInfo = mApp->mPlayerInfo;
    if (playerInfo->mChallengeRecords[GameMode::GAMEMODE_TREE_OF_WISDOM - 2] >= 99) {
        Board_GrantAchievement(mBoard, AchievementId::ACHIEVEMENT_TREE, true);
    }
}

void Challenge::LastStandUpdate() {
    if (mBoard->mNextSurvivalStageCounter == 0 && mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && mBoardStoreButton->mBtnNoDraw) {
        mBoardStoreButton->mBtnNoDraw = false;
        mBoardStoreButton->mDisabled = false;
        int holder[1];
        TodStringTranslate(holder, mSurvivalStage == 0 ? "[START_ONSLAUGHT]" : "[CONTINUE_ONSLAUGHT]");
        GameButton_SetLabel(mBoardStoreButton, holder);
        Sexy_String_Delete(holder);
        GameButton_Resize(mBoardStoreButton, 325, 555, 170, 120);
    }

    if (mChallengeState == ChallengeState::STATECHALLENGE_LAST_STAND_ONSLAUGHT && mApp->mGameScene == GameScenes::SCENE_PLAYING) {
        mChallengeStateCounter++;
    }

    if (mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && !mBoardStoreButton->mBtnNoDraw) {
        GameButton_Resize(mBoardStoreButton, 325, 555, 170, 120);
        mBoardStoreButton->mBtnNoDraw = false;
        mBoardStoreButton->mDisabled = false;
    }
}

ZombieType Challenge::IZombieSeedTypeToZombieType(SeedType theSeedType) {
    // 此处可修改VS和IZ中的僵尸类型
    switch (theSeedType) {
        case SEED_ZOMBIE_NORMAL:		    return ZOMBIE_NORMAL;
        case SEED_ZOMBIE_TRASH_BIN:		    return ZOMBIE_TRASH_BIN;
        case SEED_ZOMBIE_TRAFFIC_CONE:	    return ZOMBIE_TRAFFIC_CONE;
        case SEED_ZOMBIE_POLEVAULTER:	    return ZOMBIE_POLEVAULTER;
        case SEED_ZOMBIE_PAIL:			    return ZOMBIE_PAIL;
        case SEED_ZOMBIE_FLAG:		        return ZOMBIE_FLAG;
        case SEED_ZOMBIE_NEWSPAPER:		    return ZOMBIE_NEWSPAPER;
        case SEED_ZOMBIE_SCREEN_DOOR:	    return ZOMBIE_DOOR;
        case SEED_ZOMBIE_FOOTBALL:		    return ZOMBIE_FOOTBALL;
        case SEED_ZOMBIE_DANCER:		    return ZOMBIE_DANCER;
        case SEED_ZOMBONI:				    return ZOMBIE_ZAMBONI;
        case SEED_ZOMBIE_JACK_IN_THE_BOX:   return ZOMBIE_JACK_IN_THE_BOX;
        case SEED_ZOMBIE_DIGGER:		    return ZOMBIE_DIGGER;
        case SEED_ZOMBIE_POGO:			    return ZOMBIE_POGO;
        case SEED_ZOMBIE_BUNGEE:		    return ZOMBIE_BUNGEE;
        case SEED_ZOMBIE_LADDER:		    return ZOMBIE_LADDER;
        case SEED_ZOMBIE_CATAPULT:		    return ZOMBIE_CATAPULT;
        case SEED_ZOMBIE_GARGANTUAR:	    return ZOMBIE_GARGANTUAR;
        case SEED_ZOMBIE_UNKNOWN:           return ZOMBIE_REDEYE_GARGANTUAR;
        case SEED_ZOMBIE_DUCKY_TUBE:        return ZOMBIE_DUCKY_TUBE;
        case SEED_ZOMBIE_SNORKEL:           return ZOMBIE_SNORKEL;
        case SEED_ZOMBIE_DOLPHIN_RIDER:     return ZOMBIE_DOLPHIN_RIDER;
        case SEED_ZOMBIE_IMP:			    return ZOMBIE_IMP;
        case SEED_ZOMBIE_BALLOON:		    return ZOMBIE_BALLOON;
        default:                            return ZOMBIE_INVALID;
    }
}

void Challenge::DrawHeavyWeapon(Sexy::Graphics* g) {
    // 修复僵尸进家后重型武器关卡长草露馅
    Sexy_Graphics_DrawImage(g, *Sexy_IMAGE_HEAVY_WEAPON_OVERLAY_Addr, -73, 559);
}

bool Challenge::UpdateZombieSpawning() {
    if (stopSpawning) {
        return true;
    }

    return old_Challenge_UpdateZombieSpawning(this);
}

void Challenge::HeavyWeaponPacketClicked(SeedPacket* theSeedPacket) {
    // 修复疯狂点击毁灭菇导致GridItem数量超出上限而闪退
    if (theSeedPacket->mPacketType == SeedType::SEED_DOOMSHROOM) {
        GridItem *gridItem = nullptr;
        while (Board_IterateGridItems(mBoard, &gridItem)) {
            if (gridItem->mGridItemType == GridItemType::GRIDITEM_CRATER) {
                GridItem_GridItemDie(gridItem);
            }
        }
    }

    old_Challenge_HeavyWeaponPacketClicked(this, theSeedPacket);
}

void Challenge::StartLevel() {
    old_Challenge_StartLevel(this);

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && heavyWeaponAccel) {
        Native::BridgeApp *bridgeApp = Native_BridgeApp_getSingleton();
        JNIEnv *env = Native_BridgeApp_getJNIEnv(bridgeApp);
        jobject activity = Native_NativeApp_getActivity(bridgeApp->mNativeApp);
        jclass cls = env->GetObjectClass(activity);
        jmethodID methodID = env->GetMethodID(cls, "startOrientationListener", "()V");
        env->CallVoidMethod(activity, methodID);
        env->DeleteLocalRef(cls);
    }
}

void Challenge::Delete() {
    old_Challenge_Delete(this);

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && heavyWeaponAccel) {
        Native::BridgeApp *bridgeApp = Native_BridgeApp_getSingleton();
        JNIEnv *env = Native_BridgeApp_getJNIEnv(bridgeApp);
        jobject activity = Native_NativeApp_getActivity(bridgeApp->mNativeApp);
        jclass cls = env->GetObjectClass(activity);
        jmethodID methodID = env->GetMethodID(cls, "stopOrientationListener", "()V");
        env->CallVoidMethod(activity, methodID);
        env->DeleteLocalRef(cls);
    }
}
