#ifndef PVZ_LAWN_SEED_CHOOSER_SCREEN_H
#define PVZ_LAWN_SEED_CHOOSER_SCREEN_H

#include "PvZ/Enums.h"

class SeedChooserScreen : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener;            // 64
    int unkMem1;                                     // 65
    Sexy::GameButton *mImitaterButton;               // 66
    ChosenSeed mChosenSeeds[54];                     // 67 ~ 930
    LawnApp *mApp;                                   // 931
    Board *mBoard;                                   // 932
    int mSeedChooserAge;                             // 933
    int mSeedsInFlight;                              // 934
    int mSeedsInBothBank;                            // 935
    int mSeedsIn1PBank;                              // 936
    int unkMem2;                                     // 937
    int *mToolTipWidget1;                            // 938
    int *mToolTipWidget2;                            // 939
    int mToolTipWidgetState1;                        // 940
    int mToolTipWidgetState2;                        // 941
    int mCursorPositionX1;                           // 942
    int mCursorPositionX2;                           // 943
    int mCursorPositionY1;                           // 944
    int mCursorPositionY2;                           // 945
    SeedChooserState mChooseState; // 946
    int mViewLawnTime;                               // 947
    bool unkBool;                                    // 3792
    int mPlayerIndex;                                // 949
    SeedType mSeedType1;                   // 950
    SeedType mSeedType2;                   // 951
    float unkF;                                      // 952
    bool mIsZombieChooser;                           // 3812
    SeedBank *mSeedBank1;                            // 954
    SeedBank *mSeedBank2;                            // 955
    int unkCounter;                                  // 956
    int mImitaterDialogOpened;                       // 957
    Sexy::GameButton *mViewLawnButton;               // 958
    Sexy::GameButton *mStoreButton;                  // 959
    Sexy::GameButton *mStartButton;                  // 960
    Sexy::GameButton *mAlmanacButton;                // 961
    int unkMems3[4];                                 // 962 ~ 965
    // 大小966个整数
public:
    void MouseMove(int x, int y);
    void MouseDown(int x, int y, int theClickCount);
    void MouseUp(int x, int y);
    void MouseDrag(int x, int y);
    void ButtonPress(int theId);
};

/***************************************************************************************************************/
inline bool daveNoPickSeeds;


inline void (*SeedChooserScreen_CloseSeedChooser)(SeedChooserScreen *a);

inline int (*SeedChooserScreen_FindSeedInBank)(SeedChooserScreen *a1, int a2, int a3);

inline bool (*SeedChooserScreen_HasPacket)(SeedChooserScreen *a, int a2, bool a3);

inline bool (*SeedChooserScreen_Has7Rows)(SeedChooserScreen *instance);

inline bool (*SeedChooserScreen_CancelLawnView)(SeedChooserScreen *seedChooserScreen);

inline void (*SeedChooserScreen_GetNextSeedInDir)(SeedChooserScreen *seedChooserScreen, int a2, int a3);

inline void (*SeedChooserScreen_GetSeedPositionInChooser)(SeedChooserScreen *, SeedType, int *, int *);

inline void (*SeedChooserScreen_UpdateImitaterButton)(SeedChooserScreen *);

inline SeedType (*SeedChooserScreen_SeedHitTest)(SeedChooserScreen *, int, int);

inline void (*SeedChooserScreen_LandFlyingSeed)(SeedChooserScreen *, int *);


inline void (*old_SeedChooserScreen_RebuildHelpbar)(SeedChooserScreen *instance);

inline void (*old_SeedChooserScreen_SeedChooserScreen)(SeedChooserScreen *seedChooserScreen, bool isZombieChooser);

inline void (*old_LawnApp_KillSeedChooserScreen)(LawnApp *lawnApp);

inline void (*old_SeedChooserScreen_Update)(SeedChooserScreen *a);

inline void (*old_SeedChooserScreen_EnableStartButton)(SeedChooserScreen *seedChooserScreen, int isEnabled);

