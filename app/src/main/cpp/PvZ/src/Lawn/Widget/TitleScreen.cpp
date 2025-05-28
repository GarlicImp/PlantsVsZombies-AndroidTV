#include "PvZ/Lawn/Widget/TitleScreen.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/SexyAppFramework/Graphics/Graphics.h"
#include "PvZ/Symbols.h"

void TitleScreen_Draw(TitleScreen *titleScreen, Sexy::Graphics *graphics) {
    old_TitleScreen_Draw(titleScreen, graphics);
    //    LOGD("%d",*Sexy_IMAGE_ESRB_RATING_Addr);
    //    if (*Sexy_IMAGE_ESRB_RATING_Addr)
    //    DrawImage(graphics,*Sexy_IMAGE_ESRB_RATING_Addr,0,0);
    //    LOGD("draw");
    //    int *q = nullptr;
    //    q[1] = 1;
}

void TitleScreen_Update(TitleScreen *titleScreen) {
    old_TitleScreen_Update(titleScreen);
    //    LOGD("Update");
    //    int *q = nullptr;
    //    q[1] = 1;
}

void TitleScreen_SwitchState(TitleScreen *titleScreen, TitleScreen::TitleState state, int duration) {
    if (state == TitleScreen::PopcapLogo_OR_IntroVideo && jumpLogo) {
        state = TitleScreen::Loading;
        duration = 0;
    }
    titleScreen->mTitleState = state;
    titleScreen->mTitleStateDuration = duration;
    titleScreen->mTitleStateCounter = duration;
}
