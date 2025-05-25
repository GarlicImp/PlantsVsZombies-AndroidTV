#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/Challenge.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Plant.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/SeedBank.h"
#include "PvZ/Lawn/ZenGarden.h"
#include "PvZ/Lawn/Zombie.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Symbols.h"

void GamepadControls_pickUpCobCannon(int gamePad, int cobCannon) {
    // 用于拿起指定的加农炮
    int v8;        // r6
    int v9;        // r1
    int *v10;      // r0
    int v11;       // r3
    int v12;       // r3
    int v13;       // r7
    int v14;       // r6
    int v15;       // r1
    int v16;       // s14
    int v17;       // s15
    uint32_t *v18; // r3
    int v19;       // r3

    v8 = 0;
    v9 = *((uint32_t *)gamePad + 37);
    v10 = (int *)*((uint32_t *)gamePad + 14);
    if (v9)
        v11 = 140;
    else
        v11 = 141;
    v12 = *((uint32_t *)v10 + v11);
    if (*(uint32_t *)(v12 + 152) != -1) {
        if (*(uint8_t *)(v12 + 200)) {
            v19 = *(uint32_t *)(v12 + 196);
            if (v19) {
                if ((unsigned int)(unsigned int)v19 < *((uint32_t *)v10 + 79)) {
                    if (v19 == *(uint32_t *)(*((uint32_t *)v10 + 77) + 352 * (unsigned int)v19 + 348))
                        v8 = *((uint32_t *)v10 + 77) + 352 * (unsigned int)v19;
                    else
                        v8 = 0;
                }
            } else {
                v8 = 0;
            }
        } else {
            v8 = *(uint8_t *)(v12 + 200);
        }
    }
    v13 = cobCannon;
    if (cobCannon != v8 && *(uint32_t *)(cobCannon + 76) == 37 && *((uint32_t *)gamePad + 24) != 8) {
        v14 = *((uint8_t *)gamePad + 200);
        if (!*((uint8_t *)gamePad + 200)) {
            Board *aBoard = reinterpret_cast<Board *>(v10); // 显式类型转换
            aBoard->ClearCursor(v9);
            v15 = *(uint32_t *)(v13 + 348);
            v16 = (int)*((float *)gamePad + 27);
            v17 = (int)*((float *)gamePad + 28);
            v18 = (uint32_t *)(*((uint32_t *)gamePad + 14) + 22528);
            v18[29] = 30;
            v18[30] = v16;
            v18[31] = v17;
            *((uint32_t *)gamePad + 49) = v15;
            *((uint32_t *)gamePad + 55) = v14;
            *((uint8_t *)gamePad + 200) = 1;
        }
    }
}

