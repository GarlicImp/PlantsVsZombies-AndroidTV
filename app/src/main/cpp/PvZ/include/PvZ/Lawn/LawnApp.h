#ifndef PVZ_LAWN_LAWN_APP_H
#define PVZ_LAWN_LAWN_APP_H

#include "PvZ/Enums.h"
#include "PvZ/Symbols.h"

class ZenGarden;

class LawnApp : public SexyAppBase {
public:
    Board *mBoard;                           // 552
    TitleScreen *mTitleScreen;               // 553
    MainMenu *mGameSelector;                 // 554
    int unk1[2];                             // 555 ~ 556
    int *mHelpTextScreen;                    // 557
    int unkUnk;                              // 558
    int *mVSSetupScreen;                     // 559
    int *mVSResultsScreen;                   // 560
    SeedChooserScreen *mSeedChooserScreen;   // 561
    SeedChooserScreen *mZombieChooserScreen; // 562
    int *mAwardScreen;                       // 563
    CreditScreen *mCreditScreen;             // 564
    ChallengeScreen *mChallengeScreen;       // 565
    TodFoley *mSoundSystem;                  // 566
    int *unk3[7];                            // 567 ~ 573
    bool mRegisterResourcesLoaded;           // 2296
    bool mTodCheatKeys;                      // 2297
    bool mNewIs3DAccelerated;                // 2298，在对齐间隙插入新成员
    GameMode mGameMode;                      // 575
    GameScenes mGameScene;                   // 576
    bool mLoadingZombiesThreadCompleted;     // 2308
    bool mFirstTimeGameSelector;             // 2309
    int mGamesPlayed;                        // 578
    int mMaxExecutions;                      // 579
    int mMaxPlays;                           // 580
    int mMaxTime;                            // 581
    bool mEasyPlantingCheat;                 // 2328
    PoolEffect *mPoolEffect;                 // 583
    ZenGarden *mZenGarden;                   // 584
    EffectSystem *mEffectSystem;             // 585
    ReanimatorCache *mReanimatorCache;       // 586
    PlayerInfo *mPlayerInfo;                 // 587
    int unk6;                                // 588
    int *mLastLevelStats;                    // 589
    bool mCloseRequest;                      // 2360
    int mAppCounter;                         // 591
    Music2 *mMusic;                          // 592
    int mCrazyDaveReanimID;                  // 593
    CrazyDaveState mCrazyDaveState;          // 594
    int mCrazyDaveBlinkCounter;              // 595
    int mCrazyDaveBlinkReanimID;             // 596
    int mCrazyDaveMessageIndex;              // 597
    int *mCrazyDaveMessageText;              // 598
    int mAppRandSeed;                        // 599;
    int unk7;                                // 600
    int *mProfileMgr;                        // 601
    int unk8[35];                            // 602 ~ 636
    Sexy::Image *mQRCodeImage;               // 637
    int unk8_1[7];                           // 638 ~ 644
    int mInitialSunMoney;                    // 645     // 这个数据能给玩家加初始阳光
    bool mIsFullVersion;                     // 2584
    int unk9[7];                             // 647 ~ 653
    BoardResult mBoardResult;                // 654
    bool mKilledYetiAndRestarted;            // 2620
    int *mKonamiCheck;                       // 656
    int *mMustacheCheck;                     // 657
    int *mMoustacheCheck;                    // 658
    int *mSuperMowerCheck;                   // 659
    int *mSuperMowerCheck2;                  // 660
    int *mFutureCheck;                       // 661
    int *mPinataCheck;                       // 662
    int *mDanceCheck;                        // 663
    int *mDaisyCheck;                        // 664
    int *mSukhbirCheck;                      // 665
    bool mMustacheMode;                      // 2664
    bool mSuperMowerMode;                    // 2665
    bool mFutureMode;                        // 2666
    bool mPinataMode;                        // 2667
    bool mDanceMode;                         // 2668
    bool mDaisyMode;                         // 2669
    bool mSukhbirMode;                       // 2670
    int unk10;                               // 668
    bool mMuteSoundsForCutscene;             // 2676
    bool unkBool2;                           // 2677
    int unk11;                               // 670
    int mTwoPlayerState;                     // 671
    int unk12[3];                            // 672 ~ 674
    int *mMailBox;                           // 675
    int unk13[26];                           // 676 ~ 701
    int *mHelpBarWidget;                     // 702
    int unk14;                               // 703
    int *mLogComposer;                       // 704
    int *MLogManager;                        // 705
    int mLaunchTime;                         // 706
    int *mDaveHelp;                          // 707
    int *mMaskHelpWidget;                    // 708

