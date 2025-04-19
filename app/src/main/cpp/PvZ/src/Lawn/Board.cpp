#include "PvZ/Lawn/Board.h"
#include "Homura/Formation.h"
#include "Homura/Logger.h"
#include "PvZ/Android/IntroVideo.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Challenge.h"
#include "PvZ/Lawn/Coin.h"
#include "PvZ/Lawn/CutScene.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/GridItem.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Music.h"
#include "PvZ/Lawn/Plant.h"
#include "PvZ/Lawn/Projectile.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/SeedBank.h"
#include "PvZ/Lawn/SeedChooserScreen.h"
#include "PvZ/Lawn/SeedPacket.h"
#include "PvZ/Lawn/ZenGarden.h"
#include "PvZ/Lawn/Zombie.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Symbols.h"
#include <cstddef>
#include <cstdio>

void FixBoardAfterLoad(Board *board) {
    // 修复读档后的各种问题
    old_FixBoardAfterLoad(board);
    Board_FixReanimErrorAfterLoad(board);
}

void Board_FixReanimErrorAfterLoad(Board *board) {
    // 修复读档后的各种问题
    Zombie *zombie = nullptr;
    while (Board_IterateZombies(board, &zombie)) {
        ZombieType zombieType = zombie->mZombieType;
        Reanimation *mBodyReanim = LawnApp_ReanimationGet(board->mApp, zombie->mBodyReanimID);
        if (mBodyReanim == nullptr)
            return;

        if (!zombie->mHasArm) {
            Zombie_SetupLostArmReanim(zombie);
        }
        // 修复读档后豌豆、机枪、倭瓜僵尸头部变为普通僵尸
        if (zombieType == ZombieType::ZOMBIE_PEA_HEAD || zombieType == ZombieType::ZOMBIE_GATLING_HEAD || zombieType == ZombieType::ZOMBIE_SQUASH_HEAD) {
            Reanimation_SetImageOverride(mBodyReanim, "anim_head1", *Sexy_IMAGE_BLANK_Addr);
        }

        // 修复读档后盾牌贴图变为满血盾牌贴图、垃圾桶变为铁门
        if (zombie->mShieldType != ShieldType::SHIELDTYPE_NONE) {
            int shieldDamageIndex = Zombie_GetShieldDamageIndex(zombie);
            switch (zombie->mShieldType) {
                case ShieldType::SHIELDTYPE_DOOR:
                    switch (shieldDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_SCREENDOOR2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_SCREENDOOR3_Addr);
                            break;
                    }
                    break;
                case ShieldType::SHIELDTYPE_NEWSPAPER:
                    switch (shieldDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_paper_paper", *Sexy_IMAGE_REANIM_ZOMBIE_PAPER_PAPER2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_paper_paper", *Sexy_IMAGE_REANIM_ZOMBIE_PAPER_PAPER3_Addr);
                            break;
                    }
                    break;
                case ShieldType::SHIELDTYPE_LADDER:
                    switch (shieldDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_ladder_1", *Sexy_IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_ladder_1", *Sexy_IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2_Addr);
                            break;
                    }
                    break;
                case ShieldType::SHIELDTYPE_TRASH_BIN:
                    switch (shieldDamageIndex) {
                        case 0:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_TRASHCAN1_Addr);
                            break;
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_TRASHCAN2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_TRASHCAN3_Addr);
                            break;
                    }
                    break;
            }
        }

        // 修复读档后头盔贴图变为满血头盔贴图
        if (zombie->mHelmType != HelmType::HELMTYPE_NONE) {
            int helmDamageIndex = Zombie_GetHelmDamageIndex(zombie);
            switch (zombie->mHelmType) {
                case HelmType::HELMTYPE_TRAFFIC_CONE:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_cone", *Sexy_IMAGE_REANIM_ZOMBIE_CONE2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_cone", *Sexy_IMAGE_REANIM_ZOMBIE_CONE3_Addr);
                            break;
                    }
                    break;
                case HelmType::HELMTYPE_PAIL:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_bucket", *Sexy_IMAGE_REANIM_ZOMBIE_BUCKET2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_bucket", *Sexy_IMAGE_REANIM_ZOMBIE_BUCKET3_Addr);
                            break;
                    }
                    break;
                case HelmType::HELMTYPE_FOOTBALL:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "zombie_football_helmet", *Sexy_IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "zombie_football_helmet", *Sexy_IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3_Addr);
                            break;
                    }
                    break;
                case HelmType::HELMTYPE_DIGGER:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_digger_hardhat", *Sexy_IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_digger_hardhat", *Sexy_IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3_Addr);
                            break;
                    }
                    break;
                case HelmType::HELMTYPE_WALLNUT: {
                    Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(board->mApp, zombie->mSpecialHeadReanimID);
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face", *Sexy_IMAGE_REANIM_WALLNUT_CRACKED1_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face", *Sexy_IMAGE_REANIM_WALLNUT_CRACKED2_Addr);
                            break;
                    }
                } break;
                case HelmType::HELMTYPE_TALLNUT: {
                    Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(board->mApp, zombie->mSpecialHeadReanimID);
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face", *Sexy_IMAGE_REANIM_TALLNUT_CRACKED1_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face", *Sexy_IMAGE_REANIM_TALLNUT_CRACKED2_Addr);
                            break;
                    }
                } break;
            }
        }

        // 修复读档后巨人僵尸创可贴消失、红眼巨人变白眼巨人
        if (zombieType == ZombieType::ZOMBIE_GARGANTUAR || zombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 0:
                    if (zombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR)
                        Reanimation_SetImageOverride(mBodyReanim, "anim_head1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_Addr);
                    break;
                case 1:
                    if (zombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR)
                        Reanimation_SetImageOverride(mBodyReanim, "anim_head1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantua_body1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantuar_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2_Addr);
                    break;
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantua_body1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantuar_outerleg_foot", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantuar_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim,
                                                 "anim_head1",
                                                 zombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR ? *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE_Addr : *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_Addr);
            }
        }

        // 修复读档后僵尸博士机甲变全新机甲
        if (zombieType == ZombieType::ZOMBIE_BOSS) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 1:
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_head", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_jaw", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_hand", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_thumb2", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_innerleg_foot", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1_Addr);
                    break;
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_head", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_jaw", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_hand", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_thumb2", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerleg_foot", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2_Addr);
                    break;
            }
        }

        // 修复读档后冰车变全新冰车
        if (zombieType == ZombieType::ZOMBIE_ZAMBONI) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 1:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_1", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_2", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1_Addr);
                    break;
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_1", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_2", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2_Addr);
                    break;
            }
        }

        // 修复读档后投篮车变全新投篮车
        if (zombieType == ZombieType::ZOMBIE_CATAPULT) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 1:
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_catapult_siding", *Sexy_IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE_Addr);
                    break;
            }
        }
    }

    // 修复读档后雏菊、糖果变色、泳池闪光消失
    TodParticleSystem *particle = nullptr;
    while (Board_IterateParticles(board, &particle)) {
        if (particle->mEffectType == ParticleEffect::PARTICLE_ZOMBIE_DAISIES || particle->mEffectType == ParticleEffect::PARTICLE_ZOMBIE_PINATA) {
            // 设置颜色
            TodParticleSystem_OverrideColor(particle, nullptr, &white);
        } else if (particle->mEffectType == ParticleEffect::PARTICLE_POOL_SPARKLY) {
            // 直接删除泳池闪光特效
            TodParticleSystem_ParticleSystemDie(particle);
            board->mPoolSparklyParticleID = 0;
        }
    }

    if (board->mBackgroundType == BackgroundType::BACKGROUND_3_POOL) {
        // 添加泳池闪光特效
        TodParticleSystem *poolSparklyParticle = LawnApp_AddTodParticle(board->mApp, 450.0, 295.0, 220000, ParticleEffect::PARTICLE_POOL_SPARKLY);
        board->mPoolSparklyParticleID = LawnApp_ParticleGetID(board->mApp, poolSparklyParticle);
    }
}

void Board_SetGrids(Board *board) {
    // 更换场地时需要，用于初始化每一个格子的类型。
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 6; j++) {
            if (board->mPlantRow[j] == PlantRowType::PLANTROW_DIRT) {
                board->mGridSquareType[i][j] = GridSquareType::GRIDSQUARE_DIRT;
            } else if (board->mPlantRow[j] == PlantRowType::PLANTROW_POOL && i >= 0 && i <= 8) {
                board->mGridSquareType[i][j] = GridSquareType::GRIDSQUARE_POOL;
            } else if (board->mPlantRow[j] == PlantRowType::PLANTROW_HIGH_GROUND && i >= 4 && i <= 8) {
                board->mGridSquareType[i][j] = GridSquareType::GRIDSQUARE_HIGH_GROUND;
            }
        }
    }
}

int LawnSaveGame(Board *board, int *a2) {
    //    Zombie *zombie = nullptr;
    //    while (Board_IterateZombies(board, &zombie)) {
    //        if (zombie->mZombieType == ZombieType::ZOMBIE_FLAG) {
    //            LawnApp_RemoveReanimation(zombie->mApp, zombie->mBossFireBallReanimID);
    //            zombie->mBossFireBallReanimID = 0;
    //        }
    //    }
    return old_LawnSaveGame(board, a2);
}


void Board_ShovelDown(Board *board) {
    // 用于铲掉光标正下方的植物。
    requestDrawShovelInCursor = false;
    LawnApp *lawnApp = board->mApp;
    bool isInShovelTutorial = (unsigned int)(board->mTutorialState - 15) <= 2;
    if (isInShovelTutorial) {
        // 如果正在铲子教学中(即冒险1-5的保龄球的开场前，戴夫要求你铲掉三个豌豆的这段时间),则发送铲除键来铲除。
        GamepadControls_OnKeyDown(board->mGamepadControls1, 49, 1112);
        Board_ClearCursor(board, 0);
        Board_RefreshSeedPacketFromCursor(board, 0);
        return;
    }
    // 下方就是自己写的铲除逻辑喽。
    GamepadControls *gamepadControls1 = board->mGamepadControls1;
    float mGamePadX = gamepadControls1->mCursorPositionX;
    float mGamePadY = gamepadControls1->mCursorPositionY;
    Plant *plantUnderShovel = Board_ToolHitTest(board, mGamePadX, mGamePadY);
    if (plantUnderShovel != nullptr) {
        LawnApp_PlayFoley(lawnApp, FoleyType::UseShovel); // 播放铲除音效
        plantUnderShovel->Die();                      // 让被铲的植物趋势
        SeedType plantType = plantUnderShovel->mSeedType;
        int mPlantCol = plantUnderShovel->mPlantCol;
        int mRow = plantUnderShovel->mRow;
        if (plantType == SeedType::SEED_CATTAIL && Board_GetTopPlantAt(board, mPlantCol, mRow, PlantPriority::TOPPLANT_ONLY_PUMPKIN) != nullptr) {
            // 如果铲的是南瓜套内的猫尾草,则再在原地种植一个荷叶
            Board_NewPlant(board, mPlantCol, mRow, SeedType::SEED_LILYPAD, SeedType::SEED_NONE, -1);
        }
        if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND) {
            Challenge *challenge = board->mChallenge;
            if (challenge->mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && lawnApp->mGameScene == GameScenes::SCENE_PLAYING) {
                int theCost = Plant::GetCost(plantType, plantUnderShovel->mImitaterType);
                int num = theCost / 25;
                if (plantType == SeedType::SEED_GARLIC || plantType == SeedType::SEED_WALLNUT || plantType == SeedType::SEED_TALLNUT || plantType == SeedType::SEED_PUMPKINSHELL) {
                    int mPlantHealth = plantUnderShovel->mPlantHealth;
                    int mPlantMaxHealth = plantUnderShovel->mPlantMaxHealth;
                    num = (mPlantHealth * 3 > mPlantMaxHealth * 2) ? num : 0;
                }
                for (int i = 0; i < num; i++) {
                    Coin *coin = Board_AddCoin(board, mGamePadX, mGamePadY, 4, 2);
                    Coin_Collect(coin, 0);
                }
            }
        }
    }
    Board_ClearCursor(board, 0);
    Board_RefreshSeedPacketFromCursor(board, 0);
}

void Board_UpdateGame(Board *board) {
    if (requestPause) {
        Board_UpdateGameObjects(board);
        return;
    }

    old_Board_UpdateGame(board);

    // 防止选卡界面浓雾遮挡僵尸
    if (board->mFogBlownCountDown > 0 && board->mApp->mGameScene == GameScenes::SCENE_LEVEL_INTRO) {
        float thePositionStart = 1065.0 - 4 * 80.0 + 100; // 1065f - LeftFogColumn() * 80f + Constants.BOARD_EXTRA_ROOM;
        board->mFogOffset = TodAnimateCurveFloat(200, 0, board->mFogBlownCountDown, thePositionStart, 0.0, TodCurves::CURVE_EASE_OUT);
    }
}

void Board_UpdateGameObjects(Board *board) {
    // 修复过关后游戏卡住不动
    if (board->mBoardFadeOutCounter > 0) {
        // 如果已经过关，则手动刷新植物，僵尸，子弹
        Plant* aPlant = nullptr;
        while (Board_IteratePlants(board, &aPlant)) {
            aPlant->Update();
        }
        Zombie* aZombie = nullptr;
        while (Board_IterateZombies(board, &aZombie)) {
            aZombie->Update();
        }
        Projectile* aProjectile = nullptr;
        while (Board_IterateProjectiles(board, &aProjectile)) {
            aProjectile->Update();
        }
    }
    old_Board_UpdateGameObjects(board);
}

void Board_DrawDebugText(Board *board, Sexy::Graphics *graphics) {
    // 出僵DEBUG功能
    if (drawDebugText) {
        DebugTextMode tmp = board->mDebugTextMode;
        board->mDebugTextMode = DebugTextMode::DEBUG_TEXT_ZOMBIE_SPAWN;
        old_Board_DrawDebugText(board, graphics);
        board->mDebugTextMode = tmp;
        return;
    }
    old_Board_DrawDebugText(board, graphics);
}

void Board_DrawDebugObjectRects(Board *board, Sexy::Graphics *graphics) {
    // 碰撞体积绘制
    if (drawDebugRects) {
        DebugTextMode tmp = board->mDebugTextMode;
        board->mDebugTextMode = DebugTextMode::DEBUG_TEXT_COLLISION;
        old_Board_DrawDebugObjectRects(board, graphics);
        board->mDebugTextMode = tmp;
        return;
    }
    old_Board_DrawDebugObjectRects(board, graphics);
}

void Board_DrawFadeOut(Board *board, Sexy::Graphics *graphics) {
    // 修复关卡完成后的白色遮罩无法遮住整个屏幕
    int mBoardFadeOutCounter = board->mBoardFadeOutCounter;
    if (mBoardFadeOutCounter < 0) {
        return;
    }
    if (Board_IsSurvivalStageWithRepick(board)) {
        return;
    }
    int theAlpha = TodAnimateCurve(200, 0, mBoardFadeOutCounter, 0, 255, TodCurves::CURVE_LINEAR);
    int mLevel = board->mLevel;
    if (mLevel == 9 || mLevel == 19 || mLevel == 29 || mLevel == 39 || mLevel == 49) {
        Color theColor = {0, 0, 0, theAlpha};
        Sexy_Graphics_SetColor(graphics, &theColor);
    } else {
        Color theColor = {255, 255, 255, theAlpha};
        Sexy_Graphics_SetColor(graphics, &theColor);
    }
    Sexy_Graphics_SetColorizeImages(graphics, true);
    TRect fullScreenRect = {-240, -60, 1280, 720};
    // 修复BUG的核心原理，就是不要在此处PushState和PopState，而是直接FillRect。这将保留graphics的trans属性。
    Sexy_Graphics_FillRect(graphics, &fullScreenRect);
}

int Board_GetCurrentPlantCost(Board *board, SeedType a2, SeedType a3) {
    // 无限阳光
    if (infiniteSun)
        return 0;
    return old_Board_GetCurrentPlantCost(board, a2, a3);
}

void Board_AddSunMoney(Board *board, int theAmount, int playerIndex) {
    // 无限阳光
    if (infiniteSun) {
        if (playerIndex == 0) {
            board->mSunMoney1 = 9990;
        } else {
            board->mSunMoney2 = 9990;
        }
    } else {
        old_Board_AddSunMoney(board, theAmount, playerIndex);
    }
}

void Board_AddDeathMoney(Board *board, int theAmount) {
    // 无限阳光
    if (infiniteSun) {
        board->mDeathMoney = 9990;
    } else {
        old_Board_AddDeathMoney(board, theAmount);
    }
}

PlantingReason Board_CanPlantAt(Board *board, int theGridX, int theGridY, SeedType seedType) {
    // 自由种植！
    if (FreePlantAt) {
        return PlantingReason::PLANTING_OK;
    }
    return old_Board_CanPlantAt(board, theGridX, theGridY, seedType);
}


bool Board_PlantingRequirementsMet(Board *board, int a2) {
    // 紫卡直接种植！
    if (FreePlantAt) {
        return 1;
    }
    return old_Board_PlantingRequirementsMet(board, a2);
}

