#include "PvZ/Lawn/Widget/MailScreen.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics/Graphics.h"
#include "PvZ/SexyAppFramework/Misc/KeyCodes.h"
#include "PvZ/SexyAppFramework/Widget/GameButton.h"
#include "PvZ/Symbols.h"

namespace {
Sexy::GameButton *mMailScreenCloseButton;
Sexy::GameButton *mMailScreenReadButton;
Sexy::GameButton *mMailScreenSwitchButton;
} // namespace

MailScreen::MailScreen(LawnApp *theApp) {
    Create(theApp);
}

void MailScreen::Create(LawnApp *theApp) {
    // 修复MailScreen的可触控区域不为全屏。
    old_MailScreen_MailScreen(this, theApp);

    int holder2[1];
    TodStringTranslate(holder2, "[MARK_MESSAGE_READ]");
    mMailScreenReadButton = MakeButton(1002, &mButtonListener, this, holder2);
    GameButton_Resize(mMailScreenReadButton, -150, 450, 170, 80);
    Sexy_String_Delete(holder2);
    Sexy_Widget_AddWidget(this, (Sexy::Widget*)mMailScreenReadButton);

    int holder1[1];
    TodStringTranslate(holder1, "[GO_TO_READ_MAIL]");
    mMailScreenSwitchButton = MakeButton(1001, &mButtonListener, this, holder1);
    GameButton_Resize(mMailScreenSwitchButton, -150, 520, 170, 80);
    Sexy_String_Delete(holder1);
    Sexy_Widget_AddWidget(this, (Sexy::Widget*)mMailScreenSwitchButton);


    int holder[1];
    TodStringTranslate(holder, "[CLOSE]");
    mMailScreenCloseButton = MakeButton(1000, &mButtonListener, this, holder);
    GameButton_Resize(mMailScreenCloseButton, 800, 520, 170, 80);
    Sexy_String_Delete(holder);
    Sexy_Widget_AddWidget(this, (Sexy::Widget*)mMailScreenCloseButton);

    Sexy_Widget_Resize(this, 0, 0, 800, 600);
}

void MailScreen::AddedToManager(int *theWidgetManager) {
    old_MailScreen_AddedToManager(this, theWidgetManager);
    //    Sexy_Widget_Resize(mailScreen, -240, -60, 1280, 720);
}

void MailScreen::RemovedFromManager(int *widgetManager) {
    // 修复MailScreen的可触控区域不为全屏
    Sexy_Widget_RemoveWidget(this, (Sexy::Widget*)mMailScreenCloseButton);
    Sexy_Widget_RemoveWidget(this, (Sexy::Widget*)mMailScreenReadButton);
    Sexy_Widget_RemoveWidget(this, (Sexy::Widget*)mMailScreenSwitchButton);

    old_MailScreen_RemovedFromManager(this, widgetManager);
}

void MailScreen::Delete2() {
    old_MailScreen_Delete2(this);

    GameButton_Delete(mMailScreenCloseButton);
    mMailScreenCloseButton = nullptr;
    GameButton_Delete(mMailScreenReadButton);
    mMailScreenReadButton = nullptr;
    GameButton_Delete(mMailScreenSwitchButton);
    mMailScreenSwitchButton = nullptr;
}

void MailScreen::ButtonPress(int theId) {
    old_MailScreen_ButtonPress(this, theId);
}

void MailScreen::ButtonDepress(int theId) {
    mApp = (LawnApp *)*gLawnApp_Addr;
    MailScreen *aRealMailScreen = (MailScreen *)mApp->GetDialog(Dialogs::DIALOG_MAIL);
    if (theId == 1002) {
        aRealMailScreen->KeyDown(Sexy::KEYCODE_ACCEPT, 0, 0);
    } else if (theId == 1001) {
        aRealMailScreen->KeyDown(307, 0, 0);
        bool isAtInBox = aRealMailScreen->mPage == 0;
        mMailScreenReadButton->mDisabled = !isAtInBox;
        mMailScreenReadButton->mBtnNoDraw = !isAtInBox;
        int holder[1];
        TodStringTranslate(holder, isAtInBox ? "[GO_TO_READ_MAIL]" : "[GO_TO_INBOX]");
        GameButton_SetLabel(mMailScreenSwitchButton, holder);
        Sexy_String_Delete(holder);
    } else
        old_MailScreen_ButtonDepress(this, theId);
}


namespace {
constexpr int mMailTrigger = 20;
int mMailTouchDownX;
int mMailTouchDownY;
} // namespace

void MailScreen::MouseDown(int x, int y, int theClickCount) {
    mMailTouchDownX = x;
    mMailTouchDownY = y;
}

void MailScreen::MouseDrag(int x, int y) {}

void MailScreen::MouseUp(int x, int y) {
    if (mMailTouchDownX - x > mMailTrigger) {
        KeyDown(39, 0, 0);
    } else if (x - mMailTouchDownX > mMailTrigger) {
        KeyDown(37, 0, 0);
    } else if (mMailTouchDownX < 400) {
        KeyDown(37, 0, 0);
    } else {
        KeyDown(39, 0, 0);
    }
}
