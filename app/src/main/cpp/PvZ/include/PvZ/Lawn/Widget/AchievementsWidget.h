//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_ACHIEVEMENTSWIDGET_H
#define PLANTSVSZOMBIES_ANDROIDTV_ACHIEVEMENTSWIDGET_H

#include "PvZ/SexyAppFramework/Widget/ButtonListener.h"
#include "PvZ/SexyAppFramework/Widget/Widget.h"

class AchievementsWidget : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener; // 64
    LawnApp *mApp;                        // 65
    int mMouseDownY;
    int mLastDownY;
    int mLastDownY1;
    long mLastTimeMs;
    long mLastTimeMs1;
    float mVelocity;
    float mAccY;
    bool mIsScrolling;
}; // 我想用AchievementsWidget取代MaskHelpWidget。MaskHelpWidget的大小是66个整数。


#endif // PLANTSVSZOMBIES_ANDROIDTV_ACHIEVEMENTSWIDGET_H
