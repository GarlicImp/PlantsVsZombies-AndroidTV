#ifndef PVZ_LAWN_BOARD_H
#define PVZ_LAWN_BOARD_H

#include "Coin.h"
#include "GridItem.h"
#include "Plant.h"
#include "Projectile.h"
#include "PvZ/Enums.h"
#include "PvZ/Symbols.h"
#include "Zombie.h"

#define MAX_GRID_SIZE_X 9
#define MAX_GRID_SIZE_Y 6
#define MAX_ZOMBIES_IN_WAVE 50
#define MAX_ZOMBIE_WAVES 100
#define MAX_GRAVE_STONES MAX_GRID_SIZE_X *MAX_GRID_SIZE_Y
#define MAX_POOL_GRID_SIZE 10
#define MAX_RENDER_ITEMS 2048
#define PROGRESS_METER_COUNTER 150

class LawnApp;
class CursorObject;
class CursorPreview;
class GameButton;
class MessageWidget;
class SeedBank;
class CutScene;
class Challenge;
class Reanimation;
class TodParticleSystem;

class HitResult {
public:
    void *mObject;
    GameObjectType mObjectType;
};

struct ZombiePicker {
    int mZombieCount;
    int mZombiePoints;
    int mZombieTypeCount[ZombieType::NUM_ZOMBIE_TYPES];
    int mAllWavesZombieTypeCount[ZombieType::NUM_ZOMBIE_TYPES];
};

/*inline*/ void ZombiePickerInitForWave(ZombiePicker *theZombiePicker);
/*inline*/ void ZombiePickerInit(ZombiePicker *theZombiePicker);

struct PlantsOnLawn {
    Plant *mUnderPlant;
    Plant *mPumpkinPlant;
    Plant *mFlyingPlant;
    Plant *mNormalPlant;
};

struct BungeeDropGrid {
    TodWeightedGridArray mGridArray[MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y];
    int mGridArrayCount;
};

