#include "PvZ/Lawn/SeedChooserScreen.h"
#include "PvZ/Symbols.h"
#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/CutScene.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/SeedBank.h"

namespace {
constexpr int mSeedPacketWidth = 53;
constexpr int mSeedPacketHeight = 70;

Sexy::GameButton *mSeedChooserScreenMainMenuButton;
SeedChooserTouchState::SeedChooserTouchState mSeedChooserTouchState = SeedChooserTouchState::None;
} // namespace


void LawnApp_KillSeedChooserScreen(LawnApp *lawnApp) {
    SeedChooserScreen *seedChooserScreen = lawnApp->mSeedChooserScreen;
    if (seedChooserScreen != nullptr && lawnApp->mGameMode != GameMode::GAMEMODE_TWO_PLAYER_VS) {
        Sexy_Widget_RemoveWidget(seedChooserScreen, mSeedChooserScreenMainMenuButton);
        GameButton_Delete(mSeedChooserScreenMainMenuButton);
        mSeedChooserScreenMainMenuButton = nullptr;
    }
    old_LawnApp_KillSeedChooserScreen(lawnApp);
}

void SeedChooserScreen_RebuildHelpbar(SeedChooserScreen *seedChooserScreen) {
    // 拓宽Widget大小
    if (seedChooserScreen->mApp->mGameMode != GameMode::GAMEMODE_TWO_PLAYER_VS && !seedChooserScreen->mIsZombieChooser) {
        Sexy_Widget_Resize(seedChooserScreen, seedChooserScreen->mX, seedChooserScreen->mY, 800, 600); // 原本(472,521)，改为(800,600)，不然没办法点击模仿者按钮和底栏三按钮。
    } else {
        Sexy_Widget_Resize(seedChooserScreen, seedChooserScreen->mX, seedChooserScreen->mY, seedChooserScreen->mWidth, 600);
    }
    return old_SeedChooserScreen_RebuildHelpbar(seedChooserScreen);
}

