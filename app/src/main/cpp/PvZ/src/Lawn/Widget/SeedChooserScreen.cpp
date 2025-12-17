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

#include "PvZ/Lawn/Widget/SeedChooserScreen.h"
#include "Homura/Logger.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board/Board.h"
#include "PvZ/Lawn/Board/CutScene.h"
#include "PvZ/Lawn/Board/SeedBank.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Widget/GameButton.h"
#include "PvZ/Lawn/Widget/SeedChooserPage.h"
#include "PvZ/Lawn/Widget/VSSetupMenu.h"
#include "PvZ/Lawn/Widget/WaitForSecondPlayerDialog.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/GamepadApp.h"
#include "PvZ/Symbols.h"
#include "PvZ/TodLib/Common/TodStringFile.h"
#include <unistd.h>

using namespace Sexy;

namespace {
GameButton *gSeedChooserScreenMainMenuButton;
SeedChooserTouchState gSeedChooserTouchState = SeedChooserTouchState::SEEDCHOOSER_TOUCHSTATE_NONE;
} // namespace


SeedChooserScreen::SeedChooserScreen(bool theIsZombieChooser) {
    _constructor(theIsZombieChooser);
}


void SeedChooserScreen::_constructor(bool theIsZombieChooser) {
    // 记录当前游戏状态，同时修复在没解锁商店图鉴时依然显示相应按钮的问题、对战选种子界面的按钮问题；
    // 还添加了生存模式保留上次选卡，添加坚果艺术关卡默认选择坚果，添加向日葵艺术关卡默认选择坚果、杨桃、萝卜伞
    mApp = (LawnApp *)*Sexy_gSexyAppBase_Addr;
    mBoard = mApp->mBoard;
    GameMode mGameMode = mApp->mGameMode;
    if (mBoard->mCutScene->IsSurvivalRepick() && !mApp->IsCoopMode()) {
        GamepadControls *gamePad = mBoard->mGamepadControls1;
        SeedBank *mSeedBank = gamePad->GetSeedBank();
        int mNumPackets = mSeedBank->mNumPackets;
        std::vector<SeedType> aSeedArray(mNumPackets);
        SeedType aImitaterType = SeedType::SEED_NONE;
        for (int i = 0; i < mNumPackets; i++) {
            SeedPacket aSeedPacket = mSeedBank->mSeedPackets[i];
            aSeedArray[i] = aSeedPacket.mPacketType;
            if (aSeedPacket.mPacketType == SeedType::SEED_IMITATER && aImitaterType == SeedType::SEED_NONE) {
                aImitaterType = aSeedPacket.mImitaterType;
            }
        }

        old_SeedChooserScreen_SeedChooserScreen(this, theIsZombieChooser);

        // 实现无尽模式保留上次选卡。为什么不直接像WP版那样一一对应地选卡呢？因为玩家有可能通过爆炸坚果修改卡槽选中了多个相同类型的卡片或不在SeedChooser内的卡片，一一对应的话会有BUG
        int theValidChosenSeedNum = 0;
        for (int i = 0; i < mNumPackets; i++) {
            SeedType theSeed = aSeedArray[i];
            if (theSeed >= SeedType::NUM_SEEDS_IN_CHOOSER)
                continue;

            ChosenSeed *theChosenSeed = &(mChosenSeeds[theSeed]);
            if (theChosenSeed->mSeedType == SeedType::SEED_IMITATER) {
                theChosenSeed->mImitaterType = aImitaterType;
            }

            if (theChosenSeed->mSeedState == ChosenSeedState::SEED_IN_BANK)
                continue;

            GetSeedPositionInBank(theValidChosenSeedNum, theChosenSeed->mX, theChosenSeed->mY, 0);
            theChosenSeed->mEndX = theChosenSeed->mX;
            theChosenSeed->mEndY = theChosenSeed->mY;
            theChosenSeed->mStartX = theChosenSeed->mX;
            theChosenSeed->mStartY = theChosenSeed->mY;
            theChosenSeed->mSeedState = ChosenSeedState::SEED_IN_BANK;
            theChosenSeed->mSeedIndexInBank = theValidChosenSeedNum;
            theValidChosenSeedNum++;
        }

        mSeedsInBothBank = theValidChosenSeedNum;
        mSeedsIn1PBank = theValidChosenSeedNum;
        if (theValidChosenSeedNum == mNumPackets) {
            EnableStartButton(true);
        }

    } else {
        old_SeedChooserScreen_SeedChooserScreen(this, theIsZombieChooser);
    }

    if (mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT) {
        ChosenSeed *theChosenSeed = &(mChosenSeeds[SeedType::SEED_WALLNUT]);
        theChosenSeed->mX = mBoard->GetSeedPacketPositionX(0, 0, 0);
        theChosenSeed->mY = 8;
        theChosenSeed->mEndX = theChosenSeed->mX;
        theChosenSeed->mEndY = theChosenSeed->mY;
        theChosenSeed->mStartX = theChosenSeed->mX;
        theChosenSeed->mStartY = theChosenSeed->mY;
        theChosenSeed->mSeedState = ChosenSeedState::SEED_IN_BANK;
        theChosenSeed->mSeedIndexInBank = 0;
        mSeedsInBothBank += 1;
        mSeedsIn1PBank += 1;
    } else if (mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER) {
        SeedType types[] = {SeedType::SEED_WALLNUT, SeedType::SEED_STARFRUIT, SeedType::SEED_UMBRELLA};
        for (int i = 0; i < std::size(types); ++i) {
            ChosenSeed *theChosenSeed = &(mChosenSeeds[types[i]]);
            GetSeedPositionInBank(i, theChosenSeed->mX, theChosenSeed->mY, 0);
            theChosenSeed->mEndX = theChosenSeed->mX;
            theChosenSeed->mEndY = theChosenSeed->mY;
            theChosenSeed->mStartX = theChosenSeed->mX;
            theChosenSeed->mStartY = theChosenSeed->mY;
            theChosenSeed->mSeedState = ChosenSeedState::SEED_IN_BANK;
            theChosenSeed->mSeedIndexInBank = i;
            mSeedsInBothBank += 1;
            mSeedsIn1PBank += 1;
        }
    }

    if (mApp->IsVSMode()) {
        // 去除对战中的冗余按钮
        if (mStoreButton) {
            mStoreButton->mDisabled = true;
            mStoreButton->mBtnNoDraw = true;
        }
        if (mAlmanacButton) {
            mAlmanacButton->mDisabled = true;
            mAlmanacButton->mBtnNoDraw = true;
        }
        if (mStartButton) { // 此处仿照PS3版处理，同时去除双方的开始按钮
            mStartButton->mDisabled = true;
            mStartButton->mBtnNoDraw = true;
        }

        if (gMoreSeedType) {
            gPlantChooserPage = new SeedChooserPage();
            gZombieChooserPage = new SeedChooserPage();
            gZombieChooserPage->mIsZombie = true;
            GameButton *aNextPlantPageButton = MakeButton(SeedChooserPage::SeedChooserPage_NextPlantPage, &mButtonListener, this, "下一页");
            GameButton *aNextZombiePageButton = MakeButton(SeedChooserPage::SeedChooserPage_NextZombiePage, &mButtonListener, this, "下一页");
            gPlantChooserPage->mNextPageButton = aNextPlantPageButton;
            gZombieChooserPage->mNextPageButton = aNextZombiePageButton;
            if (!theIsZombieChooser) {
                aNextPlantPageButton->Resize(-120, 550, 120, 80);
                aNextZombiePageButton->Resize(780, 550, 120, 80);
                //                AddWidget(aNextPlantPageButton);
                AddWidget(aNextZombiePageButton);
            }
        }
    } else {
        if (mStoreButton) {
            if (!mApp->CanShowStore()) { // 去除在未解锁商店时商店按钮
                mStoreButton->mDisabled = true;
                mStoreButton->mBtnNoDraw = true;
            }
        }
        if (mAlmanacButton) {
            if (!mApp->CanShowAlmanac()) { // 去除在未解锁图鉴时的图鉴按钮
                mAlmanacButton->mDisabled = true;
                mAlmanacButton->mBtnNoDraw = true;
            }
        }

        if (gMoreSeedType) {
            gPlantChooserPage = new SeedChooserPage();
            GameButton *aNextPlantPageButton = MakeButton(SeedChooserPage::SeedChooserPage_NextPlantPage, &mButtonListener, this, "下一页");
            gPlantChooserPage->mNextPageButton = aNextPlantPageButton;
            aNextPlantPageButton->Resize(-120, 550, 120, 80);
            //            AddWidget(aNextPlantPageButton);
        }
    }

    //    if (gMoreSeedType) {
    //        memset(gNewChosenSeeds, 0, sizeof(gNewChosenSeeds));
    //        for (SeedType aSeedType = SEED_IMP_PEAR; aSeedType < NUM_NEW_SEED_TYPES; aSeedType = (SeedType)(aSeedType + 1)) {
    //            ChosenSeed &aChosenSeed = gNewChosenSeeds[aSeedType];
    //            aChosenSeed.mSeedType = aSeedType;
    //            GetSeedPositionInChooser(aSeedType, aChosenSeed.mX, aChosenSeed.mY);
    //            aChosenSeed.mTimeStartMotion = 0;
    //            aChosenSeed.mTimeEndMotion = 0;
    //            aChosenSeed.mStartX = aChosenSeed.mX;
    //            aChosenSeed.mStartY = aChosenSeed.mY;
    //            aChosenSeed.mEndX = aChosenSeed.mX;
    //            aChosenSeed.mEndY = aChosenSeed.mY;
    //            aChosenSeed.mSeedState = SEED_IN_CHOOSER;
    //            aChosenSeed.mSeedIndexInBank = 0;
    //            aChosenSeed.mRefreshCounter = 0;
    //            aChosenSeed.mRefreshing = false;
    //            aChosenSeed.mImitaterType = SEED_NONE;
    //            aChosenSeed.mCrazyDavePicked = false;
    //        }
    //    }

    if (mApp->mGameMode != GameMode::GAMEMODE_MP_VS && !mIsZombieChooser) {
        pvzstl::string str = TodStringTranslate("[MENU_BUTTON]");
        gSeedChooserScreenMainMenuButton = MakeButton(104, &mButtonListener, this, str);
        gSeedChooserScreenMainMenuButton->Resize(mApp->IsCoopMode() ? 345 : 650, -3, 120, 80);
        AddWidget(gSeedChooserScreenMainMenuButton);
    }
}