void GamepadControls_Draw(GamepadControls *gamepadControls, Sexy::Graphics *graphics) {
    // 实现在光标内绘制铲子和黄油手套(黄油手套其实就是花园的手套),并在锤僵尸关卡绘制种植预览

    if (gamepadControls->mPlayerIndex2 != -1) {
        Board *board = gamepadControls->mBoard;
        LawnApp *lawnApp = gamepadControls->mGameObject.mApp;
        bool is2P = gamepadControls->mPlayerIndex1 == 1;
        CursorObject *cursorObject = is2P ? board->mCursorObject2 : board->mCursorObject1;
        if (is2P) {
            if (requestDrawButterInCursor) {
                if (!LawnApp_IsCoopMode(lawnApp))
                    requestDrawButterInCursor = false;
                Sexy_Graphics_DrawImage(graphics, addonImages.butter_glove, gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
            }
        } else {
            if (requestDrawShovelInCursor) {
                if (!board->mShowShovel)
                    requestDrawShovelInCursor = false;
                if (lawnApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND) {
                    if (board->mChallenge->mChallengeState == ChallengeState::STATECHALLENGE_NORMAL && lawnApp->mGameScene == GameScenes::SCENE_PLAYING) {
                        cursorObject->mCursorType = CursorType::CURSOR_TYPE_MONEY_SIGN;
                        cursorObject->mX = gamepadControls->mCursorPositionX;
                        cursorObject->mY = gamepadControls->mCursorPositionY;
                    } else {
                        cursorObject->mCursorType = CursorType::CURSOR_TYPE_SHOVEL;
                        cursorObject->mX = gamepadControls->mCursorPositionX - 20;
                        cursorObject->mY = gamepadControls->mCursorPositionY - 20;
                    }
                } else {
                    cursorObject->mCursorType = CursorType::CURSOR_TYPE_SHOVEL;
                    cursorObject->mX = gamepadControls->mCursorPositionX - 20;
                    cursorObject->mY = gamepadControls->mCursorPositionY - 20;
                }

                if (CursorObject_BeginDraw(cursorObject, graphics)) {
                    CursorObject_Draw(cursorObject, graphics);
                    CursorObject_EndDraw(cursorObject, graphics);
                }
            }
        }
        if (LawnApp_IsWhackAZombieLevel(lawnApp)) {
            int theGridX = board->PixelToGridXKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
            int theGridY = board->PixelToGridYKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
            int thePixelX = gamepadControls->mBoard->GridToPixelX(theGridX, theGridY);
            int thePixelY = gamepadControls->mBoard->GridToPixelY(theGridX, theGridY);
            graphics->mTransX += thePixelX;
            graphics->mTransY += thePixelY;
            GamepadControls_DrawPreview(gamepadControls, graphics);
            graphics->mTransX -= thePixelX;
            graphics->mTransY -= thePixelY;
        }
    }
    if (gamepadControls->mIsCobCannonSelected && useNewCobCannon && !keyboardMode) {
        Sexy::Image *cobcannon_1 = *Sexy_IMAGE_COBCANNON_TARGET_1_Addr;
        *Sexy_IMAGE_COBCANNON_TARGET_1_Addr = addonImages.custom_cobcannon;
        old_GamepadControls_Draw(gamepadControls, graphics);
        *Sexy_IMAGE_COBCANNON_TARGET_1_Addr = cobcannon_1;
        return;
    }

    return old_GamepadControls_Draw(gamepadControls, graphics);
}

void GamepadControls_Update(GamepadControls *gamepadControls, float a2) {
    Board *board = gamepadControls->mBoard;
    LawnApp *lawnApp = gamepadControls->mGameObject.mApp;
    int theGridX = board->PixelToGridXKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
    int theGridY = board->PixelToGridYKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
    int mGridCenterPositionX = board->GridToPixelX(theGridX, theGridY) + board->GridCellWidth(theGridX, theGridY) / 2;
    int mGridCenterPositionY = board->GridToPixelY(theGridX, theGridY) + board->GridCellHeight(theGridX, theGridY) / 2;
    // 键盘双人模式 平滑移动光标
    if (isKeyboardTwoPlayerMode) {
        if (gamepadControls->mPlayerIndex2 == 0) {
            gamepadControls->mGamepadVelocityLeftX = GamepadVelocityXOfPlayer1;
            gamepadControls->mGamepadVelocityLeftY = GamepadVelocityYOfPlayer1;
            if (GamepadVelocityXOfPlayer1 == 0) {
                gamepadControls->mCursorPositionX += (mGridCenterPositionX - gamepadControls->mCursorPositionX) / 10;
            }
            if (GamepadVelocityYOfPlayer1 == 0) {
                gamepadControls->mCursorPositionY += (mGridCenterPositionY - gamepadControls->mCursorPositionY) / 10;
            }
        } else if (gamepadControls->mPlayerIndex2 == 1) {
            gamepadControls->mGamepadVelocityLeftX = GamepadVelocityXOfPlayer2;
            gamepadControls->mGamepadVelocityLeftY = GamepadVelocityYOfPlayer2;
            if (GamepadVelocityXOfPlayer2 == 0) {
                gamepadControls->mCursorPositionX += (mGridCenterPositionX - gamepadControls->mCursorPositionX) / 10;
            }
            if (GamepadVelocityYOfPlayer2 == 0) {
                gamepadControls->mCursorPositionY += (mGridCenterPositionY - gamepadControls->mCursorPositionY) / 10;
            }
        }
    }

    if (positionAutoFix && !LawnApp_IsWhackAZombieLevel(lawnApp) && lawnApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM) {
        if (gamepadControls->mPlayerIndex2 == 0 && gPlayerIndex != TouchPlayerIndex::Player1 && gPlayerIndexSecond != TouchPlayerIndex::Player1) {
            gamepadControls->mCursorPositionX += (mGridCenterPositionX - gamepadControls->mCursorPositionX) / 10;
            gamepadControls->mCursorPositionY += (mGridCenterPositionY - gamepadControls->mCursorPositionY) / 10;
        }
        if (gamepadControls->mPlayerIndex2 == 1 && gPlayerIndex != TouchPlayerIndex::Player2 && gPlayerIndexSecond != TouchPlayerIndex::Player2) {
            gamepadControls->mCursorPositionX += (mGridCenterPositionX - gamepadControls->mCursorPositionX) / 10;
            gamepadControls->mCursorPositionY += (mGridCenterPositionY - gamepadControls->mCursorPositionY) / 10;
        }
    }


    old_GamepadControls_Update(gamepadControls, a2);

    //    Reanimation *mCursorReanim = ReanimationTryToGet(gamepadControls->mGameObject.mApp, gamepadControls->mCursorReanimID);
    //    LOGD("%d",mCursorReanim);
    //    if (mCursorReanim != nullptr) {
    //        if ((gamepadControls->mPlayerIndex2 == 0 &&(mIsZombie == TouchPlayerIndex::Player1 || gPlayerIndexSecond == TouchPlayerIndex::Player1)) || (gamepadControls->mPlayerIndex2 == 1
    //        &&(mIsZombie == TouchPlayerIndex::Player2 || gPlayerIndexSecond == TouchPlayerIndex::Player2))) {
    //            if (!Reanimation_IsAnimPlaying(mCursorReanim, "anim_depressed"))
    //                Reanimation_PlayReanim(mCursorReanim, "anim_depressed", a::REANIM_LOOP, 0,12.0);
    //            LOGD("456456");
    //        } else if (!Reanimation_IsAnimPlaying(mCursorReanim, "anim_bounce")) {
    //            Reanimation_PlayReanim(mCursorReanim, "anim_bounce", a::REANIM_LOOP, 0, 12.0);
    //        }
    //    }

    if (!isKeyboardTwoPlayerMode && !LawnApp_CanShopLevel(lawnApp) && gamepadControls->mGamepadState == 6 && gamepadControls->mIsInShopSeedBank) {
        gamepadControls->mIsInShopSeedBank = false;
    }
}


void GamepadControls_GamepadControls(GamepadControls *gamepadControls, Board *board, int a3, int a4) {
    old_GamepadControls_GamepadControls(gamepadControls, board, a3, a4);
    if (isKeyboardTwoPlayerMode)
        return;
    GameMode mGameMode = gamepadControls->mGameObject.mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::GAMEMODE_MP_VS || (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS));
    if (!keyboardMode && !isTwoSeedBankMode && mGameMode != GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE) {
        gamepadControls->mIsInShopSeedBank = true; // 是否在Shop栏。
    }
}

