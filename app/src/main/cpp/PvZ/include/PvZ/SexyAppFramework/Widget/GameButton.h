//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_GAMEBUTTON_H
#define PLANTSVSZOMBIES_ANDROIDTV_GAMEBUTTON_H

#include "DialogButton.h"

namespace Sexy {

class GameButton : public DialogButton {
public:
    int unkMems4[2];                // 210  ~ 211
    bool unkBool5;                  // 848
    int unkMems5[2];                // 213 ~ 214
    Image *mOverOverlayImage; // 215
    bool mDrawStoneButton;          // 864
    int unkMems6[13];               // 217 ~ 229
}; // 大小230个整数

}


#endif // PLANTSVSZOMBIES_ANDROIDTV_GAMEBUTTON_H
