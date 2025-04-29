#ifndef PVZ_LAWN_CHALLENGE_H
#define PVZ_LAWN_CHALLENGE_H

#include "../SexyAppFramework/Graphics.h"
#include "PvZ/Enums.h"

#define BEGHOULED_MAX_GRIDSIZEX 8
#define BEGHOULED_MAX_GRIDSIZEY 5
#define ART_CHALLEGE_SIZE_X 8
#define MAX_PICK_GRID_SIZE 50

constexpr const int BEGHOULED_WINNING_SCORE = 75;
constexpr const int SLOT_MACHINE_WINNING_SCORE = 2000;
constexpr const int ZOMBIQUARIUM_WINNING_SCORE = 1000;
constexpr const int I_ZOMBIE_WINNING_SCORE = 5;
constexpr const int MAX_PORTALS = 4;
constexpr const int MAX_SQUIRRELS = 7;
constexpr const int MAX_SCARY_POTS = 54;
constexpr const int STORM_FLASH_TIME = 150;

class LawnApp;
class Board;
class Plant;
class Zombie;
class GridItem;
class SeedPacket;
class HitResult;

class Challenge {
public:
    int *vTable;                          // 0
    int unk1[3];                          // 1 ~ 3
    LawnApp *mApp;                        // 4
    Board *mBoard;                        // 5
    int *mHelpBarWidget;                  // 6
    bool mBeghouledMouseCapture;          // 28
    int mBeghouledMouseDownX;             // 8
    int mBeghouledMouseDownY;             // 9
    bool mBeghouledEated[9][6];           // 40 ~  93
    bool mBeghouledPurcasedUpgrade[3];    // 94 ~ 96
    int mBeghouledMatchesThisMove;        // 25
    ChallengeState mChallengeState;       // 26
    int mChallengeStateCounter;           // 27
    int mConveyorBeltCounter;             // 28
    int unk2;                             // 29
    int mChallengeScore;                  // 30
    bool mShowBowlingLine;                // 124
    SeedType mLastConveyorSeedType;       // 32
    int mSurvivalStage;                   // 33
    int mSlotMachineRollCount;            // 34
    int mReanimChallenge;                 // 35
    int mReanimCloud[6];                  // 36 ~ 41
    int mCloudCounter[6];                 // 42 ~ 47
    int mChallengeGridX;                  // 48
    int mChallengeGridY;                  // 49
    int mScaryPotterPots;                 // 50
    int mRainCounter;                     // 51
    int mTreeOfWisdomTalkIndex;           // 52
    int unk3[14];                         // 53 ~ 66
    float mHeavyWeaponX;                  // 67
    float mHeavyWeaponY;                  // 68
    float mHeavyWeaponAngle;              // 69
    int unkHeavyWeaponWithInitValue1000;  // 70
    int mHeavyWeaponCatTailAttackCounter; // 71
    int mHeavyWeaponCatTailLevel;         // 72
    int mHeavyWeaponPeaLevel;             // 73
    int mHeavyWeaponSnowPeaCounter;       // 74
    int mHeavyWeaponTorchWoodCounter;     // 75
    int unkHeavyWeaponWithInitValue10;    // 76
    ReanimationID mReanimHeavyWeaponID1;  // 77
    ReanimationID mReanimHeavyWeaponID2;  // 78
    ReanimationID mReanimHeavyWeaponID3;  // 79
    // 大小80个整数

    Challenge();

    void Create();
    void Update();
    void HeavyWeaponFire(float a2, float a3);
    void IZombieDrawPlant(Sexy::Graphics *g, Plant *thePlant);
    void HeavyWeaponUpdate();
    bool IZombieEatBrain(Zombie *theZombie);
    void DrawArtChallenge(Sexy::Graphics *g);
    PlantingReason CanPlantAt(int theGridX, int theGridY, SeedType theSeedType);
    void InitLevel();
    void InitZombieWaves();
    void TreeOfWisdomFertilize();
    void LastStandUpdate();
    void DrawHeavyWeapon(Sexy::Graphics *g);
    bool UpdateZombieSpawning();
    void HeavyWeaponPacketClicked(SeedPacket *theSeedPacket);
    static ZombieType IZombieSeedTypeToZombieType(SeedType theSeedType);
    void StartLevel();
    void Delete();
    void ScaryPotterOpenPot(GridItem *theScaryPot);
    GridItem *IZombieGetBrainTarget(Zombie *theZombie);
    void IZombieSquishBrain(GridItem *theBrain);
};

/***************************************************************************************************************/
inline int targetWavesToJump = 1;
inline bool requestJumpSurvivalStage;
inline bool stopSpawning; // 暂停刷怪


inline int (*Challenge_ScaryPotterCountSunInPot)(Challenge *a1, GridItem *a2);

inline void (*Challenge_IZombieScoreBrain)(Challenge *, GridItem *);

inline bool (*Challenge_MouseDown)(Challenge *, int, int, int, HitResult *, int);

inline SeedType (*Challenge_GetArtChallengeSeed)(Challenge *, int, int);

inline void (*Challenge_TreeOfWisdomOpenStore)(Challenge *);

inline bool (*Challenge_IsZombieSeedType)(SeedType type);

inline bool (*Challenge_IsMPSeedType)(SeedType type);

inline bool (*Challenge_IsMPSuddenDeath)(Challenge *);

inline void (*Challenge_InitZombieWavesFromList)(Challenge *, ZombieType *, int);

inline void (*Challenge_IZombieSetupPlant)(Challenge *challenge, Plant *plant);

inline void (*Challenge_IZombiePlaceZombie)(Challenge *challenge, ZombieType, int, int);

inline void (*Challenge_GraveDangerSpawnGraveAt)(Challenge *challenge, int x, int y);

inline void (*Challenge_IZombieSetPlantFilterEffect)(Challenge *, Plant *, FilterEffectType);

inline void (*Challenge_PlantAdded)(Challenge *, Plant *);


inline void (*old_Challenge_Update)(Challenge *a);

inline void (*old_Challenge_Challenge)(Challenge *a);

inline void (*old_Challenge_HeavyWeaponFire)(Challenge *challenge, float a2, float a3);

inline void (*old_Challenge_HeavyWeaponUpdate)(Challenge *challenge);

inline void (*old_Challenge_InitLevel)(Challenge *challenge);

inline void (*old_Challenge_InitZombieWaves)(Challenge *a);

inline void (*old_Challenge_TreeOfWisdomFertilize)(Challenge *);

inline ZombieType (*old_Challenge_IZombieSeedTypeToZombieType)(SeedType type);

inline bool (*old_Challenge_UpdateZombieSpawning)(Challenge *);

inline void (*old_Challenge_HeavyWeaponPacketClicked)(Challenge *challenge, SeedPacket *seedPacket);

inline void (*old_Challenge_StartLevel)(Challenge *challenge);

inline void (*old_Challenge_Delete)(Challenge *challenge);

inline void (*old_Challenge_ScaryPotterOpenPot)(Challenge *, GridItem *theScaryPot);

inline GridItem *(*old_Challenge_IZombieGetBrainTarget)(Challenge *, Zombie *theZombie);

inline void (*old_Challenge_IZombieSquishBrain)(Challenge *, GridItem *theBrain);

#endif // PVZ_LAWN_CHALLENGE_H