inline void (*old_SeedChooserScreen_OnStartButton)(SeedChooserScreen *seedChooserScreen);

inline bool (*old_SeedChooserScreen_SeedNotAllowedToPick)(SeedChooserScreen *seedChooserScreen, SeedType theSeedType);

inline void (*old_SeedChooserScreen_ClickedSeedInChooser)(SeedChooserScreen *a1, ChosenSeed *a2, int a3);

inline void (*old_SeedChooserScreen_CrazyDavePickSeeds)(SeedChooserScreen *a);

inline void (*old_SeedChooserScreen_ClickedSeedInBank)(SeedChooserScreen *seedChooserScreen, ChosenSeed *theChosenSeed, unsigned int playerIndex);

inline void (*old_SeedChooserScreen_GameButtonDown)(SeedChooserScreen *a1, int a2, unsigned int a3);

inline void (*old_SeedChooserScreen_ButtonDepress)(SeedChooserScreen *seedChooserScreen, int id);

inline void (*old_SeedChooserScreen_GetSeedPositionInBank)(SeedChooserScreen *seedChooserScreen, int theIndex, int *x, int *y, int playerIndex);

inline void (*old_SeedChooserScreen_ShowToolTip)(SeedChooserScreen *seedChooserScreen, unsigned int playerIndex);

inline void (*old_SeedChooserScreen_MouseMove)(SeedChooserScreen *seedChooserScreen, int x, int y);

inline void (*old_SeedChooserScreen_MouseDown)(SeedChooserScreen *a, int x, int y, int theClickCount);

inline void (*old_SeedChooserScreen_MouseDrag)(SeedChooserScreen *seedChooserScreen, int x, int y);

inline void (*old_SeedChooserScreen_MouseUp)(SeedChooserScreen *seedChooserScreen, int x, int y);


void SeedChooserScreen_SeedChooserScreen(SeedChooserScreen *seedChooserScreen, bool isZombieChooser);

void LawnApp_KillSeedChooserScreen(LawnApp *lawnApp);

void SeedChooserScreen_ClickedSeedInBank(SeedChooserScreen *a1, ChosenSeed *a2, unsigned int a3);

void SeedChooserScreen_GameButtonDown(SeedChooserScreen *seedChooserScreen, int buttonCode, unsigned int playerIndex);

void SeedChooserScreen_GetSeedPositionInBank(SeedChooserScreen *, int, int *, int *, int);

void SeedChooserScreen_ButtonDepress(SeedChooserScreen *, int);

void SeedChooserScreen_ClickedSeedInChooser(SeedChooserScreen *a1, ChosenSeed *chosenSeed, int playerIndex);

void SeedChooserScreen_EnableStartButton(SeedChooserScreen *seedChooserScreen, int isEnabled);

bool SeedChooserScreen_SeedNotAllowedToPick(SeedChooserScreen *seedChooserScreen, SeedType theSeedType);

void SeedChooserScreen_OnStartButton(SeedChooserScreen *seedChooserScreen);

void SeedChooserScreen_ShowToolTip(SeedChooserScreen *seedChooserScreen, unsigned int playerIndex);

void SeedChooserScreen_RebuildHelpbar(SeedChooserScreen *seedChooserScreen);

int SeedChooserScreen_GetZombieSeedType(SeedChooserScreen *a, int a2);

int SeedChooserScreen_GetZombieType(SeedChooserScreen *a, int a2);

void SeedChooserScreen_CrazyDavePickSeeds(SeedChooserScreen *a);

void SeedChooserScreen_Update(SeedChooserScreen *seedChooserScreen);

void SeedChooserScreen_DrawPacket(SeedChooserScreen *seedChooserScreen,
                                  Sexy::Graphics *graphics,
                                  int x,
                                  int y,
                                  SeedType theSeedType,
                                  SeedType theImitaterType,
                                  float coolDownPercent,
                                  int grayness,
                                  Color *theColor,
                                  bool drawCostText,
                                  bool a11);

#endif // PVZ_LAWN_SEED_CHOOSER_SCREEN_H