class Board : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener;       // 64
    int unknownMembers1[4];                     // 65 ~ 68
    LawnApp *mApp;                              // 69
    Zombie *mZombiesBlock;                      // 70
    unsigned int mZombiesMaxUsedCount;          // 71
    unsigned int mZombiesMaxSize;               // 72
    unsigned int mZombiesFreeListHead;          // 73
    unsigned int mZombiesSize;                  // 74
    unsigned int mZombiesNextKey;               // 75
    const char *mZombiesName;                   // 76
    Plant *mPlantsBlock;                        // 77
    unsigned int mPlantsMaxUsedCount;           // 78
    unsigned int mPlantsMaxSize;                // 79
    unsigned int mPlantsFreeListHead;           // 80
    unsigned int mPlantsSize;                   // 81
    unsigned int mPlantsNextKey;                // 82
    const char *mPlantsName;                    // 83
    Projectile *mProjectilesBlock;              // 84
    unsigned int mProjectilesMaxUsedCount;      // 85
    unsigned int mProjectilesMaxSize;           // 86
    unsigned int mProjectilesFreeListHead;      // 87
    unsigned int mProjectilesSize;              // 88
    unsigned int mProjectilesNextKey;           // 89
    const char *mProjectilesName;               // 90
    Coin *mCoinsBlock;                          // 91
    unsigned int mCoinsMaxUsedCount;            // 92
    unsigned int mCoinsMaxSize;                 // 93
    unsigned int mCoinsFreeListHead;            // 94
    unsigned int mCoinsSize;                    // 95
    unsigned int mCoinsNextKey;                 // 96
    const char *mCoinsName;                     // 97
    int *mLawnMowersBlock;                      // 98
    unsigned int mLawnMowersMaxUsedCount;       // 99
    unsigned int mLawnMowersMaxSize;            // 100
    unsigned int mLawnMowersFreeListHead;       // 101
    unsigned int mLawnMowersSize;               // 102
    unsigned int mLawnMowersNextKey;            // 103
    const char *mLawnMowersName;                // 104
    GridItem *mGridItemsBlock;                  // 105
    unsigned int mGridItemsMaxUsedCount;        // 106
    unsigned int mGridItemsMaxSize;             // 107
    unsigned int mGridItemsFreeListHead;        // 108
    unsigned int mGridItemsSize;                // 109
    unsigned int mGridItemsNextKey;             // 110
    const char *mGridItemsName;                 // 111
    PlantRbTree mTangleKelpTree;                // 112 ~ 117
    PlantRbTree mFlowerPotTree;                 // 118 ~ 123
    PlantRbTree mPumpkinTree;                   // 124 ~ 129
    MessageWidget *mAdvice;                     // 130
    SeedBank *mSeedBank1;                       // 131
    SeedBank *mSeedBank2;                       // 132
    int unknownMembers3[7];                     // 133 ~ 139
    GamepadControls *mGamepadControls1;         // 140
    GamepadControls *mGamepadControls2;         // 141
    CursorObject *mCursorObject1;               // 142
    CursorObject *mCursorObject2;               // 143
    CursorPreview *mCursorPreview1;             // 144
    CursorPreview *mCursorPreview2;             // 145
    int *mToolTipWidget;                        // 146
    int *mToolTipFont;                          // 147
    CutScene *mCutScene;                        // 148
    Challenge *mChallenge;                      // 149
    bool unknownBool;                           // 600
    bool mPaused;                               // 601
    GridSquareType mGridSquareType[9][6];       // 151 ~ 204
    int mGridCelLook[9][6];                     // 205 ~ 258
    int mGridCelOffset[9][6][2];                // 259 ~ 366
    int mGridCelFog[9][7];                      // 367 ~ 429
    bool mEnableGraveStones;                    // 1720
    int mSpecialGraveStoneX;                    // 431
    int mSpecialGraveStoneY;                    // 432
    float mFogOffset;                           // 433
    int mOffsetMoved;                           // 434
    ReanimationID mCoverLayerAnimIDs[7];        // 435 ~ 441
    int mFogBlownCountDown;                     // 442
    PlantRowType mPlantRow[6];                  // 443 ~ 448
    int mWaveRowGotLawnMowered[6];              // 449 ~ 454
    int mBonusLawnMowersRemaining;              // 455
    int mIceMinX[6];                            // 456 ~ 461
    int mIceTimer[6];                           // 462 ~ 467
    ParticleSystemID mIceParticleID[6];         // 468 ~ 473
    TodSmoothArray mRowPickingArray[6];         // 474 ~ 497
    ZombieType mZombiesInWave[100][50];         // 498 ~ 5497
    bool mZombieAllowed[100];                   // 5498 ~ 5522
    int mSunCountDown;                          // 5523
    int mNumSunsFallen;                         // 5524
    int mShakeCounter;                          // 5525
    int mShakeAmountX;                          // 5526
    int mShakeAmountY;                          // 5527
    BackgroundType mBackground;                 // 5528
    int mLevel;                                 // 5529
    int mSodPosition;                           // 5530
    int mPrevMouseX;                            // 5531
    int mPrevMouseY;                            // 5532
    int mSunMoney1;                             // 5533
    int mSunMoney2;                             // 5534
    int mDeathMoney;                            // 5535
    int mNumWaves;                              // 5536
    int mMainCounter;                           // 5537
    int mEffectCounter;                         // 5538
    int mDrawCount;                             // 5539
    int mRiseFromGraveCounter;                  // 5540
    int mOutOfMoneyCounter;                     // 5541
    int mCurrentWave;                           // 5542
    int mTotalSpawnedWaves;                     // 5543
    TutorialState mTutorialState;               // 5544
    int *mTutorialParticleID;                   // 5545
    int mTutorialTimer;                         // 5546
    int mLastBungeeWave;                        // 5547
    int mZombieHealthToNextWave;                // 5548
    int mZombieHealthWaveStart;                 // 5549
    int mZombieCountDown;                       // 5550
    int mZombieCountDownStart;                  // 5551
    int mHugeWaveCountDown;                     // 5552
    bool mHelpDisplayed[72];                    // 5553 ~ 5570
    AdviceType mHelpIndex;                      // 5571
    bool mFinalBossKilled;                      // 22288
    bool mShowShovel;                           // 22289
    bool mShowButter;                           // 22290
    bool mShowHammer;                           // 22291
    int mCoinBankFadeCount;                     // 5573
    DebugTextMode mDebugTextMode;               // 5574
    bool mLevelComplete;                        // 22300
    bool mNewWallNutAndSunFlowerAndChomperOnly; // 在对齐间隙插入成员，22301
    char mNewPeaShooterCount;                   // 在对齐间隙插入成员，22302
    int mBoardFadeOutCounter;                   // 5576
    int mNextSurvivalStageCounter;              // 5577
    int mScoreNextMowerCounter;                 // 5578
    bool mLevelAwardSpawned;                    // 22316
    int mProgressMeterWidth;                    // 5580
    int mFlagRaiseCounter;                      // 5581
    int mIceTrapCounter;                        // 5582
    int mBoardRandSeed;                         // 5583
    int mPoolSparklyParticleID;                 // 5584
    Reanimation *mFwooshID[6][12];              // 5585 ~ 5656
    int mFwooshCountDown;                       // 5657
    int mTimeStopCounter;                       // 5658
    bool mDroppedFirstCoin;                     // 22636
    int mFinalWaveSoundCounter;                 // 5660
    int mCobCannonCursorDelayCounter;           // 5661
    int mCobCannonMouseX;                       // 5662
    int mCobCannonMouseY;                       // 5663
    bool mKilledYeti;                           // 22656
    bool mMustacheMode;                         // 22657
    bool mSuperMowerMode;                       // 22658
    bool mFutureMode;                           // 22659
    bool mPinataMode;                           // 22660
    bool mDanceMode;                            // 22661
    bool mDaisyMode;                            // 22662
    bool mSukhbirMode;                          // 22663
    int mPrevBoardResult;                       // 5666
    int mTriggeredLawnMowers;                   // 5667
    int mPlayTimeActiveLevel;                   // 5668
    int mPlayTimeInactiveLevel;                 // 5669
    int mMaxSunPlants;                          // 5670
    int mStartDrawTime;                         // 5671
    int mIntervalDrawTime;                      // 5672
    int mIntervalDrawCountStart;                // 5673
    float mMinFPS;                              // 5674
    int mPreloadTime;                           // 5675
    int mGameID;                                // 5676
    int mGravesCleared;                         // 5677
    int mPlantsEaten;                           // 5678
    int mPlantsShoveled;                        // 5679
    int mCoinsCollected;                        // 5680
    int mDiamondsCollected;                     // 5681
    int mPottedPlantsCollected;                 // 5682
    int mChocolateCollected;                    // 5683
    bool mPeaShooterUsed;                       // 22736
    bool mCatapultPlantsUsed;                   // 22737
    int mCollectedCoinStreak;                   // 5685
    int mUnkIntSecondPlayer1;                   // 5686
    bool mUnkBoolSecondPlayer;                  // 22748
    int mUnkIntSecondPlayer2;                   // 5688
    int *mStringSecondPlayer;                   // 5689
    int unknownMembers[8];                      // 5690 ~ 5697

    Projectile *AddProjectile(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType) {
        return reinterpret_cast<Projectile *(*)(Board *, int, int, int, int, ProjectileType)>(Board_AddProjectileAddr)(this, theX, theY, theRenderOrder, theRow, theProjectileType);
    }
    int PixelToGridX(int theX, int theY) { return reinterpret_cast<int (*)(Board *, int, int)>(Board_PixelToGridXAddr)(this, theX, theY); }
    int PixelToGridY(int theX, int theY) { return reinterpret_cast<int (*)(Board *, int, int)>(Board_PixelToGridYAddr)(this, theX, theY); }
    GridItem *GetScaryPotAt(int theGridX, int theGridY);
    GridItem *GetGridItemAt(GridItemType theGridItemType, int theGridX, int theGridY);
    void Move(int theX, int theY) { reinterpret_cast<void (*)(Board *, int, int)>(Board_MoveAddr)(this, theX, theY); } // 整体移动整个草坪，包括种子栏和铲子按钮等等。
    void DoFwoosh(int theRow) { reinterpret_cast<void (*)(Board *, int)>(Board_DoFwooshAddr)(this, theRow); }
    bool IteratePlants(Plant *&thePlant) { return reinterpret_cast<bool (*)(Board *, Plant *&)>(Board_IteratePlantsAddr)(this, thePlant); }
    bool IterateZombies(Zombie *&theZombie) { return reinterpret_cast<bool (*)(Board *, Zombie *&)>(Board_IterateZombiesAddr)(this, theZombie); }
    Plant *GetTopPlantAt(int theGridX, int theGridY, PlantPriority thePriority) {
        return reinterpret_cast<Plant *(*)(Board *, int, int, PlantPriority)>(Board_GetTopPlantAtAddr)(this, theGridX, theGridY, thePriority);
    }


    Board(LawnApp *theApp);
    void Create(LawnApp *theApp);
    void InitLevel();
    void Update();
    void RemovedFromManager(int *theManager);
    int GetNumSeedsInBank(bool thePlayerIndex);
    void RemoveParticleByType(ParticleEffect theEffectType);
    void FadeOutLevel();
    Plant *AddPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, int thePlayerIndex, bool theIsDoEffect);
    void AddSunMoney(int theAmount, int thePlayerIndex);
    void AddDeathMoney(int theAmount);
    PlantingReason CanPlantAt(int theGridX, int theGridY, SeedType theSeedType);
    bool PlantingRequirementsMet(SeedType theSeedType);
    Plant *GetFlowerPotAt(int theGridX, int theGridY);
    Plant *GetPumpkinAt(int theGridX, int theGridY);
    void ZombiesWon(Zombie *theZombie);
    void UpdateSunSpawning();
    void UpdateZombieSpawning();
    void PickBackground();
    void DrawCoverLayer(Sexy::Graphics *g, int theRow);
    void UpdateGame();
    void UpdateGameObjects();
    bool IsFlagWave(int theWaveNumber);
    void SpawnZombieWave();
    void DrawProgressMeter(Sexy::Graphics *g, int theX, int theY);
    int GetNumWavesPerFlag();
    bool IsLevelDataLoaded();
    bool NeedSaveGame();
    void UpdateFwoosh();
    void UpdateFog();
    void DrawFog(Sexy::Graphics *g);
    void UpdateIce();
    void DrawBackdrop(Sexy::Graphics *g);
    bool RowCanHaveZombieType(int theRow, ZombieType theZombieType);
    void DrawDebugText(Sexy::Graphics *g);
    void DrawDebugObjectRects(Sexy::Graphics *g);
    void DrawFadeOut(Sexy::Graphics *g);
    int GetCurrentPlantCost(SeedType theSeedType, SeedType theImitaterType);
    void Pause(bool thePause);
    void AddSecondPlayer(int a2);
    bool IsLastStandFinalStage();
    bool MouseHitTest(int x, int y, HitResult *theHitResult, bool thePlayerIndex);
    void DrawShovel(Sexy::Graphics *g);
    bool StageHasPool();
    bool StageHasRoof();
    Zombie *AddZombieInRow(ZombieType theZombieType, int theRow, int theFromWave, bool theIsRustle);
    Zombie *AddZombie(ZombieType theZombieType, int theFromWave, bool theIsRustle);
    void DoPlantingEffects(int theGridX, int theGridY, Plant *thePlant);
    void InitLawnMowers();
    void PickZombieWaves();
    void DrawUITop(Sexy::Graphics *g);
    //    void GetShovelButtonRect(Rect *rect);
    void UpdateLevelEndSequence();
    void UpdateGridItems();
    void ShakeBoard(int theShakeAmountX, int theShakeAmountY);
    void DrawZenButtons(Sexy::Graphics *g);
    void SpeedUpUpdate();
    void DrawShovelButton(Sexy::Graphics *g, LawnApp *theApp);
    void ShovelDown();
    int PixelToGridXKeepOnBoard(int theX, int theY);
    int PixelToGridYKeepOnBoard(int theX, int theY);
    int GridToPixelX(int theGridX, int theGridY);
    int GridToPixelY(int theGridX, int theGridY);
    static int MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset);

    void MouseMove(int x, int y);
    void MouseDown(int x, int y, int theClickCount);
    void MouseDownSecond(int x, int y, int theClickCount);
    void MouseUp(int x, int y, int theClickCount);
    void MouseUpSecond(int x, int y, int theClickCount);
    void MouseDrag(int x, int y);
    void ButtonDepress(int theId);
    void KeyDown(Sexy::KeyCode theKey);
};