void GamepadControls_ButtonDownFireCobcannonTest(GamepadControls *gamepadControls) {
    // 解除加农炮选取半秒后才能发射的限制
    gamepadControls->mBoard->mCobCannonCursorDelayCounter = 0;
    return old_GamepadControls_ButtonDownFireCobcannonTest(gamepadControls);
}

void GamepadControls_InvalidatePreviewReanim(GamepadControls *gamepadControls) {
    Reanimation *mPreviewReanim4 = gamepadControls->mGameObject.mApp->ReanimationTryToGet(gamepadControls->mPreviewReanimID4);
    if (mPreviewReanim4 != nullptr) {
        Reanimation_ReanimationDie(mPreviewReanim4);
        gamepadControls->mPreviewReanimID4 = ReanimationID::REANIMATIONID_NULL;
    }
    int mPreviewReanim3 = gamepadControls->mPreviewReanimID3;
    if (mPreviewReanim3 != 0) {
        LawnApp_RemoveReanimation(gamepadControls->mGameObject.mApp, mPreviewReanim3);
        gamepadControls->mPreviewReanimID3 = 0;
    }
}

FilterEffect GetFilterEffectTypeBySeedType(SeedType mSeedType) {
    if (mSeedType == SeedType::SEED_HYPNOSHROOM || mSeedType == SeedType::SEED_SQUASH || mSeedType == SeedType::SEED_POTATOMINE || mSeedType == SeedType::SEED_GARLIC
        || mSeedType == SeedType::SEED_LILYPAD) {
        return FilterEffect::FILTEREFFECT_LESS_WASHED_OUT;
    }
    return FilterEffect::FILTEREFFECT_WASHED_OUT;
}