void Board_ZombiesWon(Board *board, Zombie *theZombie) {
    if (theZombie == nullptr) { // 如果是IZ或者僵尸水族馆，第二个参数是NULL，此时就返回原函数。否则闪退
        return old_BoardZombiesWon(board, theZombie);
    }
    if (ZombieCanNotWon) {
        Zombie_ApplyBurn(theZombie);
        theZombie->Zombie::DieNoLoot();
        return;
    }
    return old_BoardZombiesWon(board, theZombie);
}

Plant *Board_AddPlant(Board *board, int x, int y, SeedType seedType, SeedType theImitaterType, int playerIndex, bool doPlantEffect) {

    Plant *plant = Board_NewPlant(board, x, y, seedType, theImitaterType, playerIndex);
    if (doPlantEffect) {
        Board_DoPlantingEffects(board, x, y, plant);
    }
    Challenge_PlantAdded(board->mChallenge, plant);
    // 检查成就！
    Board_DoPlantingAchievementCheck(board, seedType);
    int mMaxSunPlants = Board_CountPlantByType(board, SeedType::SEED_SUNFLOWER) + Board_CountPlantByType(board, SeedType::SEED_SUNSHROOM);
    if (mMaxSunPlants > board->mMaxSunPlants) {
        board->mMaxSunPlants = mMaxSunPlants;
    }
    if (seedType == SeedType::SEED_CABBAGEPULT || seedType == SeedType::SEED_KERNELPULT || seedType == SeedType::SEED_MELONPULT || seedType == SeedType::SEED_WINTERMELON) {
        board->mCatapultPlantsUsed = true;
    }
    if (seedType == SeedType::SEED_PUMPKINSHELL && PumpkinWithLadder && Board_GetLadderAt(board, x, y) == nullptr) {
        Board_AddALadder(board, x, y);
    }
    return plant;
}

// 布阵用
void Board_parseFormationSegment(Board *board, char *segment) {
    SeedType seedType = SeedType::SEED_PEASHOOTER;
    bool isIZombieLevel = LawnApp_IsIZombieLevel(board->mApp);
    bool wakeUp = false;
    bool imitaterMorphed = false;
    bool addLadder = false;
    int damageState = 0;
    int offset = 0;

    if (sscanf(segment, "%d%n", &seedType, &offset) != 1) {
        return; // Failed to parse
    }

    // Move cursor to the next position after the parsed integer
    const char *cursor = segment + offset;
    while (*cursor != '\0') {
        if (*cursor == 'W') {
            wakeUp = true;
        } else if (*cursor == 'I') {
            imitaterMorphed = true;
        } else if (*cursor == 'L') {
            addLadder = true;
        } else if (*cursor == 'D') {
            damageState++;
            if (damageState > 2) {
                damageState = 2;
            }
        } else if (*cursor >= '0' && *cursor <= '9') {
            // Parse coordinates
            int x = 0, y = 0;
            if (!sscanf(cursor, "%d,%d", &x, &y)) {
                continue;
            }
            Plant *plant = old_Board_AddPlant(board, x, y, seedType, imitaterMorphed ? SeedType::SEED_IMITATER : SeedType::SEED_NONE, 1, false);
            if (imitaterMorphed) {
                plant->SetImitaterFilterEffect();
            }
            if (wakeUp) {
                plant->SetSleeping(false);
            }
            if (addLadder && Board_GetLadderAt(board, x, y) == nullptr) {
                Board_AddALadder(board, x, y);
            }
            if (damageState > 0) {
                plant->mPlantHealth = (plant->mPlantMaxHealth * (3 - damageState) / 3) - 1;
            }
            if (isIZombieLevel) {
                Challenge_IZombieSetupPlant(board->mChallenge, plant);
            }
            // Skip to next coordinate
            while (*cursor != ' ' && *cursor != '\0') {
                cursor++;
            }
            continue;
        }
        cursor++;
    }
}

// 布阵用
void Board_LoadFormation(Board *board, char *formation) {
    Board_RemoveAllPlants(board);
    const char *segmentDelimiters = ";";
    char *segment = strtok(formation, segmentDelimiters);
    while (segment != nullptr) {
        Board_parseFormationSegment(board, segment);
        segment = strtok(nullptr, segmentDelimiters);
    }
}


bool Board_ZenGardenItemNumIsZero(Board *board, CursorType cursorType) {
    // 消耗性工具的数量是否为0个
    LawnApp *lawnApp = board->mApp;
    switch (cursorType) {
        case CursorType::CURSOR_TYPE_FERTILIZER:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_FERTILIZER] <= 1000;
        case CursorType::CURSOR_TYPE_BUG_SPRAY:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_BUG_SPRAY] <= 1000;
        case CursorType::CURSOR_TYPE_CHOCOLATE:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_CHOCOLATE] <= 1000;
        case CursorType::CURSOR_TYPE_TREE_FOOD:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_TREE_FOOD] <= 1000;
    }
    return false;
}

void Board_DrawZenButtons(Board *board, Sexy::Graphics *a2) {

    return old_Board_DrawZenButtons(board, a2);
}

void Board_KeyDown(Board *board, int keyCode) {
    // 用于切换键盘模式，自动开关砸罐子老虎机种子雨关卡内的"自动拾取植物卡片"功能
    if (keyCode >= 37 && keyCode <= 40) {
        if (!keyboardMode) {
            game_patches::autoPickupSeedPacketDisable.Restore();
        }
        keyboardMode = true;
        requestDrawShovelInCursor = false;
    }
    return old_Board_KeyDown(board, keyCode);
}

void Board_UpdateSunSpawning(Board *board) {
    if (requestPause) {
        // 如果开了高级暂停
        return;
    }
    if (board->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        return;
    }
    return old_Board_UpdateSunSpawning(board);
}

void Board_UpdateZombieSpawning(Board *board) {
    if (requestPause) {
        // 如果开了高级暂停
        return;
    }

    // 在黄油爆米花关卡改变出怪倒计时。
    if (board->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        int mZombieCountDown = board->mZombieCountDown;
        if (mZombieCountDown >= 2500 && mZombieCountDown <= 3100) {
            board->mZombieCountDown = 750;
            board->mZombieCountDownStart = board->mZombieCountDown;
        }
    }
    //    int *lawnApp = (int *) board[69];
    //    GameMode::GameMode mGameMode = (GameMode::GameMode)*(lawnApp + LAWNAPP_GAMEMODE_OFFSET);
    //    if(mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN){
    //        int mFinalWaveSoundCounter = board[5660];
    //        if (mFinalWaveSoundCounter > 0) {
    //            mFinalWaveSoundCounter--;
    //            board[5660] = mFinalWaveSoundCounter;
    //            if (mFinalWaveSoundCounter == 0) {
    //                LawnApp_PlaySample(lawnApp,Sexy_SOUND_FINALWAVE_Addr);
    //            }
    //        }
    //        if (Board_HasLevelAwardDropped(board)) {
    //            return;
    //        }
    //
    //        int mRiseFromGraveCounter = board[5540];
    //        if (mRiseFromGraveCounter > 0) {
    //            mRiseFromGraveCounter--;
    //            board[5540] = mRiseFromGraveCounter;
    //            if (mRiseFromGraveCounter == 0) {
    //                Board_SpawnZombiesFromGraves(board);
    //            }
    //        }
    //
    //        int mHugeWaveCountDown = board[5552];
    //        if (mHugeWaveCountDown > 0) {
    //            mHugeWaveCountDown--;
    //            board[5552] = mHugeWaveCountDown;
    //            if (mHugeWaveCountDown == 0) {
    //                Board_ClearAdvice(board, 42);
    //                Board_NextWaveComing(board);
    //                board[5550] = 1; //  mZombieCountDown = 1;
    //            }else if(mHugeWaveCountDown == 725){
    //                LawnApp_PlaySample(lawnApp,Sexy_SOUND_FINALWAVE_Addr);
    //            }
    //        }
    //
    //        int mZombieCountDown = board[5550];
    //        mZombieCountDown--; //  mZombieCountDown--;
    //        board[5550] = mZombieCountDown;
    //
    //        int mZombieCountDownStart = board[5551];
    //        int mCurrentWave = board[5542];
    //        int mZombieHealthToNextWave = board[5548];
    //        int num2 = mZombieCountDownStart - mZombieCountDown;
    //        if (mZombieCountDown > 5 && num2 > 400) {
    //            int num3 = Board_TotalZombiesHealthInWave(board, mCurrentWave - 1);
    //            if (num3 <= mZombieHealthToNextWave && mZombieCountDown > 200) {
    //                board[5550] = 200;//  mZombieCountDown = 200;
    //            }
    //        }
    //
    //        if (mZombieCountDown == 5) {
    //            if (Board_IsFlagWave(board, mCurrentWave)) {
    //                Board_ClearAdviceImmediately(board);
    //                int holder[1];
    //                Sexy_StrFormat(holder,"[ADVICE_HUGE_WAVE]");
    //                Board_DisplayAdviceAgain(board, holder, 15, 42);
    //                Sexy_String_Delete(holder);
    //                mHugeWaveCountDown = 750;
    //                return;
    //            }
    //            Board_NextWaveComing(board);
    //        }
    //
    //        if (mZombieCountDown != 0) {
    //            return;
    //        }
    //        Board_SpawnZombieWave(board);
    //        board[5549] = Board_TotalZombiesHealthInWave(board, mCurrentWave -1);
    //        //mZombieHealthWaveStart = Board_TotalZombiesHealthInWave(board,mCurrentWave - 1);
    //        if (Board_IsFlagWave(board, mCurrentWave)) {
    //            board[5548] = 0;//  mZombieHealthToNextWave = 0;
    //            board[5550] = 0;//  mZombieCountDown = 4500;
    //        } else {
    //            board[5548] = (int) (RandRangeFloat(0.5f, 0.65f) * board[5549]);
    //            board[5550] = 750;//   mZombieCountDown = 750;
    //        }
    //        board[5551] = mZombieCountDown;
    //        return;
    //    }
    return old_Board_UpdateZombieSpawning(board);
}

void Board_UpdateIce(Board *board) {
    if (requestPause) {
        // 如果开了高级暂停
        return;
    }
    return old_Board_UpdateIce(board);
}

void Board_DrawCoverLayer(Board *board, Sexy::Graphics *graphics, int theRow) {
    BackgroundType mBackgroundType = board->mBackgroundType;
    if (mBackgroundType < BackgroundType::BACKGROUND_1_DAY || hideCoverLayer) {
        // 如果背景非法，或玩家“隐藏草丛和电线杆”，则终止绘制函数
        return;
    }
    LawnApp *lawnApp = board->mApp;
    if (mBackgroundType <= BackgroundType::BACKGROUND_4_FOG) {
        // 如果是前院(0 1)或者泳池(2 3)，则绘制草丛。整个草丛都是动画而非贴图，没有僵尸来的时候草丛会保持在动画第一帧。
        Reanimation *reanimation = LawnApp_ReanimationTryToGet(lawnApp, board->mCoverLayerAnimIDs[theRow]);
        if (reanimation != nullptr) {
            Reanimation_Draw(reanimation, graphics);
        }
    }
    if (theRow == 6) {
        // 绘制栏杆和电线杆
        switch (mBackgroundType) {
            case BackgroundType::BACKGROUND_1_DAY: // 前院白天
                if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON) {
                    // 在重型武器关卡中不绘制栏杆。
                    return;
                }
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND1_COVER_Addr, 684, 557);
                break;
            case BackgroundType::BACKGROUND_2_NIGHT: // 前院夜晚
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND2_COVER_Addr, 684, 557);
                break;
            case BackgroundType::BACKGROUND_3_POOL: // 泳池白天
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND3_COVER_Addr, 671, 613);
                break;
            case BackgroundType::BACKGROUND_4_FOG: // 泳池夜晚
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND4_COVER_Addr, 672, 613);
                break;
            case BackgroundType::BACKGROUND_5_ROOF: // 屋顶白天
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ROOF_TREE_Addr, board->mOffsetMoved * 1.5f + 628, -60);
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ROOF_POLE_Addr, board->mOffsetMoved * 2.0f + 628, -60);
                break;
            case BackgroundType::BACKGROUND_6_BOSS:
                // 可在此处添加代码绘制月夜电线杆喔
                //                if(LawnApp_IsFinalBossLevel(lawnApp))  return;

                Sexy_Graphics_DrawImage(graphics, addonImages.trees_night, board->mOffsetMoved * 1.5f + 628, -60);
                Sexy_Graphics_DrawImage(graphics, addonImages.pole_night, board->mOffsetMoved * 2.0f + 628, -60);
                break;
            default:
                return;
        }
    }
}

void Board_PickBackground(Board *board) {
    // 用于控制关卡的场地选取。可选择以下场地：前院白天/夜晚，泳池白天/夜晚，屋顶白天/夜晚
    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN) {
        board->mBackgroundType = BackgroundType::BACKGROUND_3_POOL;
        Board_LoadBackgroundImages(board);
        board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
        board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
        board->mPlantRow[2] = PlantRowType::PLANTROW_POOL;
        board->mPlantRow[3] = PlantRowType::PLANTROW_POOL;
        board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
        board->mPlantRow[5] = PlantRowType::PLANTROW_NORMAL;
        Board_InitCoverLayer(board);
        Board_SetGrids(board);
    } else if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_POOL_PARTY) {
        board->mBackgroundType = BackgroundType::BACKGROUND_3_POOL;
        Board_LoadBackgroundImages(board);
        board->mPlantRow[0] = PlantRowType::PLANTROW_POOL;
        board->mPlantRow[1] = PlantRowType::PLANTROW_POOL;
        board->mPlantRow[2] = PlantRowType::PLANTROW_POOL;
        board->mPlantRow[3] = PlantRowType::PLANTROW_POOL;
        board->mPlantRow[4] = PlantRowType::PLANTROW_POOL;
        board->mPlantRow[5] = PlantRowType::PLANTROW_NORMAL;
        Board_InitCoverLayer(board);
        Board_SetGrids(board);
    } else {
        switch (VSBackGround) {
            case 1:
                board->mBackgroundType = BackgroundType::BACKGROUND_1_DAY;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_DIRT;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 2:
                board->mBackgroundType = BackgroundType::BACKGROUND_2_NIGHT;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_DIRT;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 3:
                board->mBackgroundType = BackgroundType::BACKGROUND_3_POOL;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_POOL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_POOL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_NORMAL;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 4:
                board->mBackgroundType = BackgroundType::BACKGROUND_4_FOG;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_POOL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_POOL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_NORMAL;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 5:
                board->mBackgroundType = BackgroundType::BACKGROUND_5_ROOF;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_DIRT;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                if (lawnApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    Board_AddPlant(board, 0, 1, SeedType::SEED_FLOWERPOT, SeedType::SEED_NONE, 1, 0);
                    Board_AddPlant(board, 0, 3, SeedType::SEED_FLOWERPOT, SeedType::SEED_NONE, 1, 0);
                    for (int i = 3; i < 5; ++i) {
                        for (int j = 0; j < 5; ++j) {
                            Board_AddPlant(board, i, j, SeedType::SEED_FLOWERPOT, SeedType::SEED_NONE, 1, 0);
                        }
                    }
                }
                break;
            case 6:
                board->mBackgroundType = BackgroundType::BACKGROUND_6_BOSS;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_DIRT;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                if (lawnApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    Board_AddPlant(board, 0, 1, SeedType::SEED_FLOWERPOT, SeedType::SEED_NONE, 1, 0);
                    Board_AddPlant(board, 0, 3, SeedType::SEED_FLOWERPOT, SeedType::SEED_NONE, 1, 0);
                    for (int i = 3; i < 4; ++i) {
                        for (int j = 0; j < 5; ++j) {
                            Board_AddPlant(board, i, j, SeedType::SEED_FLOWERPOT, SeedType::SEED_NONE, 1, 0);
                        }
                    }
                }
                break;
            case 7:
                board->mBackgroundType = BackgroundType::BACKGROUND_GREENHOUSE;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_DIRT;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 8:
                board->mBackgroundType = BackgroundType::BACKGROUND_MUSHROOM_GARDEN;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_DIRT;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 9:
                board->mBackgroundType = BackgroundType::BACKGROUND_ZOMBIQUARIUM;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[1] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[2] = PlantRowType::PLANTROW_POOL;
                board->mPlantRow[3] = PlantRowType::PLANTROW_POOL;
                board->mPlantRow[4] = PlantRowType::PLANTROW_NORMAL;
                board->mPlantRow[5] = PlantRowType::PLANTROW_NORMAL;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            default:
                old_Board_PickBackground(board);
        };
    }
    mBoardBackground = board->mBackgroundType;
}

bool Board_StageIsNight(Board *board) {
    // 关系到天上阳光掉落与否。
    BackgroundType mBackground = board->mBackgroundType;
    return mBackground == BackgroundType::BACKGROUND_2_NIGHT || mBackground == BackgroundType::BACKGROUND_4_FOG || mBackground == BackgroundType::BACKGROUND_MUSHROOM_GARDEN
        || mBackground == BackgroundType::BACKGROUND_6_BOSS;
}

bool Board_StageHasPool(Board *board) {
    // 关系到泳池特有的僵尸，如救生圈僵尸、海豚僵尸、潜水僵尸在本关出现与否。此处我们添加水族馆场景。
    BackgroundType mBackground = board->mBackgroundType;
    //    return mBackground == BackgroundType::Zombiquarium || old_Board_StageHasPool(board);
    return (mBackground == BackgroundType::BACKGROUND_ZOMBIQUARIUM && board->mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM) || mBackground == BackgroundType::BACKGROUND_3_POOL
        || mBackground == BackgroundType::BACKGROUND_4_FOG;
}