void SeedChooserScreen_SeedChooserScreen(SeedChooserScreen *seedChooserScreen, bool isZombieChooser) {
    // 记录当前游戏状态，同时修复在没解锁商店图鉴时依然显示相应按钮的问题、对战选种子界面的按钮问题；
    // 还添加了生存模式保留上次选卡，添加坚果艺术关卡默认选择坚果，添加向日葵艺术关卡默认选择坚果、杨桃、萝卜伞
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    Board *board = lawnApp->mBoard;
    GameMode mGameMode = lawnApp->mGameMode;
    CutScene *mCutScene = board->mCutScene;
    if (CutScene_IsSurvivalRepick(mCutScene) && !LawnApp_IsCoopMode(lawnApp)) {
        GamepadControls *gamePad = board->mGamepadControls1;
        SeedBank *mSeedBank = GamepadControls_GetSeedBank(gamePad);
        int mNumPackets = mSeedBank->mNumPackets;
        SeedType *seedArray = (SeedType *)malloc(mNumPackets * sizeof(SeedType));
        SeedType imitaterType = SeedType::SEED_NONE;
        for (int i = 0; i < mNumPackets; i++) {
            SeedPacket seedPacket = mSeedBank->mSeedPackets[i];
            seedArray[i] = seedPacket.mPacketType;
            if (seedPacket.mPacketType == SeedType::SEED_IMITATER && imitaterType == SeedType::SEED_NONE) {
                imitaterType = seedPacket.mImitaterType;
            }
        }
        old_SeedChooserScreen_SeedChooserScreen(seedChooserScreen, isZombieChooser);
        // 实现无尽模式保留上次选卡。为什么不直接像WP版那样一一对应地选卡呢？因为玩家有可能通过爆炸坚果修改卡槽选中了多个相同类型的卡片或不在SeedChooser内的卡片，一一对应的话会有BUG
        int theValidChosenSeedNum = 0;
        for (int i = 0; i < mNumPackets; i++) {
            SeedType theSeed = seedArray[i];
            if (theSeed >= SeedType::NUM_SEEDS_IN_CHOOSER)
                continue;
            ChosenSeed *theChosenSeed = &(seedChooserScreen->mChosenSeeds[theSeed]);
            if (theChosenSeed->mSeedType == SeedType::SEED_IMITATER) {
                theChosenSeed->mImitaterType = imitaterType;
            }
            if (theChosenSeed->mSeedState == ChosenSeedState::SEED_IN_BANK)
                continue;
            SeedChooserScreen_GetSeedPositionInBank(seedChooserScreen, theValidChosenSeedNum, &theChosenSeed->mX, &theChosenSeed->mY, 0);
            theChosenSeed->mEndX = theChosenSeed->mX;
            theChosenSeed->mEndY = theChosenSeed->mY;
            theChosenSeed->mStartX = theChosenSeed->mX;
            theChosenSeed->mStartY = theChosenSeed->mY;
            theChosenSeed->mSeedState = ChosenSeedState::SEED_IN_BANK;
            theChosenSeed->mSeedIndexInBank = theValidChosenSeedNum;
            theValidChosenSeedNum++;
        }
        seedChooserScreen->mSeedsInBothBank = theValidChosenSeedNum;
        seedChooserScreen->mSeedsIn1PBank = theValidChosenSeedNum;
        if (theValidChosenSeedNum == mNumPackets) {
            SeedChooserScreen_EnableStartButton(seedChooserScreen, true);
        }
        free(seedArray);
    } else {
        old_SeedChooserScreen_SeedChooserScreen(seedChooserScreen, isZombieChooser);
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT) {
        ChosenSeed *theChosenSeed = &(seedChooserScreen->mChosenSeeds[SeedType::SEED_WALLNUT]);
        theChosenSeed->mX = Board_GetSeedPacketPositionX(board, 0, 0, 0);
        theChosenSeed->mY = 8;
        theChosenSeed->mEndX = theChosenSeed->mX;
        theChosenSeed->mEndY = theChosenSeed->mY;
        theChosenSeed->mStartX = theChosenSeed->mX;
        theChosenSeed->mStartY = theChosenSeed->mY;
        theChosenSeed->mSeedState = ChosenSeedState::SEED_IN_BANK;
        theChosenSeed->mSeedIndexInBank = 0;
        seedChooserScreen->mSeedsInBothBank += 1;
        seedChooserScreen->mSeedsIn1PBank += 1;
    } else if (mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER) {
        SeedType types[] = {SeedType::SEED_WALLNUT, SeedType::SEED_STARFRUIT, SeedType::SEED_UMBRELLA};
        for (int i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
            ChosenSeed *theChosenSeed = &(seedChooserScreen->mChosenSeeds[types[i]]);
            SeedChooserScreen_GetSeedPositionInBank(seedChooserScreen, i, &theChosenSeed->mX, &theChosenSeed->mY, 0);
            theChosenSeed->mEndX = theChosenSeed->mX;
            theChosenSeed->mEndY = theChosenSeed->mY;
            theChosenSeed->mStartX = theChosenSeed->mX;
            theChosenSeed->mStartY = theChosenSeed->mY;
            theChosenSeed->mSeedState = ChosenSeedState::SEED_IN_BANK;
            theChosenSeed->mSeedIndexInBank = i;
            seedChooserScreen->mSeedsInBothBank += 1;
            seedChooserScreen->mSeedsIn1PBank += 1;
        }
    }


    // int mViewLawnButton = *((uint32_t *) seedChooserScreen + 958);
    Sexy::GameButton *mStoreButton = seedChooserScreen->mStoreButton;
    Sexy::GameButton *mStartButton = seedChooserScreen->mStartButton;
    Sexy::GameButton *mAlmanacButton = seedChooserScreen->mAlmanacButton;

    if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) { // 去除对战中的冗余按钮
        if (mStoreButton != nullptr) {
            // mStoreButton.mDisabled = true;
            mStoreButton->mDisabled = true;
            // mStoreButton.mBtnNoDraw = true;
            mStoreButton->mBtnNoDraw = true;
        }
        if (mAlmanacButton != nullptr) {
            // mAlmanacButton.mDisabled = true;
            mAlmanacButton->mDisabled = true;
            // mAlmanacButton.mBtnNoDraw = true;
            mAlmanacButton->mBtnNoDraw = true;
        }
        if (isZombieChooser && mStartButton != nullptr) {
            // mStartButton.mDisabled = true;
            mStartButton->mDisabled = true;
            // mStartButton.mBtnNoDraw = true;
            mStartButton->mBtnNoDraw = true;
        }
    } else {
        if (mStoreButton != nullptr) {
            if (!LawnApp_CanShowStore(lawnApp)) { // 去除在未解锁商店时商店按钮
                // mStoreButton.mDisabled = true;
                mStoreButton->mDisabled = true;
                // mStoreButton.mBtnNoDraw = true;
                mStoreButton->mBtnNoDraw = true;
            }
        }
        if (mAlmanacButton != nullptr) {
            if (!LawnApp_CanShowAlmanac(lawnApp)) { // 去除在未解锁图鉴时的图鉴按钮
                // mAlmanacButton.mDisabled = true;
                mAlmanacButton->mDisabled = true;
                // mAlmanacButton.mBtnNoDraw = true;
                mAlmanacButton->mBtnNoDraw = true;
            }
        }
    }

    if (lawnApp->mGameMode != GameMode::GAMEMODE_TWO_PLAYER_VS && !seedChooserScreen->mIsZombieChooser) {
        int holder[1];
        TodStringTranslate(holder, "[MENU_BUTTON]");
        mSeedChooserScreenMainMenuButton = MakeButton(104, &seedChooserScreen->mButtonListener, seedChooserScreen, holder);
        GameButton_Resize(mSeedChooserScreenMainMenuButton, LawnApp_IsCoopMode(seedChooserScreen->mApp) ? 345 : 650, -3, 120, 80);
        Sexy_String_Delete(holder);
        Sexy_Widget_AddWidget(seedChooserScreen, mSeedChooserScreenMainMenuButton);
    }
}

