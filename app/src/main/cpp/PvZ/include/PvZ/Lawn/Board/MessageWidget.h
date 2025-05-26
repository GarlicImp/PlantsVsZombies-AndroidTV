//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_MESSAGEWIDGET_H
#define PLANTSVSZOMBIES_ANDROIDTV_MESSAGEWIDGET_H

#include "PvZ//SexyAppFramework/Misc/Common.h"
#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/SexyAppFramework/Graphics/Image.h"

#define MAX_MESSAGE_LENGTH 128
#define MAX_REANIM_LINES 5

class LawnApp;
namespace Sexy
{
class Font;
class Graphics;
}

class MessageWidget {
public:
    int *vTable;                     // 0
    int unk[3];                      // 1 ~ 3
    LawnApp *mApp;                   // 4
    char mLabel[128];                // 5 ~ 36
    int mDisplayTime;                // 37
    int mDuration;                   // 38
    MessageStyle mMessageStyle;      // 39
    Reanimation *mTextReanimID[MAX_MESSAGE_LENGTH]; // 40 ~ 167
    ReanimationType mReanimType;     // 168
    int mSlideOffTime;               // 169
    float unkFloatWithInitValue1;    // 170
    char mLabelNext[MAX_MESSAGE_LENGTH];            // 171 ~ 202
    MessageStyle mMessageStyleNext;  // 203
}; // 大小204个整数

class CustomMessageWidget : public MessageWidget {
public:
    Sexy::Image *mIcon; // 204
}; // 大小205个整数


#endif // PLANTSVSZOMBIES_ANDROIDTV_MESSAGEWIDGET_H