bool Board_StageHasRoof(Board *board) {
    BackgroundType mBackground = board->mBackgroundType;
    return mBackground == BackgroundType::BACKGROUND_5_ROOF || mBackground == BackgroundType::BACKGROUND_6_BOSS;
}

bool Board_StageHas6Rows(Board *board) {
    // 关系到第六路可否操控（比如种植植物）。
    BackgroundType mBackground = board->mBackgroundType;
    return mBackground == BackgroundType::BACKGROUND_3_POOL || mBackground == BackgroundType::BACKGROUND_4_FOG;
}


void Board_UpdateFwoosh(Board *board) {
    if (requestPause) {
        return;
    }
    old_Board_UpdateFwoosh(board);
}

void Board_UpdateFog(Board *board) {
    if (requestPause) {
        return;
    }
    old_Board_UpdateFog(board);
}

void Board_DrawFog(Board *board, Sexy::Graphics *g) {
    if (noFog) {
        return;
    }
    old_Board_DrawFog(board, g);
}

Zombie *Board_AddZombieInRow(Board *board, ZombieType theZombieType, int theRow, int theFromWave, bool playAnim) {
    // 修复蹦极僵尸出现时草丛也会摇晃
    if (theZombieType == ZombieType::ZOMBIE_BUNGEE)
        playAnim = false;
    return old_Board_AddZombieInRow(board, theZombieType, theRow, theFromWave, playAnim);
}

// void (*old_Board_UpdateCoverLayer)(Board *board);
//
// void Board_UpdateCoverLayer(Board *board) {
//     if (requestPause) {
//         return;
//     }
//     old_Board_UpdateCoverLayer(board);
// }

void Board_SpeedUpUpdate(Board *board) {
    Board_UpdateGridItems(board);
    Board_UpdateFwoosh(board);
    Board_UpdateGame(board);
    Board_UpdateFog(board);
    //    Board_UpdateCoverLayer(board);
    Challenge_Update(board->mChallenge);
}

bool TRect_Contains(TRect *rect, int x, int y) {
    return rect->mX < x && rect->mY < y && rect->mX + rect->mWidth > x && rect->mY + rect->mHeight > y;
}

void Board_Update(Board *board) {
    isMainMenu = false;
    mBoardBackground = board->mBackgroundType;
    GamepadControls *gamepadControls1 = board->mGamepadControls1;
    GamepadControls *gamepadControls2 = board->mGamepadControls2;

    if (requestDrawButterInCursor) {
        Zombie *zombieUnderButter = Board_ZombieHitTest(board, gamepadControls2->mCursorPositionX, gamepadControls2->mCursorPositionY, 1);
        if (zombieUnderButter != nullptr) {
            Zombie_AddButter(zombieUnderButter);
        }
    }

    if (requestDrawShovelInCursor) {
        Plant *plantUnderShovel = Board_ToolHitTest(board, gamepadControls1->mCursorPositionX, gamepadControls1->mCursorPositionY);
        if (plantUnderShovel != nullptr) {
            // 让这个植物高亮
            plantUnderShovel->mEatenFlashCountdown = 1000; // 1000是为了不和其他闪光效果冲突
        }
    }

    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN && lawnApp->mGameScene == GameScenes::SCENE_PLAYING) {
        Zombie *zombieUnderButter = Board_ZombieHitTest(board, gamepadControls1->mCursorPositionX, gamepadControls1->mCursorPositionY, 1);
        if (zombieUnderButter != nullptr) {
            Zombie_AddButter(zombieUnderButter);
        }
        if (gamepadControls2->mPlayerIndex2 != -1) {
            Zombie *zombieUnderButter = Board_ZombieHitTest(board, gamepadControls2->mCursorPositionX, gamepadControls2->mCursorPositionY, 1);
            if (zombieUnderButter != nullptr) {
                Zombie_AddButter(zombieUnderButter);
            }
        }
    }
    //    GameButton_Update(mBoardMenuButton);
    if (isKeyboardTwoPlayerMode) {
        gamepadControls1->mIsInShopSeedBank = false;
        gamepadControls2->mIsInShopSeedBank = false;
        gamepadControls1->mPlayerIndex2 = 0;
        gamepadControls2->mPlayerIndex2 = 1;
        gamepadControls1->mGamepadState = 7;
        gamepadControls2->mGamepadState = 7;
    }

    if (!board->mPaused && board->mTimeStopCounter <= 0) {
        switch (speedUpMode) {
            case 1:
                if (speedUpCounter++ % 5 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 2:
                if (speedUpCounter++ % 2 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 3:
                Board_SpeedUpUpdate(board);
                break;
            case 4:
                Board_SpeedUpUpdate(board);
                if (speedUpCounter++ % 2 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 5:
                for (int i = 0; i < 2; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 6:
                for (int i = 0; i < 4; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 7:
                for (int i = 0; i < 9; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            default:
                break;
        }

        // 为夜晚泳池场景补全泳池反射闪光特效
        //        if ( board->mBackgroundType == BackgroundType::BACKGROUND_4_FOG && board->mPoolSparklyParticleID == 0 && board->mDrawCount > 0 ){
        //            TodParticleSystem * poolSparklyParticle = LawnApp_AddTodParticle(board->mApp, 450.0, 295.0, 220000, a::PARTICLE_POOL_SPARKLY);
        //            board->mPoolSparklyParticleID = LawnApp_ParticleGetID(board->mApp, poolSparklyParticle);
        //        }
    }

    if (ClearAllPlant) {
        Board_RemoveAllPlants(board);
        ClearAllPlant = false;
    }

    if (clearAllZombies) {
        Board_RemoveAllZombies(board);
        clearAllZombies = false;
    }

    if (clearAllGraves) {
        GridItem *gridItem = nullptr;
        while (Board_IterateGridItems(board, &gridItem)) {
            if (gridItem->mGridItemType == GridItemType::GRIDITEM_GRAVESTONE) {
                GridItem_GridItemDie(gridItem);
            }
        }
        clearAllGraves = false;
    }

    if (clearAllMowers) {
        if (lawnApp->mGameScene == GameScenes::SCENE_PLAYING) {
            Board_RemoveAllMowers(board);
        }
        clearAllMowers = false;
    }

    if (recoverAllMowers) {
        if (lawnApp->mGameScene == GameScenes::SCENE_PLAYING) {
            //            Board_RemoveAllMowers(board);
            Board_ResetLawnMowers(board);
        }
        recoverAllMowers = false;
    }

    if (passNowLevel) {
        board->mLevelComplete = true;
        board->mApp->mBoardResult = board->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS ? BoardResult::BOARDRESULT_VS_PLANT_WON : BoardResult::BOARDRESULT_WON;
        passNowLevel = false;
    }
    // 魅惑所有僵尸
    if (hypnoAllZombies) {
        Zombie *zombie = nullptr;
        while (Board_IterateZombies(board, &zombie)) {
            if (zombie->mZombieType != ZombieType::ZOMBIE_BOSS) {
                zombie->mMindControlled = true;
            }
        }
        hypnoAllZombies = false;
    }

    if (freezeAllZombies) {
        for (Zombie *zombie = nullptr; Board_IterateZombies(board, &zombie); Zombie_HitIceTrap(zombie))
            ;
        freezeAllZombies = false;
    }

    if (startAllMowers) {
        if (lawnApp->mGameScene == GameScenes::SCENE_PLAYING)
            for (int *lawnMower = nullptr; Board_IterateLawnMowers(board, &lawnMower); LawnMower_StartMower(lawnMower))
                ;
        startAllMowers = false;
    }

    // 修改卡槽
    if (setSeedPacket && choiceSeedType != SeedType::SEED_NONE) {
        if (targetSeedBank == 1) {
            if (choiceSeedType < SeedType::NUM_SEED_TYPES && !gamepadControls1->mIsZombie) {
                board->mSeedBank1->mSeedPackets[choiceSeedPacketIndex].mPacketType = isImitaterSeed ? SeedType::SEED_IMITATER : choiceSeedType;
                board->mSeedBank1->mSeedPackets[choiceSeedPacketIndex].mImitaterType = isImitaterSeed ? choiceSeedType : SeedType::SEED_NONE;
            } else if (choiceSeedType > SeedType::SEED_ZOMBIE_TOMBSTONE && gamepadControls1->mIsZombie) // IZ模式里用不了墓碑
                board->mSeedBank1->mSeedPackets[choiceSeedPacketIndex].mPacketType = choiceSeedType;
        } else if (targetSeedBank == 2 && board->mSeedBank2 != nullptr) {
            if (choiceSeedType < SeedType::NUM_SEED_TYPES && !gamepadControls2->mIsZombie) {
                board->mSeedBank2->mSeedPackets[choiceSeedPacketIndex].mPacketType = isImitaterSeed ? SeedType::SEED_IMITATER : choiceSeedType;
                board->mSeedBank2->mSeedPackets[choiceSeedPacketIndex].mImitaterType = isImitaterSeed ? choiceSeedType : SeedType::SEED_NONE;
            } else if (Challenge_IsZombieSeedType(choiceSeedType) && gamepadControls2->mIsZombie)
                board->mSeedBank2->mSeedPackets[choiceSeedPacketIndex].mPacketType = choiceSeedType;
        }
        setSeedPacket = false;
    }

    if (passNowLevel) {
        board->mLevelComplete = true;
        board->mApp->mBoardResult = board->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS ? BoardResult::BOARDRESULT_VS_PLANT_WON : BoardResult::BOARDRESULT_WON;
        passNowLevel = false;
    }

    // 布置选择阵型
    if (layChoseFormation) // 用按钮触发, 防止进入游戏时自动布阵
    {
        if (formationId != -1) {
            const char *formation = GetFormationByIndex(formationId);
            char *copiedStr = strdup(formation);
            Board_LoadFormation(board, copiedStr);
        }
        layChoseFormation = false;
    }

    // 布置粘贴阵型
    if (layPastedFormation) {
        if (customFormation != "") {
            char *copiedStr = strdup(customFormation.c_str());
            Board_LoadFormation(board, copiedStr);
        }
        layPastedFormation = false;
    }

    if (ladderBuild) {
        if (theBuildLadderX < 9 && theBuildLadderY < (Board_StageHas6Rows(board) ? 6 : 5) && Board_GetLadderAt(board, theBuildLadderX, theBuildLadderY) == nullptr)
            // 防止选“所有行”或“所有列”的时候放置到场外
            Board_AddALadder(board, theBuildLadderX, theBuildLadderY);
        ladderBuild = false;
    }


    // 植物放置
    if (plantBuild && theBuildPlantType != SeedType::SEED_NONE) {
        int colsCount = (theBuildPlantType == SeedType::SEED_COBCANNON) ? 8 : 9; // 玉米加农炮不种在九列
        int width = (theBuildPlantType == SeedType::SEED_COBCANNON) ? 2 : 1;     // 玉米加农炮宽度两列
        int rowsCount = Board_StageHas6Rows(board) ? 6 : 5;
        bool isIZMode = LawnApp_IsIZombieLevel(lawnApp);
        // 全场
        if (theBuildPlantX == 9 && theBuildPlantY == 6) {
            for (int x = 0; x < colsCount; x += width) {
                for (int y = 0; y < rowsCount; y++) {
                    Plant *theBuiltPlant = Board_AddPlant(board, x, y, theBuildPlantType, (isImitaterPlant ? SeedType::SEED_IMITATER : SeedType::SEED_NONE), 0, true);
                    if (isImitaterPlant)
                        theBuiltPlant->SetImitaterFilterEffect();
                    if (isIZMode)
                        Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
                }
            }
        }
        // 单行
        else if (theBuildPlantX == 9 && theBuildPlantY < 6) {
            for (int x = 0; x < colsCount; x += width) {
                Plant *theBuiltPlant = Board_AddPlant(board, x, theBuildPlantY, theBuildPlantType, (isImitaterPlant ? SeedType::SEED_IMITATER : SeedType::SEED_NONE), 0, true);
                if (isImitaterPlant)
                    theBuiltPlant->SetImitaterFilterEffect();
                if (isIZMode)
                    Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
            }
        }
        // 单列
        else if (theBuildPlantX < 9 && theBuildPlantY == 6) {
            for (int y = 0; y < rowsCount; y++) {
                Plant *theBuiltPlant = Board_AddPlant(board, theBuildPlantX, y, theBuildPlantType, (isImitaterPlant ? SeedType::SEED_IMITATER : SeedType::SEED_NONE), 0, true);
                if (isImitaterPlant)
                    theBuiltPlant->SetImitaterFilterEffect();
                if (isIZMode)
                    Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
            }
        }
        // 单格
        else if (theBuildPlantX < colsCount && theBuildPlantY < rowsCount) {
            Plant *theBuiltPlant = Board_AddPlant(board, theBuildPlantX, theBuildPlantY, theBuildPlantType, (isImitaterPlant ? SeedType::SEED_IMITATER : SeedType::SEED_NONE), 0, true);
            if (isImitaterPlant)
                theBuiltPlant->SetImitaterFilterEffect();
            if (isIZMode)
                Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
        }
        plantBuild = false;
    }

    // 僵尸放置
    if (zombieBuild && theBuildZombieType != ZombieType::ZOMBIE_INVALID) {
        if (theBuildZombieType == ZombieType::ZOMBIE_BOSS)
            Board_AddZombieInRow(board, theBuildZombieType, 0, 0, true);
        else {
            int colsCount = 9;
            int rowsCount = Board_StageHas6Rows(board) ? 6 : 5;
            // 僵尸出生线
            if (BuildZombieX == 10 && BuildZombieY == 6)
                for (int y = 0; y < rowsCount; ++y)
                    Board_AddZombieInRow(board, theBuildZombieType, y, board->mCurrentWave, true);
            // 僵尸出生点
            else if (BuildZombieX == 10 && BuildZombieY < 6)
                Board_AddZombieInRow(board, theBuildZombieType, BuildZombieY, board->mCurrentWave, true);
            // 全场
            else if (BuildZombieX == 9 && BuildZombieY == 6)
                for (int x = 0; x < colsCount; ++x)
                    for (int y = 0; y < rowsCount; ++y)
                        Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, x, y);
            // 单行
            else if (BuildZombieX == 9 && BuildZombieY < 6)
                for (int x = 0; x < colsCount; ++x)
                    Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, x, BuildZombieY);
            // 单列
            else if (BuildZombieX < 9 && BuildZombieY == 6)
                for (int y = 0; y < rowsCount; ++y)
                    Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, BuildZombieX, y);
            // 单格
            else if (BuildZombieX < colsCount && BuildZombieY < rowsCount)
                Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, BuildZombieX, BuildZombieY);
        }
        zombieBuild = false;
    }

    // 放置墓碑
    if (graveBuild) {
        int colsCount = 9;
        int rowsCount = Board_StageHas6Rows(board) ? 6 : 5;
        // 全场
        if (BuildZombieX == 9 && BuildZombieY == 6) {
            GridItem *gridItem = nullptr;
            while (Board_IterateGridItems(board, &gridItem)) {
                if (gridItem->mGridItemType == GridItemType::GRIDITEM_GRAVESTONE) {
                    GridItem_GridItemDie(gridItem);
                }
            }
            for (int x = 0; x < colsCount; ++x) {
                for (int y = 0; y < rowsCount; ++y) {
                    Challenge_GraveDangerSpawnGraveAt(board->mChallenge, x, y);
                }
            }
        }
        // 单行
        else if (BuildZombieX == 9 && BuildZombieY < 6) {
            GridItem *gridItem = nullptr;
            while (Board_IterateGridItems(board, &gridItem)) {
                if (gridItem->mGridItemType == GridItemType::GRIDITEM_GRAVESTONE && gridItem->mGridY == BuildZombieY) {
                    GridItem_GridItemDie(gridItem);
                }
            }
            for (int x = 0; x < colsCount; ++x) {
                Challenge_GraveDangerSpawnGraveAt(board->mChallenge, x, BuildZombieY);
            }
        }
        // 单列
        else if (BuildZombieX < 9 && BuildZombieY == 6) {
            GridItem *gridItem = nullptr;
            while (Board_IterateGridItems(board, &gridItem)) {
                if (gridItem->mGridItemType == GridItemType::GRIDITEM_GRAVESTONE && gridItem->mGridX == BuildZombieX) {
                    GridItem_GridItemDie(gridItem);
                }
            }
            for (int y = 0; y < rowsCount; ++y) {
                Challenge_GraveDangerSpawnGraveAt(board->mChallenge, BuildZombieX, y);
            }
        }
        // 单格
        else if (BuildZombieX < 9 && BuildZombieY < 6) {
            Challenge_GraveDangerSpawnGraveAt(board->mChallenge, BuildZombieX, BuildZombieY);
        }
        graveBuild = false;
    }

    // 出怪设置
    if (buttonSetSpawn && choiceSpawnMode != 0) {
        int typesCount = 0;                          // 已选僵尸种类数
        int typesList[ZombieType::NUM_ZOMBIE_TYPES]; // 已选僵尸种类列表
        // 将僵尸代号放入种类列表, 并更新已选种类数
        for (int type = 0; type < ZombieType::NUM_ZOMBIE_TYPES; ++type) {
            if (checkZombiesAllowed[type] && type != ZombieType::ZOMBIE_BUNGEE) // 飞贼僵尸不应作为正常僵尸出现在出怪列表中
            {
                typesList[typesCount] = type;
                ++typesCount;
            }
        }
        if (typesCount > 0) // 设置出怪需要选择至少 1 种除飞贼以外的僵尸
        {
            // 自然出怪
            if (choiceSpawnMode == 1) {
                // 清空出怪列表
                for (int wave = 0; wave < board->mNumWaves; ++wave) {
                    for (int index = 0; index < MAX_ZOMBIES_IN_WAVE; ++index)
                        board->mZombiesInWave[wave][index] = ZombieType::ZOMBIE_INVALID;
                }
                // 设置游戏中的僵尸允许类型
                for (int type = 0; type < ZombieType::NUM_ZOMBIE_TYPES; ++type)
                    board->mZombieAllowed[type] = checkZombiesAllowed[type];
                board->mZombieAllowed[ZombieType::ZOMBIE_NORMAL] = true; // 自然出怪下必须含有普通僵尸
                // 由游戏生成出怪列表
                Board_PickZombieWaves(board);
            }
            // 极限出怪
            else if (choiceSpawnMode == 2) {
                int indexInLevel = 0;
                // 均匀填充出怪列表
                for (int wave = 0; wave < board->mNumWaves; ++wave) {
                    for (int indexInWave = 0; indexInWave < MAX_ZOMBIES_IN_WAVE; ++indexInWave) {
                        // 使用僵尸的“关内序号”遍历设置出怪可能会比使用“波内序号”更加均匀
                        board->mZombiesInWave[wave][indexInWave] = (ZombieType)typesList[indexInLevel % typesCount];
                        ++indexInLevel;
                    }
                    if (Board_IsFlagWave(board, wave)) {
                        board->mZombiesInWave[wave][0] = ZombieType::ZOMBIE_FLAG; // 生成旗帜僵尸
                        if (checkZombiesAllowed[ZombieType::ZOMBIE_BUNGEE]) {
                            // 生成飞贼僵尸
                            for (int index : {1, 2, 3, 4})
                                board->mZombiesInWave[wave][index] = ZombieType::ZOMBIE_BUNGEE;
                        }
                    }
                }
                // 不能只出雪人僵尸, 在第一波生成 1 只普通僵尸
                if (checkZombiesAllowed[ZombieType::ZOMBIE_YETI] && typesCount == 1)
                    board->mZombiesInWave[0][0] = ZombieType::ZOMBIE_NORMAL;
            }
            // 重新生成选卡预览僵尸
            if (lawnApp->mGameScene == GameScenes::SCENE_LEVEL_INTRO) {
                Board_RemoveCutsceneZombies(board);
                board->mCutScene->mPlacedZombies = false;
            }
        }
        buttonSetSpawn = false;
    }

    Board_UpdateButtons(board);
    return old_Board_Update(board);
}

int Board_GetNumWavesPerFlag(Board *board) {
    // 修改此函数，以做到在进度条上正常绘制旗帜波的旗帜。
    LawnApp *lawnApp = board->mApp;
    int mNumWaves = board->mNumWaves;
    if (LawnApp_IsFirstTimeAdventureMode(lawnApp) && mNumWaves < 10) {
        return mNumWaves;
    }
    // 额外添加一段判断逻辑，判断关卡代码20且波数少于10的情况
    if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && mNumWaves < 10) {
        return mNumWaves;
    }
    return 10;
}