void GamepadControls_UpdatePreviewReanim(GamepadControls *gamepadControls) {
    // 动态预览!!

    // TV后续版本仅在PreviewingSeedType切换时进行一次Reanimation::Update，而TV 1.0.1则是无时无刻进行Reanimation::Update。我们恢复1.0.1的逻辑即可。

    LawnApp *lawnApp = gamepadControls->mGameObject.mApp;
    CursorObject *cursorObject = gamepadControls->mPlayerIndex1 ? gamepadControls->mBoard->mCursorObject2 : gamepadControls->mBoard->mCursorObject1;

    if (!dynamicPreview) { // 如果没开启动态预览，则开启砸罐子无尽和锤僵尸关卡的动态预览，并执行旧游戏函数。
        if ((LawnApp_IsWhackAZombieLevel(lawnApp) || LawnApp_IsScaryPotterLevel(lawnApp)) && gamepadControls->mGamepadState == 7) {
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls);
            SeedPacket *seedPacket = &seedBank->mSeedPackets[gamepadControls->mSelectedSeedIndex];
            cursorObject->mType = seedPacket->mPacketType;
            cursorObject->mImitaterType = seedPacket->mImitaterType;
        }
        return old_GamepadControls_UpdatePreviewReanim(gamepadControls);
    }

    GameMode mGameMode = lawnApp->mGameMode;
    Board *board = gamepadControls->mBoard;
    int theGridX = board->PixelToGridXKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
    int theGridY = board->PixelToGridYKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls);
    SeedType mSeedType = cursorObject->mType;
    bool isImitater = seedBank->mSeedPackets[gamepadControls->mSelectedSeedIndex].mPacketType == SeedType::SEED_IMITATER;

    if ((LawnApp_IsWhackAZombieLevel(lawnApp) || mGameMode == GameMode::GAMEMODE_SCARY_POTTER_ENDLESS) && gamepadControls->mGamepadState == 7) {
        // 开启砸罐子无尽和锤僵尸关卡的动态预览
        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls);
        SeedPacket *seedPacket = &seedBank->mSeedPackets[gamepadControls->mSelectedSeedIndex];
        cursorObject->mType = seedPacket->mPacketType;
        cursorObject->mImitaterType = seedPacket->mImitaterType;
    }

    if (gamepadControls->mIsZombie) {
        mSeedType = seedBank->mSeedPackets[gamepadControls->mSelectedSeedIndex].mPacketType;
    }
    if (mSeedType == SeedType::SEED_IMITATER) {
        mSeedType = cursorObject->mImitaterType;
    }

    bool flagUpdateCanPlant = true;
    bool flagDrawGray = false;
    bool flagUpdateChangeType = false;
    if (gamepadControls->mPreviewingSeedType != mSeedType && mSeedType != SeedType::SEED_NONE) {
        Reanimation *theNewPreviewingReanim = nullptr;
        GamepadControls_InvalidatePreviewReanim(gamepadControls);
        RenderLayer aRenderLayer = gamepadControls->mIsZombie ? RENDER_LAYER_ZOMBIE : RENDER_LAYER_PLANT;
        int aRenderOrder = Board::MakeRenderOrder(aRenderLayer, theGridY, 100);
        float theDrawHeightOffset = PlantDrawHeightOffset(board, 0, mSeedType, theGridX, theGridY);
        if (gamepadControls->mIsZombie) {
            ZombieType theZombieType = Challenge::IZombieSeedTypeToZombieType(mSeedType);
            switch (theZombieType) {
                case ZombieType::ZOMBIE_INVALID:
                    gamepadControls->mPreviewingSeedType = mSeedType;
                    return;
                case ZombieType::ZOMBIE_GARGANTUAR:
                case ZombieType::ZOMBIE_REDEYE_GARGANTUAR: // 在对战里可能用得到
                    theDrawHeightOffset += 30.0;
                    break;
                case ZombieType::ZOMBIE_POLEVAULTER:
                    theDrawHeightOffset += 15.0;
                    break;
            }
            ZombieDefinition &theZombieDefinition = GetZombieDefinition(theZombieType);
            Reanimation *zombieReanim = LawnApp_AddReanimation(lawnApp, -20.0, -35 - theDrawHeightOffset, aRenderOrder + 1, theZombieDefinition.mReanimationType);
            Zombie::SetupReanimLayers(zombieReanim, theZombieType);
            if (theZombieType == ZombieType::ZOMBIE_DOOR || theZombieType == ZombieType::ZOMBIE_TRASH_BIN || theZombieType == ZombieType::ZOMBIE_NEWSPAPER
                || theZombieType == ZombieType::ZOMBIE_LADDER) {
                Zombie::SetupShieldReanims(theZombieType, zombieReanim);
            }
            zombieReanim->mIsAttachment = true;
            if (theZombieType == ZombieType::ZOMBIE_POGO) {
                Reanimation_PlayReanim(zombieReanim, "anim_pogo", ReanimLoopType::REANIM_LOOP, 0, 12.0);
            } else if (theZombieType == ZombieType::ZOMBIE_DANCER) {
                Reanimation_PlayReanim(zombieReanim, "anim_armraise", ReanimLoopType::REANIM_LOOP, 0, 12.0);
            } else if (theZombieType == ZombieType::ZOMBIE_ZAMBONI) {
                Reanimation_PlayReanim(zombieReanim, "anim_drive", ReanimLoopType::REANIM_LOOP, 0, 12.0);
            } else if (theZombieType == ZombieType::ZOMBIE_IMP) {
                Reanimation_PlayReanim(zombieReanim, "anim_walk", ReanimLoopType::REANIM_LOOP, 0, 12.0);
            } else {
                if (theZombieType == ZombieType::ZOMBIE_FLAG) {
                    Reanimation *zombieReanimAttachment = LawnApp_AddReanimation(lawnApp, 0, 0, 0, ReanimationType::REANIM_ZOMBIE_FLAGPOLE);
                    Reanimation_PlayReanim(zombieReanimAttachment, "Zombie_flag", ReanimLoopType::REANIM_LOOP, 0, 15.0);
                    gamepadControls->mPreviewReanimID3 = LawnApp_ReanimationGetID(lawnApp, zombieReanimAttachment);
                    ReanimatorTrackInstance *TrackInstanceByName = Reanimation_GetTrackInstanceByName(zombieReanim, "Zombie_flaghand");
                    AttachReanim(&TrackInstanceByName->mAttachmentID, zombieReanimAttachment, 0.0, 0.0);
                    zombieReanim->mFrameBasePose = 0;
                } else if (theZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR) {
                    Reanimation_SetImageOverride(zombieReanim, "anim_head1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_Addr);
                } else if (theZombieType == ZombieType::ZOMBIE_PEA_HEAD) {
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_hair", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_head2", true);
                    Reanimation_SetFramesForLayer(zombieReanim, "anim_walk2");
                    ReanimatorTrackInstance *aTrackInstance = Reanimation_GetTrackInstanceByName(zombieReanim, "anim_head1");
                    aTrackInstance->mImageOverride = *Sexy_IMAGE_BLANK_Addr;
                    Reanimation *aPeaHeadReanim = LawnApp_AddReanimation(lawnApp, 0.0f, 0.0f, 0, ReanimationType::REANIM_PEASHOOTER);
                    Reanimation_PlayReanim(aPeaHeadReanim, "anim_head_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
                    AttachEffect *aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aPeaHeadReanim, 0.0f, 0.0f);
                    zombieReanim->mFrameBasePose = 0;
                    TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 65.0f, -8.0f, 0.2f, -1.0f, 1.0f);
                } else if (theZombieType == ZombieType::ZOMBIE_WALLNUT_HEAD) {
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_hair", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_head", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "Zombie_tie", true);
                    Reanimation_SetFramesForLayer(zombieReanim, "anim_walk2");
                    ReanimatorTrackInstance *aTrackInstance = Reanimation_GetTrackInstanceByName(zombieReanim, "zombie_body");
                    Reanimation *aWallnutHeadReanim = LawnApp_AddReanimation(lawnApp, 0.0f, 0.0f, 0, ReanimationType::REANIM_WALLNUT);
                    Reanimation_PlayReanim(aWallnutHeadReanim, "anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
                    AttachEffect *aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aWallnutHeadReanim, 0.0f, 0.0f);
                    zombieReanim->mFrameBasePose = 0;
                    TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 50.0f, 0.0f, 0.2f, -0.8f, 0.8f);
                } else if (theZombieType == ZombieType::ZOMBIE_TALLNUT_HEAD) {
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_hair", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_head", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "Zombie_tie", true);
                    Reanimation_SetFramesForLayer(zombieReanim, "anim_walk2");
                    ReanimatorTrackInstance *aTrackInstance = Reanimation_GetTrackInstanceByName(zombieReanim, "zombie_body");
                    Reanimation *aTallnutHeadReanim = LawnApp_AddReanimation(lawnApp, 0.0f, 0.0f, 0, ReanimationType::REANIM_TALLNUT);
                    Reanimation_PlayReanim(aTallnutHeadReanim, "anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
                    AttachEffect *aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aTallnutHeadReanim, 0.0f, 0.0f);
                    zombieReanim->mFrameBasePose = 0;
                    TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 37.0f, 0.0f, 0.2f, -0.8f, 0.8f);
                } else if (theZombieType == ZombieType::ZOMBIE_JALAPENO_HEAD) {
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_hair", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_head", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "Zombie_tie", true);
                    Reanimation_SetFramesForLayer(zombieReanim, "anim_walk2");
                    ReanimatorTrackInstance *aTrackInstance = Reanimation_GetTrackInstanceByName(zombieReanim, "zombie_body");
                    Reanimation *aJalapenoHeadReanim = LawnApp_AddReanimation(lawnApp, 0.0f, 0.0f, 0, ReanimationType::REANIM_JALAPENO);
                    Reanimation_PlayReanim(aJalapenoHeadReanim, "anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
                    AttachEffect *aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aJalapenoHeadReanim, 0.0f, 0.0f);
                    zombieReanim->mFrameBasePose = 0;
                    TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 55.0f, -5.0f, 0.2f, -1.0f, 1.0f);
                } else if (theZombieType == ZombieType::ZOMBIE_GATLING_HEAD) {
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_hair", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_head2", true);
                    Reanimation_SetFramesForLayer(zombieReanim, "anim_walk2");
                    ReanimatorTrackInstance *aTrackInstance = Reanimation_GetTrackInstanceByName(zombieReanim, "anim_head1");
                    aTrackInstance->mImageOverride = *Sexy_IMAGE_BLANK_Addr;
                    Reanimation *aGatlingHeadReanim = LawnApp_AddReanimation(lawnApp, 0.0f, 0.0f, 0, ReanimationType::REANIM_GATLINGPEA);
                    Reanimation_PlayReanim(aGatlingHeadReanim, "anim_head_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
                    AttachEffect *aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aGatlingHeadReanim, 0.0f, 0.0f);
                    zombieReanim->mFrameBasePose = 0;
                    TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 65.0f, -5.0f, 0.2f, -1.0f, 1.0f);
                } else if (theZombieType == ZombieType::ZOMBIE_SQUASH_HEAD) {
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_hair", true);
                    Reanimation_HideTrackByPrefix(zombieReanim, "anim_head2", true);
                    Reanimation_SetFramesForLayer(zombieReanim, "anim_walk2");
                    ReanimatorTrackInstance *aTrackInstance = Reanimation_GetTrackInstanceByName(zombieReanim, "anim_head1");
                    aTrackInstance->mImageOverride = *Sexy_IMAGE_BLANK_Addr;
                    Reanimation *aSquashHeadReanim = LawnApp_AddReanimation(lawnApp, 0.0f, 0.0f, 0, ReanimationType::REANIM_SQUASH);
                    Reanimation_PlayReanim(aSquashHeadReanim, "anim_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0f);
                    AttachEffect *aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aSquashHeadReanim, 0.0f, 0.0f);
                    zombieReanim->mFrameBasePose = 0;
                    TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 55.0f, -15.0f, 0.2f, -0.75f, 0.75f);
                }
                Reanimation_PlayReanim(zombieReanim, "anim_idle", ReanimLoopType::REANIM_LOOP, 0, 12.0);
            }
            theNewPreviewingReanim = zombieReanim;
        } else {
            if (mSeedType >= SeedType::NUM_SEED_TYPES || mSeedType == SeedType::NUM_SEEDS_IN_CHOOSER)
                return;
            Reanimation *plantReanim = LawnApp_AddReanimation(lawnApp, 0.0, theDrawHeightOffset, aRenderOrder + 2, GetPlantDefinition(mSeedType).mReanimationType);
            plantReanim->mIsAttachment = true;
            if (isImitater)
                plantReanim->mFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
            Reanimation_PlayReanim(plantReanim, "anim_idle", ReanimLoopType::REANIM_LOOP, 0, 12.0);

            // 为豌豆家族加入其stem动画
            if (mSeedType == SeedType::SEED_PEASHOOTER || mSeedType == SeedType::SEED_SNOWPEA || mSeedType == SeedType::SEED_REPEATER || mSeedType == SeedType::SEED_GATLINGPEA
                || mSeedType == SeedType::SEED_LEFTPEATER) {
                Reanimation *plantReanimAttachment = LawnApp_AddReanimation(lawnApp, 0.0, theDrawHeightOffset, aRenderOrder + 3, GetPlantDefinition(mSeedType).mReanimationType);
                plantReanimAttachment->mLoopType = ReanimLoopType::REANIM_LOOP;
                if (isImitater)
                    plantReanimAttachment->mFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
                Reanimation_SetFramesForLayer(plantReanimAttachment, "anim_head_idle");
                const char *trackName = "anim_stem";
                if (Reanimation_TrackExists(plantReanim, trackName) || (trackName = "anim_idle", Reanimation_TrackExists(plantReanim, trackName))) {
                    Reanimation_AttachToAnotherReanimation(plantReanimAttachment, plantReanim, trackName);
                }
            }
            // 为反向射手的两个头、三发射手的三个头加入动画
            if (mSeedType == SeedType::SEED_SPLITPEA) {
                Reanimation *plantReanimAttachment1 = LawnApp_AddReanimation(lawnApp, 0.0, 0.0, aRenderOrder + 3, GetPlantDefinition(mSeedType).mReanimationType);
                plantReanimAttachment1->mAnimRate = plantReanim->mAnimRate;
                plantReanimAttachment1->mLoopType = ReanimLoopType::REANIM_LOOP;
                if (isImitater)
                    plantReanimAttachment1->mFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
                Reanimation_SetFramesForLayer(plantReanimAttachment1, "anim_head_idle");
                Reanimation_AttachToAnotherReanimation(plantReanimAttachment1, plantReanim, "anim_idle");
                Reanimation *plantReanimAttachment2 = LawnApp_AddReanimation(lawnApp, 0.0, 0.0, aRenderOrder + 3, GetPlantDefinition(mSeedType).mReanimationType);
                plantReanimAttachment2->mAnimRate = plantReanim->mAnimRate;
                plantReanimAttachment2->mLoopType = ReanimLoopType::REANIM_LOOP;
                if (isImitater)
                    plantReanimAttachment2->mFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
                Reanimation_SetFramesForLayer(plantReanimAttachment2, "anim_splitpea_idle");
                Reanimation_AttachToAnotherReanimation(plantReanimAttachment2, plantReanim, "anim_idle");
            } else if (mSeedType == SeedType::SEED_THREEPEATER) {
                plantReanim->mAnimRate = RandRangeFloat(15.0, 20.0);
                Reanimation *plantReanimAttachment1 = LawnApp_AddReanimation(lawnApp, 0.0, 0.0, aRenderOrder + 3, GetPlantDefinition(mSeedType).mReanimationType);
                plantReanimAttachment1->mAnimRate = plantReanim->mAnimRate;
                plantReanimAttachment1->mLoopType = ReanimLoopType::REANIM_LOOP;
                if (isImitater)
                    plantReanimAttachment1->mFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
                Reanimation_SetFramesForLayer(plantReanimAttachment1, "anim_head_idle1");
                Reanimation_AttachToAnotherReanimation(plantReanimAttachment1, plantReanim, "anim_head1");
                Reanimation *plantReanimAttachment2 = LawnApp_AddReanimation(lawnApp, 0.0, 0.0, aRenderOrder + 3, GetPlantDefinition(mSeedType).mReanimationType);
                plantReanimAttachment2->mAnimRate = plantReanim->mAnimRate;
                plantReanimAttachment2->mLoopType = ReanimLoopType::REANIM_LOOP;
                if (isImitater)
                    plantReanimAttachment2->mFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
                Reanimation_SetFramesForLayer(plantReanimAttachment2, "anim_head_idle2");
                Reanimation_AttachToAnotherReanimation(plantReanimAttachment2, plantReanim, "anim_head2");
                Reanimation *plantReanimAttachment3 = LawnApp_AddReanimation(lawnApp, 0.0, 0.0, aRenderOrder + 3, GetPlantDefinition(mSeedType).mReanimationType);
                plantReanimAttachment3->mAnimRate = plantReanim->mAnimRate;
                plantReanimAttachment3->mLoopType = ReanimLoopType::REANIM_LOOP;
                if (isImitater)
                    plantReanimAttachment3->mFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
                Reanimation_SetFramesForLayer(plantReanimAttachment3, "anim_head_idle3");
                Reanimation_AttachToAnotherReanimation(plantReanimAttachment3, plantReanim, "anim_head3");
            }
            theNewPreviewingReanim = plantReanim;
        }
        gamepadControls->mPreviewingSeedType = mSeedType;
        gamepadControls->mPreviewReanimID4 = LawnApp_ReanimationGetID(lawnApp, theNewPreviewingReanim);
        flagUpdateChangeType = true;
    } else {
        // 如果目标预览植物类型没变化, 则为模仿者上色
        Reanimation *mPreviewReanim4 = gamepadControls->mGameObject.mApp->ReanimationTryToGet(gamepadControls->mPreviewReanimID4);
        if (mPreviewReanim4 != nullptr) {
            FilterEffect aFilterEffect = isImitater ? GetFilterEffectTypeBySeedType(mSeedType) : FilterEffect::FILTEREFFECT_NONE;
            mPreviewReanim4->mFilterEffect = aFilterEffect;
            if (mSeedType == SeedType::SEED_THREEPEATER || mSeedType == SeedType::SEED_SPLITPEA || mSeedType == SeedType::SEED_PEASHOOTER || mSeedType == SeedType::SEED_SNOWPEA
                || mSeedType == SeedType::SEED_REPEATER || mSeedType == SeedType::SEED_GATLINGPEA || mSeedType == SeedType::SEED_LEFTPEATER) {
                int mTrackCount = mPreviewReanim4->mDefinition->mTrackCount;
                for (int i = 0; i < mTrackCount; i++) {
                    ReanimatorTrackInstance *reanimatorTrackInstance = mPreviewReanim4->mTrackInstances + i;
                    unsigned short mAttachmentID = reanimatorTrackInstance->mAttachmentID;
                    if (mAttachmentID == 0)
                        continue;
                    Attachment **attachmentSystem = *(Attachment ***)(*gEffectSystem_Addr + 12);
                    Attachment *attachment = &(*attachmentSystem)[mAttachmentID];
                    int mNumEffects = attachment->mNumEffects;
                    for (int j = 0; j < mNumEffects; ++j) {
                        if (attachment->mEffectArray[j].mEffectType == AttachEffect::Reanim) {
                            Reanimation *attachReanim = lawnApp->ReanimationTryToGet(attachment->mEffectArray[j].mEffectID);
                            if (attachReanim != nullptr) {
                                attachReanim->mFilterEffect = aFilterEffect;
                            }
                        }
                    }
                }
            }
        }
    }

    Reanimation *mPreviewReanim4 = gamepadControls->mGameObject.mApp->ReanimationTryToGet(gamepadControls->mPreviewReanimID4);
    if (mPreviewReanim4 == nullptr)
        return;

    if (cursorObject->mCursorType != CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN && gamepadControls->mGamepadState != 7)
        return;
    if (gamepadControls->mSelectedSeedIndex == -1)
        return;

    SeedPacket *seedPacket = &GamepadControls_GetSeedBank(gamepadControls)->mSeedPackets[gamepadControls->mSelectedSeedIndex];
    if (!seedPacket->mActive) {
        flagUpdateCanPlant = false;
        flagDrawGray = true;
    }
    if (gamepadControls->mBoard->CanPlantAt(theGridX, theGridY, mSeedType) != PlantingReason::PLANTING_OK) {
        flagUpdateCanPlant = false;
        flagDrawGray = true;
    }
    if (!gamepadControls->mBoard->HasConveyorBeltSeedBank(gamepadControls->mPlayerIndex2) && cursorObject->mCursorType != CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
        if (gamepadControls->mIsZombie && gamepadControls->mGameObject.mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
            if (!gamepadControls->mBoard->CanTakeDeathMoney(gamepadControls->mBoard->GetCurrentPlantCost(mSeedType, SeedType::SEED_NONE))) {
                flagUpdateCanPlant = false;
                flagDrawGray = true;
            }
        } else {
            if (!gamepadControls->mBoard->CanTakeSunMoney(gamepadControls->mBoard->GetCurrentPlantCost(mSeedType, SeedType::SEED_NONE), gamepadControls->mPlayerIndex2)) {
                flagUpdateCanPlant = false;
                flagDrawGray = true;
            }
        }
    }

    Sexy::Graphics newGraphics;
    Sexy_Graphics_Graphics2(&newGraphics, gamepadControls->mPreviewImage);
    Sexy_Graphics_ClearRect(&newGraphics, 0, 0, gamepadControls->mPreviewImage->mWidth, gamepadControls->mPreviewImage->mHeight);
    Sexy_Graphics_Translate(&newGraphics, 256, 256);
    if (flagUpdateCanPlant || flagUpdateChangeType)
        Reanimation_Update(mPreviewReanim4);
    if (flagDrawGray) {
        Sexy_Graphics_SetColorizeImages(&newGraphics, true);
        Sexy_Graphics_SetColor(&newGraphics, &gray);
    }
    Reanimation_Draw(mPreviewReanim4, &newGraphics);
    Reanimation_DrawRenderGroup(mPreviewReanim4, &newGraphics, 2);
    Reanimation_DrawRenderGroup(mPreviewReanim4, &newGraphics, 1);
    Reanimation_DrawRenderGroup(mPreviewReanim4, &newGraphics, 3);
    Sexy_Graphics_Delete2(&newGraphics);
}