void LawnApp::KillSeedChooserScreen() {
    SeedChooserScreen *seedChooserScreen = mSeedChooserScreen;
    if (seedChooserScreen != nullptr && mGameMode != GameMode::GAMEMODE_MP_VS) {
        seedChooserScreen->RemoveWidget(gSeedChooserScreenMainMenuButton);
        gSeedChooserScreenMainMenuButton->~GameButton();
        ;
        gSeedChooserScreenMainMenuButton = nullptr;
    }

    old_LawnApp_KillSeedChooserScreen(this);
}

void SeedChooserScreen::RebuildHelpbar() {
    // 拓宽Widget大小
    if (mApp->mGameMode != GameMode::GAMEMODE_MP_VS && !mIsZombieChooser) {
        Resize(mX, mY, 800, 600); // 原本(472,521)，改为(800,600)，不然没办法点击模仿者按钮和底栏三按钮。
    } else {
        Resize(mX, mY, mWidth, 600);
    }

    old_SeedChooserScreen_RebuildHelpbar(this);
}


void SeedChooserScreen::Update() {
    // 记录当前1P选卡是否选满
    if (mApp->IsCoopMode()) {
        m1PChoosingSeeds = mSeedsIn1PBank < 4;
    }

    // 调用基类更新
    this->Widget::Update();

    // 增加选择器年龄
    ++mSeedChooserAge;

    // 检查是否可以拾取种子
    bool canPickNow = CanPickNow();
    int counterValue = 0;
    if (!canPickNow) {
        counterValue = unkCounter + 1;
    }

    // 更新角度值
    float *anglePtr = &unkF;
    float currentAngle = unkF;
    unkCounter = counterValue;

    // 处理角度循环
    if ((currentAngle + 0.01f) <= 6.2832f) {
        *anglePtr = currentAngle + 0.01f;
    } else {
        counterValue = 0;
    }

    if ((currentAngle + 0.01f) > 6.2832f) {
        *(int *)anglePtr = counterValue;
    }

    // 更新工具提示组件
    mToolTip1->Update();
    mToolTip2->Update();

    // 处理所有种子的状态
    for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = SeedType(aSeedType + 1)) {
        if (HasPacket(aSeedType, mIsZombieChooser)) {
            ChosenSeed &aChosenSeed = mChosenSeeds[aSeedType];
            if (aChosenSeed.mSeedState == SEED_FLYING_TO_BANK || aChosenSeed.mSeedState == SEED_FLYING_TO_CHOOSER) {
                int aTimeStart = aChosenSeed.mTimeStartMotion;
                int aTimeEnd = aChosenSeed.mTimeEndMotion;
                aChosenSeed.mX = TodAnimateCurve(aTimeStart, aTimeEnd, mSeedChooserAge, aChosenSeed.mStartX, aChosenSeed.mEndX, CURVE_EASE_IN_OUT);
                aChosenSeed.mY = TodAnimateCurve(aTimeStart, aTimeEnd, mSeedChooserAge, aChosenSeed.mStartY, aChosenSeed.mEndY, CURVE_EASE_IN_OUT);
                if (mSeedChooserAge >= aChosenSeed.mTimeEndMotion) {
                    LandFlyingSeed(aChosenSeed);
                }
            }
        }
    }

    // 处理玩家索引和工具提示
    int aPlayerIndex = mApp->GamepadToPlayerIndex(mPlayerIndex);
    ShowToolTip(aPlayerIndex);

    // 合作模式下的额外工具提示
    if (mApp->IsCoopMode() || (mApp->IsAdventureMode() && mApp->mTwoPlayerState != -1)) {
        ShowToolTip(aPlayerIndex == 0);
    }

    // 更新模仿者按钮
    mImitaterButton->Update();

    // 处理游戏手柄相关逻辑
    if (unkMems3[3]) {
        if (reinterpret_cast<GamepadApp *>(mApp)->HasGamepad() || (mApp->mGamePad1IsOn && mApp->mGamePad2IsOn)) {
            int v16 = unkMems3[3];
            *(bool *)(v16 + 121) = false;
            *(bool *)(v16 + 120) = false;
            unkMems3[3] = 0;
        }
    }

    // 更新未命名内存数组中的对象
    int startPtr = unkMems3[0];
    int count = (unkMems3[1] - startPtr) >> 2;

    if (count > 0) {
        for (unsigned int i = 0; i < count; i++) {
            int objectPtr = *(int *)(startPtr + 4 * i);
            // 调用对象的更新方法
            (*(void (**)(int))(*(int *)objectPtr + 124))(objectPtr);
        }
    }

    // 更新草坪视图并调用虚函数
    UpdateViewLawn();
    MarkDirty();
}


void SeedChooserScreen::EnableStartButton(int theIsEnabled) {
    // 双人键盘模式下结盟选满后直接开始
    if (theIsEnabled && mApp->IsCoopMode() && isKeyboardTwoPlayerMode) {
        old_SeedChooserScreen_EnableStartButton(this, theIsEnabled);
        OnStartButton();
        mBoard->mSeedBank2->mSeedPackets[3].mPacketType = mSeedType2;
        mBoard->mSeedBank2->mSeedPackets[3].mImitaterType = SeedType::SEED_NONE;
        return;
    }

    old_SeedChooserScreen_EnableStartButton(this, theIsEnabled);
}

void SeedChooserScreen::OnStartButton() {
    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
        // 如果是对战模式，则直接关闭种子选择界面。用于修复对战模式选卡完毕后点击开始按钮导致的闪退
        CloseSeedChooser();
        return;
    }

    old_SeedChooserScreen_OnStartButton(this);
}

bool SeedChooserScreen::SeedNotAllowedToPick(SeedType theSeedType) {
    // 解除更多对战场地中的某些植物不能选取的问题，如泳池对战不能选荷叶，屋顶对战不能选花盆
    if (mApp->IsVSMode()) {
        if (theSeedType == gVSSetupWidget->mBannedSeed[theSeedType].mSeedType) {
            return true;
        }
        if (gVSSetupWidget->mBanMode && theSeedType == SeedType::SEED_INSTANT_COFFEE) {
            return true;
        }
        if (mBoard->StageHasPool()) {
            if (theSeedType == SeedType::SEED_LILYPAD || theSeedType == SeedType::SEED_TANGLEKELP || theSeedType == SeedType::SEED_SEASHROOM) {
                return false;
            }
            if (mBoard->StageIsNight() && theSeedType == SeedType::SEED_PLANTERN) {
                return false;
            }
        } else {
            if (theSeedType == SeedType::SEED_ZOMBIE_DUCKY_TUBE || theSeedType == SeedType::SEED_ZOMBIE_SNORKEL || theSeedType == SeedType::SEED_ZOMBIE_DOLPHIN_RIDER) {
                return true;
            }
        }
        if (mBoard->StageHasRoof() && theSeedType == SeedType::SEED_FLOWERPOT) {
            return false;
        }
        if (gMoreSeedType && theSeedType == SeedType::SEED_BLOVER) {
            return false;
        }
    }

    return old_SeedChooserScreen_SeedNotAllowedToPick(this, theSeedType);
}

SeedType SeedChooserScreen::GetZombieSeedType(SeedType theSeedType) {
    int aSeedType = theSeedType + SEED_ZOMBIE_GRAVESTONE;
    if (gMoreSeedType) { // 解锁更多对战僵尸
        return aSeedType >= NUM_ZOMBIE_SEED_IN_CHOOSER ? SEED_NONE : (SeedType)aSeedType;
    } else {
        return aSeedType > SEED_ZOMBIE_GARGANTUAR ? SEED_NONE : (SeedType)aSeedType;
    }
}

ZombieType SeedChooserScreen::GetZombieType(ZombieType theZombieType) {
    return theZombieType >= NUM_ZOMBIE_TYPES ? ZOMBIE_INVALID : theZombieType;
}

int SeedChooserScreen::GetSeedPacketIndex(int theSeedIndex) {
    if (mIsZombieChooser)
        return theSeedIndex - SEED_ZOMBIE_GRAVESTONE;
    else
        return theSeedIndex;
}

void SeedChooserScreen::OnPlayerPickedSeed(int thePlayerIndex) {
    VSSetupMenu *aVSSetupScreen = mApp->mVSSetupScreen;
    if (aVSSetupScreen)
        aVSSetupScreen->OnPlayerPickedSeed(thePlayerIndex);
}

SeedType SeedChooserScreen::FindSeedInBank(int theIndexInBank, int thePlayerIndex) {
    for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1)) {
        SeedType aZombieSeedType;
        if (mIsZombieChooser) {
            aZombieSeedType = GetZombieSeedType(aSeedType);
            aSeedType = aZombieSeedType;
        }
        if (HasPacket(aSeedType, mIsZombieChooser) && mChosenSeeds->mSeedState == SEED_IN_BANK && mChosenSeeds->mSeedIndexInBank == theIndexInBank
            && mChosenSeeds->mChosenPlayerIndex == thePlayerIndex) {
            return mChosenSeeds->mSeedType;
        }
    }
    return SEED_NONE;
}