void SeedChooserScreen_Update(SeedChooserScreen *seedChooserScreen) {
    // 记录当前1P选卡是否选满
    GameMode mGameMode = seedChooserScreen->mApp->mGameMode;
    if (mGameMode >= GameMode::GAMEMODE_TWO_PLAYER_COOP_DAY && mGameMode <= GameMode::GAMEMODE_TWO_PLAYER_COOP_ENDLESS) {
        m1PChoosingSeeds = seedChooserScreen->mSeedsIn1PBank < 4;
    }
    return old_SeedChooserScreen_Update(seedChooserScreen);
}

void SeedChooserScreen_EnableStartButton(SeedChooserScreen *seedChooserScreen, int isEnabled) {
    // 双人键盘模式下结盟选满后直接开始
    if (isEnabled && LawnApp_IsCoopMode(seedChooserScreen->mApp) && isKeyboardTwoPlayerMode) {
        old_SeedChooserScreen_EnableStartButton(seedChooserScreen, isEnabled);
        SeedChooserScreen_OnStartButton(seedChooserScreen);
        seedChooserScreen->mBoard->mSeedBank2->mSeedPackets[3].mPacketType = seedChooserScreen->mSeedType2;
        seedChooserScreen->mBoard->mSeedBank2->mSeedPackets[3].mImitaterType = SeedType::SEED_NONE;
        return;
    }
    return old_SeedChooserScreen_EnableStartButton(seedChooserScreen, isEnabled);
}

void SeedChooserScreen_OnStartButton(SeedChooserScreen *seedChooserScreen) {
    if (seedChooserScreen->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        // 如果是对战模式，则直接关闭种子选择界面。用于修复对战模式选卡完毕后点击开始按钮导致的闪退
        return SeedChooserScreen_CloseSeedChooser(seedChooserScreen);
    }

    return old_SeedChooserScreen_OnStartButton(seedChooserScreen);
}

bool SeedChooserScreen_SeedNotAllowedToPick(SeedChooserScreen *seedChooserScreen, SeedType theSeedType) {
    // 解除更多对战场地中的某些植物不能选取的问题，如泳池对战不能选荷叶，屋顶对战不能选花盆
    if (seedChooserScreen->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS && VSBackGround > 1) {
        // 直接在其他对战场景解锁全部植物即可
        return false;
    }
    // 此处添加一些逻辑，就可以自定义Ban卡
    // 此处Ban卡仅对植物方生效，theSeedType取值范围是0~39。
    return old_SeedChooserScreen_SeedNotAllowedToPick(seedChooserScreen, theSeedType);
}