void GamepadControls_DrawPreview(GamepadControls *gamepadControls, Sexy::Graphics *graphics) {
    // 修复排山倒海、砸罐子无尽、锤僵尸、种子雨不显示植物预览的问题。
    LawnApp *lawnApp = gamepadControls->mGameObject.mApp;
    Board *board = gamepadControls->mBoard;
    GameMode mGameMode = lawnApp->mGameMode;
    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_RAINING_SEEDS) { // 为种子雨添加种植预览
        CursorObject *cursorObject = gamepadControls->mPlayerIndex1 ? gamepadControls->mBoard->mCursorObject2 : gamepadControls->mBoard->mCursorObject1;
        if (cursorObject->mCursorType == CursorType::CURSOR_TYPE_PLANT_FROM_USABLE_COIN) {
            gamepadControls->mGamepadState = 7;
            old_GamepadControls_DrawPreview(gamepadControls, graphics);
            gamepadControls->mGamepadState = 1;
            return;
        }
    }

    if (LawnApp_IsWhackAZombieLevel(lawnApp) || LawnApp_IsScaryPotterLevel(lawnApp)) {
        if (gamepadControls->mGamepadState == 7) {
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls);
            SeedPacket *seedPacket = &seedBank->mSeedPackets[gamepadControls->mSelectedSeedIndex];
            gamepadControls->mSelectedSeedType = seedPacket->mPacketType == SeedType::SEED_IMITATER ? seedPacket->mImitaterType : seedPacket->mPacketType;
            old_GamepadControls_DrawPreview(gamepadControls, graphics);
            return;
        }
    }
    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_COLUMN) {
        int mGridX = board->PixelToGridXKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
        int mGridY = board->PixelToGridYKeepOnBoard(gamepadControls->mCursorPositionX, gamepadControls->mCursorPositionY);
        SeedType mSelectedSeedType = gamepadControls->mSelectedSeedType;
        if (mSelectedSeedType != SeedType::SEED_NONE) {
            Sexy_Graphics_SetColorizeImages(graphics, true);
            Color theColor = {255, 255, 255, 125};
            Sexy_Graphics_SetColor(graphics, &theColor);
            Sexy_Graphics_Translate(graphics, -256, -256);
            if (dynamicPreview) { // 修复动态预览时植物错位
                int thePixelY = gamepadControls->mBoard->GridToPixelY(mGridX, mGridY);
                for (int i = 0; i != 6; ++i) {
                    if (board->CanPlantAt(mGridX, i, mSelectedSeedType) == PlantingReason::PLANTING_OK) {
                        int theGridPixelY = gamepadControls->mBoard->GridToPixelY(mGridX, i);
                        Sexy_Graphics_DrawImage(graphics, gamepadControls->mPreviewImage, 0, theGridPixelY - thePixelY);
                    }
                }
            } else {
                for (int i = 0; i != 6; ++i) {
                    if (board->CanPlantAt(mGridX, i, mSelectedSeedType) == PlantingReason::PLANTING_OK) {
                        float offset = PlantDrawHeightOffset(board, 0, mSelectedSeedType, mGridX, i);
                        Sexy_Graphics_DrawImage(graphics, gamepadControls->mPreviewImage, 0, offset + (i - mGridY) * 85);
                    }
                }
            }
            Sexy_Graphics_Translate(graphics, 256, 256);
            Sexy_Graphics_SetColorizeImages(graphics, false);
        }
        return;
    }

    return old_GamepadControls_DrawPreview(gamepadControls, graphics);
}

void ZenGardenControls_Update(ZenGardenControls *a1, float a2) {
    old_ZenGardenControls_Update(a1, a2);
}