int GetRectOverlap(const Sexy::Rect &rect1, const Sexy::Rect &rect2);
bool GetCircleRectOverlap(int theCircleX, int theCircleY, int theRadius, const Sexy::Rect &theRect);
/***************************************************************************************************************/
inline int theBuildLadderX;
inline int theBuildPlantX;
inline int BuildZombieX;
inline int theBuildLadderY;
inline int theBuildPlantY;
inline int BuildZombieY;
inline bool ladderBuild;
inline bool graveBuild;
inline bool plantBuild;
inline bool zombieBuild;
inline SeedType theBuildPlantType = SeedType::SEED_NONE;
inline ZombieType theBuildZombieType = ZombieType::ZOMBIE_INVALID;
inline bool isImitaterPlant;
inline int theBuildZombieCount = 1;
inline int theZombieBuildRow;
inline int theZombieBuildi;
inline bool uniformBuildZombie;
inline int theUniformZombieBuildRow;
inline bool passNowLevel;
inline std::string customFormation;
inline int formationId = -1;
inline bool ClearAllPlant;
inline bool clearAllZombies;
inline bool hypnoAllZombies;
inline bool freezeAllZombies;
inline bool clearAllGraves;
inline bool clearAllMowers;
inline bool recoverAllMowers;
inline bool startAllMowers;
inline bool banMower;
inline bool layChoseFormation;
inline bool layPastedFormation;
inline bool noFog;
inline bool checkZombiesAllowed[ZombieType::NUM_ZOMBIE_TYPES]; // 僵尸选中情况
inline int choiceSpawnMode;                                    // 刷怪模式
inline bool buttonSetSpawn;                                    // 设置出怪
inline int targetSeedBank = 1;
inline int choiceSeedPacketIndex;
inline SeedType choiceSeedType = SeedType::SEED_NONE;
inline bool isImitaterSeed;
inline bool setSeedPacket;
inline Sexy::Rect mTouchVSShovelRect = {0, 85, 56, 56};
inline bool hideCoverLayer;
inline bool infiniteSun; // 无限阳光
inline bool drawDebugText;
inline bool drawDebugRects;
inline bool FreePlantAt;
inline bool ZombieCanNotWon;
inline bool PumpkinWithLadder; // AddPlant
inline bool endlessLastStand;

