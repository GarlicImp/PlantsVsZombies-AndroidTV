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

#include "PvZ/Lawn/Widget/VSSetupMenu.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board/SeedBank.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Widget/WaitForSecondPlayerDialog.h"

using namespace Sexy;

VSSetupWidget::VSSetupWidget() {
    mApp = reinterpret_cast<LawnApp *>(*gLawnApp_Addr);
    mBoard = mApp->mBoard;
    mPlayerInfo = mApp->mPlayerInfo;
    mMoreSeedsButton = nullptr;
    mMorePacketsButton = nullptr;
    mCheckboxImage = nullptr;
    mCheckboxImagePress = nullptr;
    mDrawString = false;
}

VSSetupWidget::~VSSetupWidget() {
    //    gVSMoreSeedsButton->mMoreSeedsButton->__Destructor(); // 析构Button导致崩溃故采用禁用按钮
    gVSMoreSeedsButton->mMoreSeedsButton->mBtnNoDraw = true;
    gVSMoreSeedsButton->mMoreSeedsButton->mDisabled = true;
    gVSMoreSeedsButton->mDrawString = false;
    //    gVSMoreSeedsButton = nullptr;

    gVSMorePacketsButton->mMorePacketsButton->mBtnNoDraw = true;
    gVSMorePacketsButton->mMorePacketsButton->mDisabled = true;
    gVSMorePacketsButton->mDrawString = false;
}

void VSSetupWidget::ButtonDepress(this VSSetupWidget &self, int theId) {
    if (theId == 1145) {
        self.CheckboxChecked(1145, self.mPlayerInfo->mIsVSMoreSeeds);
        std::swap(gVSMoreSeedsButton->mCheckboxImage, gVSMoreSeedsButton->mCheckboxImagePress);
        ButtonWidget *aButton = gVSMoreSeedsButton->mMoreSeedsButton;
        aButton->mButtonImage = gVSMoreSeedsButton->mCheckboxImage;
        aButton->mOverImage = gVSMoreSeedsButton->mCheckboxImage;
        aButton->mDownImage = gVSMoreSeedsButton->mCheckboxImage;
    } else if (theId == 1146) {
        self.CheckboxChecked(1146, self.mPlayerInfo->mIsVSMorePackets);
        std::swap(gVSMorePacketsButton->mCheckboxImage, gVSMorePacketsButton->mCheckboxImagePress);
        ButtonWidget *aButton = gVSMorePacketsButton->mMorePacketsButton;
        aButton->mButtonImage = gVSMorePacketsButton->mCheckboxImage;
        aButton->mOverImage = gVSMorePacketsButton->mCheckboxImage;
        aButton->mDownImage = gVSMorePacketsButton->mCheckboxImage;
    }
}

void VSSetupWidget::CheckboxChecked(int theId, bool checked) {
    switch (theId) {
        case 1145:
            mPlayerInfo->mIsVSMoreSeeds = !checked;
            break;
        case 1146:
            mPlayerInfo->mIsVSMorePackets = !checked;
            break;
        default:
            break;
    }
}

void VSSetupMenu::__Constructor() {
    old_VSSetupMenu_Constructor(this);

    bool aIsMoreSeeds = mApp->mPlayerInfo->mIsVSMoreSeeds;
    bool aIsMorePackets = mApp->mPlayerInfo->mIsVSMorePackets;
    Image *aCheckbox = *Sexy_IMAGE_OPTIONS_CHECKBOX0_Addr;
    Image *aCheckboxPressed = *Sexy_IMAGE_OPTIONS_CHECKBOX1_Addr;
    pvzstl::string str = StrFormat("");
    // 拓展僵尸选卡
    gVSMoreSeedsButton = new VSSetupWidget;
    Image *aMoreSeedsCheckbox = (aIsMoreSeeds == false) ? aCheckbox : aCheckboxPressed;
    ButtonWidget *aMoreSeedsButton = MakeNewButton(1145, &mButtonListener, this, str, nullptr, aMoreSeedsCheckbox, aMoreSeedsCheckbox, aMoreSeedsCheckbox);
    gVSMoreSeedsButton->mMoreSeedsButton = aMoreSeedsButton;
    gVSMoreSeedsButton->mCheckboxImage = aMoreSeedsCheckbox;
    gVSMoreSeedsButton->mCheckboxImagePress = (aIsMoreSeeds == true) ? aCheckbox : aCheckboxPressed;
    aMoreSeedsButton->Resize(MORE_SEEDS_BUTTON_X, MORE_SEEDS_BUTTON_Y, 175, 50);
    mApp->mBoard->AddWidget(aMoreSeedsButton);
    // 拓展卡槽
    gVSMorePacketsButton = new VSSetupWidget;
    Image *aMorePacketsCheckbox = (aIsMorePackets == false) ? aCheckbox : aCheckboxPressed;
    ButtonWidget *aMorePacketsButton = MakeNewButton(1146, &mButtonListener, this, str, nullptr, aMorePacketsCheckbox, aMorePacketsCheckbox, aMorePacketsCheckbox);
    gVSMorePacketsButton->mMorePacketsButton = aMorePacketsButton;
    gVSMorePacketsButton->mCheckboxImage = aMorePacketsCheckbox;
    gVSMorePacketsButton->mCheckboxImagePress = (aIsMorePackets == true) ? aCheckbox : aCheckboxPressed;
    aMorePacketsButton->Resize(MORE_PACKETS_BUTTON_X, MORE_PACKETS_BUTTON_Y, 175, 50);
    mApp->mBoard->AddWidget(aMorePacketsButton);

    gVSMoreSeedsButton->mDrawString = true;
}

