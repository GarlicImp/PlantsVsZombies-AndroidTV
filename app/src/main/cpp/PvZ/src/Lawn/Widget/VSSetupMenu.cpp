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
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Widget/WaitForSecondPlayerDialog.h"
#include "PvZ/SexyAppFramework/Widget/Checkbox.h"
#include "PvZ/SexyAppFramework/Widget/CheckboxListener.h"

using namespace Sexy;

void VSSetupMenu::__Constructor() {
    old_VSSetupMenu_VSSetupMenu(this);
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