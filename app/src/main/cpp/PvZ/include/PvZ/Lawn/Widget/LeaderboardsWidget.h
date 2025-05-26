//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_LEADERBOARDSWIDGET_H
#define PLANTSVSZOMBIES_ANDROIDTV_LEADERBOARDSWIDGET_H

#include "PvZ/SexyAppFramework/Widget/ButtonListener.h"
#include "PvZ/SexyAppFramework/Widget/GameButton.h"
#include "PvZ/SexyAppFramework/Widget/Widget.h"
#include "TrashBin.h"

class LeaderboardsWidget : public Sexy::Widget {
public:
    LawnApp *mApp;                                     // 64
    TrashBin *mZombieTrashBin;                         // 65
    TrashBin *mPlantTrashBin;                          // 66
    bool mAchievements[12];                            // 67 ~ 69
    LeaderboardReanimations *mLeaderboardReanimations; // 70
    int mLongestRecordPool;                            // 71
    Sexy::GameButton *mBackButton;
    Sexy::ButtonListener *mButtonListener;
    int mFocusedAchievementIndex;
    bool mHighLightAchievement;
}; // 我想用LeaderboardsWidget取代DaveHelp。


#endif // PLANTSVSZOMBIES_ANDROIDTV_LEADERBOARDSWIDGET_H