void VSSetupMenu::__Destructor() {
    old_VSSetupMenu_Destructor(this);

    gVSMoreSeedsButton->~VSSetupWidget();
}

void VSSetupMenu::Draw(Graphics *g) {
    old_VSSetupMenu_Draw(this, g);
}

void VSSetupMenu::Update() {
    // 记录当前游戏状态
    if (mState == 1) {
        // 自动分配阵营
        GameButtonDown(18, 0, 0);
        GameButtonDown(19, 1, 0);
        GameButtonDown(6, 0, 0);
        GameButtonDown(6, 1, 0);
    }

    old_VSSetupMenu_Update(this);
}

void VSSetupMenu::KeyDown(Sexy::KeyCode theKey) {
    // 修复在对战的阵营选取界面无法按返回键退出的BUG。
    if (theKey == Sexy::KeyCode::KEYCODE_ESCAPE) {
        switch (mState) {
            case 1:
            case 2:
                mApp->DoBackToMain();
                return;
            case 3:
                mApp->DoNewOptions(false, 0);
                return;
        }
    }

    old_VSSetupMenu_KeyDown(this, theKey);
}

void VSSetupMenu::OnStateEnter(int theState) {
    if (theState == 0) {
        mInt76 = -1;
        // TODO:修复 WaitForSecondPlayerDialog重复构造
        auto *aWaitDialog = new WaitForSecondPlayerDialog(mApp);
        //        mApp->AddDialog(aWaitDialog); // 生成了两份mLawnNoButton

        int buttonId = ((int (*)(WaitForSecondPlayerDialog *, bool))aWaitDialog->vTable[127])(aWaitDialog, true);
        if (buttonId == 1000) {
            SetSecondPlayerIndex(mApp->mTwoPlayerState);
            GoToState(1);
        } else if (buttonId == 1001) {
            CloseVSSetup(1);
            mApp->KillBoard();
            mApp->ShowGameSelector();
        } else {
            // TODO：联机
        }
        return;
    }

    old_VSSetupMenu_OnStateEnter(this, theState);
}

void VSSetupMenu::ButtonPress(int theId) {
    old_VSSetupMenu_ButtonPress(this, theId);
}

void VSSetupMenu::ButtonDepress(int theId) {
    old_VSSetupMenu_ButtonDepress(this, theId);

    // 对战额外卡槽
    int aNumPackets = mApp->mBoard->GetNumSeedsInBank(false);
    mApp->mBoard->mSeedBank1->mNumPackets = aNumPackets;
    mApp->mBoard->mSeedBank2->mNumPackets = aNumPackets;

    mApp->mBoard->PickBackground(); // 修改器修改场地后开局立即更换

    switch (theId) {
        case 9: // 快速游戏
            break;
        case 10: // 自定义战场
            gVSMoreSeedsButton->~VSSetupWidget();
            break;
        case 11: // 随机战场
            break;
        case 1145: // 拓展僵尸选卡
            gVSMoreSeedsButton->ButtonDepress(1145);
            break;
        case 1146: // 额外卡槽
            gVSMorePacketsButton->ButtonDepress(1146);
            break;
        default:
            break;
    }
}