// 检查加农炮用
inline Plant *(*Board_GetPlantsOnLawn)(Board *board, unsigned int a2, unsigned int a3, int *a4);

inline int (*Board_GridToPixelX)(Board *board, unsigned int a2, unsigned int a3);

inline int (*Board_GridToPixelY)(Board *board, unsigned int a2, unsigned int a3);

inline int (*Board_PixelToGridY)(Board *board, unsigned int a2, unsigned int a3);

inline int (*Board_LoadBackgroundImages)(Board *board);

inline GridItem *(*Board_AddALadder)(Board *board, int x, int y);

inline Plant *(*Board_ToolHitTest)(Board *board, int a2, int a3);

inline int (*Board_RefreshSeedPacketFromCursor)(Board *board, int a2);

inline int (*Board_CanUseGameObject)(Board *board, GameObjectType a2);

inline Plant *(*Board_NewPlant)(Board *board, int a2, int a3, SeedType a4, SeedType a5, int a6);

inline Plant *(*Board_GetTopPlantAt)(Board *board, unsigned int a2, unsigned int a3, PlantPriority a4);

inline int (*Board_ClearCursor)(Board *board, int a2);

inline int (*Board_MouseDownWithTool)(Board *board, int a2, int a3, int a4, int a5, int a6);

inline int (*Board_CountPlantByType)(Board *board, int a2);

