#include "PvZ/Lawn/HelpTextScreen.h"
#include "PvZ/Enums.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Symbols.h"

namespace {
constexpr int nextPageButtonX = 836;
constexpr int nextPageButtonY = 318;

constexpr int prevPageButtonX = 2540;
constexpr int prevPageButtonY = 318;

Sexy::GameButton *mHelpTextScreenCloseButton;
} // namespace


void HelpTextScreen_Update(Sexy::Widget *helpTextScreen) {
    if (mHelpTextScreenCloseButton == nullptr) {
        int holder[1];
        TodStringTranslate(holder, "[CLOSE]");
        mHelpTextScreenCloseButton = MakeButton(1000, (Sexy::ButtonListener *)helpTextScreen + 64, helpTextScreen, holder);
        Sexy_String_Delete(holder);
        Sexy_Widget_AddWidget(helpTextScreen, mHelpTextScreenCloseButton);
    }
    GameButton_Resize(mHelpTextScreenCloseButton, 650 - helpTextScreen->mX, 540 - helpTextScreen->mY, 170, 50);
    old_HelpTextScreen_Update(helpTextScreen);
}

void HelpTextScreen_Draw(Sexy::Widget *helpTextScreen, Sexy::Graphics *graphics) {
    old_HelpTextScreen_Draw(helpTextScreen, graphics);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ZEN_NEXTGARDEN_Addr, nextPageButtonX, nextPageButtonY);
    Sexy_Graphics_DrawImageMirror(graphics, *Sexy_IMAGE_ZEN_NEXTGARDEN_Addr, prevPageButtonX, prevPageButtonY, true);
}

void HelpTextScreen_HelpTextScreen(Sexy::Widget *helpTextScreen, int *lawnApp, int pageIndex) {
    old_HelpTextScreen_HelpTextScreen(helpTextScreen, lawnApp, pageIndex);
    // 这个HelpTextScreen是全屏的，但触控事件并不会分发到此处，而是发给子控件。只有内容外侧的点击事件才能收到。

    Sexy_Widget_Resize(helpTextScreen, helpTextScreen->mX, helpTextScreen->mY, 3000, helpTextScreen->mHeight);
}

void HelpTextScreen_AddedToManager(Sexy::Widget *helpTextScreen, int *manager) {
    // 创建按钮
    old_HelpTextScreen_AddedToManager(helpTextScreen, manager);
}

void HelpTextScreen_MouseDown(Sexy::Widget *helpTextScreen, int x, int y, int theClickCount) {
    //    LOGD("D%d %d", x, y);
    //    prevPageButtonX = x;
    //    prevPageButtonY = y;

    int imageWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_ZEN_NEXTGARDEN_Addr);
    int imageHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_ZEN_NEXTGARDEN_Addr);

    Sexy::Rect nextPageRect = {nextPageButtonX, nextPageButtonY, imageWidth, imageHeight};
    if (TRect_Contains(&nextPageRect, x, y)) {
        HelpTextScreen_KeyDown(helpTextScreen, 39);
        return;
    }

    Sexy::Rect prevPageRect = {prevPageButtonX, prevPageButtonY, imageWidth, imageHeight};
    if (TRect_Contains(&prevPageRect, x, y)) {
        HelpTextScreen_KeyDown(helpTextScreen, 37);
        return;
    }
}

void HelpTextScreen_RemovedFromManager(Sexy::Widget *helpTextScreen, int *widgetManager) {
    // 修复MailScreen的可触控区域不为全屏
    if (mHelpTextScreenCloseButton != nullptr) {
        Sexy_Widget_RemoveWidget(helpTextScreen, mHelpTextScreenCloseButton);
    }
    old_HelpTextScreen_RemovedFromManager(helpTextScreen, widgetManager);
}

void HelpTextScreen_Delete2(Sexy::Widget *helpTextScreen) {
    old_HelpTextScreen_Delete2(helpTextScreen);
    if (mHelpTextScreenCloseButton != nullptr) {
        GameButton_Delete(mHelpTextScreenCloseButton);
        mHelpTextScreenCloseButton = nullptr;
    }
}

void HelpTextScreen_ButtonDepress(Sexy::Widget *helpTextScreen, int id) {
    if (id == 1000) {
        LawnApp_KillHelpTextScreen((LawnApp *)*gLawnApp_Addr);
    } else
        return old_HelpTextScreen_ButtonDepress(helpTextScreen, id);
}