void SeedChooserScreen::ClickedSeedInChooser(ChosenSeed &theChosenSeed, int thePlayerIndex) {
    // 实现1P结盟选卡选满后自动转换为2P选卡
    if (mApp->IsCoopMode())
        thePlayerIndex = !m1PChoosingSeeds;

    int aGamepadIndex = mApp->PlayerToGamepadIndex(thePlayerIndex);

    // 检查是否允许选择种子
    bool canPickSeed = true;

    // 合作模式检查
    if (mApp->IsCoopMode()) {
        if (mSeedsInBothBank > 8) {
            canPickSeed = false;
        }
    }
    // 非合作模式检查
    else if (mSeedsInBothBank == mSeedBank1->mNumPackets) {
        canPickSeed = false;
    }

    // VS模式检查
    if (mApp->IsVSMode() && !CanPickNow()) {
        mApp->PlaySample(*SOUND_BUZZER);
        canPickSeed = false;
    }

    // 检查玩家种子栏容量
    if (mApp->IsCoopMode()) {
        int *aNumSeedsInBank = (&mSeedsIn1PBank + thePlayerIndex);
        if (*aNumSeedsInBank > 3) {
            canPickSeed = false;
        }
    }

    if (!canPickSeed) {
        return;
    }

    // 禁选模式（BP）
    if (mApp->IsVSMode() && gVSSetupWidget->mBanMode) {
        int x = (aGamepadIndex == 1) ? mCursorPositionX2 : mCursorPositionX1;
        int y = (aGamepadIndex == 1) ? mCursorPositionY2 : mCursorPositionY1;
        SeedType aSeedType = SeedHitTest(x, y);
        if (aSeedType != SEED_NONE && !SeedNotAllowedToPick(aSeedType)) {
            BannedSeed &aBannedSeed = gVSSetupWidget->mBannedSeed[aSeedType];
            aBannedSeed.mSeedType = theChosenSeed.mSeedType;

            int aSeedBanned = aBannedSeed.mSeedType;
            int aChooserPage = GetPage();
            gVSSetupWidget->mBannedSeed[aSeedBanned].mX = theChosenSeed.mX;
            if (aChooserPage == 0) {
                gVSSetupWidget->mBannedSeed[aSeedBanned].mY = theChosenSeed.mY;
            } else {
                gVSSetupWidget->mBannedSeed[aSeedBanned].mY = theChosenSeed.mY - SEED_PACKET_HEIGHT * 6;
            }
            gVSSetupWidget->mBannedSeed[aSeedBanned].mSeedState = BannedSeedState::SEED_BANNED;
            if (mIsZombieChooser)
                gVSSetupWidget->mBannedSeed[aSeedBanned].mChosenPlayerIndex = 1;

            gVSSetupWidget->mSeedsInBothBanned++;
            if (gVSSetupWidget->mSeedsInBothBanned == gVSSetupWidget->mNumBanPackets) {
                gVSSetupWidget->mBanMode = false;
                mBoard->SwitchGamepadControls();
            }

            mApp->PlaySample(*SOUND_TAP);
            OnPlayerPickedSeed(aGamepadIndex);
        }
        return;
    }

    // 确定种子栏
    int aSeedsInBank;
    if (mApp->IsCoopMode() && thePlayerIndex == 1) {
        aSeedsInBank = mSeedsIn2PBank;
    } else {
        aSeedsInBank = mSeedsIn1PBank;
    }

    // 设置种子动画参数
    theChosenSeed.mStartX = theChosenSeed.mX;
    theChosenSeed.mStartY = theChosenSeed.mY;
    theChosenSeed.mTimeStartMotion = mSeedChooserAge;
    theChosenSeed.mTimeEndMotion = mSeedChooserAge + 25;
    if (gMoreSeedType && GetPage() == 1)
        theChosenSeed.mStartY -= 6 * SEED_PACKET_HEIGHT;

    // 确定实际玩家索引
    int aActualPlayerIndex;
    if (mApp->IsAdventureMode()) {
        aActualPlayerIndex = 0;
        theChosenSeed.mChosenPlayerIndex = 0;
    } else {
        if (mApp->IsVSMode()) {
            VSSetupMenu *aVSSetupScreen = mApp->mVSSetupScreen;
            aActualPlayerIndex = (thePlayerIndex == 1) ? aVSSetupScreen->mController2Position : aVSSetupScreen->mController1Position;
            theChosenSeed.mChosenPlayerIndex = aActualPlayerIndex;
        } else {
            aActualPlayerIndex = thePlayerIndex;
            theChosenSeed.mChosenPlayerIndex = thePlayerIndex;
        }
    }

    // 获取种子在种子栏中的位置
    GetSeedPositionInBank(aSeedsInBank, theChosenSeed.mEndX, theChosenSeed.mEndY, aActualPlayerIndex);

    // 更新种子状态和计数
    theChosenSeed.mSeedIndexInBank = aSeedsInBank;
    theChosenSeed.mSeedState = SEED_FLYING_TO_BANK;

    mSeedsInFlight++;
    mSeedsInBothBank++;

    if (mApp->IsCoopMode() && thePlayerIndex == 1) {
        mSeedsIn2PBank++;
    } else {
        mSeedsIn1PBank++;
    }

    // 播放音效并更新UI
    RemoveToolTip(thePlayerIndex);
    mApp->PlaySample(*SOUND_TAP);

    // 检查是否启用开始按钮
    if (!mApp->IsCoopMode() && mSeedsInBothBank == mSeedBank1->mNumPackets) {
        EnableStartButton(true);
    }

    if (mApp->IsCoopMode() && mSeedsInBothBank == (mSeedBank2->mNumPackets + mSeedBank1->mNumPackets)) {
        EnableStartButton(true);
    }

    // VS模式特殊处理
    if (mApp->IsVSMode()) {
        OnPlayerPickedSeed(aGamepadIndex);

        if (gVSSetupWidget && gVSSetupWidget->mSeedsInBothBanned > 0 && mSeedsIn1PBank == 4 && !mIsZombieChooser) {
            gVSSetupWidget->mBanMode = true;
            gVSSetupWidget->mSeedsInBothBanned = 0;
            gVSSetupWidget->mNumBanPackets = 2;
            mBoard->SwitchGamepadControls();
        }
    }
}

void SeedChooserScreen::CrazyDavePickSeeds() {
    if (daveNoPickSeeds) {
        return;
    }

    TodWeightedArray aSeedArray[NUM_SEED_TYPES];
    for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1)) {
        aSeedArray[aSeedType].mItem = aSeedType;
        uint aRecFlags = SeedNotRecommendedToPick(aSeedType);
        if ((aSeedType == SEED_GATLINGPEA && !mApp->mPlayerInfo->mPurchases[STORE_ITEM_PLANT_GATLINGPEA]) || !HasPacket(aSeedType, mIsZombieChooser) || SeedNotAllowedToPick(aSeedType)
            || Plant::IsUpgrade(aSeedType) || aSeedType == SEED_IMITATER || aSeedType == SEED_UMBRELLA || aSeedType == SEED_BLOVER) {
            aSeedArray[aSeedType].mWeight = 0;
        } else {
            aSeedArray[aSeedType].mWeight = 1;
        }
    }
    if (mBoard->mZombieAllowed[ZOMBIE_BUNGEE] || mBoard->mZombieAllowed[ZOMBIE_CATAPULT]) {
        aSeedArray[SEED_UMBRELLA].mWeight = 1;
    }
    if (mBoard->mZombieAllowed[ZOMBIE_BALLOON] || mBoard->StageHasFog()) {
        aSeedArray[SEED_BLOVER].mWeight = 1;
    }
    if (mBoard->StageHasRoof()) {
        aSeedArray[SEED_TORCHWOOD].mWeight = 0;
    }

    MTRand aLevelRNG = MTRand(mBoard->GetLevelRandSeed());
    for (int i = 0; i < 3; i++) {
        SeedType aPickedSeed = (SeedType)PickFromWeightedArrayUsingSpecialRandSeed(aSeedArray, NUM_SEEDS_IN_CHOOSER, aLevelRNG);
        aSeedArray[aPickedSeed].mWeight = 0;
        ChosenSeed &aChosenSeed = mChosenSeeds[aPickedSeed];

        int aPosX = mBoard->GetSeedPacketPositionX(i, 0, 0);
        aChosenSeed.mX = aPosX;
        aChosenSeed.mY = 8;
        aChosenSeed.mStartX = aPosX;
        aChosenSeed.mStartY = 8;
        aChosenSeed.mEndX = aPosX;
        aChosenSeed.mEndY = 8;
        aChosenSeed.mSeedState = SEED_IN_BANK;
        aChosenSeed.mSeedIndexInBank = i;
        aChosenSeed.mCrazyDavePicked = true;
        mSeedsIn1PBank++;
    }
}

void SeedChooserScreen::PickRandomSeeds() {
    for (int anIndex = mSeedsIn1PBank; anIndex < mBoard->mSeedBank1->mNumPackets; anIndex++) {
        SeedType aSeedType;
        do
            aSeedType = (SeedType)Rand(mApp->GetSeedsAvailable(mIsZombieChooser));
        while (!HasPacket(aSeedType, mIsZombieChooser) || aSeedType == SEED_IMITATER || mChosenSeeds[aSeedType].mSeedState != SEED_IN_CHOOSER);
        ChosenSeed &aChosenSeed = mChosenSeeds[aSeedType];
        aChosenSeed.mTimeStartMotion = 0;
        aChosenSeed.mTimeEndMotion = 0;
        aChosenSeed.mStartX = aChosenSeed.mX;
        aChosenSeed.mStartY = aChosenSeed.mY;
        GetSeedPositionInBank(anIndex, aChosenSeed.mEndX, aChosenSeed.mEndY, mPlayerIndex);
        aChosenSeed.mSeedState = SEED_IN_BANK;
        aChosenSeed.mSeedIndexInBank = anIndex;
        mSeedsIn1PBank++;
    }
    for (SeedType aSeedFlying = SEED_PEASHOOTER; aSeedFlying < NUM_SEEDS_IN_CHOOSER; aSeedFlying = (SeedType)(aSeedFlying + 1))
        LandFlyingSeed(mChosenSeeds[aSeedFlying]);
    CloseSeedChooser();
}

void SeedChooserScreen::ClickedSeedInBank(ChosenSeed *theChosenSeed, unsigned int thePlayerIndex) {
    // 解决结盟1P选够4个种子之后，无法点击种子栏内的已选种子来退选的问题
    if (mApp->IsCoopMode()) {
        thePlayerIndex = theChosenSeed->mChosenPlayerIndex;
    }

    old_SeedChooserScreen_ClickedSeedInBank(this, theChosenSeed, thePlayerIndex);
}

void SeedChooserScreen::OnKeyDown(KeyCode theKey, unsigned int thePlayerIndex) {
    old_SeedChooserScreen_OnKeyDown(this, theKey, thePlayerIndex);
}

