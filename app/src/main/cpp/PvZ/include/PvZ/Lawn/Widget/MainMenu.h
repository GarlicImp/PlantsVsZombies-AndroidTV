#ifndef PVZ_LAWN_MAIN_MENU_H
#define PVZ_LAWN_MAIN_MENU_H

#include "PvZ/Enums.h"
#include "PvZ/Symbols.h"

class MainMenu : public Sexy::MenuWidget {
public:
    ReanimationID mMainMenuReanimID;      // 70 , PSV 59
    float mCameraPositionX;               // 71
    float mCameraPositionY;               // 72
    LawnApp *mApp;                        // 73
    int unkMem1;                          // 74
    int mScene;                           // 75
    int mSceneNext;                       // 76
    char *MPlayingTrackName;              // 77
    int mTransitionCounter;               // 78
    ReanimationID mSkyReanimID;           // 79 ,PSV 68
    ReanimationID mSky2ReanimID;          // 80 ,PSV 69
    ReanimationID mHouseReanimID;         // 81 ,PSV 70
    ReanimationID mZombieHandReanimID;    // 82
    ReanimationID mCrowReanimID;          // 83 , psv 72
    ReanimationID mFallingLeavesReanimID; // 84
    ReanimationID mButterflyReanimID;     // 85
    ReanimationID mUnkReanimID2;          // 86
    MainMenuButtonId mPressedButtonId;    // 87
    char *mExitTrackName;                 // 88
    int mEnterReanimationCounter;         // 89
    int mExitCounter;                     // 90
    bool unk1;                            // 364
    bool mFirstTimeAdventure;             // 365
    bool mMiniGameLocked;                 // 366
    bool mCoopModeLocked;                 // 367
    bool mPuzzleModeLocked;               // 368
    bool mSurvivalModeLocked;             // 369
    bool mVSModeLocked;                   // 370
    bool unkBool3;                        // 371
    bool unkBool4;                        // 372
    bool unkBool5;                        // 373
    int unkMems3[5];                      // 94 ~ 98
    bool mRetainWidgetsOnExit;            // 396
    float mXUnkFloat1;                    // 100
    float mYUnkFloat2;                    // 101
    float mFadeCounterFloat;              // 102
    bool unkMems4[16];                    // 103 ~ 106
    Sexy::Image *m2DMarkImage;            // 107
    // 大小108个整数
public:
    bool InTransition() { return reinterpret_cast<bool (*)(MainMenu *)>(MainMenu_InTransitionAddr)(this); };
    void SetScene(MainMenuScene theScene) { reinterpret_cast<void (*)(MainMenu *, MainMenuScene)>(MainMenu_SetSceneAddr)(this, theScene); };
    void StartAdventureMode() { reinterpret_cast<void (*)(MainMenu *)>(MainMenu_StartAdventureModeAddr)(this); };

    MainMenu(LawnApp *theApp) { Create(theApp); }
    void Create(LawnApp *theApp);
    void KeyDown(Sexy::KeyCode theKeyCode);
    void ButtonDepress(MainMenuButtonId theSelectedButton);
    void Update();
    void SyncProfile(bool a2);
    void Enter();
    void Exit();
    bool UpdateExit();
    void OnExit();
    void OnScene(int theScene);
    void SyncButtons();
    void UpdateCameraPosition();
    void AddedToManager(int *a2);
    void RemovedFromManager(int *a2);
    void DrawOverlay(Sexy::Graphics *g);
    void DrawFade(Sexy::Graphics *g);
    void Delete2();
    void Draw(Sexy::Graphics *g);
    void ButtonPress(MainMenuButtonId theSelectedButton);
};


inline void (*DaveHelp_DaveHelp)(LeaderboardsWidget *leaderboardsWidget, LawnApp *lawnApp);


inline void (*old_MainMenu_Update)(MainMenu *instance);

inline void (*old_MainMenu_ButtonDepress)(MainMenu *mainMenu, MainMenuButtonId a2);

inline void (*old_MainMenu_KeyDown)(MainMenu *mainMenu, Sexy::KeyCode keyCode);

inline void (*old_MainMenu_SyncProfile)(MainMenu *a, bool a2);

inline void (*old_MainMenu_Enter)(MainMenu *mainMenu);

inline bool (*old_MainMenu_UpdateExit)(MainMenu *mainMenu);