bool Board_IsFlagWave(Board *board, int currentWave) {
    // 修改此函数，以做到正常出旗帜波僵尸。
    if (!normalLevel) {
        return old_Board_IsFlagWave(board, currentWave);
    }
    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS)
        return true;
    if (LawnApp_IsFirstTimeAdventureMode(lawnApp) && board->mLevel == 1)
        return false;
    int mNumWavesPerFlag = Board_GetNumWavesPerFlag(board);
    return currentWave % mNumWavesPerFlag == mNumWavesPerFlag - 1;
}

void Board_SpawnZombieWave(Board *board) {
    // 在对战模式中放出一大波僵尸时播放大波僵尸音效
    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        LawnApp_PlaySample(lawnApp, *Sexy_SOUND_HUGE_WAVE_Addr);
    }
    old_Board_SpawnZombieWave(board);
}

void Board_DrawProgressMeter(Board *board, Sexy::Graphics *graphics, int a3, int a4) {
    // 修改此函数，以做到在进度条上正常绘制旗帜波的旗帜。
    if (normalLevel) {
        LawnApp *lawnApp = board->mApp;
        if (LawnApp_IsAdventureMode(lawnApp) && Board_ProgressMeterHasFlags(board)) {
            lawnApp->mGameMode = GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON; // 修改关卡信息为非冒险模式
            old_Board_DrawProgressMeter(board, graphics, a3, a4);
            lawnApp->mGameMode = GameMode::GAMEMODE_ADVENTURE; // 再把关卡信息改回冒险模式
            return;
        }
        old_Board_DrawProgressMeter(board, graphics, a3, a4);
    } else {
        old_Board_DrawProgressMeter(board, graphics, a3, a4);
    }
}

bool Board_IsLevelDataLoaded(Board *board) {
    // 确保在开启原版难度时，所有用到levels.xml的地方都不生效
    if (normalLevel)
        return false;
    return old_Board_IsLevelDataLoaded(board);
}

bool Board_NeedSaveGame(Board *board) {
    // 可以让结盟关卡存档，但是好多BUG啊
    //    if (LawnApp_IsCoopMode(*((int **) board + 69))) {
    //        return true;
    //    }
    return old_Board_NeedSaveGame(board);
}

void Board_DrawHammerButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) {
    if (!keyboardMode)
        return;
    float tmp = graphics->mTransY;
    TRect rect;
    Board_GetButterButtonRect(&rect, board);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, rect.mX, rect.mY);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_HAMMER_ICON_Addr, rect.mX - 7, rect.mY - 3);

    if (Sexy_GamepadApp_HasGamepad(lawnApp) || (lawnApp->mGamePad1IsOn && lawnApp->mGamePad2IsOn)) {
        Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr, rect.mX + 36, rect.mY + 40, 2);
    } else {
        Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS2_Addr, rect.mX + 36, rect.mY + 40, 2);
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
    graphics->mTransY = tmp;
}

void Board_DrawButterButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) {
    if (!LawnApp_IsCoopMode(lawnApp)) {
        if (!LawnApp_IsAdventureMode(lawnApp))
            return;
        if (lawnApp->mTwoPlayerState == -1)
            return;
    }
    float tmp = graphics->mTransY;
    TRect rect;
    Board_GetButterButtonRect(&rect, board);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, rect.mX, rect.mY);
    if (board->mChallenge->mChallengeState == ChallengeState::STATECHALLENGE_SHOVEL_FLASHING) {
        Color color;
        GetFlashingColor(&color, board->mMainCounter, 75);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        Sexy_Graphics_SetColor(graphics, &color);
    }
    // 实现拿着黄油的时候不在栏内绘制黄油
    if (!requestDrawButterInCursor) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BUTTER_ICON_Addr, rect.mX - 7, rect.mY - 3);
    }
    if (keyboardMode) {
        Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr, rect.mX + 36, rect.mY + 40, 2);
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
    graphics->mTransY = tmp;
}

void Board_DrawShovelButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) {
    // 实现玩家拿着铲子时不在ShovelBank中绘制铲子、实现在对战模式中添加铲子按钮

    if (lawnApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        //        LOGD("%d %d",rect[0],rect[1]);
        // return;  原版游戏在此处就return了，所以对战中不绘制铲子按钮。
        if (keyboardMode)
            return;
        TodDrawImageScaledF(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, mTouchVSShovelRect.mX, mTouchVSShovelRect.mY, 0.8f, 0.8f);
        if (!requestDrawShovelInCursor)
            TodDrawImageScaledF(graphics, *Sexy_IMAGE_SHOVEL_Addr, -6, 78, 0.8f, 0.8f);
        return;
    }
    float tmp = graphics->mTransY;
    TRect rect;
    Board_GetShovelButtonRect(&rect, board);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, rect.mX, rect.mY);
    if (board->mChallenge->mChallengeState == ChallengeState::STATECHALLENGE_SHOVEL_FLASHING) {
        Color color;
        GetFlashingColor(&color, board->mMainCounter, 75);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        Sexy_Graphics_SetColor(graphics, &color);
    }
    // 实现拿着铲子的时候不在栏内绘制铲子
    if (!requestDrawShovelInCursor) {
        if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND) {
            Challenge *challenge = board->mChallenge;
            if (challenge->mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && lawnApp->mGameScene == GameScenes::SCENE_PLAYING) {
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ZEN_MONEYSIGN_Addr, rect.mX - 7, rect.mY - 3);
            } else {
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVEL_Addr, rect.mX - 7, rect.mY - 3);
            }
        } else {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVEL_Addr, rect.mX - 7, rect.mY - 3);
        }
    }
    if (keyboardMode) {
        if (LawnApp_IsCoopMode(lawnApp)) {
            Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr, rect.mX + 40, rect.mY + 40, 1);
        } else {
            if (Sexy_GamepadApp_HasGamepad(lawnApp) || (lawnApp->mGamePad1IsOn && lawnApp->mGamePad2IsOn)) {
                Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr, rect.mX + 50, rect.mY + 40, 1);
            } else {
                Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS2_Addr, rect.mX + 50, rect.mY + 40, 1);
            }
        }
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
    graphics->mTransY = tmp;
}

void Board_DrawShovel(Board *board, Sexy::Graphics *graphics) {
    // 实现拿着铲子、黄油的时候不在栏内绘制铲子、黄油，同时为对战模式添加铲子按钮
    LawnApp *lawnApp = board->mApp;
    GameMode mGameMode = lawnApp->mGameMode;
    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON)
        return;
    if (mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM || mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN) { // 如果是花园或智慧树
        return Board_DrawZenButtons(board, graphics);
    }
    if (board->mShowHammer) { // 绘制锤子按钮
        Board_DrawHammerButton(board, graphics, lawnApp);
    }
    if (board->mShowButter) { // 绘制黄油按钮
        Board_DrawButterButton(board, graphics, lawnApp);
    }
    if (board->mShowShovel) { // 绘制铲子按钮
        Board_DrawShovelButton(board, graphics, lawnApp);
    }
}

void Board_Pause(Board *board, bool a2) {
    //  能在这里得知游戏是否暂停
    //    if (a2) Music2_StopAllMusic((Music2*)board->mApp->mMusic);
    //    else Music2_StartGameMusic((Music2*)board->mApp->mMusic, true);
    old_Board_Pause(board, a2);
}

void Board_AddSecondPlayer(Board *board, int a2) {
    // 去除加入2P时的声音

    //    (*(void (**)(int, int, int))(*(uint32_t *)this[69] + 680))(this[69], Sexy::SOUND_CHIME, 1);
    //    ((void (*)(int *, const char *, int))loc_2F098C)(v2 + 25, "[P2_JOINED]", 11);
    board->mUnkIntSecondPlayer1 = 3;
    board->mUnkBoolSecondPlayer = false;
    board->mUnkIntSecondPlayer2 = 0;
}

bool Board_IsLastStandFinalStage(Board *board) {
    // 无尽坚不可摧
    if (endlessLastStand)
        return false;
    return board->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND && board->mChallenge->mSurvivalStage == 4;
}

Plant *Board_GetFlowerPotAt(Board *board, int theGridX, int theGridY) {
    // 修复 屋顶关卡加农炮无法种植在第三第四列的组合上
    Plant *plant = nullptr;
    while (Board_IteratePlants(board, &plant)) {
        if (plant->mSeedType == SeedType::SEED_FLOWERPOT && plant->mRow == theGridY && plant->mPlantCol == theGridX && !Plant_NotOnGround(plant)) {
            return plant;
        }
    }
    return nullptr;
}

Plant *Board_GetPumpkinAt(Board *board, int theGridX, int theGridY) {
    Plant *plant = nullptr;
    while (Board_IteratePlants(board, &plant)) {
        if (plant->mSeedType == SeedType::SEED_PUMPKINSHELL && plant->mRow == theGridY && plant->mPlantCol == theGridX && !Plant_NotOnGround(plant)) {
            return plant;
        }
    }
    return nullptr;
}

void Board_DoPlantingEffects(Board *board, int theGridX, int theGridY, Plant *plant) {
    int num = Board_GridToPixelX(board, theGridX, theGridY) + 41;
    int num2 = Board_GridToPixelY(board, theGridX, theGridY) + 74;
    SeedType mSeedType = plant->mSeedType;
    LawnApp *lawnApp = board->mApp;
    if (mSeedType == SeedType::SEED_LILYPAD) {
        num2 += 15;
    } else if (mSeedType == SeedType::SEED_FLOWERPOT) {
        num2 += 30;
    }
    BackgroundType mBackground = board->mBackgroundType;
    if (mBackground == BackgroundType::BACKGROUND_GREENHOUSE) {
        LawnApp_PlayFoley(lawnApp, FoleyType::Ceramic);
        return;
    }
    if (mBackground == BackgroundType::BACKGROUND_ZOMBIQUARIUM) {
        LawnApp_PlayFoley(lawnApp, FoleyType::PlantWater);
        return;
    }

    if (Plant_IsFlying(mSeedType)) {
        LawnApp_PlayFoley(lawnApp, FoleyType::Plant);
        return;
    }
    if (Board_IsPoolSquare(board, theGridX, theGridY)) {
        LawnApp_PlayFoley(lawnApp, FoleyType::PlantWater);
        LawnApp_AddTodParticle(lawnApp, num, num2, 400000, ParticleEffect::PARTICLE_PLANTING_POOL);
        return;
    }

    LawnApp_PlayFoley(lawnApp, FoleyType::Plant);
    //    switch (mSeedType) {
    //        case a::SEED_SUNFLOWER:
    //            LawnApp_PlaySample(lawnApp, Addon_Sounds.achievement);
    //            break;
    //        default:
    //            LawnApp_PlayFoley(lawnApp, FoleyType::Plant);
    //            break;
    //    }
    LawnApp_AddTodParticle(lawnApp, num, num2, 400000, ParticleEffect::PARTICLE_PLANTING);
}


void Board_InitLawnMowers(Board *board) {
    if (banMower)
        return;
    if (board->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN)
        return;
    return old_Board_InitLawnMowers(board);
}


void Board_PickZombieWaves(Board *board) {
    // 有问题，在111和115里，冒险中锤僵尸的mNumWaves从8变6了
    if (board->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BUTTERED_POPCORN && !Board_IsLevelDataLoaded(board)) {
        board->mNumWaves = 20;
        ZombiePicker zombiePicker;
        Board_ZombiePickerInit(&zombiePicker);
        //        ZombieType introducedZombieType = Board_GetIntroducedZombieType(board);
        for (int i = 0; i < board->mNumWaves; i++) {
            Board_ZombiePickerInitForWave(&zombiePicker);
            board->mZombiesInWave[i][0] = ZombieType::ZOMBIE_INVALID;
            bool isFlagWave = Board_IsFlagWave(board, i);
            //            bool isBeforeLastWave = i == mNumWaves - 1;
            int &aZombiePoints = zombiePicker.mZombiePoints;
            aZombiePoints = i * 4 / 5 + 1;
            if (isFlagWave) {
                int num2 = std::min(zombiePicker.mZombiePoints, 8);
                zombiePicker.mZombiePoints = (int)(zombiePicker.mZombiePoints * 2.5f);
                for (int k = 0; k < num2; k++) {
                    Board_PutZombieInWave(board, ZombieType::ZOMBIE_NORMAL, i, &zombiePicker);
                }
                Board_PutZombieInWave(board, ZombieType::ZOMBIE_FLAG, i, &zombiePicker);
            }
            if (i == board->mNumWaves - 1)
                Board_PutZombieInWave(board, ZombieType::ZOMBIE_GARGANTUAR, i, &zombiePicker);
            while (aZombiePoints > 0 && zombiePicker.mZombieCount < MAX_ZOMBIES_IN_WAVE) {
                ZombieType aZombieType = Board_PickZombieType(board, aZombiePoints, i, &zombiePicker);
                Board_PutZombieInWave(board, aZombieType, i, &zombiePicker);
            }
        }
        return;
    }
    if (board->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_POOL_PARTY && !Board_IsLevelDataLoaded(board)) {
        board->mNumWaves = 20;
        ZombiePicker zombiePicker;
        Board_ZombiePickerInit(&zombiePicker);
        //        ZombieType introducedZombieType = Board_GetIntroducedZombieType(board);
        for (int i = 0; i < board->mNumWaves; i++) {
            Board_ZombiePickerInitForWave(&zombiePicker);
            board->mZombiesInWave[i][0] = ZombieType::ZOMBIE_INVALID;
            bool isFlagWave = Board_IsFlagWave(board, i);
            //            bool isBeforeLastWave = i == mNumWaves - 1;
            int &aZombiePoints = zombiePicker.mZombiePoints;
            aZombiePoints = i * 4 / 5 + 1;
            if (isFlagWave) {
                int num2 = std::min(zombiePicker.mZombiePoints, 8);
                zombiePicker.mZombiePoints = (int)(zombiePicker.mZombiePoints * 2.5f);
                for (int k = 0; k < num2; k++) {
                    Board_PutZombieInWave(board, ZombieType::ZOMBIE_NORMAL, i, &zombiePicker);
                }
                Board_PutZombieInWave(board, ZombieType::ZOMBIE_FLAG, i, &zombiePicker);
            }
            while (aZombiePoints > 0 && zombiePicker.mZombieCount < MAX_ZOMBIES_IN_WAVE) {
                ZombieType aZombieType = Board_PickZombieType(board, aZombiePoints, i, &zombiePicker);
                Board_PutZombieInWave(board, aZombieType, i, &zombiePicker);
            }
        }
        return;
    }
    return old_Board_PickZombieWaves(board);
}