void SeedChooserScreen::GameButtonDown(GamepadButton theButton, unsigned int thePlayerIndex) {
    // 修复结盟2P无法选择模仿者
    if (mApp->IsCoopMode() && theButton == GamepadButton::BUTTONCODE_A) {
        if (mChooseState == SeedChooserState::CHOOSE_VIEW_LAWN) {
            old_SeedChooserScreen_GameButtonDown(this, theButton, thePlayerIndex);
            return;
        }

        if (mApp->mTwoPlayerState == -1 && mPlayerIndex != thePlayerIndex)
            return;

        SeedType aSeedType = thePlayerIndex ? mSeedType2 : mSeedType1;
        int aSeedsInBank = mSeedsInBothBank;
        // 此处将判定条件改为选满8个种子时无法选取模仿者。原版游戏中此处是选满4个则无法选取，导致模仿者选取出现问题。
        if (aSeedType == SeedType::SEED_IMITATER && aSeedsInBank < 8) {
            if (mChosenSeeds[SeedType::SEED_IMITATER].mSeedState != ChosenSeedState::SEED_IN_BANK) {
                // 先将已选种子数改为0，然后执行旧函数，这样模仿者选取界面就被打开了。
                mSeedsInBothBank = 0;
                old_SeedChooserScreen_GameButtonDown(this, theButton, thePlayerIndex);
                // 然后再恢复已选种子数即可。
                mSeedsInBothBank = aSeedsInBank;
                return;
            }
        }
    }

    if (mApp->IsVSMode()) {
        if (theButton == GamepadButton::BUTTONCODE_R1) {
            if (mIsZombieChooser) {
                ButtonDepress(SeedChooserPage::SeedChooserPage_NextZombiePage);
            } else {
                ButtonDepress(SeedChooserPage::SeedChooserPage_NextPlantPage);
            }
        }
    }

    if (mSeedsInFlight > 0) {
        for (int i = 0; i < NUM_SEEDS_IN_CHOOSER; i++) {
            LandFlyingSeed(mChosenSeeds[i]);
        }
    }

    if (tcpClientSocket >= 0 && mApp->IsVSMode()) {
        U8U8_Event event = {{EventType::EVENT_SEEDCHOOSER_SELECT_SEED}, uint8_t(mIsZombieChooser ? mSeedType2 : mSeedType1), mIsZombieChooser};
        send(tcpClientSocket, &event, sizeof(U8U8_Event), 0);
    }

    old_SeedChooserScreen_GameButtonDown(this, theButton, thePlayerIndex);
}

void SeedChooserScreen::DrawPacket(
    Sexy::Graphics *g, int x, int y, SeedType theSeedType, SeedType theImitaterType, float thePercentDark, int theGrayness, Color *theColor, bool theDrawCost, bool theUseCurrentCost) {
    // 修复SeedChooser里的卡片亮度不正确。
    // 已选的卡片grayness为55，不推荐的卡片grayness为115。theColor则固定为{255,255,255,255}。

    // int theConvertedGrayness = ((theColor->mRed + theColor->mGreen + theColor->mBlue) / 3 + theGrayness) / 2;
    // 此算法用于在对战模式将非选卡的一方的卡片整体变暗。但这种算法下，55亮度会变成155亮度，115亮度会变成185亮度，严重影响非对战模式的选卡体验。所以需要修复。

    int theConvertedGrayness = (mApp->IsVSMode()) ? ((theColor->mRed + theColor->mGreen + theColor->mBlue) / 3 + theGrayness) / 2 : theGrayness;
    if (mApp->IsVSMode()) {
        if (mIsZombieChooser && SeedNotAllowedToPick(theSeedType)) {
            if (CanPickNow())
                theConvertedGrayness = 115;
            else
                theConvertedGrayness = 55;
        }

        if (gVSSetupWidget && gVSSetupWidget->mBanMode) {
            for (int i = 0; i < NUM_SEEDS_IN_CHOOSER; i++) {
                if (mChosenSeeds[i].mSeedType == theSeedType && mChosenSeeds[i].mSeedState == ChosenSeedState::SEED_IN_BANK) {
                    theConvertedGrayness = 115;
                }
            }
        }
    }

    DrawSeedPacket(g, x, y, theSeedType, theImitaterType, thePercentDark, theConvertedGrayness, theDrawCost, false, mIsZombieChooser, theUseCurrentCost);
}

void SeedChooserScreen::ButtonPress(int theId) {
    LawnApp *lawnApp = *gLawnApp_Addr;
    lawnApp->mSeedChooserScreen->mFocusedChildWidget = nullptr; // 修复点击菜单后无法按键选取植物卡片
}

void SeedChooserScreen::ButtonDepress(int theId) {

    if (mSeedsInFlight > 0 || mChooseState == SeedChooserState::CHOOSE_VIEW_LAWN || !mMouseVisible) {
        return;
    }

    if (theId == SeedChooserScreen_Menu) {
        mApp->PlaySample(*Sexy_SOUND_PAUSE_Addr);
        mApp->DoNewOptions(false, 0);
        return;
    }
    if (theId == SeedChooserPage::SeedChooserPage_NextPlantPage) {
        gPlantChooserPage->ButtonDepress(theId);
    }
    if (theId == SeedChooserPage::SeedChooserPage_NextZombiePage) {
        gZombieChooserPage->ButtonDepress(theId);
    }

    old_SeedChooserScreen_ButtonDepress(this, theId);
}

void SeedChooserScreen::GetSeedPositionInBank(int theIndex, int &x, int &y, int thePlayerIndex) {
    // 修复对战选卡时的错位
    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
        if (!mIsZombieChooser) {
            x = mBoard->mSeedBank1->mX - mX + mBoard->GetSeedPacketPositionX(theIndex, 0, mIsZombieChooser);
            y = mBoard->mSeedBank1->mY - mY + 8;
        } else {
            x = mBoard->mSeedBank2->mX - mX + mBoard->GetSeedPacketPositionX(theIndex, 0, mIsZombieChooser);
            y = mBoard->mSeedBank2->mY - mY + 8;
        }
        return;
    }

    old_SeedChooserScreen_GetSeedPositionInBank(this, theIndex, x, y, thePlayerIndex);
}

void SeedChooserScreen::GetSeedPositionInChooser(int theIndex, int &x, int &y) {
    if (!mIsZombieChooser && theIndex == SeedType::SEED_IMITATER) {
        x = mImitaterButton->mX;
        y = mImitaterButton->mY;
        return;
    }
    if (theIndex > SeedType::SEED_IMITATER)
        theIndex -= 2;
    int aRow = theIndex / NumColumns();
    int aCol = theIndex % NumColumns();
    x = 53 * aCol + 22;
    if (mIsZombieChooser) {
        if (aRow == 3 && !gMoreSeedType) {
            x = 53 * aCol + 48;
        }
    }

    if (Has7Rows()) {
        y = 70 * aRow + 123;
    } else {
        y = 73 * aRow + 128;
    }

    if (mIsZombieChooser) {
        y = 70 * aRow + 123;
    }
}

int SeedChooserScreen::NumColumns() {
    if (mIsZombieChooser) {
        return 5;
    } else {
        return 8;
    }
}


