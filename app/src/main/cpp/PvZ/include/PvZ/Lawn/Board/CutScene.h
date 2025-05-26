#ifndef PVZ_LAWN_CUT_SCENE_H
#define PVZ_LAWN_CUT_SCENE_H

#include "PvZ/Lawn/Common/ConstEnums.h"

class CutScene {
public:
    LawnApp *mApp;                           // 0
    Board *mBoard;                           // 1
    int mCutsceneTime;                       // 2
    int mSodTime;                            // 3
    int mGraveStoneTime;                     // 4
    int mReadySetPlantTime;                  // 5
    int mFogTime;                            // 6
    int mBossTime;                           // 7
    int mCrazyDaveTime;                      // 8
    int mLawnMowerTime;                      // 9
    int mCrazyDaveDialogStart;               // 10
    bool mSeedChoosing;                      // 44
    Reanimation *mZombiesWonReanimID;        // 12
    bool mPreloaded;                         // 52
    bool mPlacedZombies;                     // 53
    bool mPlacedLawnItems;                   // 54
    int mCrazyDaveCountDown;                 // 14
    int mCrazyDaveLastTalkIndex;             // 15
    bool mUpsellHideBoard;                   // 64
    ChallengeScreen *mUpsellChallengeScreen; // 17
    bool mPreUpdatingBoard;                  // 72
    int unk[11];                             // 19 ~ 29
}; // 大小30个整数

inline bool (*CutScene_IsSurvivalRepick)(CutScene *instance);

inline bool (*CutScene_OnKeyDown)(CutScene *, int, int);

inline void (*CutScene_MouseDown)(CutScene *, int, int);

inline bool (*CutScene_IsBeforePreloading)(CutScene *);

inline bool (*CutScene_ShouldRunUpsellBoard)(CutScene *);


inline void (*old_CutScene_ShowShovel)(CutScene *cutScene);

inline void (*old_CutScene_Update)(CutScene *instance);


void CutScene_ShowShovel(CutScene *cutScene);

void CutScene_Update(CutScene *cutScene);

#endif // PVZ_LAWN_CUT_SCENE_H
