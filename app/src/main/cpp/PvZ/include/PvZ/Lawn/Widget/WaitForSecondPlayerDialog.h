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

#ifndef PVZ_LAWN_WIDGET_WAIT_FOR_SECOND_PLAYER_DIALOG_H
#define PVZ_LAWN_WIDGET_WAIT_FOR_SECOND_PLAYER_DIALOG_H

#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/Widget/LawnDialog.h"
#include "PvZ/SexyAppFramework/Widget/GameButton.h"
#include "PvZ/Symbols.h"

class WaitForSecondPlayerDialog : public __LawnDialog {
public:
    bool m2PJoined;

    int *roomName1;
    int *roomName2;
    int *roomName3;
    int *roomName4;
    int *roomName5;
    int *roomName6;

    GameButton *mJoinButton;
    GameButton *mCreateButton;
    bool mIsCreatingRoom;
    // 115：192，111：194。自roomName1起的成员为我新增的成员，我Hook了构造函数调用方，为构造时分配了更多内存，因此可以为WaitForSecondPlayerDialog任意地新增成员。

    void GameButtonDown(ButtonCode theButton, unsigned int thePlayerIndex) {
        reinterpret_cast<void (*)(WaitForSecondPlayerDialog *, ButtonCode, unsigned int)>(WaitForSecondPlayerDialog_GameButtonDownAddr)(this, theButton, thePlayerIndex);
    }

    WaitForSecondPlayerDialog(LawnApp *theApp) {
        __Constructor(theApp);
    }
    ~WaitForSecondPlayerDialog() {
        __Destructor();
    }
    void Update();
    void Draw(Sexy::Graphics *g);
    void Resize(int theX, int theY, int theWidth, int theHeight);

protected:
    friend void InitHookFunction();

    void __Constructor(LawnApp *theApp);
    void __Destructor();
};

void WaitForSecondPlayerDialog_ButtonDepress(Sexy::ButtonListener *listener, int id);

inline void (*old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog)(WaitForSecondPlayerDialog *a, LawnApp *theApp);

inline void (*old_WaitForSecondPlayerDialog_Draw)(WaitForSecondPlayerDialog *dialog, Sexy::Graphics *graphics);

inline void (*old_WaitForSecondPlayerDialog_ButtonDepress)(Sexy::ButtonListener *listener, int id);

inline void (*old_WaitForSecondPlayerDialog_Delete)(WaitForSecondPlayerDialog *dialog);


#endif // PVZ_LAWN_WIDGET_WAIT_FOR_SECOND_PLAYER_DIALOG_H