void SeedChooserScreen::ShowToolTip(unsigned int thePlayerIndex) {
    old_SeedChooserScreen_ShowToolTip(this, thePlayerIndex);

    bool aIsPlayer2 = thePlayerIndex == 1 ? true : false;
    ToolTipWidget *aTolTip = aIsPlayer2 ? mToolTip2 : mToolTip1;

    if (mApp->IsVSMode()) {
        int aGamepadIndex = mApp->PlayerToGamepadIndex(thePlayerIndex);
        int x = (aGamepadIndex == 1) ? mCursorPositionX2 : mCursorPositionX1;
        int y = (aGamepadIndex == 1) ? mCursorPositionY2 : mCursorPositionY1;
        SeedType aSeedType = SeedHitTest(x, y);
        for (int i = 0; i < NUM_ZOMBIE_SEED_TYPES; ++i) {
            if (gVSSetupWidget && aSeedType == gVSSetupWidget->mBannedSeed[i].mSeedType) {
                aTolTip->SetWarningText("本轮已禁用");
            }
        }

        if (mIsZombieChooser) {
            if (mChosenSeeds[aSeedType - SeedType::SEED_ZOMBIE_GRAVESTONE].mSeedState == ChosenSeedState::SEED_IN_BANK && mChosenSeeds[aSeedType - SeedType::SEED_ZOMBIE_GRAVESTONE].mCrazyDavePicked) {
                bool seedIsGrave = (mToolTipSeed1 == SeedType::SEED_ZOMBIE_GRAVESTONE || mToolTipSeed2 == SeedType::SEED_ZOMBIE_GRAVESTONE) ? true : false;
                pvzstl::string str = seedIsGrave ? TodStringTranslate("[ZOMBIE_BOSS_WANTS]") : "";
                aTolTip->SetWarningText(str);
            }
            // 对战显示隐藏僵尸卡信息
            if (aSeedType > SeedType::SEED_ZOMBIE_GARGANTUAR && aSeedType < SeedType::NUM_ZOMBIE_SEED_IN_CHOOSER) {
                pvzstl::string aTitle, aLabel;
                switch (aSeedType) {
                        // case SeedType::SEED_ZOMBIE_REDEYE_GARGANTUAR: // 红眼巨人僵尸
                        // aTitle = TodStringTranslate("[REDEYE_GARGANTUAR_ZOMBIE]");
                        // aLabel = TodStringTranslate("[REDEYE_GARGANTUAR_ZOMBIE_DESCRIPTION_HEADER]");
                        // break;
                    case SeedType::SEED_ZOMBIE_REDEYE_GARGANTUAR: // 红眼巨人僵尸
                        aTitle = TodStringTranslate("[REDEYE_GARGANTUAR_ZOMBIE]");
                        aLabel = TodStringTranslate("[REDEYE_GARGANTUAR_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_PEA_HEAD: // 豌豆射手僵尸
                        aTitle = TodStringTranslate("[PEA_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[PEA_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_WALLNUT_HEAD: // 坚果僵尸
                        aTitle = TodStringTranslate("[WALLNUT_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[WALLNUT_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_JALAPENO_HEAD: // 火爆辣椒僵尸
                        aTitle = TodStringTranslate("[JALAPENO_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[JALAPENO_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_GATLINGPEA_HEAD: // 机枪射手僵尸
                        aTitle = TodStringTranslate("[GATLING_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[GATLING_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_SQUASH_HEAD: // 窝瓜僵尸
                        aTitle = TodStringTranslate("[SQUASH_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[SQUASH_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_TALLNUT_HEAD: // 高坚果僵尸
                        aTitle = TodStringTranslate("[TALLNUT_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[TALLNUT_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_SUNFLOWER_HEAD: // 向日葵僵尸
                        aTitle = TodStringTranslate("[SUNFLOWER_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[SUNFLOWER_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_TORCHWOOD_HEAD: // 火炬树桩僵尸
                        aTitle = TodStringTranslate("[TORCHWOOD_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[TORCHWOOD_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_EXPLODE_O_NUT_HEAD: // 爆炸坚果僵尸
                        aTitle = TodStringTranslate("[EXPLODE_O_NUT_HEAD_ZOMBIE]");
                        aLabel = TodStringTranslate("[EXPLODE_O_NUT_HEAD_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_GIGA_FOOTBALL:
                        aTitle = TodStringTranslate("[GIGA_FOOTBALL_ZOMBIE]");
                        aLabel = TodStringTranslate("[GIGA_FOOTBALL_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    case SeedType::SEED_ZOMBIE_JACKSON:
                        aTitle = TodStringTranslate("[JACKSON_ZOMBIE]");
                        aLabel = TodStringTranslate("[JACKSON_ZOMBIE_DESCRIPTION_HEADER]");
                        break;
                    default:
                        return;
                }
                aTolTip->SetTitle(aTitle);
                aTolTip->SetLabel(aLabel);
            }
        } else {
            if (gVSSetupWidget && gVSSetupWidget->mBanMode) {
                if (mChosenSeeds[aSeedType].mSeedState == ChosenSeedState::SEED_IN_CHOOSER) {
                    bool seedIsCoffee = (mToolTipSeed1 == SeedType::SEED_INSTANT_COFFEE || mToolTipSeed2 == SeedType::SEED_INSTANT_COFFEE) ? true : false;
                    pvzstl::string str = seedIsCoffee ? "此阶段不允许" : "";
                    aTolTip->SetWarningText(str);
                }
            }
        }

        if (mSeedsInFlight <= 0 && GetPage() == 1) {
            int aSeedX, aSeedY;
            SeedType aZombieSeedType = mIsZombieChooser ? GetZombieIndexBySeedType(aSeedType) : aSeedType;
            GetSeedPositionInChooser(aZombieSeedType, aSeedX, aSeedY);
            aTolTip->mY = aSeedY - 5 * SEED_PACKET_HEIGHT;
        }
    }
}

SeedType SeedChooserScreen::GetZombieIndexBySeedType(SeedType theSeedType) {
    return theSeedType - SEED_ZOMBIE_GRAVESTONE < 0 ? SeedType::SEED_NONE : (SeedType)(theSeedType - SEED_ZOMBIE_GRAVESTONE);
}

void SeedChooserScreen::MouseMove(int x, int y) {
    SeedType aSeedType = SeedHitTest(x, y);
    // 该函数探测不到模仿者位置
    if (aSeedType == SeedType::SEED_NONE) {
        return;
    }

    if (mIsZombieChooser) {
        int aChooserPage = GetPage();
        if ((aChooserPage == 0 && aSeedType > SeedType::SEED_ZOMBIE_TALLNUT_HEAD) || (aChooserPage == 1 && aSeedType >= SeedType::NUM_ZOMBIE_SEED_IN_CHOOSER))
            return;

        if (aChooserPage == 1) {
            aSeedType = SeedType(aSeedType - 30);
        }
        SeedType aZombieSeedType = GetZombieIndexBySeedType(aSeedType);
        GetSeedPositionInChooser(aZombieSeedType, mCursorPositionX1, mCursorPositionX1);
        GetSeedPositionInChooser(aZombieSeedType, mCursorPositionX2, mCursorPositionY2);
        mSeedType2 = aZombieSeedType;
    } else if (m1PChoosingSeeds) {
        int aChooserPage = GetPage();
        if (mApp->IsVSMode() && (Plant::IsUpgrade(aSeedType) || aSeedType == SeedType::SEED_IMITATER || aSeedType >= SeedType::NUM_SEEDS_IN_CHOOSER))
            return;

        if (aChooserPage == 1) {
            aSeedType = SeedType(aSeedType - (SEED_IMITATER + 2));
        }

        if (mApp->IsVSMode()) {
            GetSeedPositionInChooser(aSeedType, mCursorPositionX1, mCursorPositionX1);
            GetSeedPositionInChooser(aSeedType, mCursorPositionX2, mCursorPositionY2);
        } else {
            GetSeedPositionInChooser(aSeedType, mCursorPositionX1, mCursorPositionY1);
        }
        mSeedType1 = aSeedType;
    } else {
        GetSeedPositionInChooser(aSeedType, mCursorPositionX2, mCursorPositionY2);
        mSeedType2 = aSeedType;
    }
}

void SeedChooserScreen::MouseDown(int x, int y, int theClickCount) {
    m1PChoosingSeeds = !mApp->IsCoopMode() || mSeedsIn1PBank < 4;

    bool mViewLawnButtonDisabled = mViewLawnButton == nullptr || !mBoard->mCutScene->IsSurvivalRepick();
    bool mStoreButtonDisabled = mStoreButton == nullptr || mStoreButton->mDisabled;
    bool mStartButtonDisabled = mStartButton == nullptr || mStartButton->mDisabled;
    bool mAlmanacButtonDisabled = mAlmanacButton == nullptr || mAlmanacButton->mDisabled;

    if (!mViewLawnButtonDisabled) { // !mDisabled
        Sexy::Rect mViewLawnButtonRect = {mViewLawnButton->mX, mViewLawnButton->mY, mViewLawnButton->mWidth, 50};
        // LOGD("mStoreButtonRect:%d %d %d %d",mStoreButtonRect[0],mStoreButtonRect[1],mStoreButtonRect[2],mStoreButtonRect[3]);
        if (TRect_Contains(&mViewLawnButtonRect, x, y)) {
            mApp->PlaySample(*Sexy_SOUND_TAP_Addr);
            gSeedChooserTouchState = SeedChooserTouchState::ViewLawnButton;
            // GameButtonDown(seedChooserScreen, 8, 0);
            return;
        }
    }

    if (!mStoreButtonDisabled) { // !mDisabled
        Sexy::Rect mStoreButtonRect = {mStoreButton->mX, mStoreButton->mY, mStoreButton->mWidth, 50};
        // LOGD("mStoreButtonRect:%d %d %d %d",mStoreButtonRect[0],mStoreButtonRect[1],mStoreButtonRect[2],mStoreButtonRect[3]);
        if (TRect_Contains(&mStoreButtonRect, x, y)) {
            mApp->PlaySample(*Sexy_SOUND_TAP_Addr);
            gSeedChooserTouchState = SeedChooserTouchState::StoreButton;
            // GameButtonDown(seedChooserScreen, 8, 0);
            return;
        }
    }

    if (!mStartButtonDisabled) { // !mDisabled
        Sexy::Rect mStartButtonRect = {mStartButton->mX, mStartButton->mY, mStartButton->mWidth, 50};
        if (TRect_Contains(&mStartButtonRect, x, y)) {
            mApp->PlaySample(*Sexy_SOUND_TAP_Addr);
            gSeedChooserTouchState = SeedChooserTouchState::StartButton;

            // SeedChooserScreen_OnStartButton(seedChooserScreen);
            return;
        }
    }

    if (!mAlmanacButtonDisabled) { // !mDisabled
        Sexy::Rect mAlmanacButtonRect = {mAlmanacButton->mX, mAlmanacButton->mY, mAlmanacButton->mWidth, 50};
        if (TRect_Contains(&mAlmanacButtonRect, x, y)) {
            mApp->PlaySample(*Sexy_SOUND_TAP_Addr);
            gSeedChooserTouchState = SeedChooserTouchState::AlmanacButton;

            // GameButtonDown(seedChooserScreen, 9, 0);
            return;
        }
    }

    if (HasPacket(SeedType::SEED_IMITATER, 0) && !mApp->IsVSMode() && !mIsZombieChooser) {
        int mImitaterPositionX = 0;
        int mImitaterPositionY = 0;
        GetSeedPositionInChooser(SeedType::SEED_IMITATER, mImitaterPositionX, mImitaterPositionY);
        Sexy::Rect mImitaterPositionRect = {mImitaterPositionX, mImitaterPositionY, SEED_PACKET_WIDTH, SEED_PACKET_HEIGHT};
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
            GameButtonDown(BUTTONCODE_A, !m1PChoosingSeeds);
            return;
        }
    }
    SeedType aSeedType = SeedHitTest(x, y);
    // 该函数探测不到模仿者位置

    if (aSeedType == SeedType::SEED_NONE) {
        return;
    }

    if (!mIsZombieChooser && (mChosenSeeds[aSeedType].mSeedState == ChosenSeedState::SEED_FLYING_TO_BANK || mChosenSeeds[aSeedType].mSeedState == ChosenSeedState::SEED_FLYING_TO_CHOOSER)) {
        return;
    }

    if (mIsZombieChooser) {
        int aChooserPage = GetPage();
        if ((aChooserPage == 0 && aSeedType > SeedType::SEED_ZOMBIE_TALLNUT_HEAD) || (aChooserPage == 1 && aSeedType >= SeedType::NUM_ZOMBIE_SEED_IN_CHOOSER))
            return;

        if (aChooserPage == 1) {
            aSeedType = SeedType(aSeedType - 30);
        }
        SeedType aZombieSeedType = GetZombieIndexBySeedType(aSeedType);
        GetSeedPositionInChooser(aZombieSeedType, mCursorPositionX1, mCursorPositionY1);
        GetSeedPositionInChooser(aZombieSeedType, mCursorPositionX2, mCursorPositionY2);
        mSeedType2 = aZombieSeedType;
    } else if (m1PChoosingSeeds) {
        int aChooserPage = GetPage();
        if (mApp->IsVSMode() && (Plant::IsUpgrade(aSeedType) || aSeedType == SeedType::SEED_IMITATER || aSeedType >= SeedType::NUM_SEEDS_IN_CHOOSER))
            return;

        if (aChooserPage == 1) {
            aSeedType = SeedType(aSeedType - (SEED_IMITATER + 2));
        }

        if (mApp->IsVSMode()) {
            GetSeedPositionInChooser(aSeedType, mCursorPositionX1, mCursorPositionY1);
            GetSeedPositionInChooser(aSeedType, mCursorPositionX2, mCursorPositionY2);
        } else {
            GetSeedPositionInChooser(aSeedType, mCursorPositionX1, mCursorPositionY1);
        }
        mSeedType1 = aSeedType;
    } else {
        GetSeedPositionInChooser(aSeedType, mCursorPositionX2, mCursorPositionY2);
        mSeedType2 = aSeedType;
    }
    gSeedChooserTouchState = SeedChooserTouchState::SeedChooser;
}

void SeedChooserScreen::MouseDrag(int x, int y) {
    if (gSeedChooserTouchState == SeedChooserTouchState::SeedChooser) {
        SeedType aSeedType = SeedHitTest(x, y);
        // 该函数探测不到模仿者位置
        if (aSeedType == SeedType::SEED_NONE) {
            return;
        }
        if (mIsZombieChooser) {
            int aChooserPage = GetPage();
            if ((aChooserPage == 0 && aSeedType > SeedType::SEED_ZOMBIE_TALLNUT_HEAD) || (aChooserPage == 1 && aSeedType >= SeedType::NUM_ZOMBIE_SEED_IN_CHOOSER))
                return;

            if (aChooserPage == 1) {
                aSeedType = SeedType(aSeedType - 30);
            }
            SeedType aZombieSeedType = GetZombieIndexBySeedType(aSeedType);
            GetSeedPositionInChooser(aZombieSeedType, mCursorPositionX1, mCursorPositionY1);
            GetSeedPositionInChooser(aZombieSeedType, mCursorPositionX2, mCursorPositionY2);
            mSeedType2 = aZombieSeedType;
        } else if (m1PChoosingSeeds) {
            int aChooserPage = GetPage();
            if (mApp->IsVSMode() && (Plant::IsUpgrade(aSeedType) || aSeedType == SeedType::SEED_IMITATER || aSeedType >= SeedType::NUM_SEEDS_IN_CHOOSER))
                return;

            if (aChooserPage == 1) {
                aSeedType = SeedType(aSeedType - (SEED_IMITATER + 2));
            }

            if (mApp->IsVSMode()) {
                GetSeedPositionInChooser(aSeedType, mCursorPositionX1, mCursorPositionY1);
                GetSeedPositionInChooser(aSeedType, mCursorPositionX2, mCursorPositionY2);
            } else {
                GetSeedPositionInChooser(aSeedType, mCursorPositionX1, mCursorPositionY1);
            }
            mSeedType1 = aSeedType;
        } else {
            GetSeedPositionInChooser(aSeedType, mCursorPositionX2, mCursorPositionY2);
            mSeedType2 = aSeedType;
        }
    }
}

void SeedChooserScreen::MouseUp(int x, int y) {

    if (tcp_connected && mApp->mGameMode == GAMEMODE_MP_VS) {
        U8U8_Event event = {{EventType::EVENT_SEEDCHOOSER_SELECT_SEED}, uint8_t(mIsZombieChooser ? mSeedType2 : mSeedType1), mIsZombieChooser};
        send(tcpServerSocket, &event, sizeof(U8U8_Event), 0);
        return;
    }

    switch (gSeedChooserTouchState) {
        case SeedChooserTouchState::ViewLawnButton:
            ButtonDepress(SeedChooserScreen_ViewLawn);
            break;
        case SeedChooserTouchState::SeedChooser:
            if (mIsZombieChooser) {
                GameButtonDown(BUTTONCODE_A, 1);
            } else if (m1PChoosingSeeds) {
                if (mApp->IsCoopMode()) {
                    GameButtonDown(BUTTONCODE_A, 0);
                } else {
                    GameButtonDown(BUTTONCODE_A, 1);
                }
            } else {
                GameButtonDown(BUTTONCODE_A, 1);
            }
            break;
        case SeedChooserTouchState::StoreButton:
            ButtonDepress(SeedChooserScreen_Store);
            break;
        case SeedChooserTouchState::StartButton:
            ButtonDepress(SeedChooserScreen_Start);
            break;
        case SeedChooserTouchState::AlmanacButton:
            ButtonDepress(SeedChooserScreen_Almanac);
            break;
        default:
            break;
    }
    gSeedChooserTouchState = SeedChooserTouchState::SEEDCHOOSER_TOUCHSTATE_NONE;
}

int SeedChooserScreen::GetNextSeedInDir(int theNumSeed, int theMoveDirection) {
    int aNumCol = NumColumns();
    int aRow;
    int aCol;

    // 计算当前行列位置
    if (theNumSeed == 48) {
        aCol = 8;
        aRow = 5;
    } else {
        aRow = theNumSeed / aNumCol;
        aCol = theNumSeed % aNumCol;
    }

    // 确定最大行数
    int aNumRow;
    if (mApp->IsVSMode()) {
        aNumRow = 4;
    } else if (Has7Rows()) {
        aNumRow = 5;
    } else {
        aNumRow = 4;
    }

    // 僵尸选择特殊处理
    if (mIsZombieChooser) {
        // 边界条件检查
        if (theNumSeed == 14 && theMoveDirection == 1) {
            return 19;
        }
        if (theNumSeed == 19 && theMoveDirection == 3) {
            return 19;
        }
        if (theNumSeed > NUM_ZOMBIE_SEED_IN_CHOOSER) {
            return NUM_ZOMBIE_SEED_IN_CHOOSER;
        }
        if (gMoreSeedType) { // 拓展僵尸选卡适配键盘选取
            aNumRow = 5;
            if (GetPage() == 1) {
                aNumRow = 0;
            }
        }
    } else {
        if (theNumSeed == 53 && theMoveDirection == 3) {
            return 53;
        }
        if (theNumSeed >= NUM_SEEDS_IN_CHOOSER) {
            return 53;
        }
        if (GetPage() == 1) {
            aNumCol = 3;
            aNumRow = 0;
        }
    }

    // 根据方向移动
    int aNextSeed;
    switch (theMoveDirection) {
        case 0: // 向上
            if (aRow > 0) {
                --aRow;
            }
            aNextSeed = aCol + NumColumns() * aRow;
            break;

        case 1: // 向下
            if (aRow < aNumRow) {
                ++aRow;
            }
            aNextSeed = aCol + NumColumns() * aRow;
            break;

        case 2: // 向左
            if (aCol > 0) {
                --aCol;
            }
            aNextSeed = aCol + NumColumns() * aRow;
            break;

        case 3: // 向右
            if (aCol < NumColumns() - 1) {
                ++aCol;
            }
            aNextSeed = aCol + NumColumns() * aRow;
            break;

        default:
            aNextSeed = aCol + NumColumns() * aRow;
            break;
    }

    return aNextSeed;
}

void SeedChooserScreen::Draw(Graphics *g) {
    if (gMoreSeedType) {
        if (mApp->GetDialog(DIALOG_STORE) || mApp->GetDialog(DIALOG_ALMANAC))
            return;

        g->SetLinearBlend(true);
        if (!mBoard->ChooseSeedsOnCurrentLevel() || (mBoard->mCutScene && mBoard->mCutScene->IsBeforePreloading()))
            return;

        Image *aBackgroundImage = mIsZombieChooser ? *Sexy::IMAGE_SEEDCHOOSER_BACKGROUND2 : *Sexy::IMAGE_SEEDCHOOSER_BACKGROUND;
        g->DrawImage(aBackgroundImage, 0, 87);
        if (!mApp->IsVSMode() && HasPacket(SEED_IMITATER, false)) {
            g->DrawImage(*Sexy::IMAGE_SEEDCHOOSER_IMITATERADDON, mImitaterButton->mX - 5, mImitaterButton->mY - 12);
        }
        Color aColor = mIsZombieChooser ? Color(0, 255, 0) : Color(213, 159, 43);
        pvzstl::string aChooserStr = mIsZombieChooser ? TodStringTranslate("[CHOOSE_YOUR_ZOMBIES]") : TodStringTranslate("[CHOOSE_YOUR_PLANTS]");
        int aStringX = *(reinterpret_cast<int *>(aBackgroundImage) + 9) / 2;
        TodDrawString(g, aChooserStr, aStringX, 114, *Sexy::FONT_DWARVENTODCRAFT18, aColor, DS_ALIGN_CENTER);

        if (mIsZombieChooser) {
            int aChooserPage = GetPage();
            int aNumSeeds = SEED_ZOMBIE_SUNFLOWER_HEAD - SEED_ZOMBIE_GRAVESTONE;
            if (aChooserPage == 1) {
                aNumSeeds += NUM_ZOMBIE_SEED_IN_CHOOSER - SEED_ZOMBIE_SUNFLOWER_HEAD;
            }
            for (SeedType aSeedShadow = SEED_PEASHOOTER; aSeedShadow < aNumSeeds; aSeedShadow = SeedType(aSeedShadow + 1)) {
                int x, y;
                GetSeedPositionInChooser(aSeedShadow, x, y);
                if (aChooserPage == 1)
                    y -= 6 * SEED_PACKET_HEIGHT;

                if (HasPacket(aSeedShadow, mIsZombieChooser)) {
                    ChosenSeed &aChosenSeed = mChosenSeeds[GetSeedPacketIndex(aSeedShadow)];

                    SeedType aZombieSeedType = GetZombieSeedType(aSeedShadow);
                    if (aChooserPage == 1 && aZombieSeedType < SEED_ZOMBIE_SUNFLOWER_HEAD)
                        continue;

                    if (aChosenSeed.mSeedState != SEED_IN_CHOOSER) {
                        DrawPacket(g, x, y, aZombieSeedType, SEED_NONE, 0, 55, &Color::White, true, true);
                    }
                } else {
                    g->DrawImage(*Sexy::IMAGE_SEEDPACKETSILHOUETTE, x, y);
                }
            }


            int aNumSeedsInBank = mSeedBank1->mNumPackets;
            if (aNumSeedsInBank > 0) {
                for (int anIndex = 0; anIndex < aNumSeedsInBank; anIndex++) {
                    if (FindSeedInBank(anIndex, mIsZombieChooser) == SEED_NONE) {
                        int x, y;
                        GetSeedPositionInBank(anIndex, x, y, 0);
                        g->DrawImage(*Sexy::IMAGE_SEEDPACKETSILHOUETTE, x, y);
                    }
                }
            }
            if (mApp->IsCoopMode() && mSeedBank2 && aNumSeedsInBank > 0) {
                for (int i = 0; i != aNumSeedsInBank; ++i) {
                    if (FindSeedInBank(i, 1) == SEED_NONE) {
                        int x, y;
                        GetSeedPositionInBank(i, x, y, 1);
                        g->DrawImage(*Sexy::IMAGE_SEEDPACKETSILHOUETTE, x, y);
                    }
                }
            }

            SeedType aSeedTypeInCursor = SEED_NONE;
            int aCursorX, aCursorY;
            bool aGrayedInCursor = false;
            for (SeedType aSeedType = SEED_ZOMBIE_GRAVESTONE; aSeedType < NUM_ZOMBIE_SEED_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1)) {
                ChosenSeed &aChosenSeed = mChosenSeeds[GetSeedPacketIndex(aSeedType)];
                ChosenSeedState aSeedState = aChosenSeed.mSeedState;
                if (HasPacket(aSeedType, mIsZombieChooser) && aSeedState != SEED_FLYING_TO_BANK && aSeedState != SEED_FLYING_TO_CHOOSER && aSeedState != SEED_PACKET_HIDDEN
                    && (aSeedState == SEED_IN_CHOOSER || mBoard->mCutScene->mSeedChoosing)) {
                    bool aGrayed = false;
                    if (((SeedNotRecommendedToPick(aSeedType) || SeedNotAllowedToPick(aSeedType)) && aSeedState == SEED_IN_CHOOSER) || SeedNotAllowedDuringTrial(aSeedType) || !CanPickNow())
                        aGrayed = true;

                    int aPosX = aChosenSeed.mX;
                    int aPosY = aChosenSeed.mY;
                    if (aSeedState == SEED_IN_BANK) {
                        int aSeedIndexInBank = aChosenSeed.mSeedIndexInBank;
                        int aChosenPlayerIndex = aChosenSeed.mChosenPlayerIndex;
                        GetSeedPositionInBank(aSeedIndexInBank, aPosX, aPosY, aChosenPlayerIndex);
                    } else {
                        GetSeedPositionInChooser(GetSeedPacketIndex(aSeedType), aPosX, aPosY);
                        if (aChooserPage == 0 && aSeedType >= SEED_ZOMBIE_SUNFLOWER_HEAD)
                            continue;

                        if (aChooserPage == 1) {
                            if (aSeedType < SEED_ZOMBIE_SUNFLOWER_HEAD)
                                continue;
                            else
                                aPosY -= 6 * SEED_PACKET_HEIGHT;
                        }
                    }

                    if (mSeedType1 == aSeedType && mBoard->mGamepadControls1->mPlayerIndex2 != -1 && aChosenSeed.mSeedState == SEED_IN_CHOOSER) {
                        aSeedTypeInCursor = aSeedType;
                        aGrayedInCursor = aGrayed;
                    }
                    if (mSeedType2 == aSeedType && mBoard->mGamepadControls2->mPlayerIndex2 != -1 && aChosenSeed.mSeedState == SEED_IN_CHOOSER) {
                        aSeedTypeInCursor = aSeedType;
                        aGrayedInCursor = aGrayed;
                    }

                    DrawPacket(g, aPosX, aPosY, aChosenSeed.mSeedType, SEED_NONE, 0, aGrayed ? 115 : 255, &Color::White, true, true);
                }
            }

            for (SeedType aSeedType = SEED_ZOMBIE_GRAVESTONE; aSeedType < NUM_ZOMBIE_SEED_IN_CHOOSER; aSeedType = SeedType(aSeedType + 1)) {
                ChosenSeed &aChosenSeed = mChosenSeeds[GetSeedPacketIndex(aSeedType)];
                ChosenSeedState aSeedState = aChosenSeed.mSeedState;
                if (HasPacket(aSeedType, mIsZombieChooser) && (aSeedState == SEED_FLYING_TO_BANK || aSeedState == SEED_FLYING_TO_CHOOSER)) {
                    DrawPacket(g, aChosenSeed.mX, aChosenSeed.mY, aChosenSeed.mSeedType, SEED_NONE, 0, 255, &Color::White, true, true);
                }
            }
        } else {
            int aChooserPage = GetPage();
            int aNumSeeds = Has7Rows() ? 49 : 39;
            if (aChooserPage == 1) {
                aNumSeeds = NUM_SEEDS_IN_CHOOSER;
            }
            for (SeedType aSeedShadow = SEED_PEASHOOTER; aSeedShadow < aNumSeeds - 1; aSeedShadow = SeedType(aSeedShadow + 1)) {
                int x, y;
                GetSeedPositionInChooser(aSeedShadow, x, y);
                int aOffsetY = mApp->IsVSMode() ? 3 : 0;
                if (aSeedShadow > NUM_SEEDS_IN_CHOOSER) {
                    y -= 6 * (SEED_PACKET_HEIGHT + aOffsetY);
                }
                if (aSeedShadow == SEED_IMITATER) {
                    continue;
                }

                if (aChooserPage == 0) {
                    if ((mApp->IsVSMode() && Plant::IsUpgrade(aSeedShadow)) || aSeedShadow >= SEED_IMITATER)
                        continue;
                }

                if (aChooserPage == 1 && aSeedShadow <= SEED_IMITATER)
                    continue;

                if (HasPacket(aSeedShadow, mIsZombieChooser)) {
                    ChosenSeed &aChosenSeed = mChosenSeeds[GetSeedPacketIndex(aSeedShadow)];
                    if (aChosenSeed.mSeedState != SEED_IN_CHOOSER) {
                        DrawPacket(g, x, y, aSeedShadow, SEED_NONE, 0, 55, &Color::White, true, true);
                    }
                } else {
                    g->DrawImage(*Sexy::IMAGE_SEEDPACKETSILHOUETTE, x, y);
                }
            }

            int aNumSeedsInBank = mSeedBank1->mNumPackets;
            if (aNumSeedsInBank > 0) {
                for (int anIndex = 0; anIndex < aNumSeedsInBank; anIndex++) {
                    if (FindSeedInBank(anIndex, mIsZombieChooser) == SEED_NONE) {
                        int x, y;
                        GetSeedPositionInBank(anIndex, x, y, 0);
                        g->DrawImage(*Sexy::IMAGE_SEEDPACKETSILHOUETTE, x, y);
                    }
                }
            }
            if (mApp->IsCoopMode() && mSeedBank2 && aNumSeedsInBank > 0) {
                for (int i = 0; i != aNumSeedsInBank; ++i) {
                    if (FindSeedInBank(i, 1) == SEED_NONE) {
                        int x, y;
                        GetSeedPositionInBank(i, x, y, 1);
                        g->DrawImage(*Sexy::IMAGE_SEEDPACKETSILHOUETTE, x, y);
                    }
                }
            }

            for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1)) {
                ChosenSeed &aChosenSeed = mChosenSeeds[GetSeedPacketIndex(aSeedType)];
                ChosenSeedState aSeedState = aChosenSeed.mSeedState;
                if (HasPacket(aSeedType, mIsZombieChooser) && aSeedState != SEED_FLYING_TO_BANK && aSeedState != SEED_FLYING_TO_CHOOSER && aSeedState != SEED_PACKET_HIDDEN
                    && (aSeedState == SEED_IN_CHOOSER || mBoard->mCutScene->mSeedChoosing)) {
                    bool aGrayed = false;
                    if (((SeedNotRecommendedToPick(aSeedType) || SeedNotAllowedToPick(aSeedType)) && aSeedState == SEED_IN_CHOOSER) || SeedNotAllowedDuringTrial(aSeedType) || !CanPickNow())
                        aGrayed = true;

                    int aPosX = aChosenSeed.mX;
                    int aPosY = aChosenSeed.mY;
                    if (aSeedState == SEED_IN_BANK) {
                        int aSeedIndexInBank = aChosenSeed.mSeedIndexInBank;
                        int aChosenPlayerIndex = aChosenSeed.mChosenPlayerIndex;
                        GetSeedPositionInBank(aSeedIndexInBank, aPosX, aPosY, aChosenPlayerIndex);
                    } else {
                        GetSeedPositionInChooser(GetSeedPacketIndex(aSeedType), aPosX, aPosY);
                        if (aChooserPage == 0) {
                            if ((mApp->IsVSMode() && Plant::IsUpgrade(aSeedType)) || aSeedType >= SEED_IMITATER)
                                continue;
                        } else {
                            continue;
                        }
                    }

                    DrawPacket(g, aPosX, aPosY, aChosenSeed.mSeedType, aChosenSeed.mImitaterType, 0, aGrayed ? 115 : 255, &Color::White, true, true);
                }
            }

            for (SeedType aSeedType = SEED_EXPLODE_O_NUT; aSeedType < NUM_SEED_TYPES; aSeedType = (SeedType)(aSeedType + 1)) {
                ChosenSeed &aChosenSeed = mChosenSeeds[aSeedType];
                ChosenSeedState aSeedState = aChosenSeed.mSeedState;
                if (HasPacket(aSeedType, mIsZombieChooser) && aSeedState != SEED_FLYING_TO_BANK && aSeedState != SEED_FLYING_TO_CHOOSER /*&& aSeedState != SEED_PACKET_HIDDEN*/
                    && (aSeedState == SEED_IN_CHOOSER || mBoard->mCutScene->mSeedChoosing)) {
                    bool aGrayed = false;
                    if (((SeedNotRecommendedToPick(aSeedType) || SeedNotAllowedToPick(aSeedType)) && aSeedState == SEED_IN_CHOOSER) || SeedNotAllowedDuringTrial(aSeedType))
                        aGrayed = true;

                    int aPosX = aChosenSeed.mX;
                    int aPosY = aChosenSeed.mY;
                    if (aSeedState == SEED_IN_BANK) {
                        int aSeedIndexInBank = aChosenSeed.mSeedIndexInBank;
                        int aChosenPlayerIndex = aChosenSeed.mChosenPlayerIndex;
                        GetSeedPositionInBank(aSeedIndexInBank, aPosX, aPosY, aChosenPlayerIndex);
                    } else {
                        GetSeedPositionInChooser(GetSeedPacketIndex(aSeedType), aPosX, aPosY);
                        if (aChooserPage == 0) {
                            continue;
                        }
                        if (aChooserPage == 1) {
                            if (aSeedType <= SEED_IMITATER)
                                continue;
                            else
                                aPosY -= 6 * SEED_PACKET_HEIGHT;
                        }
                    }
                    DrawPacket(g, aPosX, aPosY, aChosenSeed.mSeedType, aChosenSeed.mImitaterType, 0, aGrayed ? 115 : 255, &Color::White, true, true);
                }
            }

            if (mImitaterButton) {
                g->mTransX += mImitaterButton->mX;
                g->mTransY += mImitaterButton->mY;
                mImitaterButton->Draw(g);
                g->mTransX -= mImitaterButton->mX;
                g->mTransY -= mImitaterButton->mY;
            }

            for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = SeedType(aSeedType + 1)) {
                ChosenSeed &aChosenSeed = mChosenSeeds[GetSeedPacketIndex(aSeedType)];
                ChosenSeedState aSeedState = aChosenSeed.mSeedState;
                if (aSeedType == SeedType::SEED_IMITATER || aSeedType == SeedType::NUM_SEEDS_IN_CHOOSER)
                    continue;

                if (HasPacket(aSeedType, mIsZombieChooser) && (aSeedState == SEED_FLYING_TO_BANK || aSeedState == SEED_FLYING_TO_CHOOSER)) {
                    DrawPacket(g, aChosenSeed.mX, aChosenSeed.mY, aChosenSeed.mSeedType, aChosenSeed.mImitaterType, 0, 255, &Color::White, true, true);
                }
            }
        }

        int aGamepadIndex = mApp->PlayerToGamepadIndex(mPlayerIndex);
        int aCursorPositionX = (aGamepadIndex == 1) ? mCursorPositionX2 : mCursorPositionX1;
        int aCursorPositionY = (aGamepadIndex == 1) ? mCursorPositionY2 : mCursorPositionY1;
        for (int i = 0; i != 2; ++i) {
            int v50 = *(int *)(mBoard->unknownMembers3[i + 7] + 152);
            if (v50 != -1 && !unkMems3[3]) {
                if (v50 == mPlayerIndex || !mApp->IsVSMode()) {
                    Image *aSeedSelectorImage = (v50 == mApp->mTwoPlayerState) ? *Sexy::IMAGE_SEED_SELECTOR_BLUE : *Sexy::IMAGE_SEED_SELECTOR;
                    g->DrawImage(aSeedSelectorImage, aCursorPositionX - 8, aCursorPositionY - 4, 64, 85);
                }
            }
        }

        for (int i = 0; i != 2; ++i) {
            if (ShouldDisplayCursor(i) && *(int *)(mBoard->unknownMembers3[i + 7] + 152) != -1) {
                Image *aCursorArrowImage = (i == 1) ? *Sexy::IMAGE_CURSOR_ARROW_P2 : *Sexy::IMAGE_CURSOR_ARROW_P1;
                Image *aCursorTextImage = (i == 1) ? *Sexy::IMAGE_CURSOR_P2_TEXT : *Sexy::IMAGE_CURSOR_P1_TEXT;
                float v57 = sinf(unkF * 5.0);
                g->DrawImageF(aCursorArrowImage, (float)(aCursorPositionX + 25 - *((int *)aCursorArrowImage + 9) / 2), (float)(v57 + v57) + (float)(aCursorPositionY - 8));
                g->DrawImageF(aCursorTextImage, (float)(aCursorPositionX + 25 - *((int *)aCursorTextImage + 9) / 2), (float)(aCursorPositionY - 32));
            }
        }

        mToolTip1->Draw(g);
        mToolTip2->Draw(g);

        if (mStartButton) {
            g->Translate(mStartButton->mX, mStartButton->mY);
            mStartButton->Draw(g);
            g->Translate(-mStartButton->mX, -mStartButton->mY);
        }
        if (mViewLawnButton) {
            g->Translate(mViewLawnButton->mX, mViewLawnButton->mY);
            mViewLawnButton->Draw(g);
            g->Translate(-mViewLawnButton->mX, -mViewLawnButton->mY);
        }
        if (mAlmanacButton) {
            g->Translate(mAlmanacButton->mX, mAlmanacButton->mY);
            mAlmanacButton->Draw(g);
            g->Translate(-mAlmanacButton->mX, -mAlmanacButton->mY);
        }
        if (mStoreButton) {
            g->Translate(mStoreButton->mX, mStoreButton->mY);
            mStoreButton->Draw(g);
            g->Translate(-mStoreButton->mX, -mStoreButton->mY);
        }
    } else {
        old_SeedChooserScreen_Draw(this, g);
    }

    if (gVSSetupWidget) {
        if (gVSSetupWidget->mBanMode) {
            Graphics aBanGraphics(*g);
            aBanGraphics.mTransX = 0;
            aBanGraphics.mTransY = 0;
            aBanGraphics.SetColor(Color(205, 0, 0, 255));
            aBanGraphics.SetFont(*Sexy_FONT_DWARVENTODCRAFT18_Addr);
            aBanGraphics.DrawString("禁            用                            阶            段", 440, 110);
        }

        for (int i = 0; i < NUM_ZOMBIE_SEED_TYPES; i++) {
            if (gVSSetupWidget->mBannedSeed[i].mSeedState == BannedSeedState::SEED_BANNED) {
                if ((mIsZombieChooser && gVSSetupWidget->mBannedSeed[i].mChosenPlayerIndex == 1) || (!mIsZombieChooser && gVSSetupWidget->mBannedSeed[i].mChosenPlayerIndex == 0)) {
                    int x = gVSSetupWidget->mBannedSeed[i].mX;
                    int y = gVSSetupWidget->mBannedSeed[i].mY;
                    int aChooserPage = GetPage();
                    if ((aChooserPage == 0 && gVSSetupWidget->mBannedSeed[i].mSeedType >= SeedType::SEED_ZOMBIE_SUNFLOWER_HEAD)
                        || (aChooserPage == 1 && gVSSetupWidget->mBannedSeed[i].mSeedType < SeedType::SEED_ZOMBIE_SUNFLOWER_HEAD))
                        continue;
                    g->DrawImage(*IMAGE_MP_TARGETS_X, x + 5, y + 5);
                }
            }
        }
    }
}

SeedType SeedChooserScreen::SeedHitTest(int x, int y) {
    //    if (mMouseVisible && GetPage() == 1) {
    //        for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1)) {
    //            ChosenSeed &aChosenSeed = mChosenSeeds[aSeedType];
    //            ChosenSeedState aSeedState = aChosenSeed.mSeedState;
    //            if (aSeedState == SEED_IN_BANK && Rect(aChosenSeed.mX, aChosenSeed.mY, SEED_PACKET_WIDTH, SEED_PACKET_HEIGHT).Contains(x, y))
    //                return aSeedType;
    //        }
    //        for (SeedType aSeedType = SEED_EXPLODE_O_NUT; aSeedType < NUM_SEED_TYPES; aSeedType = (SeedType)(aSeedType + 1)) {
    //            ChosenSeed &aChosenSeed = mChosenSeeds[aSeedType];
    //            if (Rect(aChosenSeed.mX, aChosenSeed.mY, SEED_PACKET_WIDTH, SEED_PACKET_HEIGHT).Contains(x, y)) {
    //                return aSeedType;
    //            }
    //        }
    //    }

    int aSeed;                // r4
    int mX;                   // r3
    int mY;                   // r2
    SeedType aSeedType;       // r6
    SeedType aZombieSeedType; // r0
    int aX;                   // [sp+0h] [bp-30h] BYREF
    int aY;                   // [sp+4h] [bp-2Ch] BYREF

    aSeed = 0;
    if (!mMouseVisible)
        return SEED_NONE;
    while (1) {
        aSeedType = SeedType(aSeed);
        if (mIsZombieChooser) {
            aZombieSeedType = GetZombieSeedType(SeedType(aSeed));
            aSeedType = aZombieSeedType;
        }
        if (HasPacket(aSeedType, mIsZombieChooser) && mChosenSeeds[GetSeedPacketIndex(aSeed)].mSeedState != SEED_PACKET_HIDDEN) {
            GetSeedPositionInChooser(aSeed, aX, aY);
            mX = mChosenSeeds[GetSeedPacketIndex(aSeed)].mX;
            if (mX <= x) {
                mY = mChosenSeeds[GetSeedPacketIndex(aSeed)].mY;
                if (mY <= y && x <= mX + 49 && y <= mY + 69)
                    break;
            }
            if (x >= aX && y >= aY && x <= aX + 49 && y <= aY + 69)
                break;
        }
        ++aSeed;
        if (aSeed == NUM_SEEDS_IN_CHOOSER)
            return SEED_NONE;
    }

    int aSeedTypeOffset = 0;
    if (mIsZombieChooser) {
        int aChooserPage = GetPage();
        if (aChooserPage == 1) {
            aSeedTypeOffset += 30;
        }
    } else {
        int aChooserPage = GetPage();
        if (aChooserPage == 1) {
            aSeedTypeOffset += (SEED_IMITATER + 2);
        }
    }
    aSeedType = SeedType(aSeedType + aSeedTypeOffset);
    LOG_DEBUG("aSeedType: {}", (int)aSeedType);
    return aSeedType;
}

bool SeedChooserScreen::PickedPlantType(SeedType theSeedType) {
    for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1)) {
        ChosenSeed &aChosenSeed = mChosenSeeds[aSeedType];
        if (aChosenSeed.mSeedState == SEED_IN_BANK) {
            if (aChosenSeed.mSeedType == theSeedType || (aChosenSeed.mSeedType == SEED_IMITATER && aChosenSeed.mImitaterType == theSeedType)) {
                return true;
            }
        }
    }
    return false;
}

void SeedChooserScreen::UpdateAfterPurchase() {
    for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1)) {
        ChosenSeed &aChosenSeed = mChosenSeeds[aSeedType];
        if (aChosenSeed.mSeedState == SEED_IN_BANK)
            GetSeedPositionInBank(aChosenSeed.mSeedIndexInBank, aChosenSeed.mX, aChosenSeed.mY, mPlayerIndex);
        else if (aChosenSeed.mSeedState == SEED_IN_CHOOSER)
            GetSeedPositionInChooser(aSeedType, aChosenSeed.mX, aChosenSeed.mY);
        else
            continue;
        aChosenSeed.mStartX = aChosenSeed.mX;
        aChosenSeed.mStartY = aChosenSeed.mY;
        aChosenSeed.mEndX = aChosenSeed.mX;
        aChosenSeed.mEndY = aChosenSeed.mY;
    }
    if (mSeedsInBothBank == mSeedBank1->mNumPackets || mApp->IsCoopMode() && mSeedsInBothBank == mSeedBank2->mNumPackets + mSeedBank1->mNumPackets) {
        EnableStartButton(true);
        UpdateImitaterButton();
    } else {
        EnableStartButton(false);
        UpdateImitaterButton();
    }
}

int SeedChooserScreen::GetPage() {
    if (!gMoreSeedType)
        return 0;

    SeedChooserPage *aChooserPage = mIsZombieChooser ? gZombieChooserPage : gPlantChooserPage;
    int aPage = aChooserPage->GetPage();
    return aPage;
}