int Board_GetLiveGargantuarCount(Board *board) {
    int num = 0;
    Zombie *zombie = nullptr;
    while (Board_IterateZombies(board, (Zombie **)&zombie)) {
        if (!zombie->mDead && zombie->mHasHead && !Zombie_IsDeadOrDying(zombie) && Zombie_IsOnBoard(zombie)
            && (zombie->mZombieType == ZombieType::ZOMBIE_GARGANTUAR || zombie->mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR)) {
            num++;
        }
    }
    return num;
}

int Board_GetLiveZombiesCount(Board *board) {
    int num = 0;
    Zombie *zombie = nullptr;
    while (Board_IterateZombies(board, (Zombie **)&zombie)) {
        if (!zombie->mDead && zombie->mHasHead && !Zombie_IsDeadOrDying(zombie) && Zombie_IsOnBoard(zombie)) {
            num++;
        }
    }
    return num;
}

void Board_UpdateLevelEndSequence(Board *board) {
    // 修复无尽最后一波僵尸出现后高级暂停无法暂停下一关的到来
    if (requestPause)
        return;
    return old_Board_UpdateLevelEndSequence(board);
}

void Board_UpdateGridItems(Board *board) {
    if (requestPause)
        return;
    return old_Board_UpdateGridItems(board);
}

void Board_MouseMove(Board *board, int x, int y) {
    // 无用。鼠标指针移动、但左键未按下时调用
    // LOGD("Move%d %d", x, y);
    old_Board_MouseMove(board, x, y);
    //    positionAutoFix = false;
    //    LawnApp *mApp = board->mApp;
    //    GameMode::GameMode mGameMode = mApp->mGameMode;
    //    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    //    CursorObject* cursorObject = board->mCursorObject1;
    //    CursorType::CursorType mCursorType = cursorObject->mCursorType;
    //    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
    //        gamepadControls1->mCursorPositionX = x - 40;
    //        gamepadControls1->mCursorPositionY = y - 40;
    //    } else if (mCursorType == CursorType::CURSOR_TYPE_WATERING_CAN && mApp->mPlayerInfo->mPurchases[a::STORE_ITEM_GOLD_WATERINGCAN] != 0) {
    //        gamepadControls1->mCursorPositionX = x - 40;
    //        gamepadControls1->mCursorPositionY = y - 40;
    //    }else {
    //        gamepadControls1->mCursorPositionX = x;
    //        gamepadControls1->mCursorPositionY = y;
    //    }
}

bool Board_MouseHitTest(Board *board, int x, int y, HitResult *hitResult, bool playerIndex) {
    LawnApp *mApp = board->mApp;
    GameMode mGameMode = mApp->mGameMode;
    if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        if (TRect_Contains(&mTouchVSShovelRect, x, y)) {
            hitResult->mObjectType = GameObjectType::OBJECT_TYPE_SHOVEL;
            return true;
        }
    } else {
        TRect shovelButtonRect;
        Board_GetShovelButtonRect(&shovelButtonRect, board);
        if (board->mShowShovel && TRect_Contains(&shovelButtonRect, x, y)) {
            hitResult->mObjectType = GameObjectType::OBJECT_TYPE_SHOVEL;
            return true;
        }
    }

    if (LawnApp_IsCoopMode(board->mApp)) {
        TRect butterButtonRect;
        Board_GetButterButtonRect(&butterButtonRect, board);
        if (board->mShowButter && TRect_Contains(&butterButtonRect, x, y)) {
            hitResult->mObjectType = GameObjectType::OBJECT_TYPE_BUTTER;
            return true;
        }
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) {
        TRect rect;
        for (int i = GameObjectType::OBJECT_TYPE_WATERING_CAN; i <= GameObjectType::OBJECT_TYPE_TREE_OF_WISDOM_GARDEN; i++) {
            if (Board_CanUseGameObject(board, (GameObjectType)i)) {
                Board_GetZenButtonRect(&rect, board, (GameObjectType)i);
                if (TRect_Contains(&rect, x, y)) {
                    hitResult->mObjectType = (GameObjectType)i;
                    return true;
                }
            }
        }
    }

    if (old_Board_MouseHitTest(board, x, y, hitResult, playerIndex)) {
        if (hitResult->mObjectType == GameObjectType::OBJECT_TYPE_TREE_OF_WISDOM_GARDEN) {
            hitResult->mObjectType = GameObjectType::OBJECT_TYPE_NONE;
            return false;
        }
        return true;
    }

    GamepadControls *gamepadControls1 = board->mGamepadControls1;
    SeedBank *mSeedBank = GamepadControls_GetSeedBank(gamepadControls1);
    if (SeedBank_ContainsPoint(mSeedBank, x, y)) {
        if (mSeedBank->SeedBank::MouseHitTest(x, y, hitResult)) {
            CursorObject *cursorObject = board->mCursorObject1;
            CursorType mCursorType = cursorObject->mCursorType;
            if (mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_BANK) {
                Board_RefreshSeedPacketFromCursor(board, 0);
            }
            return true;
        }
        hitResult->mObjectType = GameObjectType::OBJECT_TYPE_SEED_BANK_BLANK;
        return false;
    }

    if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || LawnApp_IsCoopMode(mApp)) {
        GamepadControls *gamepadControls2 = board->mGamepadControls2;
        SeedBank *mSeedBank2 = GamepadControls_GetSeedBank(gamepadControls2);
        if (SeedBank_ContainsPoint(mSeedBank2, x, y)) {
            if (mSeedBank2->SeedBank::MouseHitTest(x, y, hitResult)) {
                CursorObject *cursorObject_2P = board->mCursorObject2;
                CursorType mCursorType_2P = cursorObject_2P->mCursorType;
                if (mCursorType_2P == CursorType::CURSOR_TYPE_PLANT_FROM_BANK) {
                    Board_RefreshSeedPacketFromCursor(board, 1);
                }
                return true;
            }
            hitResult->mObjectType = GameObjectType::OBJECT_TYPE_SEED_BANK_BLANK;
            return false;
        }
    }
    return false;
}


namespace {
constexpr int mTouchShovelRectWidth = 72;
constexpr int mTouchButterRectWidth = 72;
constexpr int mTouchTrigger = 40;

int mTouchLastX;
int mTouchLastY;
int mTouchDownX;
int mTouchDownY;
bool mSendKeyWhenTouchUp;
TouchState::TouchState mTouchState = TouchState::None;
float mHeavyWeaponX;
TRect slotMachineRect = {250, 0, 320, 100};
} // namespace

// 触控落下手指在此处理
void Board_MouseDown(Board *board, int x, int y, int theClickCount) {
    old_Board_MouseDown(board, x, y, theClickCount);
    mTouchDownX = x;
    mTouchDownY = y;
    mTouchLastX = x;
    mTouchLastY = y;
    //    xx = x;
    //    yy = y;
    //    LOGD("%d %d",x,y);
    if (keyboardMode) {
        game_patches::autoPickupSeedPacketDisable.Modify();
    }
    keyboardMode = false;
    GamepadControls *gamepadControls1 = board->mGamepadControls1;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
    int mGameState = gamepadControls1->mGamepadState;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

    GamepadControls *gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P = gamepadControls2->mIsCobCannonSelected;
    HitResult hitResult;
    Board_MouseHitTest(board, x, y, &hitResult, false);
    GameObjectType mObjectType = hitResult.mObjectType;
    Challenge *mChallenge = board->mChallenge;
    LawnApp *mApp = board->mApp;
    GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || LawnApp_IsCoopMode(mApp));
    CutScene *mCutScene = board->mCutScene;
    GameScenes mGameScene = mApp->mGameScene;

    SeedChooserScreen *mSeedChooserScreen = mApp->mSeedChooserScreen;
    if (mGameScene == GameScenes::SCENE_LEVEL_INTRO && mSeedChooserScreen != nullptr && mSeedChooserScreen->mChooseState == SeedChooserState::CHOOSE_VIEW_LAWN) {
        SeedChooserScreen_GameButtonDown(mSeedChooserScreen, 6, 0);
        return;
    }
    if (mGameScene == GameScenes::SCENE_LEVEL_INTRO) {
        CutScene_MouseDown(mCutScene, x, y);
    }


    if (mObjectType == GameObjectType::OBJECT_TYPE_SEEDPACKET) {
        if (mGameScene == GameScenes::SCENE_LEVEL_INTRO)
            return;
        SeedPacket *seedPacket = (SeedPacket *)hitResult.mObject;
        mPlayerIndex = (TouchPlayerIndex::TouchPlayerIndex)SeedPacket_GetPlayerIndex(seedPacket); // 玩家1或玩家2
        if (mPlayerIndex == TouchPlayerIndex::Player1) {
            requestDrawShovelInCursor = false; // 不再绘制铲子
            if (isCobCannonSelected) {         // 如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST
                || mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUp = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE) { // 拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
                return;
            }
            mTouchState = TouchState::SeedBank; // 记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 0);
            int newSeedPacketIndex = seedPacket->mIndex;
            gamepadControls1->mSelectedSeedIndex = newSeedPacketIndex;
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用
            if (currentSeedBankIndex != newSeedPacketIndex || mGameState != 7) {
                gamepadControls1->mGamepadState = 7;
                gamepadControls1->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex == newSeedPacketIndex && mGameState == 7) {
                gamepadControls1->mGamepadState = 1;
                if (!isTwoSeedBankMode)
                    gamepadControls1->mIsInShopSeedBank = true;
            }
        } else {
            requestDrawButterInCursor = false; // 不再绘制黄油
            SeedPacket *seedPacket = (SeedPacket *)hitResult.mObject;
            if (isCobCannonSelected_2P) { // 如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST
                || mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUp = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE) { // 拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls2, 50, 1112);
                return;
            }
            mTouchState = TouchState::SeedBank; // 记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 1);
            int newSeedPacketIndex_2P = seedPacket->mIndex;
            gamepadControls2->mSelectedSeedIndex = newSeedPacketIndex_2P;
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用

            if (currentSeedBankIndex_2P != newSeedPacketIndex_2P || mGameState_2P != 7) {
                gamepadControls2->mGamepadState = 7;
                gamepadControls2->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex_2P == newSeedPacketIndex_2P && mGameState_2P == 7) {
                gamepadControls2->mGamepadState = 1;
                if (!isTwoSeedBankMode)
                    gamepadControls2->mIsInShopSeedBank = true;
            }
        }
        return;
    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_SEED_BANK_BLANK) {
        return;
    }

    CursorObject *cursorObject = board->mCursorObject1;
    CursorType mCursorType = cursorObject->mCursorType;
    CursorObject *cursorObject_2P = board->mCursorObject2;
    CursorType mCursorType_2P = cursorObject_2P->mCursorType;

    if (mObjectType == GameObjectType::OBJECT_TYPE_SHOVEL) {
        mPlayerIndex = TouchPlayerIndex::Player1; // 玩家1
        mTouchState = TouchState::ShovelRect;
        if (mGameState == 7) {
            gamepadControls1->mGamepadState = 1;
            if (!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用
        }
        if (mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
            Board_RefreshSeedPacketFromCursor(board, 0);
            Board_ClearCursor(board, 0);
        }
        if (isCobCannonSelected) { // 如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 0);
        if (requestDrawShovelInCursor) {
            requestDrawShovelInCursor = false;
        } else {
            requestDrawShovelInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Shovel);
        }
        return;
    }
    if (mObjectType == GameObjectType::OBJECT_TYPE_BUTTER) {
        mPlayerIndex = TouchPlayerIndex::Player2; // 玩家2
        mTouchState = TouchState::ButterRect;
        if (mGameState == 7) {
            gamepadControls2->mGamepadState = 1;
            if (!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用
        }
        if (mCursorType_2P == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
            Board_RefreshSeedPacketFromCursor(board, 1);
            Board_ClearCursor(board, 1);
        }
        if (isCobCannonSelected_2P) { // 如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 1);
        if (requestDrawButterInCursor) {
            requestDrawButterInCursor = false;
        } else {
            requestDrawButterInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Floop);
        }
        return;
    }

    if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        mPlayerIndex = Board_PixelToGridX(board, x, y) > 5 ? TouchPlayerIndex::Player2 : TouchPlayerIndex::Player1;
    } else if (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS) {
        mPlayerIndex = x > 400 ? TouchPlayerIndex::Player2 : TouchPlayerIndex::Player1;
    } else {
        mPlayerIndex = TouchPlayerIndex::Player1;
    }

    if (mPlayerIndexSecond != TouchPlayerIndex::None && mPlayerIndexSecond == mPlayerIndex) {
        mPlayerIndex = TouchPlayerIndex::None;
        mTouchState = TouchState::None;
        return;
    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_COIN) {
        Coin *coin = (Coin *)hitResult.mObject;
        if (coin->mType == CoinType::COIN_USABLE_SEED_PACKET) {
            mTouchState = TouchState::UsefulSeedPacket;
            requestDrawShovelInCursor = false;
            //            if (mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
            //                LOGD("5656565656");
            //                GamepadControls_OnKeyDown(gamepadCon
            //               trols1, 27, 1096);//放下手上的植物卡片
            //                mSendKeyWhenTouchUp = false;
            //            }
            Board_RefreshSeedPacketFromCursor(board, 0);
            old_Coin_GamepadCursorOver(coin, 0); // 捡起植物卡片
            //            Coin_Collect((int) coin, 0);
        }
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE) { // 拉老虎机用
        if (TRect_Contains(&slotMachineRect, x, y)) {
            GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
            return;
        }
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON) { // 移动重型武器
        mTouchState = TouchState::HeavyWeapon;
        mHeavyWeaponX = mChallenge->mHeavyWeaponX;
        return;
    }

    if (Challenge_MouseDown(mChallenge, x, y, 0, &hitResult, 0)) {
        if (LawnApp_IsScaryPotterLevel(mApp)) {
            requestDrawShovelInCursor = false;
        }
        if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
        if (!LawnApp_IsWhackAZombieLevel(mApp) || mGameState != 7)
            return; // 这一行代码的意义：在锤僵尸关卡，手持植物时，允许拖动种植。
    }
    if (mObjectType == GameObjectType::OBJECT_TYPE_WATERING_CAN || mObjectType == GameObjectType::OBJECT_TYPE_FERTILIZER || mObjectType == GameObjectType::OBJECT_TYPE_BUG_SPRAY
        || mObjectType == GameObjectType::OBJECT_TYPE_PHONOGRAPH || mObjectType == GameObjectType::OBJECT_TYPE_CHOCOLATE || mObjectType == GameObjectType::OBJECT_TYPE_GLOVE
        || mObjectType == GameObjectType::OBJECT_TYPE_MONEY_SIGN || mObjectType == GameObjectType::OBJECT_TYPE_WHEELBARROW || mObjectType == GameObjectType::OBJECT_TYPE_TREE_FOOD) {
        Board_PickUpTool(board, mObjectType, 0);
        ((ZenGardenControls *)gamepadControls1)->mObjectType = mObjectType;
        mTouchState = TouchState::ZenGardenTools;
        return;
    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_ZEN_GARDEN || mObjectType == GameObjectType::OBJECT_TYPE_MUSHROOM_GARDEN || mObjectType == GameObjectType::OBJECT_TYPE_QUARIUM_GARDEN
        || mObjectType == GameObjectType::OBJECT_TYPE_TREE_OF_WISDOM_GARDEN) {
        ((ZenGardenControls *)gamepadControls1)->mObjectType = mObjectType;
        Board_MouseDownWithTool(board, x, y, 0, mObjectType + 3, 0);
        return;
    }


    if (mCursorType == CursorType::CURSOR_TYPE_WATERING_CAN || mCursorType == CursorType::CURSOR_TYPE_FERTILIZER || mCursorType == CursorType::CURSOR_TYPE_BUG_SPRAY
        || mCursorType == CursorType::CURSOR_TYPE_PHONOGRAPH || mCursorType == CursorType::CURSOR_TYPE_CHOCOLATE || mCursorType == CursorType::CURSOR_TYPE_GLOVE || mCursorType == CursorType::CURSOR_TYPE_MONEY_SIGN || mCursorType == CursorType::CURSOR_TYPE_WHEEELBARROW || mCursorType == CursorType::CURSOR_TYPE_TREE_FOOD
        || mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_GLOVE) {
        mSendKeyWhenTouchUp = true;
    }

    //    *(uint32_t *) (gamepadControls1 + 152) = 0;//疑似用于设置该gamepadControls1属于玩家1。可能的取值：-1，0，1
    //    其中，1P恒为0，2P禁用时为-1，2P启用时为1。

    if (mPlayerIndex == TouchPlayerIndex::Player1) {
        if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else if (mCursorType == CursorType::CURSOR_TYPE_WATERING_CAN && mApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_GOLD_WATERINGCAN] != 0) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
    } else {
        if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
            gamepadControls2->mCursorPositionX = x - 40;
            gamepadControls2->mCursorPositionY = y - 40;
        } else {
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }


    int seekBankPosition = gamepadControls1->mSelectedSeedIndex;
    if (mPlayerIndex == TouchPlayerIndex::Player1) {
        if (mGameState == 7 || isCobCannonSelected || requestDrawShovelInCursor || (mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN && mTouchState != TouchState::UsefulSeedPacket)) {
            mTouchState = TouchState::PickingSomething;
            mSendKeyWhenTouchUp = true;
        }
    } else {
        if (mGameState_2P == 7 || isCobCannonSelected_2P || requestDrawButterInCursor || (mCursorType_2P == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN && mTouchState != TouchState::UsefulSeedPacket)) {
            mTouchState = TouchState::PickingSomething;
            mSendKeyWhenTouchUp = true;
        }
    }


    if (mObjectType == GameObjectType::OBJECT_TYPE_PLANT) {
        if (mPlayerIndex == TouchPlayerIndex::Player1 && requestDrawShovelInCursor)
            return;
        Plant *plant = (Plant *)hitResult.mObject;
        bool isValidCobCannon = plant->mSeedType == SeedType::SEED_COBCANNON && plant->mState == PlantState::STATE_COBCANNON_READY;
        if (isValidCobCannon) {
            if (mPlayerIndex == TouchPlayerIndex::Player1) {
                if (mGameState == 7) {
                    gamepadControls1->mGamepadState = 1;
                    mSendKeyWhenTouchUp = false;
                    if (!isTwoSeedBankMode)
                        gamepadControls1->mIsInShopSeedBank = true;
                    int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
                    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                    seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用
                }
                if (gamepadControls2->mIsCobCannonSelected && gamepadControls2->mCobCannonPlantIndexInList == plant->mPlantIndexInList) {
                    // 不能同时选同一个加农炮！
                    mTouchState = TouchState::None;
                    return;
                }
                GamepadControls_pickUpCobCannon((int)gamepadControls1, (int)plant);
            } else {
                if (mGameState_2P == 7) {
                    gamepadControls2->mGamepadState = 1;
                    mSendKeyWhenTouchUp = false;
                    if (!isTwoSeedBankMode)
                        gamepadControls2->mIsInShopSeedBank = true;
                    int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
                    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                    seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用
                }
                if (gamepadControls1->mIsCobCannonSelected && gamepadControls1->mCobCannonPlantIndexInList == plant->mPlantIndexInList) {
                    // 不能同时选同一个加农炮！
                    mTouchState = TouchState::None;
                    return;
                }
                GamepadControls_pickUpCobCannon((int)gamepadControls2, (int)plant);
            }
            mTouchState = TouchState::ValidCobCannon;
            return;
        }
    }
    if (mTouchState == TouchState::None)
        mTouchState = TouchState::Board;
}