    Reanimation *ReanimationGet(ReanimationID theReanimationID) { return reinterpret_cast<Reanimation *(*)(LawnApp *, ReanimationID)>(LawnApp_ReanimationGetAddr)(this, theReanimationID); }
    Reanimation *ReanimationTryToGet(ReanimationID theReanimationID) { return reinterpret_cast<Reanimation *(*)(LawnApp *, ReanimationID)>(LawnApp_ReanimationTryToGetAddr)(this, theReanimationID); }

    void KillSeedChooserScreen();
    bool IsIZombieLevel();
    bool IsWallnutBowlingLevel();
    void PlayFoley(FoleyType theFoleyType) { reinterpret_cast<void (*)(LawnApp *, FoleyType)>(LawnApp_PlayFoleyAddr)(this, theFoleyType); }
    void PlaySample(int theSoundNum) { reinterpret_cast<void (*)(LawnApp *, int)>(LawnApp_PlaySampleAddr)(this, theSoundNum); }
    bool IsAdventureMode();
    bool IsScaryPotterLevel();
};

/***************************************************************************************************************/
inline bool disableShop;
inline bool doCheatDialog;     // 菜单DoCheatDialog
inline bool doCheatCodeDialog; // 菜单DoCheatCodeDialog


inline void (*LawnApp_KillChallengeScreen)(LawnApp *lawnApp);

inline void (*LawnApp_KillMainMenu)(LawnApp *lawnApp);

inline void (*LawnApp_KillNewOptionsDialog)(LawnApp *lawnApp);

inline void (*LawnApp_PreNewGame)(LawnApp *lawnApp, GameMode a2, bool a3);

inline bool (*LawnApp_CanShowStore)(LawnApp *lawnApp);

inline bool (*LawnApp_CanShowAlmanac)(LawnApp *lawnApp);

inline void (*LawnApp_PlayFoleyPitch)(LawnApp *lawnApp, FoleyType theFoleyType, float aPitch);

inline void (*LawnApp_DoCheatDialog)(LawnApp *lawnApp);

inline void (*LawnApp_DoCheatCodeDialog)(LawnApp *lawnApp);

inline void (*LawnApp_DoUserDialog)(LawnApp *lawnApp);

inline void (*LawnApp_ClearSecondPlayer)(LawnApp *lawnApp);

inline bool (*LawnApp_IsScaryPotterLevel)(LawnApp *lawnApp);

inline bool (*LawnApp_IsWhackAZombieLevel)(LawnApp *lawnApp);

inline bool (*LawnApp_IsFirstTimeAdventureMode)(LawnApp *lawnApp);

inline bool (*LawnApp_IsAdventureMode)(LawnApp *lawnApp);

inline bool (*LawnApp_IsWallnutBowlingLevel)(LawnApp *lawnApp);

inline bool (*LawnApp_IsCoopMode)(LawnApp *lawnApp);

inline bool (*LawnApp_IsTwinSunbankMode)(LawnApp *lawnApp);

inline bool (*LawnApp_IsIZombieLevel)(LawnApp *lawnApp);

inline bool (*LawnApp_IsSurvivalMode)(LawnApp *);

inline bool (*LawnApp_IsPuzzleMode)(LawnApp *);

inline bool (*LawnApp_IsFinalBossLevel)(LawnApp *);

inline bool (*LawnApp_IsArtChallenge)(LawnApp *);

