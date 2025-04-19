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

void Challenge_Update(Challenge *challenge) {
    if (requestJumpSurvivalStage) {
        // 如果玩家按了无尽跳关
        if (challenge->mSurvivalStage > 0 || challenge->mApp->mGameScene == GameScenes::SCENE_PLAYING) {
            // 需要玩家至少已完成选种子，才能跳关。否则有BUG
            challenge->mSurvivalStage = targetWavesToJump;
        }
        requestJumpSurvivalStage = false;
    }
    GameMode gameMode = challenge->mApp->mGameMode;
    if (gameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || gameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) {
        TutorialState mTutorialState = challenge->mBoard->mTutorialState;
        if (mTutorialState == TutorialState::TUTORIAL_ZEN_GARDEN_PICKUP_WATER || mTutorialState == TutorialState::TUTORIAL_ZEN_GARDEN_WATER_PLANT
            || mTutorialState == TutorialState::TUTORIAL_ZEN_GARDEN_KEEP_WATERING) {
            mBoardMenuButton->mBtnNoDraw = true;
            mBoardStoreButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = true;
            mBoardMenuButton->mDisabled = true;
        } else if (challenge->mApp->mCrazyDaveState != CrazyDaveState::CRAZY_DAVE_OFF) {
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
    return old_Challenge_Update(challenge);
}

void Challenge_Challenge(Challenge *challenge) {
    if (requestJumpSurvivalStage) {
        // 如果玩家按了无尽跳关
        if (challenge->mSurvivalStage > 0 || challenge->mApp->mGameScene == GameScenes::SCENE_PLAYING) {
            // 需要玩家至少已完成选种子，才能跳关。否则有BUG
            challenge->mSurvivalStage = targetWavesToJump;
        }
        requestJumpSurvivalStage = false;
    }
    old_Challenge_Challenge(challenge);
}

void Challenge_HeavyWeaponFire(Challenge *challenge, float a2, float a3) {
    // 设定重型武器子弹的发射角度
    if (a2 == 0 && a3 == 1) {
        a2 = angle1;
        a3 = angle2;
    }
    return old_Challenge_HeavyWeaponFire(challenge, a2, a3);
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

void Challenge_HeavyWeaponUpdate(Challenge *challenge) {
    // 设定重型武器动画的发射角度
    old_Challenge_HeavyWeaponUpdate(challenge);

    if (angle1 != 0) {
        challenge->mHeavyWeaponAngle = acosf(angle1) - 1.5708f;
        Challenge_HeavyWeaponReanimUpdate(challenge);
    }
}

void Challenge_IZombieDrawPlant(Challenge *challenge, Sexy::Graphics *graphics, Plant *thePlant) {
    // 参照PC内测版源代码，在IZ模式绘制植物的函数开始前额外绘制纸板效果。

    Reanimation *mBodyReanim = LawnApp_ReanimationTryToGet(challenge->mApp, thePlant->mBodyReanimID);
    if (mBodyReanim != nullptr) {
        Challenge_IZombieSetPlantFilterEffect(challenge, thePlant, FilterEffectType::White);
        float aOffsetX = graphics->mTransX;
        float aOffsetY = graphics->mTransY;
        Color theColor;
        Sexy_Graphics_SetColorizeImages(graphics, true);
        graphics->mTransX = aOffsetX + 4.0;
        graphics->mTransY = aOffsetY + 4.0;
        theColor.mRed = 122;
        theColor.mGreen = 86;
        theColor.mBlue = 58;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(graphics, &theColor);
        Reanimation_DrawRenderGroup(mBodyReanim, graphics, 0);
        graphics->mTransX = aOffsetX + 2.0;
        graphics->mTransY = aOffsetY + 2.0;
        theColor.mRed = 171;
        theColor.mGreen = 135;
        theColor.mBlue = 107;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(graphics, &theColor);
        Reanimation_DrawRenderGroup(mBodyReanim, graphics, 0);
        graphics->mTransX = aOffsetX - 2.0;
        graphics->mTransY = aOffsetY - 2.0;
        theColor.mRed = 171;
        theColor.mGreen = 135;
        theColor.mBlue = 107;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(graphics, &theColor);
        Reanimation_DrawRenderGroup(mBodyReanim, graphics, 0);
        graphics->mTransX = aOffsetX;
        graphics->mTransY = aOffsetY;
        theColor.mRed = 255;
        theColor.mGreen = 201;
        theColor.mBlue = 160;
        theColor.mAlpha = 255;
        Sexy_Graphics_SetColor(graphics, &theColor);
        Challenge_IZombieSetPlantFilterEffect(challenge, thePlant, FilterEffectType::None);
        Reanimation_DrawRenderGroup(mBodyReanim, graphics, 0);
        Challenge_IZombieSetPlantFilterEffect(challenge, thePlant, FilterEffectType::None);
        Sexy_Graphics_SetDrawMode(graphics, DrawMode::DRAWMODE_NORMAL);
        Sexy_Graphics_SetColorizeImages(graphics, false);
    }
}

bool Challenge_IZombieEatBrain(Challenge *challenge, Zombie *zombie) {
    // 修复IZ脑子血量太高
    GridItem *brain = Challenge_IZombieGetBrainTarget(challenge, zombie);
    if (brain == nullptr)
        return false;
    Zombie_StartEating(zombie);
    //    int mHealth = brain->mGridItemCounter - 1;
    int mHealth = brain->mGridItemCounter - 2; // 一次吃掉脑子的两滴血
    brain->mGridItemCounter = mHealth;
    if (mHealth <= 0) {
        LawnApp_PlaySample(challenge->mApp, *Sexy_SOUND_GULP_Addr);
        GridItem_GridItemDie(brain);
        Challenge_IZombieScoreBrain(challenge, brain);
    }
    return true;
}

void Challenge_DrawArtChallenge(Challenge *challenge, Sexy::Graphics *graphics) {
    // 绘制坚果的两只大眼睛
    Sexy_Graphics_SetColorizeImages(graphics, true);
    Color theColor = {255, 255, 255, 100};
    Sexy_Graphics_SetColor(graphics, &theColor);
    Board *board = challenge->mBoard;
    for (int theGridY = 0; theGridY < 6; theGridY++) {
        for (int theGridX = 0; theGridX < 9; theGridX++) {
            SeedType ArtChallengeSeed = Challenge_GetArtChallengeSeed(challenge, theGridX, theGridY);
            if (ArtChallengeSeed != SeedType::SEED_NONE && Board_GetTopPlantAt(board, theGridX, theGridY, PlantPriority::TOPPLANT_ONLY_NORMAL_POSITION) == nullptr) {
                int x = Board_GridToPixelX(board, theGridX, theGridY);
                int y = Board_GridToPixelY(board, theGridX, theGridY);
                Plant_DrawSeedType(graphics, ArtChallengeSeed, SeedType::SEED_NONE, DrawVariation::VARIATION_NORMAL, x, y);
            }
        }
    }
    if (challenge->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT) {
        Color theColor = {255, 255, 255, 255};
        Sexy_Graphics_SetColor(graphics, &theColor);
        int x1 = Board_GridToPixelX(board, 4, 1);
        int y1 = Board_GridToPixelY(board, 4, 1);
        Sexy_Graphics_DrawImage(graphics, addonImages.googlyeye, x1, y1);
        int x2 = Board_GridToPixelX(board, 6, 1);
        int y2 = Board_GridToPixelY(board, 6, 1);
        Sexy_Graphics_DrawImage(graphics, addonImages.googlyeye, x2, y2);
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
}

PlantingReason Challenge_CanPlantAt(Challenge *challenge, int theGridX, int theGridY, SeedType theType) {
    // 修复IZ多个蹦极可放置在同一格子内
    LawnApp *lawnApp = challenge->mApp;
    GameMode mGameMode = lawnApp->mGameMode;
    if (LawnApp_IsWallnutBowlingLevel(lawnApp)) {
        if (theGridX > 2) {
            return PlantingReason::PLANTING_NOT_PASSED_LINE;
        }
    } else if (LawnApp_IsIZombieLevel(lawnApp)) {
        int num = 6;
        if (mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_2 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_3
            || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_4 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_5) {
            num = 4;
        }
        if (mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_6 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_7 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_8
            || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS) {
            num = 5;
        }
        if (theType == SeedType::SEED_ZOMBIE_BUNGEE) {
            if (theGridX < num) {
                Board *board = challenge->mBoard;
                Zombie *zombie = nullptr;
                while (Board_IterateZombies(board, &zombie)) {
                    if (zombie->mZombieType == ZombieType::ZOMBIE_BUNGEE) {
                        int mGridX = Board_PixelToGridX(board, zombie->mX, zombie->mY);
                        if (mGridX == theGridX && zombie->mRow == theGridY) {
                            return PlantingReason::PLANTING_NOT_HERE;
                        }
                    }
                }
                return PlantingReason::PLANTING_OK;
            }
            return PlantingReason::PLANTING_NOT_HERE;
        } else if (Challenge_IsZombieSeedType(theType)) {
            if (theGridX >= num) {
                return PlantingReason::PLANTING_OK;
            }
            return PlantingReason::PLANTING_NOT_HERE;
        }
    } else if (LawnApp_IsArtChallenge(lawnApp)) {
        SeedType artChallengeSeed = Challenge_GetArtChallengeSeed(challenge, theGridX, theGridY);
        if (artChallengeSeed != SeedType::SEED_NONE && artChallengeSeed != theType && theType != SeedType::SEED_LILYPAD && theType != SeedType::SEED_PUMPKINSHELL) {
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
    } else if (LawnApp_IsFinalBossLevel(lawnApp) && theGridX >= 8) {
        return PlantingReason::PLANTING_NOT_HERE;
    } else if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS_HIDE || mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        if (Challenge_IsMPSeedType(theType)) {
            if (theGridX > 5 || theType == SeedType::SEED_ZOMBIE_BUNGEE)
                return PlantingReason::PLANTING_OK;
            return PlantingReason::PLANTING_NOT_PASSED_LINE_VS;
        }
        if (theType == SeedType::SEED_GRAVEBUSTER) {
            if (Board_GetGridItemAt(challenge->mBoard, GridItemType::GRIDITEM_GRAVESTONE, theGridX, theGridY) == nullptr)
                return PlantingReason::PLANTING_ONLY_ON_GRAVES;
        } else {
            if (theGridX <= 5)
                return PlantingReason::PLANTING_OK;
            return PlantingReason::PLANTING_NOT_PASSED_LINE_VS;
        }
    }
    return PlantingReason::PLANTING_OK;
}

void Challenge_InitLevel(Challenge *challenge) {
    old_Challenge_InitLevel(challenge);
    LawnApp *lawnApp = challenge->mApp;
    Board *board = challenge->mBoard;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        Board_NewPlant(board, 0, 0, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
        Board_NewPlant(board, 0, 1, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
        Board_NewPlant(board, 0, 4, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
        Board_NewPlant(board, 0, 5, SeedType::SEED_COBCANNON, SeedType::SEED_NONE, -1);
    }
}

void Challenge_InitZombieWaves(Challenge *challenge) {
    old_Challenge_InitZombieWaves(challenge);
    LawnApp *lawnApp = challenge->mApp;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
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
        Challenge_InitZombieWavesFromList(challenge, zombieList, sizeof(zombieList) / sizeof(zombieList[0]));
    }
}

void Challenge_TreeOfWisdomFertilize(Challenge *challenge) {
    old_Challenge_TreeOfWisdomFertilize(challenge);
    // 检查智慧树成就
    LawnApp *lawnApp = challenge->mApp;
    PlayerInfo *playerInfo = lawnApp->mPlayerInfo;
    if (playerInfo->mChallengeRecords[GameMode::GAMEMODE_TREE_OF_WISDOM - 2] >= 99) {
        Board_GrantAchievement(challenge->mBoard, AchievementId::ACHIEVEMENT_TREE, true);
    }
}

void Challenge_LastStandUpdate(Challenge *challenge) {
    if (challenge->mBoard->mNextSurvivalStageCounter == 0 && challenge->mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && mBoardStoreButton->mBtnNoDraw) {
        mBoardStoreButton->mBtnNoDraw = false;
        mBoardStoreButton->mDisabled = false;
        int holder[1];
        TodStringTranslate(holder, challenge->mSurvivalStage == 0 ? "[START_ONSLAUGHT]" : "[CONTINUE_ONSLAUGHT]");
        GameButton_SetLabel(mBoardStoreButton, holder);
        Sexy_String_Delete(holder);
        GameButton_Resize(mBoardStoreButton, 325, 555, 170, 120);
    }
    if (challenge->mChallengeState == ChallengeState::STATECHALLENGE_LAST_STAND_ONSLAUGHT && challenge->mApp->mGameScene == GameScenes::SCENE_PLAYING) {
        challenge->mChallengeStateCounter++;
    }

    if (challenge->mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && !mBoardStoreButton->mBtnNoDraw) {
        GameButton_Resize(mBoardStoreButton, 325, 555, 170, 120);
        mBoardStoreButton->mBtnNoDraw = false;
        mBoardStoreButton->mDisabled = false;
    }
}

ZombieType Challenge_IZombieSeedTypeToZombieType(SeedType type) {
    // 此处可修改VS和IZ中的僵尸类型
    if (type == SeedType::SEED_ZOMBIE_UNKNOWN) {
        return ZombieType::ZOMBIE_REDEYE_GARGANTUAR;
    }
    return old_Challenge_IZombieSeedTypeToZombieType(type);
}

void Challenge_DrawHeavyWeapon(Challenge *challenge, Sexy::Graphics *graphics) {
    // 修复僵尸进家后重型武器关卡长草露馅
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_HEAVY_WEAPON_OVERLAY_Addr, -73, 559);
}

bool Challenge_UpdateZombieSpawning(Challenge *challenge) {
    if (stopSpawning) {
        return true;
    }
    return old_Challenge_UpdateZombieSpawning(challenge);
}

void Challenge_HeavyWeaponPacketClicked(Challenge *challenge, SeedPacket *seedPacket) {
    // 修复疯狂点击毁灭菇导致GridItem数量超出上限而闪退
    if (seedPacket->mPacketType == SeedType::SEED_DOOMSHROOM) {
        GridItem *gridItem = nullptr;
        while (Board_IterateGridItems(challenge->mBoard, &gridItem)) {
            if (gridItem->mGridItemType == GridItemType::GRIDITEM_CRATER) {
                GridItem_GridItemDie(gridItem);
            }
        }
    }
    old_Challenge_HeavyWeaponPacketClicked(challenge, seedPacket);
}

void Challenge_StartLevel(Challenge *challenge) {
    old_Challenge_StartLevel(challenge);
    if (challenge->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && heavyWeaponAccel) {
        Native::BridgeApp *bridgeApp = Native_BridgeApp_getSingleton();
        JNIEnv *env = Native_BridgeApp_getJNIEnv(bridgeApp);
        jobject activity = Native_NativeApp_getActivity(bridgeApp->mNativeApp);
        jclass cls = env->GetObjectClass(activity);
        jmethodID methodID = env->GetMethodID(cls, "startOrientationListener", "()V");
        env->CallVoidMethod(activity, methodID);
        env->DeleteLocalRef(cls);
    }
}

void Challenge_Delete(Challenge *challenge) {
    old_Challenge_Delete(challenge);
    if (challenge->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && heavyWeaponAccel) {
        Native::BridgeApp *bridgeApp = Native_BridgeApp_getSingleton();
        JNIEnv *env = Native_BridgeApp_getJNIEnv(bridgeApp);
        jobject activity = Native_NativeApp_getActivity(bridgeApp->mNativeApp);
        jclass cls = env->GetObjectClass(activity);
        jmethodID methodID = env->GetMethodID(cls, "stopOrientationListener", "()V");
        env->CallVoidMethod(activity, methodID);
        env->DeleteLocalRef(cls);
    }
}