inline int (*Board_SetTutorialState)(Board *board, int a2);

inline Zombie *(*Board_ZombieHitTest)(Board *board, int a2, int a3, int a4);

inline int (*Board_HasConveyorBeltSeedBank)(Board *board, int a2);

inline int (*Board_InitCoverLayer)(Board *board);

// isLongPress的数值为：首次按下为0，后续按下为1
// playerIndex为0或者1，代表玩家1或者2
// buttonCode和GameButton通用
// 上 0
// 下 1
// 左 2
// 右 3
inline int (*Board_GameAxisMove)(Board *board, int buttonCode, int playerIndex, int isLongPress);

inline bool (*Board_IterateZombies)(Board *board, Zombie **zombie);

inline bool (*Board_IterateGridItems)(Board *board, GridItem **gridItem);

inline bool (*Board_IteratePlants)(Board *board, Plant **plant);

inline bool (*Board_IterateProjectiles)(Board *board, Projectile **projectile);

inline bool (*Board_IterateCoins)(Board *board, Coin **coin);

inline bool (*Board_IterateLawnMowers)(Board *board, int **lawnMower);

inline bool (*Board_IterateParticles)(Board *, TodParticleSystem **);

inline bool (*Board_IsSurvivalStageWithRepick)(Board *board);

inline void (*Board_PickUpTool)(Board *board, GameObjectType a2, int a3);