inline void (*old_MainMenu_Exit)(MainMenu *mainMenu);

inline void (*old_MainMenu_OnExit)(MainMenu *a);

inline void (*old_MainMenu_OnScene)(MainMenu *mainMenu, int scene);

inline void (*old_MainMenu_SyncButtons)(MainMenu *mainMenu);

inline void (*old_MainMenu_MainMenu)(MainMenu *mainMenu, LawnApp *);

inline void (*old_MainMenu_UpdateCameraPosition)(MainMenu *mainMenu);

inline void (*old_MainMenu_AddedToManager)(MainMenu *instance, int *a2);

inline void (*old_MainMenu_RemovedFromManager)(MainMenu *instance, int *a2);

inline void (*old_MainMenu_Delete2)(MainMenu *mainMenu);

inline void (*old_MainMenu_Draw)(MainMenu *mainMenu, Sexy::Graphics *a2);

inline void (*old_MainMenu_DrawOverlay)(MainMenu *mainMenu, Sexy::Graphics *a2);

inline void (*old_MainMenu_DrawFade)(MainMenu *mainMenu, Sexy::Graphics *a2);

inline void (*old_TrashBin_TrashBin)(TrashBin *trashBin, TrashBin::TrashPileType theTrashPileType, float height);

inline void (*old_DaveHelp_Delete2)(LeaderboardsWidget *leaderboardsWidget);

inline void (*old_TestMenuWidget_RemovedFromManager)(ZombatarWidget *zombatarWidget, int *manager);

inline void (*old_TestMenuWidget_Delete2)(ZombatarWidget *zombatarWidget);

inline void (*old_TestMenuWidget_Delete)(ZombatarWidget *zombatarWidget);


void LeaderboardsWidget_LeaderboardsWidget(LeaderboardsWidget *this_, LawnApp *lawnApp);

void DaveHelp_Delete2(LeaderboardsWidget *leaderboardsWidget);

void ZombatarWidget_ZombatarWidget(ZombatarWidget *zombatarWidget, LawnApp *lawnApp);

void TestMenuWidget_DrawPortrait(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics, int x, int y);

bool ZombatarWidget_AccessoryIsColorized(int tab, int accessory);

void MaskHelpWidget_Update(AchievementsWidget *achievementsWidget);

void MaskHelpWidget_Draw(AchievementsWidget *achievementsWidget, Sexy::Graphics *graphics);

void DaveHelp_Update(LeaderboardsWidget *leaderboardsWidget);

void DaveHelp_Draw(LeaderboardsWidget *leaderboardsWidget, Sexy::Graphics *graphics);

void DaveHelp_DealClick(LeaderboardsWidget *leaderboardsWidget, int id);

void TestMenuWidget_Delete(ZombatarWidget *zombatarWidget);

void TestMenuWidget_Delete2(ZombatarWidget *zombatarWidget);

void MaskHelpWidget_MouseDown(AchievementsWidget *achievementsWidget, int x, int y, int theClickCount);

void MaskHelpWidget_MouseUp(AchievementsWidget *achievementsWidget, int x, int y);

void MaskHelpWidget_MouseDrag(AchievementsWidget *achievementsWidget, int x, int y);

void DaveHelp_MouseDown(LeaderboardsWidget *leaderboardsWidget, int x, int y, int theClickCount);

void DaveHelp_MouseUp(LeaderboardsWidget *leaderboardsWidget, int x, int y);

void DaveHelp_MouseDrag(LeaderboardsWidget *leaderboardsWidget, int x, int y);

void DaveHelp_KeyDown(LeaderboardsWidget *leaderboardsWidget, int keyCode);

void TestMenuWidget_RemovedFromManager(ZombatarWidget *zombatarWidget, int *manager);

void TestMenuWidget_Update(ZombatarWidget *zombatarWidget);

void TestMenuWidget_Draw(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics);

void TestMenuWidget_MouseDown(ZombatarWidget *zombatarWidget, int x, int y);

void TestMenuWidget_MouseUp(ZombatarWidget *zombatarWidget, int x, int y);

void TestMenuWidget_MouseDrag(ZombatarWidget *zombatarWidget, int x, int y);

void TestMenuWidget_KeyDown(ZombatarWidget *zombatarWidget, int keyCode);
#endif // PVZ_LAWN_MAIN_MENU_H