int SeedChooserScreen_GetZombieSeedType(SeedChooserScreen *a, int a2) {
    int result = a2 + 61;
    return result > 85 ? -1 : result;
    //    return result > 90 ? -1 : result;
}

int SeedChooserScreen_GetZombieType(SeedChooserScreen *a, int a2) {
    return a2 > 33 ? -1 : a2;
}

void SeedChooserScreen_ClickedSeedInChooser(SeedChooserScreen *a1, ChosenSeed *a2, int a3) {
    // 实现1P结盟选卡选满后自动转换为2P选卡
    if (LawnApp_IsCoopMode(a1->mApp))
        a3 = !m1PChoosingSeeds;
    old_SeedChooserScreen_ClickedSeedInChooser(a1, a2, a3);
}

void SeedChooserScreen_CrazyDavePickSeeds(SeedChooserScreen *a) {
    if (daveNoPickSeeds) {
        return;
    }
    return old_SeedChooserScreen_CrazyDavePickSeeds(a);
}

void SeedChooserScreen_ClickedSeedInBank(SeedChooserScreen *seedChooserScreen, ChosenSeed *theChosenSeed, unsigned int playerIndex) {
    // 解决结盟1P选够4个种子之后，无法点击种子栏内的已选种子来退选的问题
    if (LawnApp_IsCoopMode(seedChooserScreen->mApp)) {
        playerIndex = theChosenSeed->mChosenPlayerIndex;
    }
    old_SeedChooserScreen_ClickedSeedInBank(seedChooserScreen, theChosenSeed, playerIndex);
}

void SeedChooserScreen_GameButtonDown(SeedChooserScreen *seedChooserScreen, int buttonCode, unsigned int playerIndex) {
    // 修复结盟2P无法选择模仿者
    LawnApp *lawnApp = seedChooserScreen->mApp;
    if (LawnApp_IsCoopMode(lawnApp) && buttonCode == 6) {
        if (seedChooserScreen->mChooseState == SeedChooserState::CHOOSE_VIEW_LAWN) {
            return old_SeedChooserScreen_GameButtonDown(seedChooserScreen, buttonCode, playerIndex);
        }

        if (lawnApp->mTwoPlayerState == -1 && seedChooserScreen->mPlayerIndex != playerIndex)
            return;

        SeedType seedType = playerIndex ? seedChooserScreen->mSeedType2 : seedChooserScreen->mSeedType1;
        int mSeedsInBank = seedChooserScreen->mSeedsInBothBank;
        // 此处将判定条件改为选满8个种子时无法选取模仿者。原版游戏中此处是选满4个则无法选取，导致模仿者选取出现问题。
        if (seedType == SeedType::SEED_IMITATER && mSeedsInBank < 8) {
            if (seedChooserScreen->mChosenSeeds[SeedType::SEED_IMITATER].mSeedState != ChosenSeedState::SEED_IN_BANK) {
                // 先将已选种子数改为0，然后执行旧函数，这样模仿者选取界面就被打开了。
                seedChooserScreen->mSeedsInBothBank = 0;
                old_SeedChooserScreen_GameButtonDown(seedChooserScreen, buttonCode, playerIndex);
                // 然后再恢复已选种子数即可。
                seedChooserScreen->mSeedsInBothBank = mSeedsInBank;
                return;
            }
        }
    }
    return old_SeedChooserScreen_GameButtonDown(seedChooserScreen, buttonCode, playerIndex);
}

void SeedChooserScreen_DrawPacket(SeedChooserScreen *seedChooserScreen,
                                  Sexy::Graphics *graphics,
                                  int x,
                                  int y,
                                  SeedType theSeedType,
                                  SeedType theImitaterType,
                                  float coolDownPercent,
                                  int grayness,
                                  Color *theColor,
                                  bool drawCostText,
                                  bool a11) {
    // 修复SeedChooser里的卡片亮度不正确。
    // 已选的卡片grayness为55，不推荐的卡片grayness为115。theColor则固定为{255,255,255,255}。

    // int theConvertedGrayness = ((theColor->mRed + theColor->mGreen + theColor->mBlue) / 3 + grayness) / 2;
    // 此算法用于在对战模式将非选卡的一方的卡片整体变暗。但这种算法下，55亮度会变成155亮度，115亮度会变成185亮度，严重影响非对战模式的选卡体验。所以需要修复。

    int theConvertedGrayness = (seedChooserScreen->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) ? ((theColor->mRed + theColor->mGreen + theColor->mBlue) / 3 + grayness) / 2 : grayness;
    DrawSeedPacket(graphics, x, y, theSeedType, theImitaterType, coolDownPercent, theConvertedGrayness, drawCostText, false, seedChooserScreen->mIsZombieChooser, a11);
}