inline bool (*Board_ProgressMeterHasFlags)(Board *board);

inline void (*Board_GetButterButtonRect)(Sexy::Rect *, Board *);

inline Zombie *(*Board_ZombieTryToGet)(Board *, Zombie *);

inline int (*Board_MakeRenderOrder)(int, int, int);

inline bool (*Board_PlantUsesAcceleratedPricing)(Board *board, SeedType seedType);

inline bool (*Board_CanInteractWithBoardButtons)(Board *board);

inline bool (*Board_IsPlantInCursor)(Board *board);

inline void (*Board_MouseDownWithPlant)(Board *, int, int, int);

inline void (*Board_RemoveAllPlants)(Board *);

inline int (*Board_GetSeedBankExtraWidth)(Board *);

inline int (*Board_GetSeedPacketPositionX)(Board *, int, int, bool);

inline Coin *(*Board_AddCoin)(Board *, int, int, int, int);

inline bool (*Board_CanTakeSunMoney)(Board *, int, int);

inline GridItem *(*Board_GetGridItemAt)(Board *, GridItemType, int, int);

inline void (*Board_GetZenButtonRect)(Sexy::Rect *, Board *, GameObjectType);

inline GridItem *(*Board_GetLadderAt)(Board *, int, int);

inline int (*Board_PixelToGridXKeepOnBoard)(Board *, int, int);

inline int (*Board_PixelToGridYKeepOnBoard)(Board *, int, int);

inline bool (*Board_IsValidCobCannonSpotHelper)(Board *, int, int);

inline int (*Board_PickRowForNewZombie)(Board *, int);

inline bool (*Board_IsPoolSquare)(Board *, int, int);

inline void (*Board_ZombiePickerInit)(ZombiePicker *);

inline ZombieType (*Board_GetIntroducedZombieType)(Board *);

inline void (*Board_ZombiePickerInitForWave)(ZombiePicker *);

