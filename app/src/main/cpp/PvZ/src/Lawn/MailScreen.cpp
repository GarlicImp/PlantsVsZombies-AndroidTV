#include "PvZ/Lawn/MailScreen.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/Lawn/LawnApp.h"

namespace {
Sexy::GameButton *mMailScreenCloseButton;
Sexy::GameButton *mMailScreenReadButton;
Sexy::GameButton *mMailScreenSwitchButton;
} // namespace


void MailScreen_MailScreen(MailScreen *mailScreen, LawnApp *lawnApp) {
    // 修复MailScreen的可触控区域不为全屏。
    old_MailScreen_MailScreen(mailScreen, lawnApp);
    int holder2[1];
    TodStringTranslate(holder2, "[MARK_MESSAGE_READ]");
    mMailScreenReadButton = MakeButton(1002, &mailScreen->mButtonListener, mailScreen, holder2);
    GameButton_Resize(mMailScreenReadButton, -150, 450, 170, 80);
    Sexy_String_Delete(holder2);
    Sexy_Widget_AddWidget(mailScreen, mMailScreenReadButton);

    int holder1[1];
    TodStringTranslate(holder1, "[GO_TO_READ_MAIL]");
    mMailScreenSwitchButton = MakeButton(1001, &mailScreen->mButtonListener, mailScreen, holder1);
    GameButton_Resize(mMailScreenSwitchButton, -150, 520, 170, 80);
    Sexy_String_Delete(holder1);
    Sexy_Widget_AddWidget(mailScreen, mMailScreenSwitchButton);


    int holder[1];
    TodStringTranslate(holder, "[CLOSE]");
    mMailScreenCloseButton = MakeButton(1000, &mailScreen->mButtonListener, mailScreen, holder);
    GameButton_Resize(mMailScreenCloseButton, 800, 520, 170, 80);
    Sexy_String_Delete(holder);
    Sexy_Widget_AddWidget(mailScreen, mMailScreenCloseButton);

    Sexy_Widget_Resize(mailScreen, 0, 0, 800, 600);
}

void MailScreen_AddedToManager(MailScreen *mailScreen, int *widgetManager) {
    old_MailScreen_AddedToManager(mailScreen, widgetManager);
    //    Sexy_Widget_Resize(mailScreen, -240, -60, 1280, 720);
}

void MailScreen_RemovedFromManager(MailScreen *mailScreen, int *widgetManager) {
    // 修复MailScreen的可触控区域不为全屏
    Sexy_Widget_RemoveWidget(mailScreen, mMailScreenCloseButton);
    Sexy_Widget_RemoveWidget(mailScreen, mMailScreenReadButton);
    Sexy_Widget_RemoveWidget(mailScreen, mMailScreenSwitchButton);
    old_MailScreen_RemovedFromManager(mailScreen, widgetManager);
}

void MailScreen_Delete2(MailScreen *mailScreen) {
    old_MailScreen_Delete2(mailScreen);
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
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    MailScreen *theRealMailScreen = (MailScreen *)Sexy_SexyAppBase_GetDialog(lawnApp, Dialogs::DIALOG_MAIL);
    if (theId == 1002) {
        MailScreen_KeyDown(theRealMailScreen, Sexy::Ok, 0, 0);
    } else if (theId == 1001) {
        MailScreen_KeyDown(theRealMailScreen, 307, 0, 0);
        bool isAtInBox = theRealMailScreen->mPage == 0;
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
        MailScreen_KeyDown(this, 39, 0, 0);
    } else if (x - mMailTouchDownX > mMailTrigger) {
        MailScreen_KeyDown(this, 37, 0, 0);
    } else if (mMailTouchDownX < 400) {
        MailScreen_KeyDown(this, 37, 0, 0);
    } else {
        MailScreen_KeyDown(this, 39, 0, 0);
    }
}
