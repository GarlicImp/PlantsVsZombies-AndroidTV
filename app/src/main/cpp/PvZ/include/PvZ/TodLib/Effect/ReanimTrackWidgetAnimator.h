//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_REANIMTRACKWIDGETANIMATOR_H
#define PLANTSVSZOMBIES_ANDROIDTV_REANIMTRACKWIDGETANIMATOR_H


#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/SexyAppFramework/Misc/WidgetAnimator.h"

class ReanimTrackWidgetAnimator : public Sexy::WidgetAnimator {
public:
    LawnApp *mApp;                 // 6
    Sexy::Widget *mLawnMenuWidget; // 7
    int *mTrackName1;              // 8
    int *mTrackName2;              // 9
    int *mTrackName3;              // 10
    int unk2[2];                   // 11 ~ 12
};

#endif // PLANTSVSZOMBIES_ANDROIDTV_REANIMTRACKWIDGETANIMATOR_H