inline void (*Board_PutZombieInWave)(Board *, ZombieType, int, ZombiePicker *);

inline ZombieType (*Board_PickZombieType)(Board *, int, int, ZombiePicker *);

inline bool (*Board_HasLevelAwardDropped)(Board *);

inline void (*Board_SpawnZombiesFromGraves)(Board *);

inline void (*Board_ClearAdvice)(Board *, int);

inline void (*Board_NextWaveComing)(Board *);

inline int (*Board_TotalZombiesHealthInWave)(Board *, int);

inline void (*Board_ClearAdviceImmediately)(Board *);

inline void (*Board_DisplayAdviceAgain)(Board *, int *, MessageStyle, AdviceType);

inline int (*Board_GridCellWidth)(Board *, int, int);

inline int (*Board_GridCellHeight)(Board *, int, int);

inline SeedType (*Board_GetSeedTypeInCursor)(Board *, int);

inline int (*Board_KillAllZombiesInRadius)(Board *, int, int, int, int, int, bool, int);

inline void (*Board_TryToSaveGame)(Board *board);

inline void (*Board_RemoveCutsceneZombies)(Board *);

inline int (*Board_CountZombiesOnScreen)(Board *);

inline float (*Board_GetPosYBasedOnRow)(Board *board, float, int);

inline bool (*Board_CanTakeDeathMoney)(Board *, int);

inline Zombie *(*Board_GetBossZombie)(Board *);

inline void (*Board_RemoveAllMowers)(Board *);

inline void (*Board_ResetLawnMowers)(Board *board);

inline void (*Board_RemoveAllZombies)(Board *);

inline GamepadControls *(*Board_GetGamepadControlsByPlayerIndex)(Board *, int);


inline void (*old_FixBoardAfterLoad)(Board *board);

inline int (*old_LawnSaveGame)(Board *a1, int *a2);

inline void (*old_Board_UpdateGame)(Board *board);

inline void (*old_Board_UpdateGameObjects)(Board *board);

inline void (*old_Board_DrawDebugText)(Board *board, Sexy::Graphics *graphics);

inline void (*old_Board_DrawDebugObjectRects)(Board *board, Sexy::Graphics *graphics);

inline int (*old_Board_GetCurrentPlantCost)(Board *board, SeedType a2, SeedType a3);

inline PlantingReason (*old_Board_CanPlantAt)(Board *board, int theGridX, int theGridY, SeedType seedType);

inline bool (*old_Board_PlantingRequirementsMet)(Board *board, SeedType theSeedType);

inline void (*old_BoardZombiesWon)(Board *board, Zombie *zombie);

inline Plant *(*old_Board_AddPlant)(Board *board, int x, int y, SeedType seedType, SeedType theImitaterType, int playerIndex, bool doPlantEffect);

inline void (*old_Board_KeyDown)(Board *board, Sexy::KeyCode theKey);

inline void (*old_Board_UpdateSunSpawning)(Board *board);

inline void (*old_Board_UpdateZombieSpawning)(Board *board);

inline void (*old_Board_UpdateIce)(Board *board);

inline void (*old_Board_PickBackground)(Board *board);

inline bool (*old_Board_StageHasPool)(Board *board);

inline void (*old_Board_UpdateFwoosh)(Board *board);

inline void (*old_Board_DrawFog)(Board *board, Sexy::Graphics *g);

inline Zombie *(*old_Board_AddZombieInRow)(Board *board, ZombieType theZombieType, int theRow, int theFromWave, bool playAnim);

inline Zombie *(*old_Board_AddZombie)(Board *, ZombieType theZombieType, int theFromWave, bool theIsRustle);

inline void (*old_Board_Update)(Board *board);

inline bool (*old_Board_IsFlagWave)(Board *board, int currentWave);

inline void (*old_Board_SpawnZombieWave)(Board *board);

inline void (*old_Board_DrawProgressMeter)(Board *board, Sexy::Graphics *graphics, int a3, int a4);