// 阻塞式函数，能创建并立即展示一个带按钮的对话框。按钮个数由最后一个参数决定。其返回值就是用户按下的按钮ID，一般情况下只可能为1000或1001。
inline int (*LawnApp_LawnMessageBox)(LawnApp *lawnApp,
                                     Dialogs theDialogId, // 用于标识本对话框的ID，以便于用KillDialog(theDialogId)关闭此对话框。一般用不到，所以随便填个数字就可以。
                                     const char *theHeaderName,
                                     const char *theLinesName,
                                     const char *theButton1Name,
                                     const char *theButton2Name,
                                     int theButtonMode); // 取值为0，1，2，3。其中0就是无按钮；1和2会展示两个按钮，其ID分别为1000和1001；3只会展示一个按钮，其ID为1000。

inline TodParticleSystem *(*LawnApp_AddTodParticle)(LawnApp *lawnApp, float, float, int, ParticleEffect);

inline int (*LawnApp_ParticleGetID)(LawnApp *, TodParticleSystem *);

inline Reanimation *(*LawnApp_AddReanimation)(LawnApp *, float, float, int, ReanimationType);

inline void (*LawnApp_ShowChallengeScreen)(LawnApp *, ChallengePage);

inline bool (*LawnApp_HasFinishedAdventure)(LawnApp *);

inline void (*LawnApp_KillVSResultsScreen)(LawnApp *);

inline void (*LawnApp_HideHelpBarWidget)(LawnApp *);

inline void (*LawnApp_ShowHelpTextScreen)(LawnApp *, int);

inline int (*LawnApp_GetPottedPlantByIndex)(LawnApp *, int);

inline void (*LawnApp_CrazyDaveStopTalking)(LawnApp *);

inline void (*LawnApp_NextTestDialog)(LawnApp *);

inline void (*LawnApp_DoRetryAchievementsDialog)(LawnApp *);

inline bool (*LawnApp_EarnedGoldTrophy)(LawnApp *);

inline void (*LawnApp_RemoveReanimation)(LawnApp *, int);

inline ReanimationID (*LawnApp_ReanimationGetID)(LawnApp *, Reanimation *);

inline bool (*LawnApp_IsSlotMachineLevel)(LawnApp *);

inline void (*LawnApp_KillAlmanacDialog)(LawnApp *);

inline void (*LawnApp_KillHelpTextScreen)(LawnApp *);

inline bool (*LawnApp_IsLittleTroubleLevel)(LawnApp *);

inline int *(*Sexy_SexyAppBase_GetDialog)(LawnApp *lawnApp, Dialogs dialogId);

inline int (*LawnApp_GetNumTrophies)(LawnApp *, ChallengePage);

inline bool (*LawnApp_IsSurvivalEndless)(LawnApp *lawnApp, GameMode);

inline void (*LawnApp_ShowMainMenuScreen)(LawnApp *lawnApp);

inline TodParticleSystem *(*LawnApp_ParticleTryToGet)(LawnApp *lawnApp, int);


inline void (*old_LawnApp_DoBackToMain)(LawnApp *lawnApp);

inline void (*old_LawnApp_ShowAwardScreen)(LawnApp *lawnApp, int a2);

inline void (*old_LawnApp_KillAwardScreen)(LawnApp *lawnApp);

inline int (*old_LawnApp_GamepadToPlayerIndex)(LawnApp *lawnApp, unsigned int a2);

inline void (*old_LawnApp_UpDateApp)(LawnApp *lawnApp);

inline bool (*old_LawnApp_CanShopLevel)(LawnApp *lawnApp);

inline void (*old_LawnApp_ShowCreditScreen)(LawnApp *lawnApp, bool isFromMainMenu);

inline void (*old_LawnApp_LoadLevelConfiguration)(LawnApp *lawnApp, int a2, int a3);

inline void (*old_LawnApp_LawnApp)(LawnApp *lawnApp);

inline void (*old_LawnApp_Init)(LawnApp *lawnApp);

inline void (*old_LawnApp_LoadingThreadProc)(LawnApp *lawnApp);

