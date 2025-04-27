#include "PvZ/Symbols.h"
#include "PvZ/Lawn/AwardScreen.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"

void AwardScreen_MouseDown(int *awardScreen, int x, int y, int theClickCount) {
    Sexy::GameButton *gameButton = *((Sexy::GameButton **)awardScreen + 65);
    Sexy::Rect rect = {gameButton->mX, gameButton->mY, gameButton->mWidth, gameButton->mHeight};
    if (TRect_Contains(&rect, x, y)) {
        LawnApp_PlaySample((LawnApp *)awardScreen[67], *Sexy_SOUND_TAP_Addr);
    }
}

void AwardScreen_MouseUp(int *awardScreen, int x, int y, int theClickCount) {
    Sexy::GameButton *gameButton = *((Sexy::GameButton **)awardScreen + 65);
    Sexy::Rect rect = {gameButton->mX, gameButton->mY, gameButton->mWidth, gameButton->mHeight};
    if (TRect_Contains(&rect, x, y)) {
        AwardScreen_StartButtonPressed(awardScreen);
    }
}