void Board_MouseDrag(Board *board, int x, int y) {
    // Drag函数仅仅负责移动光标即可
    old_Board_MouseDrag(board, x, y);
    //    xx = x;
    //    yy = y;
    //    LOGD("%d %d",x,y);
    if (mTouchState == TouchState::None)
        return;
    GamepadControls *gamepadControls1 = board->mGamepadControls1;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;
    GamepadControls *gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P = gamepadControls2->mIsCobCannonSelected;
    int mGameState = gamepadControls1->mGamepadState;
    LawnApp *mApp = board->mApp;
    GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS));
    int seedBankHeight = LawnApp_IsChallengeWithoutSeedBank(mApp) ? 87 : seedBank->mY + seedBank->mHeight;
    if (mTouchState == TouchState::SeedBank && mTouchLastY < seedBankHeight && y >= seedBankHeight) {
        mTouchState = TouchState::BoardMovedFromSeedBank;
        if (mPlayerIndex == TouchPlayerIndex::Player1) {
            gamepadControls1->mGamepadState = 7;
            gamepadControls1->mIsInShopSeedBank = false;
            requestDrawShovelInCursor = false;
        } else {
            gamepadControls2->mGamepadState = 7;
            gamepadControls2->mIsInShopSeedBank = false;
            requestDrawButterInCursor = false;
        }
        mSendKeyWhenTouchUp = true;
    }

    if (mTouchState == TouchState::ShovelRect) {
        if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
            if (TRect_Contains(&mTouchVSShovelRect, mTouchLastX, mTouchLastY) && !TRect_Contains(&mTouchVSShovelRect, x, y)) {
                mTouchState = TouchState::BoardMovedFromShovelRect;
                if (!requestDrawShovelInCursor)
                    LawnApp_PlayFoley(mApp, FoleyType::Shovel);
                requestDrawShovelInCursor = true;
                gamepadControls1->mGamepadState = 1;
                mSendKeyWhenTouchUp = true;
            }
        } else if (mTouchLastY < mTouchShovelRectWidth && y >= mTouchShovelRectWidth) {
            mTouchState = TouchState::BoardMovedFromShovelRect;
            if (!requestDrawShovelInCursor)
                LawnApp_PlayFoley(mApp, FoleyType::Shovel);
            requestDrawShovelInCursor = true;
            gamepadControls1->mGamepadState = 1;
            mSendKeyWhenTouchUp = true;
        }
    }

    if (mTouchState == TouchState::ButterRect && mTouchLastY < mTouchButterRectWidth && y >= mTouchButterRectWidth) {
        mTouchState = TouchState::BoardMovedFromButterRect;
        if (!requestDrawButterInCursor)
            LawnApp_PlayFoley(mApp, FoleyType::Floop);
        requestDrawButterInCursor = true;
        gamepadControls2->mGamepadState = 1;
        mSendKeyWhenTouchUp = true;
    }

    if (mTouchState == TouchState::ValidCobCannon || mTouchState == TouchState::UsefulSeedPacket) {
        if (!mSendKeyWhenTouchUp && (abs(x - mTouchDownX) > mTouchTrigger || abs(y - mTouchDownY) > mTouchTrigger)) {
            mSendKeyWhenTouchUp = true;
        }
    }

    if (mTouchState == TouchState::ZenGardenTools && mTouchLastY < mTouchButterRectWidth && y >= mTouchButterRectWidth) {
        mTouchState = TouchState::BoardMovedFromZenGardenTools;
        mSendKeyWhenTouchUp = true;
    }

    if (mPlayerIndex == TouchPlayerIndex::Player1 && isCobCannonSelected && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls1, 27, 1096); // 退选加农炮
        mTouchState = TouchState::None;
        mSendKeyWhenTouchUp = false;
    }
    if (mPlayerIndex == TouchPlayerIndex::Player2 && isCobCannonSelected_2P && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls2, 27, 1096); // 退选加农炮
        mTouchState = TouchState::None;
        mSendKeyWhenTouchUp = false;
    }

    if (mPlayerIndex == TouchPlayerIndex::Player1) {
        if (mGameState == 7 && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
            gamepadControls1->mGamepadState = 1; // 退选植物
            if (!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用
            mTouchState = TouchState::None;
            mSendKeyWhenTouchUp = false;
        }
    } else {
        if (mGameState_2P == 7 && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
            gamepadControls2->mGamepadState = 1; // 退选植物
            if (!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用
            mTouchState = TouchState::None;
            mSendKeyWhenTouchUp = false;
        }
    }


    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && mTouchState == TouchState::HeavyWeapon) {
        Challenge *mChallenge = board->mChallenge;
        mChallenge->mHeavyWeaponX = mHeavyWeaponX + x - mTouchDownX; // 移动重型武器X坐标
        return;
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
        return;
    }

    if (mTouchState != TouchState::SeedBank && mTouchState != TouchState::ZenGardenTools) {
        if (x > 770)
            x = 770;
        if (x < 40)
            x = 40;
        if (y > 580)
            y = 580;
        if (mPlayerIndex == TouchPlayerIndex::Player1) {
            CursorObject *cursorObject = board->mCursorObject1;
            CursorType mCursorType = cursorObject->mCursorType;
            if (mCursorType == CursorType::CURSOR_TYPE_WATERING_CAN && mApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_GOLD_WATERINGCAN] != 0) {
                gamepadControls1->mCursorPositionX = x - 40;
                gamepadControls1->mCursorPositionY = y - 40;
            } else {
                gamepadControls1->mCursorPositionX = x;
                gamepadControls1->mCursorPositionY = y;
            }
        } else {
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }
    mTouchLastX = x;
    mTouchLastY = y;
}

void Board_MouseUp(Board *board, int x, int y, int theClickCount) {
    old_Board_MouseUp(board, x, y, theClickCount);
    if (mTouchState != TouchState::None && mSendKeyWhenTouchUp) {
        GamepadControls *gamepadControls1 = board->mGamepadControls1;
        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
        int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
        int numSeedsInBank = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
        int mGameState = gamepadControls1->mGamepadState;
        bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

        GamepadControls *gamepadControls2 = board->mGamepadControls2;
        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
        int numSeedsInBank_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
        int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
        int mGameState_2P = gamepadControls2->mGamepadState;
        bool isCobCannonSelected_2P = gamepadControls2->mIsCobCannonSelected;

        LawnApp *mApp = board->mApp;
        GameMode mGameMode = mApp->mGameMode;
        CursorObject *cursorObject = board->mCursorObject1;
        CursorType mCursorType = cursorObject->mCursorType;
        CursorObject *cursorObject_2P = board->mCursorObject2;
        CursorType mCursorType_2P = cursorObject_2P->mCursorType;
        Challenge *mChallenge = board->mChallenge;
        ChallengeState mChallengeState = mChallenge->mChallengeState;

        if (mPlayerIndex == TouchPlayerIndex::Player1) {
            if (requestDrawShovelInCursor) {
                Board_ShovelDown(board);
            } else if (mGameState == 7 || isCobCannonSelected || mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
                if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                } else if ((mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND && mChallenge->mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && mApp->mGameScene == GameScenes::SCENE_PLAYING)
                           || mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    GamepadControls_OnButtonDown(gamepadControls1, 6, 0, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                }
                int mGameStateNew = gamepadControls1->mGamepadState;
                int seedPacketIndexNew = gamepadControls1->mSelectedSeedIndex;
                int numSeedsInBankNew = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
                gamepadControls1->mIsInShopSeedBank = mGameStateNew != 7;
                if (mGameState != mGameStateNew) {
                    if (!Board_HasConveyorBeltSeedBank(board, 0) || numSeedsInBank == numSeedsInBankNew) { // 修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                        seedBank->mSeedPackets[seedPacketIndexNew].mLastSelectedTime = 0.0f; // 动画效果专用
                    }
                }
            } else if (mCursorType == CursorType::CURSOR_TYPE_WATERING_CAN || mCursorType == CursorType::CURSOR_TYPE_FERTILIZER || mCursorType == CursorType::CURSOR_TYPE_BUG_SPRAY
                       || mCursorType == CursorType::CURSOR_TYPE_PHONOGRAPH || mCursorType == CursorType::CURSOR_TYPE_CHOCOLATE || mCursorType == CursorType::CURSOR_TYPE_GLOVE
                       || mCursorType == CursorType::CURSOR_TYPE_MONEY_SIGN || mCursorType == CursorType::CURSOR_TYPE_WHEEELBARROW || mCursorType == CursorType::CURSOR_TYPE_TREE_FOOD
                       || mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_GLOVE) {
                if (!Board_ZenGardenItemNumIsZero(board, mCursorType)) {
                    if (mCursorType == CursorType::CURSOR_TYPE_WATERING_CAN && mApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_GOLD_WATERINGCAN] != 0) {
                        Board_MouseDownWithTool(board, x - 40, y - 40, 0, mCursorType, 0);
                    } else {
                        Board_MouseDownWithTool(board, x, y, 0, mCursorType, 0);
                    }
                }
            }
        } else {
            if (requestDrawButterInCursor) {
                requestDrawButterInCursor = false;
            } else if (mGameState_2P == 7 || isCobCannonSelected_2P || mCursorType_2P == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
                if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                } else if ((mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND && mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && mApp->mGameScene == GameScenes::SCENE_PLAYING) || mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    GamepadControls_OnButtonDown(gamepadControls2, 6, 1, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                }
                int mGameStateNew_2P = gamepadControls2->mGamepadState;
                int seedPacketIndexNew_2P = gamepadControls2->mSelectedSeedIndex;
                int numSeedsInBankNew_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
                gamepadControls2->mIsInShopSeedBank = mGameStateNew_2P != 7;
                if (mGameState_2P != mGameStateNew_2P) {
                    if (!Board_HasConveyorBeltSeedBank(board, 1) || numSeedsInBank_2P == numSeedsInBankNew_2P) { // 修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                        seedBank_2P->mSeedPackets[seedPacketIndexNew_2P].mLastSelectedTime = 0.0f; // 动画效果专用
                    }
                }
                if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    gamepadControls2->mGamepadState = 1;
                }
            }
        }
    }
    mPlayerIndex = TouchPlayerIndex::None;
    mSendKeyWhenTouchUp = false;
    mTouchState = TouchState::None;
}


namespace {
int mTouchLastXSecond;
int mTouchLastYSecond;
int mTouchDownXSecond;
int mTouchDownYSecond;
bool mSendKeyWhenTouchUpSecond;
TouchState::TouchState mTouchStateSecond = TouchState::None;
} // namespace