inline bool (*old_Board_IsLevelDataLoaded)(Board *board);

inline bool (*old_Board_NeedSaveGame)(Board *board);

inline void (*old_Board_DrawBackdrop)(Board *board, Sexy::Graphics *graphics);

inline void (*old_Board_Pause)(Board *board, bool a2);

inline void (*old_Board_InitLawnMowers)(Board *board);

inline void (*old_Board_PickZombieWaves)(Board *board);

inline void (*old_Board_RemovedFromManager)(Board *board, int *manager);

inline void (*old_Board_InitLevel)(Board *board);

inline void (*old_Board_ButtonDepress)(Board *board, int id);

inline void (*old_Board_Board)(Board *board, LawnApp *mApp);

inline void (*old_Board_MouseUp)(Board *board, int a2, int a3, int a4);

inline void (*old_Board_MouseDrag)(Board *board, int x, int y);

inline void (*old_Board_MouseDown)(Board *board, int x, int y, int theClickCount);

inline void (*old_Board_MouseMove)(Board *board, int x, int y);

inline bool (*old_Board_MouseHitTest)(Board *board, int x, int y, HitResult *hitResult, bool posScaled);

inline void (*old_Board_FadeOutLevel)(Board *board);

inline void (*old_Board_AddSunMoney)(Board *board, int theAmount, int playerIndex);

inline void (*old_Board_AddDeathMoney)(Board *board, int theAmount);

inline void (*old_Board_UpdateLevelEndSequence)(Board *board);

inline void (*old_Board_UpdateGridItems)(Board *board);

inline void (*old_Board_startLevel)(Board *board);

inline void (*old_Board_DrawUITop)(Board *board, Sexy::Graphics *graphics);

inline bool (*old_Board_RowCanHaveZombieType)(Board *board, int theRow, ZombieType theZombieType);

inline void (*old_Board_ShakeBoard)(Board *board, int theShakeAmountX, int theShakeAmountY);

inline void (*old_Board_UpdateFog)(Board *board);

inline void (*old_Board_GetShovelButtonRect)(Sexy::Rect *rect, Board *board);

inline void (*old_Board_DrawZenButtons)(Board *board, Sexy::Graphics *a2);

inline int (*old_Board_GetNumSeedsInBank)(Board *, bool);


void FixBoardAfterLoad(Board *board);

void SyncReanimation(Board *a1, Reanimation *a2, int *theSaveGameContext);

int LawnSaveGame(Board *board, int *a2);

const char *GetNameByAchievementId(AchievementId::AchievementId theAchievementId);

Sexy::Image *GetIconByAchievementId(AchievementId::AchievementId theAchievementId);

void Board_FixReanimErrorAfterLoad(Board *board);

void Board_GetShovelButtonRect(Sexy::Rect *, Board *);

bool TRect_Contains(Sexy::Rect *rect, int x, int y);

void Board_MouseDragSecond(Board *board, int x, int y);

void Board_MouseUpSecond(Board *board, int x, int y, int theClickCount);

void Board_LoadFormation(Board *board, const char *formation);

bool Board_GrantAchievement(Board *board, AchievementId::AchievementId theAchievementId, bool show);

void Board_DoPlantingAchievementCheck(Board *board, SeedType theType);

int Board_GetLiveZombiesCount(Board *board);

bool Board_ZenGardenItemNumIsZero(Board *, CursorType);

void Board_SetGrids(Board *board);

void Board_parseFormationSegment(Board *board, char *segment);

void Board_LoadFormation(Board *board, char *formation);

bool Board_KeyUp(Board *board, int keyCode);

bool Board_StageIsNight(Board *board);

bool Board_StageHasRoof(Board *board);

bool Board_StageHas6Rows(Board *board);

void Board_DrawHammerButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp);

void Board_DrawButterButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp);

void Board_DrawStartButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp);

int Board_GetLiveGargantuarCount(Board *board);

void Board_UpdateButtons(Board *board);

#endif // PVZ_LAWN_BOARD_H