void SeedChooserScreen::ButtonPress(int theId) {
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    lawnApp->mSeedChooserScreen->mFocusedChildWidget = nullptr; // 修复点击菜单后无法按键选取植物卡片
}

void SeedChooserScreen_ButtonDepress(SeedChooserScreen *seedChooserScreen, int id) {

    if (seedChooserScreen->mSeedsInFlight > 0 || seedChooserScreen->mChooseState == SeedChooserState::CHOOSE_VIEW_LAWN || !seedChooserScreen->mMouseVisible) {
        return;
    }
    if (id == 104) {
        LawnApp_PlaySample(seedChooserScreen->mApp, *Sexy_SOUND_PAUSE_Addr);
        LawnApp_DoNewOptions(seedChooserScreen->mApp, false, 0);
        return;
    }
    return old_SeedChooserScreen_ButtonDepress(seedChooserScreen, id);
}

void SeedChooserScreen_GetSeedPositionInBank(SeedChooserScreen *seedChooserScreen, int theIndex, int *x, int *y, int playerIndex) {
    // 修复对战选卡时的错位
    if (seedChooserScreen->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        SeedBank *mSeedBank1 = seedChooserScreen->mSeedBank1;
        int SeedPacketPositionX = Board_GetSeedPacketPositionX(seedChooserScreen->mBoard, theIndex, 0, seedChooserScreen->mIsZombieChooser);
        *x = mSeedBank1->mX + SeedPacketPositionX - seedChooserScreen->mX;
        *y = mSeedBank1->mY + 8 - seedChooserScreen->mY;
        return;
    }
    return old_SeedChooserScreen_GetSeedPositionInBank(seedChooserScreen, theIndex, x, y, playerIndex);
}

void SeedChooserScreen_ShowToolTip(SeedChooserScreen *seedChooserScreen, unsigned int playerIndex) {
    old_SeedChooserScreen_ShowToolTip(seedChooserScreen, playerIndex);
    if (seedChooserScreen->mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS && seedChooserScreen->mIsZombieChooser) {
        SeedType seedType = SeedChooserScreen_SeedHitTest(seedChooserScreen, seedChooserScreen->mCursorPositionX2, seedChooserScreen->mCursorPositionY2);
        if (seedChooserScreen->mChosenSeeds[seedType - SeedType::SEED_ZOMBIE_TOMBSTONE].mSeedState == ChosenSeedState::SEED_IN_BANK
            && seedChooserScreen->mChosenSeeds[seedType - SeedType::SEED_ZOMBIE_TOMBSTONE].mCrazyDavePicked) {
            int holder[1];
            TodStringTranslate(holder, "[ZOMBIE_BOSS_WANTS]");
            ToolTipWidget_SetWarningText(seedChooserScreen->mToolTipWidget2, holder);
            Sexy_String_Delete(holder);
        }
    }
}

SeedType SeedChooserScreen_GetZombieIndexBySeedType(SeedType seedType) {
    return seedType - 61 < 0 ? SeedType::SEED_NONE : (SeedType)(seedType - 61);
}

void SeedChooserScreen::MouseMove(int x, int y) {
    SeedType seedType = SeedChooserScreen_SeedHitTest(this, x, y);
    // 该函数探测不到模仿者位置
    if (seedType == SeedType::SEED_NONE) {
        return;
    }
    if (mIsZombieChooser) {
        SeedType zombieSeedType = SeedChooserScreen_GetZombieIndexBySeedType(seedType);
        SeedChooserScreen_GetSeedPositionInChooser(this, zombieSeedType, &mCursorPositionX2, &mCursorPositionY2);
        mSeedType2 = zombieSeedType;
    } else if (m1PChoosingSeeds) {
        if (mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS && seedType > SeedType::SEED_MELONPULT)
            return;
        SeedChooserScreen_GetSeedPositionInChooser(this, seedType, &mCursorPositionX1, &mCursorPositionY1);
        mSeedType1 = seedType;
    } else {
        SeedChooserScreen_GetSeedPositionInChooser(this, seedType, &mCursorPositionX2, &mCursorPositionY2);
        mSeedType2 = seedType;
    }
}