void Board_MouseDownSecond(Board *board, int x, int y, int theClickCount) {
    // 触控落下手指在此处理
    mTouchDownXSecond = x;
    mTouchDownYSecond = y;
    mTouchLastXSecond = x;
    mTouchLastYSecond = y;
    if (keyboardMode) {
        game_patches::autoPickupSeedPacketDisable.Modify();
    }
    keyboardMode = false;

    GamepadControls *gamepadControls1 = board->mGamepadControls1;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
    int mGameState = gamepadControls1->mGamepadState;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

    GamepadControls *gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P = gamepadControls2->mIsCobCannonSelected;
    HitResult hitResult;
    Board_MouseHitTest(board, x, y, &hitResult, false);
    GameObjectType mObjectType = hitResult.mObjectType;
    Challenge *mChallenge = board->mChallenge;
    LawnApp *mApp = board->mApp;
    GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS));
    CutScene *mCutScene = board->mCutScene;
    GameScenes mGameScene = mApp->mGameScene;

    SeedChooserScreen *mSeedChooserScreen = mApp->mSeedChooserScreen;
    if (mGameScene == GameScenes::SCENE_LEVEL_INTRO && mSeedChooserScreen != nullptr && mSeedChooserScreen->mChooseState == SeedChooserState::CHOOSE_VIEW_LAWN) {
        SeedChooserScreen_GameButtonDown(mSeedChooserScreen, 6, 0);
        return;
    }
    if (mGameScene == GameScenes::SCENE_LEVEL_INTRO) {
        CutScene_MouseDown(mCutScene, x, y);
    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_SEEDPACKET) {
        if (mGameScene == GameScenes::SCENE_LEVEL_INTRO)
            return;
        SeedPacket *seedPacket = (SeedPacket *)hitResult.mObject;
        int newSeedPacketIndex = seedPacket->mIndex;
        mPlayerIndexSecond = (TouchPlayerIndex::TouchPlayerIndex)SeedPacket_GetPlayerIndex(seedPacket); // 玩家1或玩家2

        if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
            requestDrawShovelInCursor = false; // 不再绘制铲子
            if (isCobCannonSelected) {         // 如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST
                || mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUpSecond = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE) { // 拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
                return;
            }
            mTouchStateSecond = TouchState::SeedBank; // 记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 0);

            gamepadControls1->mSelectedSeedIndex = newSeedPacketIndex;
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用

            if (currentSeedBankIndex != newSeedPacketIndex || mGameState != 7) {
                gamepadControls1->mGamepadState = 7;
                gamepadControls1->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex == newSeedPacketIndex && mGameState == 7) {
                gamepadControls1->mGamepadState = 1;
                if (!isTwoSeedBankMode)
                    gamepadControls1->mIsInShopSeedBank = true;
            }
        } else {
            requestDrawButterInCursor = false; // 不再绘制黄油
            SeedPacket *seedPacket = (SeedPacket *)hitResult.mObject;
            if (isCobCannonSelected_2P) { // 如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST
                || mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUpSecond = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE) { // 拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls2, 50, 1112);
                return;
            }
            mTouchStateSecond = TouchState::SeedBank; // 记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 1);
            int newSeedPacketIndex_2P = seedPacket->mIndex;
            gamepadControls2->mSelectedSeedIndex = newSeedPacketIndex_2P;
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用

            if (currentSeedBankIndex_2P != newSeedPacketIndex_2P || mGameState_2P != 7) {
                gamepadControls2->mGamepadState = 7;
                gamepadControls2->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex_2P == newSeedPacketIndex_2P && mGameState_2P == 7) {
                gamepadControls2->mGamepadState = 1;
                if (!isTwoSeedBankMode)
                    gamepadControls2->mIsInShopSeedBank = true;
            }
        }
        return;
    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_SEED_BANK_BLANK) {
        return;
    }

    CursorObject *cursorObject = board->mCursorObject1;
    CursorType mCursorType = cursorObject->mCursorType;
    CursorObject *cursorObject_2P = board->mCursorObject2;
    CursorType mCursorType_2P = cursorObject_2P->mCursorType;
    //    if (mCursorType == CursorType::CURSOR_TYPE_WATERING_CAN || mCursorType == CursorType::CURSOR_TYPE_FERTILIZER ||
    //        mCursorType == CursorType::CURSOR_TYPE_BUG_SPRAY || mCursorType == CursorType::OBJECT_TYPE_PHONOGRAPH ||
    //        mCursorType == CursorType::OBJECT_TYPE_CHOCOLATE || mCursorType == CursorType::OBJECT_TYPE_GLOVE ||
    //        mCursorType == CursorType::CURSOR_TYPE_MONEY_SIGN || mCursorType == CursorType::CURSOR_TYPE_WHEEELBARROW ||
    //        mCursorType == CursorType::CURSOR_TYPE_TREE_FOOD) {
    //        Board_MouseDownWithTool(board, x, y, 0, mCursorType, false);
    //        return;
    //    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_SHOVEL) {
        if (!useNewShovel) {
            GamepadControls_OnKeyDown(board->mGamepadControls1, 49, 1112);
            return;
        }
        mPlayerIndexSecond = TouchPlayerIndex::Player1; // 玩家1
        mTouchStateSecond = TouchState::ShovelRect;
        if (mGameState == 7) {
            gamepadControls1->mGamepadState = 1;
            if (!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用
        }
        if (mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
            Board_RefreshSeedPacketFromCursor(board, 0);
            Board_ClearCursor(board, 0);
        }
        if (isCobCannonSelected) { // 如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 0);
        if (requestDrawShovelInCursor) {
            requestDrawShovelInCursor = false;
        } else {
            requestDrawShovelInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Shovel);
        }
        return;
    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_BUTTER) {
        mPlayerIndexSecond = TouchPlayerIndex::Player2; // 玩家2
        mTouchStateSecond = TouchState::ButterRect;
        if (mGameState == 7) {
            gamepadControls2->mGamepadState = 1;
            if (!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用
        }
        if (mCursorType_2P == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
            Board_RefreshSeedPacketFromCursor(board, 1);
            Board_ClearCursor(board, 1);
        }
        if (isCobCannonSelected_2P) { // 如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 1);
        if (requestDrawButterInCursor) {
            requestDrawButterInCursor = false;
        } else {
            requestDrawButterInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Floop);
        }
        return;
    }

    if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        mPlayerIndexSecond = Board_PixelToGridX(board, x, y) > 5 ? TouchPlayerIndex::Player2 : TouchPlayerIndex::Player1;
    } else if (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS) {
        mPlayerIndexSecond = x > 400 ? TouchPlayerIndex::Player2 : TouchPlayerIndex::Player1;
    } else {
        mPlayerIndexSecond = TouchPlayerIndex::Player1;
    }

    if (mPlayerIndex != TouchPlayerIndex::None && mPlayerIndexSecond == mPlayerIndex) {
        if (mObjectType == GameObjectType::OBJECT_TYPE_PLANT) {
            Plant *plant = (Plant *)hitResult.mObject;
            bool isValidCobCannon = plant->mSeedType == SeedType::SEED_COBCANNON && plant->mState == PlantState::STATE_COBCANNON_READY;
            if (!isValidCobCannon) {
                mPlayerIndexSecond = TouchPlayerIndex::None;
                mTouchStateSecond = TouchState::None;
                return;
            }
        } else {
            mPlayerIndexSecond = TouchPlayerIndex::None;
            mTouchStateSecond = TouchState::None;
            return;
        }
    }

    if (mObjectType == GameObjectType::OBJECT_TYPE_COIN) {
        Coin *coin = (Coin *)hitResult.mObject;

        if (coin->mType == CoinType::COIN_USABLE_SEED_PACKET) {
            mTouchStateSecond = TouchState::UsefulSeedPacket;
            requestDrawShovelInCursor = false;
            //            if (mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
            //                LOGD("5656565656");
            //                GamepadControls_OnKeyDown(gamepadCon
            //               trols1, 27, 1096);//放下手上的植物卡片
            //                mSendKeyWhenTouchUp = false;
            //            }
            Board_RefreshSeedPacketFromCursor(board, 0);
            old_Coin_GamepadCursorOver(coin, 0); // 捡起植物卡片
            //            Coin_Collect((int) coin, 0);
        }
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE) { // 拉老虎机用
        if (TRect_Contains(&slotMachineRect, x, y)) {
            GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
            return;
        }
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON) { // 移动重型武器
        mTouchStateSecond = TouchState::HeavyWeapon;
        mHeavyWeaponX = *((float *)mChallenge + 67);
        return;
    }

    if (Challenge_MouseDown(mChallenge, x, y, 0, &hitResult, 0)) {
        if (LawnApp_IsScaryPotterLevel(mApp)) {
            requestDrawShovelInCursor = false;
        }
        if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
        if (!LawnApp_IsWhackAZombieLevel(mApp) || mGameState != 7)
            return; // 这一行代码的意义：在锤僵尸关卡，手持植物时，允许拖动种植。
    }


    if (mObjectType == GameObjectType::OBJECT_TYPE_WATERING_CAN || mObjectType == GameObjectType::OBJECT_TYPE_FERTILIZER || mObjectType == GameObjectType::OBJECT_TYPE_BUG_SPRAY
        || mObjectType == GameObjectType::OBJECT_TYPE_PHONOGRAPH || mObjectType == GameObjectType::OBJECT_TYPE_CHOCOLATE || mObjectType == GameObjectType::OBJECT_TYPE_GLOVE
        || mObjectType == GameObjectType::OBJECT_TYPE_MONEY_SIGN || mObjectType == GameObjectType::OBJECT_TYPE_WHEELBARROW || mObjectType == GameObjectType::OBJECT_TYPE_TREE_FOOD) {
        Board_PickUpTool(board, mObjectType, 0);
        return;
    }

    float tmpX1, tmpY1;
    tmpX1 = gamepadControls1->mCursorPositionX;
    tmpY1 = gamepadControls1->mCursorPositionY;

    if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
        if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
    } else {
        if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
            gamepadControls2->mCursorPositionX = x - 40;
            gamepadControls2->mCursorPositionY = y - 40;
        } else {
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }


    int seekBankPosition = gamepadControls1->mSelectedSeedIndex;
    if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
        if (mGameState == 7 || isCobCannonSelected || requestDrawShovelInCursor || (mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN && mTouchStateSecond != TouchState::UsefulSeedPacket)) {
            mTouchStateSecond = TouchState::PickingSomething;
            mSendKeyWhenTouchUpSecond = true;
        }
    } else {
        if (mGameState_2P == 7 || isCobCannonSelected_2P || requestDrawButterInCursor || (mCursorType_2P == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN && mTouchStateSecond != TouchState::UsefulSeedPacket)) {
            mTouchStateSecond = TouchState::PickingSomething;
            mSendKeyWhenTouchUpSecond = true;
        }
    }


    if (mObjectType == GameObjectType::OBJECT_TYPE_PLANT) {
        if (mPlayerIndexSecond == TouchPlayerIndex::Player1 && requestDrawShovelInCursor)
            return;
        Plant *plant = (Plant *)hitResult.mObject;
        bool isValidCobCannon = plant->mSeedType == SeedType::SEED_COBCANNON && plant->mState == PlantState::STATE_COBCANNON_READY;
        if (isValidCobCannon) {
            if (mPlayerIndex == TouchPlayerIndex::Player1 && gamepadControls2->mPlayerIndex2 == -1) {
                gamepadControls2->mCursorPositionX = x;
                gamepadControls2->mCursorPositionY = y;
                gamepadControls1->mCursorPositionX = tmpX1;
                gamepadControls1->mCursorPositionY = tmpY1;
                if (gamepadControls1->mIsCobCannonSelected && gamepadControls1->mCobCannonPlantIndexInList == plant->mPlantIndexInList) {
                    // 不能同时选同一个加农炮！
                    mTouchStateSecond = TouchState::None;
                    return;
                }
                gamepadControls2->mIsInShopSeedBank = true;
                gamepadControls2->mPlayerIndex2 = 1;
                mPlayerIndexSecond = TouchPlayerIndex::Player2;
                GamepadControls_pickUpCobCannon((int)gamepadControls2, (int)plant);
                mTouchStateSecond = TouchState::ValidCobCannonSecond;
                return;
            } else if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
                if (mGameState == 7) {
                    gamepadControls1->mGamepadState = 1;
                    mSendKeyWhenTouchUpSecond = false;
                    if (!isTwoSeedBankMode)
                        gamepadControls1->mIsInShopSeedBank = true;
                    int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
                    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                    seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用
                }
                GamepadControls_pickUpCobCannon((int)gamepadControls1, (int)plant);
            } else {
                if (mGameState_2P == 7) {
                    gamepadControls2->mGamepadState = 1;
                    mSendKeyWhenTouchUpSecond = false;
                    if (!isTwoSeedBankMode)
                        gamepadControls2->mIsInShopSeedBank = true;
                    int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
                    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                    seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用
                }
                GamepadControls_pickUpCobCannon((int)gamepadControls2, (int)plant);
            }
            mTouchStateSecond = TouchState::ValidCobCannon;
            return;
        }
    }

    if (mTouchStateSecond == TouchState::None)
        mTouchStateSecond = TouchState::Board;
}


void Board_MouseDragSecond(Board *board, int x, int y) {
    // Drag函数仅仅负责移动光标即可
    if (mTouchStateSecond == TouchState::None)
        return;

    GamepadControls *gamepadControls1 = board->mGamepadControls1;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;
    GamepadControls *gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P = gamepadControls2->mIsCobCannonSelected;
    int mGameState = gamepadControls1->mGamepadState;
    LawnApp *mApp = board->mApp;
    GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS));
    int seedBankHeight = LawnApp_IsChallengeWithoutSeedBank(mApp) ? 87 : seedBank->mY + seedBank->mHeight;
    if (mTouchStateSecond == TouchState::SeedBank && mTouchLastYSecond < seedBankHeight && y >= seedBankHeight) {
        mTouchStateSecond = TouchState::BoardMovedFromSeedBank;
        if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
            gamepadControls1->mGamepadState = 7;
            gamepadControls1->mIsInShopSeedBank = false;
            requestDrawShovelInCursor = false;
        } else {
            gamepadControls2->mGamepadState = 7;
            gamepadControls2->mIsInShopSeedBank = false;
            requestDrawButterInCursor = false;
        }
        mSendKeyWhenTouchUpSecond = true;
    }
    if (mTouchStateSecond == TouchState::ShovelRect) {
        if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
            if (TRect_Contains(&mTouchVSShovelRect, mTouchLastXSecond, mTouchLastYSecond) && !TRect_Contains(&mTouchVSShovelRect, x, y)) {
                mTouchStateSecond = TouchState::BoardMovedFromShovelRect;
                if (!requestDrawShovelInCursor)
                    LawnApp_PlayFoley(mApp, FoleyType::Shovel);
                requestDrawShovelInCursor = true;
                gamepadControls1->mGamepadState = 1;
                mSendKeyWhenTouchUpSecond = true;
            }
        } else if (mTouchLastYSecond < mTouchShovelRectWidth && y >= mTouchShovelRectWidth) {
            mTouchStateSecond = TouchState::BoardMovedFromShovelRect;
            if (!requestDrawShovelInCursor)
                LawnApp_PlayFoley(mApp, FoleyType::Shovel);
            requestDrawShovelInCursor = true;
            gamepadControls1->mGamepadState = 1;
            mSendKeyWhenTouchUpSecond = true;
        }
    }

    if (mTouchStateSecond == TouchState::ButterRect && mTouchLastYSecond < mTouchButterRectWidth && y >= mTouchButterRectWidth) {
        mTouchStateSecond = TouchState::BoardMovedFromButterRect;
        if (!requestDrawButterInCursor)
            LawnApp_PlayFoley(mApp, FoleyType::Floop);
        requestDrawButterInCursor = true;
        gamepadControls2->mGamepadState = 1;
        mSendKeyWhenTouchUpSecond = true;
    }

    if (mTouchStateSecond == TouchState::ValidCobCannon || mTouchStateSecond == TouchState::ValidCobCannonSecond || mTouchStateSecond == TouchState::UsefulSeedPacket) {
        if (!mSendKeyWhenTouchUpSecond && (abs(x - mTouchDownXSecond) > mTouchTrigger || abs(y - mTouchDownYSecond) > mTouchTrigger)) {
            mSendKeyWhenTouchUpSecond = true;
        }
    }


    if (mPlayerIndexSecond == TouchPlayerIndex::Player1 && isCobCannonSelected && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls1, 27, 1096); // 退选加农炮
        mTouchStateSecond = TouchState::None;
        mSendKeyWhenTouchUpSecond = false;
    }
    if (mPlayerIndexSecond == TouchPlayerIndex::Player2 && isCobCannonSelected_2P && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls2, 27, 1096); // 退选加农炮
        if (mTouchStateSecond == TouchState::ValidCobCannonSecond) {
            LawnApp_ClearSecondPlayer(mApp);
            gamepadControls2->mPlayerIndex2 = -1;
        }
        mTouchStateSecond = TouchState::None;
        mSendKeyWhenTouchUpSecond = false;
    }

    if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
        if (mGameState == 7 && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
            gamepadControls1->mGamepadState = 1; // 退选植物
            if (!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f; // 动画效果专用
            mTouchStateSecond = TouchState::None;
            mSendKeyWhenTouchUpSecond = false;
        }
    } else {
        if (mGameState_2P == 7 && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
            gamepadControls2->mGamepadState = 1; // 退选植物
            if (!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f; // 动画效果专用
            mTouchStateSecond = TouchState::None;
            mSendKeyWhenTouchUpSecond = false;
        }
    }


    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && mTouchStateSecond == TouchState::HeavyWeapon) {
        Challenge *mChallenge = board->mChallenge;
        mChallenge->mHeavyWeaponX = mHeavyWeaponX + x - mTouchDownXSecond; // 移动重型武器X坐标
        return;
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
        return;
    }

    if (mTouchStateSecond != TouchState::SeedBank) {
        if (x > 770)
            x = 770;
        if (x < 40)
            x = 40;
        if (y > 580)
            y = 580;
        if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        } else {
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }
    mTouchLastXSecond = x;
    mTouchLastYSecond = y;
}


void Board_MouseUpSecond(Board *board, int x, int y, int theClickCount) {
    if (mTouchStateSecond != TouchState::None && mSendKeyWhenTouchUpSecond) {
        GamepadControls *gamepadControls1 = board->mGamepadControls1;
        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
        int numSeedsInBank = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
        int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
        int mGameState = gamepadControls1->mGamepadState;
        bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

        GamepadControls *gamepadControls2 = board->mGamepadControls2;
        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
        int numSeedsInBank_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
        int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
        int mGameState_2P = gamepadControls2->mGamepadState;
        bool isCobCannonSelected_2P = gamepadControls2->mIsCobCannonSelected;

        LawnApp *mApp = board->mApp;
        GameMode mGameMode = mApp->mGameMode;
        CursorObject *cursorObject = board->mCursorObject1;
        CursorType mCursorType = cursorObject->mCursorType;
        CursorObject *cursorObject_2P = board->mCursorObject2;
        CursorType mCursorType_2P = cursorObject_2P->mCursorType;
        Challenge *mChallenge = board->mChallenge;
        ChallengeState mChallengeState = mChallenge->mChallengeState;
        GameScenes mGameScene = mApp->mGameScene;

        if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
            if (requestDrawShovelInCursor) {
                Board_ShovelDown(board);
            } else if (mGameState == 7 || isCobCannonSelected || mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {

                if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                } else if ((mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND && mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && mGameScene == GameScenes::SCENE_PLAYING) || mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    GamepadControls_OnButtonDown(gamepadControls1, 6, 0, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                }
                int mGameStateNew = gamepadControls1->mGamepadState;
                int numSeedsInBankNew = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
                int seedPacketIndexNew = gamepadControls1->mSelectedSeedIndex;
                gamepadControls1->mIsInShopSeedBank = mGameStateNew != 7;
                if (mGameState != mGameStateNew) {
                    if (!Board_HasConveyorBeltSeedBank(board, 0) || numSeedsInBank == numSeedsInBankNew) { // 修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                        seedBank->mSeedPackets[seedPacketIndexNew].mLastSelectedTime = 0.0f; // 动画效果专用
                    }
                }
            }
        } else {
            if (requestDrawButterInCursor) {
                requestDrawButterInCursor = false;
            } else if (mGameState_2P == 7 || isCobCannonSelected_2P || mCursorType_2P == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
                if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST) {
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                } else if ((mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND && mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && mGameScene == GameScenes::SCENE_PLAYING) || mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    GamepadControls_OnButtonDown(gamepadControls2, 6, 1, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                }
                int mGameStateNew_2P = gamepadControls2->mGamepadState;
                int numSeedsInBankNew_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
                int seedPacketIndexNew_2P = gamepadControls2->mSelectedSeedIndex;
                gamepadControls2->mIsInShopSeedBank = mGameStateNew_2P != 7;
                if (mGameState_2P != mGameStateNew_2P) {
                    if (!Board_HasConveyorBeltSeedBank(board, 1) || numSeedsInBank_2P == numSeedsInBankNew_2P) { // 修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                        seedBank_2P->mSeedPackets[seedPacketIndexNew_2P].mLastSelectedTime = 0.0f; // 动画效果专用
                    }
                }
                if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
                    gamepadControls2->mGamepadState = 1;
                }
                if (mTouchStateSecond == TouchState::ValidCobCannonSecond) {
                    LawnApp_ClearSecondPlayer(mApp);
                    gamepadControls2->mPlayerIndex2 = -1;
                }
            }
        }
    }
    mPlayerIndexSecond = TouchPlayerIndex::None;
    mSendKeyWhenTouchUpSecond = false;
    mTouchStateSecond = TouchState::None;
}


