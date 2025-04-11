#ifndef PVZ_LAWN_CHALLENGE_SCREEN_H
#define PVZ_LAWN_CHALLENGE_SCREEN_H

#include "PvZ/Enums.h"

class ChallengeScreen : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener;        // 64
    Sexy::ButtonWidget *mButtons[94];            // 65 ~ 158
    LawnApp *mApp;                               // 159
    int *mToolTipWidget;                         // 160
    ChallengePage::ChallengePage mPage;          // 161
    bool mCheatEnableChallenges;                 // 648
    UnlockingState::UnlockingState mUnlockState; // 163
    int mUnlockStateCounter;                     // 164
    int mUnlockChallengeIndex;                   // 165
    float mLockShakeX;                           // 166
    float mLockShakeY;                           // 167
    Curve1DUtil mUtil;                           // 168 ~ 183
    int *mHelpBarWidget;                         // 184
    int mScreenTopChallengeIndex;                // 185
    int mSelectedChallengeIndex;                 // 186
    float mUnkFloat;                             // 187
    GameMode::GameMode mUnk1[94];                // 188 ~ 281
    int mUnk2[94];                               // 282 ~ 375
    int mTotalGameInPage;                        // 376
    int mSelectedChallenge;                      // 377 其值固定比mSelectedMode小2
    GameMode::GameMode mSelectedMode;            // 378
    int unk4;                                    // 379
    // 大小380个整数
public:
    void MouseDown(int x, int y, int theClickCount);
    void MouseUp(int x, int y);
    void MouseDrag(int x, int y);
    void ButtonPress(int theButtonId);
};

/***************************************************************************************************************/
inline void (*ChallengeScreen_SetScrollTarget)(ChallengeScreen *instance, int a);

inline void (*ChallengeScreen_KeyDown)(ChallengeScreen *, int);


inline void (*old_ChallengeScreen_ChallengeScreen)(ChallengeScreen *challengeScreen, LawnApp *lawnApp, ChallengePage::ChallengePage page);

inline void (*old_ChallengeScreen_Draw)(ChallengeScreen *challengeScreen, Sexy::Graphics *graphics);

inline void (*old_ChallengeScreen_AddedToManager)(ChallengeScreen *a, int a2);

inline void (*old_ChallengeScreen_Update)(ChallengeScreen *a);

inline void (*old_ChallengeScreen_RemovedFromManager)(ChallengeScreen *a, int a2);

inline void (*old_ChallengeScreen_Delete2)(ChallengeScreen *challengeScreen);

inline ChallengeDefinition &(*old_GetChallengeDefinition)(int index);

inline void (*old_ChallengeScreen_MouseDown)(ChallengeScreen *challengeScreen, int x, int y, int theClickCount);

inline void (*old_ChallengeScreen_MouseDrag)(ChallengeScreen *challengeScreen, int x, int y);

inline void (*old_ChallengeScreen_MouseUp)(ChallengeScreen *challengeScreen, int x, int y);


ChallengeDefinition &GetChallengeDefinition(int);

void ChallengeScreen_AddedToManager(ChallengeScreen *challengeScreen, int a2);

void ChallengeScreen_Update(ChallengeScreen *a);

void ChallengeScreen_RemovedFromManager(ChallengeScreen *challengeScreen, int a2);

void ChallengeScreen_Delete2(ChallengeScreen *challengeScreen);

void ChallengeScreen_UpdateButtons(ChallengeScreen *challengeScreen);

void ChallengeScreen_ChallengeScreen(ChallengeScreen *challengeScreen, LawnApp *lawnApp, ChallengePage::ChallengePage page);

void ChallengeScreen_Draw(ChallengeScreen *challengeScreen, Sexy::Graphics *graphics);

void ChallengeScreen_ButtonDepress(ChallengeScreen *challengeScreen, int buttonId);

#endif // PVZ_LAWN_CHALLENGE_SCREEN_H