inline bool (*old_LawnApp_IsChallengeWithoutSeedBank)(LawnApp *lawnApp);

inline int (*old_LawnApp_GetSeedsAvailable)(LawnApp *lawnApp, int isZombieChooser);

inline void (*old_LawnApp_HardwareInit)(LawnApp *lawnApp);

inline int (*old_LawnApp_GetNumPreloadingTasks)(LawnApp *lawnApp);

inline bool (*old_LawnApp_IsNight)(LawnApp *lawnApp);

inline void (*old_Sexy_SexyAppBase_SexyAppBase)(SexyAppBase *appBase);

inline bool (*old_LawnApp_HasSeedType)(LawnApp *lawnApp, SeedType theSeedType, int playerIndex);

inline void (*old_LawnApp_DoNewOptions)(LawnApp *lawnApp, bool a2, unsigned int a3);


void LawnApp_LawnApp(LawnApp *lawnApp);

void LawnApp_Init(LawnApp *lawnApp);

void LawnApp_HardwareInit(LawnApp *lawnApp);

int LawnApp_GetNumPreloadingTasks(LawnApp *lawnApp);

void LawnApp_DoConfirmBackToMain(LawnApp *lawnApp, bool save);

int LawnApp_TrophiesNeedForGoldSunflower(LawnApp *lawnApp);

int LawnApp_GamepadToPlayerIndex(LawnApp *lawnApp, unsigned int a2);

void LawnApp_ShowCreditScreen(LawnApp *lawnApp, bool isFromMainMenu);

void LawnApp_OnSessionTaskFailed(LawnApp *lawnApp);

void LawnApp_UpdateApp(LawnApp *lawnApp);

void LawnApp_ShowAwardScreen(LawnApp *lawnApp, int a2);

void LawnApp_KillAwardScreen(LawnApp *lawnApp);

void LawnApp_LoadLevelConfiguration(LawnApp *lawnApp, int a2, int a3);

void LawnApp_LoadingThreadProc(LawnApp *lawnApp);

void LawnApp_TryHelpTextScreen(LawnApp *lawnApp, int a2);

void LawnApp_LoadAddonImages(LawnApp *lawnApp);

void LawnApp_LoadAddonSounds(LawnApp *lawnApp);

void LawnApp_Load(LawnApp *lawnApp, const char *theGroupName);

void LawnApp_ShowZombatarScreen(LawnApp *lawnApp);

void LawnApp_KillZombatarScreen(LawnApp *lawnApp);

bool LawnApp_CanShopLevel(LawnApp *lawnApp);

void LawnApp_DoNewOptions(LawnApp *lawnApp, bool a2, unsigned int a3);

Sexy::Image *LawnApp_GetImageByFileName(LawnApp *lawnApp, const char *fileName);

int LawnApp_GetSoundByFileName(LawnApp *lawnApp, const char *fileName);

void LawnApp_PlaySample(LawnApp *lawnApp, int soundId);

bool LawnApp_GrantAchievement(LawnApp *lawnApp, AchievementId::AchievementId theAchievementId);

void LawnApp_DoBackToMain(LawnApp *lawnApp);

bool LawnApp_IsChallengeWithoutSeedBank(LawnApp *);

bool LawnApp_IsNight(LawnApp *);

void LawnApp_SetFoleyVolume(LawnApp *lawnApp, FoleyType type, double theVolume);

void LawnApp_KillDialog(LawnApp *lawnApp, Dialogs id);

void LawnApp_ShowLeaderboards(LawnApp *lawnApp);

void LawnApp_KillLeaderboards(LawnApp *lawnApp);

void LawnApp_SetHouseReanim(LawnApp *lawnApp, Reanimation *houseAnimation);

void LawnApp_LoadZombatarResources(LawnApp *lawnApp);

bool LawnApp_HasSeedType(LawnApp *lawnApp, SeedType theSeedType, int playerIndex);

void Sexy_SexyAppBase_SexyAppBase(SexyAppBase *appBase);
#endif // PVZ_LAWN_LAWN_APP_H
