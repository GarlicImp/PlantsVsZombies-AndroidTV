//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_LEADERBOARDSWIDGET_H
#define PLANTSVSZOMBIES_ANDROIDTV_LEADERBOARDSWIDGET_H

#include "HouseChooserDialog.h"
#include "PvZ/SexyAppFramework/Widget/ButtonListener.h"
#include "PvZ/SexyAppFramework/Widget/GameButton.h"
#include "PvZ/SexyAppFramework/Widget/Widget.h"
#include "TrashBin.h"

struct GameStats {

    enum MiscStat { ZOMBIES_KILLED = 0, PLANTS_KILLED = 1, MONEY = 2, TREE_HEIGHT = 4, ENDLESS_FLAGS = 5, MOWED_ZOMBIES = 6, STINKY_CHOCOLATES = 7 };

    HouseType mHouseType;            // 0
    int unk;                         // 1
    int mMiscStats[9];               // 2 ~ 10
    char mFavoritePlants[49];        // 44 ~ 92
    char mFavoriteZombies[47];       // 93 ~ 139
    float mSurvivalCompletion;       // 35
    float mMiniGameCompletion;       // 36
    float mPuzzleCompletion;         // 37
}; // 大小38个整数

struct LeaderboardReanimations {
    Reanimation *backgroundReanim[5];
    Reanimation *achievementReanim[12];
};

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

    LeaderboardsWidget(LawnApp *theApp);
}; // 我想用LeaderboardsWidget取代DaveHelp。

inline void (*old_DaveHelp_Delete2)(LeaderboardsWidget *leaderboardsWidget);

void DaveHelp_Delete2(LeaderboardsWidget *leaderboardsWidget);

void DaveHelp_Update(LeaderboardsWidget *leaderboardsWidget);

void DaveHelp_Draw(LeaderboardsWidget *leaderboardsWidget, Sexy::Graphics *graphics);

void DaveHelp_DealClick(LeaderboardsWidget *leaderboardsWidget, int id);

void DaveHelp_MouseDown(LeaderboardsWidget *leaderboardsWidget, int x, int y, int theClickCount);

void DaveHelp_MouseUp(LeaderboardsWidget *leaderboardsWidget, int x, int y);

void DaveHelp_MouseDrag(LeaderboardsWidget *leaderboardsWidget, int x, int y);

void DaveHelp_KeyDown(LeaderboardsWidget *leaderboardsWidget, int keyCode);

inline void (*DaveHelp_DaveHelp)(LeaderboardsWidget *leaderboardsWidget, LawnApp *lawnApp);

#endif // PLANTSVSZOMBIES_ANDROIDTV_LEADERBOARDSWIDGET_H