void Board_Board(Board *board, LawnApp *mApp) {
    old_Board_Board(board, mApp);

    if (mBoardMenuButton != nullptr) {
        GameButton_Delete(mBoardMenuButton);
    }
    if (mBoardStoreButton != nullptr) {
        GameButton_Delete(mBoardStoreButton);
    }
    int holder[1];
    TodStringTranslate(holder, (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || mApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) ? "[MAIN_MENU_BUTTON]" : "[MENU_BUTTON]");
    mBoardMenuButton = MakeButton(1000, &board->mButtonListener, board, holder);
    GameButton_Resize(mBoardMenuButton, 705, -3, 120, 80);
    mBoardMenuButton->mBtnNoDraw = true;
    mBoardMenuButton->mDisabled = true;
    if (LawnApp_IsCoopMode(mApp) || mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        GameButton_Resize(mBoardMenuButton, 880, -3, 120, 80);
    } else if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || mApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) {
        GameButton_Resize(mBoardMenuButton, 650, 550, 170, 120);
    }
    Sexy_String_Delete(holder);

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND) {
        int holder1[1];
        TodStringTranslate(holder1, "[START_ONSLAUGHT]");
        mBoardStoreButton = MakeButton(1001, &board->mButtonListener, board, holder1);
        GameButton_Resize(mBoardStoreButton, 0, 0, 0, 0);
        mBoardStoreButton->mBtnNoDraw = true;
        mBoardStoreButton->mDisabled = true;
        Sexy_String_Delete(holder1);
    } else {
        int holder1[1];
        TodStringTranslate(holder1, "[SHOP_BUTTON]");
        mBoardStoreButton = MakeButton(1001, &board->mButtonListener, board, holder1);
        Sexy_String_Delete(holder1);
        if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || mApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) {
            GameButton_Resize(mBoardStoreButton, 0, 550, 170, 120);
        } else {
            GameButton_Resize(mBoardStoreButton, 0, 0, 0, 0);
            mBoardStoreButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = true;
        }
    }
    Sexy_Widget_AddWidget(board, mBoardMenuButton);
    Sexy_Widget_AddWidget(board, mBoardStoreButton);
    MessageWidget_Delete(board->mAdvice);
    CustomMessageWidget *theAdvice = (CustomMessageWidget *)operator new(820u);
    MessageWidget_MessageWidget(theAdvice, board->mApp);
    theAdvice->mIcon = nullptr;
    board->mAdvice = theAdvice;
}

void Board_startLevel(Board *board) {
    old_Board_startLevel(board);
}

void Board::InitLevel() {
    old_Board_InitLevel(this);
    mNewWallNutAndSunFlowerAndChomperOnly = !(LawnApp_IsScaryPotterLevel(mApp) || LawnApp_IsIZombieLevel(mApp) || LawnApp_IsWhackAZombieLevel(mApp)
                                                     || Board_HasConveyorBeltSeedBank(this, 0) || LawnApp_IsChallengeWithoutSeedBank(mApp));
    mNewPeaShooterCount = 0;
}

void Board_RemovedFromManager(Board *board, int *manager) {
    Sexy_Widget_RemoveWidget(board, mBoardMenuButton);
    Sexy_Widget_RemoveWidget(board, mBoardStoreButton);
    GameButton_Delete(mBoardMenuButton);
    GameButton_Delete(mBoardStoreButton);
    mBoardMenuButton = nullptr;
    mBoardStoreButton = nullptr;
    old_Board_RemovedFromManager(board, manager);
}

void Board_UpdateButtons(Board *board) {
    if (board->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        mBoardMenuButton->mBtnNoDraw = false;
        mBoardMenuButton->mDisabled = false;
    } else {
        if (board->mApp->mGameScene == GameScenes::SCENE_PLAYING) {
            mBoardMenuButton->mBtnNoDraw = false;
            mBoardMenuButton->mDisabled = false;
        } else {
            mBoardMenuButton->mBtnNoDraw = true;
            mBoardMenuButton->mDisabled = true;
        }
    }
    if (board->mBoardFadeOutCounter > 0) {
        mBoardMenuButton->mBtnNoDraw = true;
        mBoardMenuButton->mDisabled = true;
    }
}


void Board_ButtonDepress(Board *board, int id) {
    if (id == 1000) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || lawnApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) {
            LawnApp_DoBackToMain(lawnApp);
            return;
        }
        LawnApp_PlaySample(lawnApp, *Sexy_SOUND_PAUSE_Addr);
        LawnApp_DoNewOptions(lawnApp, false, 0);
        return;
    } else if (id == 1001) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND) {
            Board *mBoard = lawnApp->mBoard;
            mBoard->mChallenge->mChallengeState = ChallengeState::STATECHALLENGE_LAST_STAND_ONSLAUGHT;
            mBoardStoreButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = true;
            GameButton_Resize(mBoardStoreButton, 0, 0, 0, 0);
            mBoard->mZombieCountDown = 9;
            mBoard->mZombieCountDownStart = mBoard->mZombieCountDown;
        } else if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN) {
            ZenGarden_OpenStore(lawnApp->mZenGarden);
        } else if (lawnApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM) {
            Challenge_TreeOfWisdomOpenStore(lawnApp->mBoard->mChallenge);
        }
    }
    old_Board_ButtonDepress(board, id);
}

Sexy::Image *GetIconByAchievementId(AchievementId::AchievementId theAchievementId) {
    switch (theAchievementId) {
        case AchievementId::ACHIEVEMENT_HOME_SECURITY:
            return addonImages.achievement_homeLawnsecurity;
        case AchievementId::ACHIEVEMENT_MORTICULTURALIST:
            return addonImages.achievement_morticulturalist;
        case AchievementId::ACHIEVEMENT_IMMORTAL:
            return addonImages.achievement_immortal;
        case AchievementId::ACHIEVEMENT_SOILPLANTS:
            return addonImages.achievement_soilplants;
        case AchievementId::ACHIEVEMENT_CLOSESHAVE:
            return addonImages.achievement_closeshave;
        case AchievementId::ACHIEVEMENT_CHOMP:
            return addonImages.achievement_chomp;
        case AchievementId::ACHIEVEMENT_VERSUS:
            return addonImages.achievement_versusz;
        case AchievementId::ACHIEVEMENT_GARG:
            return addonImages.achievement_garg;
        case AchievementId::ACHIEVEMENT_COOP:
            return addonImages.achievement_coop;
        case AchievementId::ACHIEVEMENT_SHOP:
            return addonImages.achievement_shop;
        case AchievementId::ACHIEVEMENT_EXPLODONATOR:
            return addonImages.achievement_explodonator;
        case AchievementId::ACHIEVEMENT_TREE:
            return addonImages.achievement_tree;
        default:
            return nullptr;
    }
}

const char *GetNameByAchievementId(AchievementId::AchievementId theAchievementId) {
    switch (theAchievementId) {
        case AchievementId::ACHIEVEMENT_HOME_SECURITY:
            return "ACHIEVEMENT_HOME_SECURITY";
        case AchievementId::ACHIEVEMENT_MORTICULTURALIST:
            return "ACHIEVEMENT_MORTICULTURALIST";
        case AchievementId::ACHIEVEMENT_IMMORTAL:
            return "ACHIEVEMENT_IMMORTAL";
        case AchievementId::ACHIEVEMENT_SOILPLANTS:
            return "ACHIEVEMENT_SOILPLANTS";
        case AchievementId::ACHIEVEMENT_CLOSESHAVE:
            return "ACHIEVEMENT_CLOSESHAVE";
        case AchievementId::ACHIEVEMENT_CHOMP:
            return "ACHIEVEMENT_CHOMP";
        case AchievementId::ACHIEVEMENT_VERSUS:
            return "ACHIEVEMENT_VERSUS";
        case AchievementId::ACHIEVEMENT_GARG:
            return "ACHIEVEMENT_GARG";
        case AchievementId::ACHIEVEMENT_COOP:
            return "ACHIEVEMENT_COOP";
        case AchievementId::ACHIEVEMENT_SHOP:
            return "ACHIEVEMENT_SHOP";
        case AchievementId::ACHIEVEMENT_EXPLODONATOR:
            return "ACHIEVEMENT_EXPLODONATOR";
        case AchievementId::ACHIEVEMENT_TREE:
            return "ACHIEVEMENT_TREE";
        default:
            return "";
    }
}

bool Board_GrantAchievement(Board *board, AchievementId::AchievementId theAchievementId, bool show) {
    LawnApp *lawnApp = board->mApp;
    PlayerInfo *playerInfo = lawnApp->mPlayerInfo;
    if (!playerInfo->mAchievements[theAchievementId]) {
        LawnApp_PlaySample(lawnApp, addonSounds.achievement);
        Board_ClearAdviceImmediately(board);
        const char *theAchievementName = GetNameByAchievementId(theAchievementId);
        int holder[1];
        int holder1[1];
        int holder2[1];
        TodStringTranslate(holder, "[ACHIEVEMENT_GRANTED]");
        Sexy_StrFormat(holder1, "[%s]", theAchievementName);
        TodReplaceString(holder2, holder, "{achievement}", holder1);
        Board_DisplayAdviceAgain(board, holder2, MessageStyle::MESSAGE_STYLE_ACHIEVEMENT, AdviceType::ADVICE_NEED_ACHIVEMENT_EARNED);
        ((CustomMessageWidget *)board->mAdvice)->mIcon = GetIconByAchievementId(theAchievementId);
        Sexy_String_Delete(holder);
        Sexy_String_Delete(holder1);
        Sexy_String_Delete(holder2);
        playerInfo->mAchievements[theAchievementId] = true;
        return true;
    }
    return false;
}

void Board_FadeOutLevel(Board *board) {
    old_Board_FadeOutLevel(board);

    if (LawnApp_IsSurvivalMode(board->mApp) && board->mChallenge->mSurvivalStage >= 19) {
        Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_IMMORTAL, true);
    }

    if (!LawnApp_IsSurvivalMode(board->mApp)) {
        int theNumLawnMowers = 0;
        for (int i = 0; i < 6; ++i) {
            if (board->mPlantRow[i] != PlantRowType::PLANTROW_DIRT) {
                theNumLawnMowers++;
            }
        }
        if (board->mTriggeredLawnMowers == theNumLawnMowers) {
            Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_CLOSESHAVE, true);
        }
    }
    if (board->mLevel == 50) {
        Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_HOME_SECURITY, true);
    }

    if (board->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_COOP_BOWLING) {
        Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_COOP, true);
    }

    if (board->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        if ((VSResultsMenu_msPlayerRecords_Addr[3] == 4 && board->mApp->mBoardResult == BoardResult::BOARDRESULT_VS_PLANT_WON)
            || (VSResultsMenu_msPlayerRecords_Addr[8] == 4 && board->mApp->mBoardResult == BoardResult::BOARDRESULT_VS_ZOMBIE_WON)) {
            Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_VERSUS, true);
        }
    }

    if (board->mNewWallNutAndSunFlowerAndChomperOnly && !LawnApp_IsSurvivalMode(board->mApp) && !Board_HasConveyorBeltSeedBank(board, 0)) {
        int num = board->mSeedBank1->mNumPackets;
        for (int i = 0; i < num; ++i) {
            SeedType theType = board->mSeedBank1->mSeedPackets[i].mPacketType;
            if (theType == SeedType::SEED_CHOMPER || theType == SeedType::SEED_WALLNUT || theType == SeedType::SEED_SUNFLOWER) {
                Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_CHOMP, true);
                break;
            }
        }
    }
}

void Board_DoPlantingAchievementCheck(Board *board, SeedType theType) {
    if (theType != SeedType::SEED_CHOMPER && theType != SeedType::SEED_SUNFLOWER && theType != SeedType::SEED_WALLNUT) {
        board->mNewWallNutAndSunFlowerAndChomperOnly = false;
    }
    if (theType == SeedType::SEED_PEASHOOTER && !Board_HasConveyorBeltSeedBank(board, 0)) {
        board->mNewPeaShooterCount++;
        if (board->mNewPeaShooterCount >= 10) {
            Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_SOILPLANTS, true);
        }
    }
}

void Board_DrawUITop(Board *board, Sexy::Graphics *graphics) {
    if (seedBankPin && !LawnApp_IsSlotMachineLevel(board->mApp)) {
        if (board->mApp->mGameScene != GameScenes::SCENE_LEADER_BOARD && board->mApp->mGameScene != GameScenes::SCENE_ZOMBIES_WON) {
            if (SeedBank_BeginDraw(board->mSeedBank1, graphics)) {
                board->mSeedBank1->SeedBank::Draw(graphics);
                SeedBank_EndDraw(board->mSeedBank1, graphics);
            }

            if (board->mSeedBank2 != nullptr) {
                if (SeedBank_BeginDraw(board->mSeedBank2, graphics)) {
                    board->mSeedBank2->SeedBank::Draw(graphics);
                    SeedBank_EndDraw(board->mSeedBank2, graphics);
                }
            }
        }
    }
    old_Board_DrawUITop(board, graphics);
}

void Board_GetShovelButtonRect(TRect *rect, Board *board) {
    old_Board_GetShovelButtonRect(rect, board);
}

void Board_DrawBackdrop(Board *board, Sexy::Graphics *graphics) {
    // 实现泳池动态效果、实现对战结盟分界线
    old_Board_DrawBackdrop(board, graphics);
    BackgroundType mBackgroundType = board->mBackgroundType;

    //    if (mBackgroundType == BackgroundType::BACKGROUND_3_POOL || mBackgroundType == BackgroundType::BACKGROUND_4_FOG) {
    //        PoolEffect_PoolEffectDraw(board->mApp->mPoolEffect, graphics, Board_StageIsNight(board));
    //    }

    LawnApp *lawnApp = board->mApp;
    GameMode mGameMode = lawnApp->mGameMode;
    if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        switch (mBackgroundType) {
            case BackgroundType::BACKGROUND_1_DAY:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::BACKGROUND_2_NIGHT:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::BACKGROUND_3_POOL:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::BACKGROUND_4_FOG:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::BACKGROUND_5_ROOF:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::BACKGROUND_6_BOSS:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            default:
                break;
        }
        return;
    }
    if (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS && mGameMode != GameMode::GAMEMODE_TWO_PLAYER_COOP_BOWLING) {
        switch (mBackgroundType) {
            case BackgroundType::BACKGROUND_1_DAY:
                Sexy_Graphics_DrawImage(graphics, addonImages.stripe_day_coop, 384, 69);
                break;
            case BackgroundType::BACKGROUND_2_NIGHT:
                Sexy_Graphics_DrawImage(graphics, addonImages.stripe_day_coop, 384, 69);
                break;
            case BackgroundType::BACKGROUND_3_POOL:
                Sexy_Graphics_DrawImage(graphics, addonImages.stripe_pool_coop, 348, 72);
                break;
            case BackgroundType::BACKGROUND_4_FOG:
                Sexy_Graphics_DrawImage(graphics, addonImages.stripe_pool_coop, 348, 72);
                break;
            case BackgroundType::BACKGROUND_5_ROOF:
                Sexy_Graphics_DrawImage(graphics, addonImages.stripe_roof_left, 365, 82);
                break;
            case BackgroundType::BACKGROUND_6_BOSS:
                Sexy_Graphics_DrawImage(graphics, addonImages.stripe_roof_left, 365, 82);
                break;
            default:
                break;
        }
    }
}

bool Board_RowCanHaveZombieType(Board *board, int theRow, ZombieType theZombieType) {
    if (board->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_POOL_PARTY) {
        return ZombieTypeCanGoInPool(theZombieType);
    }
    return old_Board_RowCanHaveZombieType(board, theRow, theZombieType);
}

void Board_ShakeBoard(Board *board, int theShakeAmountX, int theShakeAmountY) {
    // 添加 手机震动效果
    old_Board_ShakeBoard(board, theShakeAmountX, theShakeAmountY);
    if (board->mApp->mPlayerInfo->mIsVibrateClosed) {
        return;
    }
    Native::BridgeApp *bridgeApp = Native_BridgeApp_getSingleton();
    JNIEnv *env = Native_BridgeApp_getJNIEnv(bridgeApp);
    jobject activity = Native_NativeApp_getActivity(bridgeApp->mNativeApp);
    jclass cls = env->GetObjectClass(activity);
    jmethodID methodID = env->GetMethodID(cls, "vibrate", "(I)V");
    //    env->CallVoidMethod(activity, methodID, 120);
    env->CallVoidMethod(activity, methodID, (abs(theShakeAmountX) + abs(theShakeAmountY)) * 50);
    env->DeleteLocalRef(cls);
}

int Board::GetNumSeedsInBank(bool thePlayerIdx) {
    return old_Board_GetNumSeedsInBank(this, thePlayerIdx);
}

void Board::RemoveParticleByType(ParticleEffect theEffectType) {
    TodParticleSystem* aParticle = nullptr;
    while (Board_IterateParticles(this, &aParticle))
    {
        if (aParticle->mEffectType == theEffectType)
        {
            TodParticleSystem_ParticleSystemDie(aParticle);
        }
    }
}