void SeedChooserScreen::MouseDown(int x, int y, int theClickCount) {
    GameMode mGameMode = mApp->mGameMode;

    m1PChoosingSeeds = !LawnApp_IsCoopMode(mApp) || mSeedsIn1PBank < 4;

    bool mViewLawnButtonDisabled = mViewLawnButton == nullptr || !CutScene_IsSurvivalRepick(mBoard->mCutScene);
    bool mStoreButtonDisabled = mStoreButton == nullptr || mStoreButton->mDisabled;
    bool mStartButtonDisabled = mStartButton == nullptr || mStartButton->mDisabled;
    bool mAlmanacButtonDisabled = mAlmanacButton == nullptr || mAlmanacButton->mDisabled;

    if (!mViewLawnButtonDisabled) { // !mDisabled
        TRect mViewLawnButtonRect = {mViewLawnButton->mX, mViewLawnButton->mY, mViewLawnButton->mWidth, 50};
        //        LOGD("mStoreButtonRect:%d %d %d %d",mStoreButtonRect[0],mStoreButtonRect[1],mStoreButtonRect[2],mStoreButtonRect[3]);
        if (TRect_Contains(&mViewLawnButtonRect, x, y)) {
            LawnApp_PlaySample(mApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::ViewLawnButton;
            //            SeedChooserScreen_GameButtonDown(seedChooserScreen, 8, 0);
            return;
        }
    }

    if (!mStoreButtonDisabled) { // !mDisabled
        TRect mStoreButtonRect = {mStoreButton->mX, mStoreButton->mY, mStoreButton->mWidth, 50};
        //        LOGD("mStoreButtonRect:%d %d %d %d",mStoreButtonRect[0],mStoreButtonRect[1],mStoreButtonRect[2],mStoreButtonRect[3]);
        if (TRect_Contains(&mStoreButtonRect, x, y)) {
            LawnApp_PlaySample(mApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::StoreButton;
            //            SeedChooserScreen_GameButtonDown(seedChooserScreen, 8, 0);
            return;
        }
    }

    if (!mStartButtonDisabled) { // !mDisabled
        TRect mStartButtonRect = {mStartButton->mX, mStartButton->mY, mStartButton->mWidth, 50};
        if (TRect_Contains(&mStartButtonRect, x, y)) {
            LawnApp_PlaySample(mApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::StartButton;

            //            SeedChooserScreen_OnStartButton(seedChooserScreen);
            return;
        }
    }

    if (!mAlmanacButtonDisabled) { // !mDisabled
        TRect mAlmanacButtonRect = {mAlmanacButton->mX, mAlmanacButton->mY, mAlmanacButton->mWidth, 50};
        if (TRect_Contains(&mAlmanacButtonRect, x, y)) {
            LawnApp_PlaySample(mApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::AlmanacButton;

            //            SeedChooserScreen_GameButtonDown(seedChooserScreen, 9, 0);
            return;
        }
    }

    if (SeedChooserScreen_HasPacket(this, SeedType::SEED_IMITATER, 0) && mGameMode != GameMode::GAMEMODE_TWO_PLAYER_VS && !mIsZombieChooser) {
        int mImitaterPositionX = 0;
        int mImitaterPositionY = 0;
        SeedChooserScreen_GetSeedPositionInChooser(this, SeedType::SEED_IMITATER, &mImitaterPositionX, &mImitaterPositionY);
        TRect mImitaterPositionRect = {mImitaterPositionX, mImitaterPositionY, mSeedPacketWidth, mSeedPacketHeight};
        if (TRect_Contains(&mImitaterPositionRect, x, y)) {
            if (m1PChoosingSeeds) {
                mCursorPositionX1 = mImitaterPositionX;
                mCursorPositionY1 = mImitaterPositionY;
                mSeedType1 = SeedType::SEED_IMITATER;
            } else {
                mCursorPositionX2 = mImitaterPositionX;
                mCursorPositionY2 = mImitaterPositionY;
                mSeedType2 = SeedType::SEED_IMITATER;
            }
            SeedChooserScreen_GameButtonDown(this, 6, !m1PChoosingSeeds);
            return;
        }
    }
    SeedType aSeedType = SeedChooserScreen_SeedHitTest(this, x, y);
    // 该函数探测不到模仿者位置

    if (aSeedType == SeedType::SEED_NONE) {
        return;
    }

    if (!mIsZombieChooser && (mChosenSeeds[aSeedType].mSeedState == ChosenSeedState::SEED_FLYING_TO_BANK
            || mChosenSeeds[aSeedType].mSeedState == ChosenSeedState::SEED_FLYING_TO_CHOOSER)) {
        return;
    }

    if (mIsZombieChooser) {
        SeedType zombieSeedType = SeedChooserScreen_GetZombieIndexBySeedType(aSeedType);
        SeedChooserScreen_GetSeedPositionInChooser(this, zombieSeedType, &mCursorPositionX2, &mCursorPositionY2);
        mSeedType2 = zombieSeedType;
    } else if (m1PChoosingSeeds) {
        if (mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS && aSeedType > SeedType::SEED_MELONPULT)
            return;
        SeedChooserScreen_GetSeedPositionInChooser(this, aSeedType, &mCursorPositionX1, &mCursorPositionY1);
        mSeedType1 = aSeedType;
    } else {
        SeedChooserScreen_GetSeedPositionInChooser(this, aSeedType, &mCursorPositionX2, &mCursorPositionY2);
        mSeedType2 = aSeedType;
    }
    mSeedChooserTouchState = SeedChooserTouchState::SeedChooser;
}

void SeedChooserScreen::MouseDrag(int x, int y) {
    if (mSeedChooserTouchState == SeedChooserTouchState::SeedChooser) {
        SeedType aSeedType = SeedChooserScreen_SeedHitTest(this, x, y);
        // 该函数探测不到模仿者位置
        if (aSeedType == SeedType::SEED_NONE) {
            return;
        }
        if (mIsZombieChooser) {
            SeedType zombieSeedType = SeedChooserScreen_GetZombieIndexBySeedType(aSeedType);
            SeedChooserScreen_GetSeedPositionInChooser(this, zombieSeedType, &mCursorPositionX2, &mCursorPositionY2);
            mSeedType2 = zombieSeedType;
        } else if (m1PChoosingSeeds) {
            if (mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS && aSeedType > SeedType::SEED_MELONPULT)
                return;
            SeedChooserScreen_GetSeedPositionInChooser(this, aSeedType, &mCursorPositionX1, &mCursorPositionY1);
            mSeedType1 = aSeedType;
        } else {
            SeedChooserScreen_GetSeedPositionInChooser(this, aSeedType, &mCursorPositionX2, &mCursorPositionY2);
            mSeedType2 = aSeedType;
        }
    }
}

void SeedChooserScreen::MouseUp(int x, int y) {
    switch (mSeedChooserTouchState) {
        case SeedChooserTouchState::ViewLawnButton:
            SeedChooserScreen_ButtonDepress(this, 102);
            break;
        case SeedChooserTouchState::SeedChooser:
            if (mIsZombieChooser) {
                SeedChooserScreen_GameButtonDown(this, 6, 1);
            } else if (m1PChoosingSeeds) {
                SeedChooserScreen_GameButtonDown(this, 6, 0);
            } else {
                SeedChooserScreen_GameButtonDown(this, 6, 1);
            }
            break;
        case SeedChooserTouchState::StoreButton:
            SeedChooserScreen_ButtonDepress(this, 105);
            break;
        case SeedChooserTouchState::StartButton:
            SeedChooserScreen_ButtonDepress(this, 100);
            break;
        case SeedChooserTouchState::AlmanacButton:
            SeedChooserScreen_ButtonDepress(this, 103);
            break;
        default:
            break;
    }
    mSeedChooserTouchState = SeedChooserTouchState::None;
}
