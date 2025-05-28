#include "PvZ/Lawn/Widget/SettingsDialog.h"
#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics/Graphics.h"
#include "PvZ/SexyAppFramework/Widget/GameButton.h"
#include "PvZ/Symbols.h"

using namespace Sexy;

namespace {
Sexy::Checkbox *m3DAccleratedCheckbox;
Sexy::Checkbox *mVibrateCheckbox;
} // namespace


void SettingsDialog_AddedToManager(SettingsDialog *settingsDialog, int *manager) {
    old_SettingsDialog_AddedToManager(settingsDialog, manager);
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    Sexy::Widget *mSoundSlider = settingsDialog->mSoundSlider;
    Sexy::Widget *mBackButton = settingsDialog->mBackButton;


    m3DAccleratedCheckbox = MakeNewCheckbox(1024, &settingsDialog->mCheckboxListener, settingsDialog, Sexy_SexyAppBase_Is3DAccelerated(lawnApp));
    mVibrateCheckbox = MakeNewCheckbox(1025, &settingsDialog->mCheckboxListener, settingsDialog, !lawnApp->mPlayerInfo->mIsVibrateClosed);

    Sexy_Widget_Resize(m3DAccleratedCheckbox, 80, 260, 300, 50);
    Sexy_Widget_Resize(mVibrateCheckbox, 80, 320, 300, 50);

    Sexy_Widget_AddWidget(settingsDialog, m3DAccleratedCheckbox);
    Sexy_Widget_AddWidget(settingsDialog, mVibrateCheckbox);

    mSoundSlider->mFocusLinks[1] = m3DAccleratedCheckbox;
    m3DAccleratedCheckbox->mFocusLinks[1] = mVibrateCheckbox;
    mVibrateCheckbox->mFocusLinks[1] = mBackButton;

    mBackButton->mFocusLinks[0] = mVibrateCheckbox;
    mVibrateCheckbox->mFocusLinks[0] = m3DAccleratedCheckbox;
    m3DAccleratedCheckbox->mFocusLinks[0] = mSoundSlider;
}

void SettingsDialog_RemovedFromManager(SettingsDialog *settingsDialog, int *manager) {
    old_SettingsDialog_RemovedFromManager(settingsDialog, manager);
    Sexy_Widget_RemoveWidget(settingsDialog, m3DAccleratedCheckbox);
    Sexy_Widget_RemoveWidget(settingsDialog, mVibrateCheckbox);
}

void SettingsDialog_Delete2(SettingsDialog *settingsDialog) {
    old_SettingsDialog_Delete2(settingsDialog);
    //    Sexy_Checkbox_Delete(m3DAccleratedCheckbox); // 在安卓4.2上，这么Delete会闪退
    (*((void (**)(Sexy::Widget *))m3DAccleratedCheckbox->vTable + 1))(m3DAccleratedCheckbox); // Delete() ，用这种方式Delete在安卓4.2上就不会闪退，虽然我也不知道为什么会这样
    m3DAccleratedCheckbox = nullptr;
    (*((void (**)(Sexy::Widget *))mVibrateCheckbox->vTable + 1))(mVibrateCheckbox); // Delete() ，用这种方式Delete在安卓4.2上就不会闪退，虽然我也不知道为什么会这样
    mVibrateCheckbox = nullptr;
}

void SettingsDialog_Draw(SettingsDialog *settingsDialog, Sexy::Graphics *g) {
    old_SettingsDialog_Draw(settingsDialog, g);

    Color color = {107, 110, 145, 255};
    if (settingsDialog->mFocusedChildWidget == m3DAccleratedCheckbox) {
        color.mRed = 0;
        color.mGreen = 255;
        color.mBlue = 0;
        color.mAlpha = 255;
    }
    int holder[1];
    g->SetFont(*Sexy_FONT_DWARVENTODCRAFT18_Addr);
    g->SetColor(color);
    TodStringTranslate((int*)holder, "[OPTIONS_3D_ACCELERATION]");
    g->DrawString((SexyString&)holder, m3DAccleratedCheckbox->mX + 80, m3DAccleratedCheckbox->mY + 20);
    Sexy_String_Delete((int*)holder);

    Color color1 = {107, 110, 145, 255};
    if (settingsDialog->mFocusedChildWidget == mVibrateCheckbox) {
        color1.mRed = 0;
        color1.mGreen = 255;
        color1.mBlue = 0;
        color1.mAlpha = 255;
    }
    int holder1[1];
    g->SetFont(*Sexy_FONT_DWARVENTODCRAFT18_Addr);
    g->SetColor(color1);
    TodStringTranslate((int*)holder1, "[OPTIONS_VIBRATE]");
    g->DrawString((SexyString&)holder1, mVibrateCheckbox->mX + 80, mVibrateCheckbox->mY + 20);
    Sexy_String_Delete((int*)holder1);
}

void SettingsDialog_CheckboxChecked(SettingsDialog *settingsDialog, int id, bool isChecked) {
    switch (id) {
        case 1024: {
            LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
            Sexy_SexyAppBase_Set3DAccelerated(lawnApp, isChecked);
        } break;
        case 1025: {
            LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
            lawnApp->mPlayerInfo->mIsVibrateClosed = !isChecked;
        } break;
    }
}
