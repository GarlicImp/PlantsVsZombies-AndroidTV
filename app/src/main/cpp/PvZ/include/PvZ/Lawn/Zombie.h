#ifndef PVZ_TV_1_1_5_ZOMBIE_H
#define PVZ_TV_1_1_5_ZOMBIE_H

#include "PvZ/Enums.h"

#define MAX_ZOMBIE_FOLLOWERS 4
#define NUM_BOBSLED_FOLLOWERS 3
#define NUM_BACKUP_DANCERS 4
#define NUM_BOSS_BUNGEES 3

constexpr const int ZOMBIE_START_RANDOM_OFFSET = 40;
constexpr const int BUNGEE_ZOMBIE_HEIGHT = 3000;
constexpr const int RENDER_GROUP_SHIELD = 1;
constexpr const int RENDER_GROUP_ARMS = 2;
constexpr const int RENDER_GROUP_OVER_SHIELD = 3;
constexpr const int RENDER_GROUP_BOSS_BACK_LEG = 4;
constexpr const int RENDER_GROUP_BOSS_FRONT_LEG = 5;
constexpr const int RENDER_GROUP_BOSS_BACK_ARM = 6;
constexpr const int RENDER_GROUP_BOSS_FIREBALL_ADDITIVE = 7;
constexpr const int RENDER_GROUP_BOSS_FIREBALL_TOP = 8;
constexpr const int ZOMBIE_LIMP_SPEED_FACTOR = 2;
constexpr const int POGO_BOUNCE_TIME = 80;
constexpr const int DOLPHIN_JUMP_TIME = 120;
constexpr const int JackInTheBoxZombieRadius = 115;
constexpr const int JackInTheBoxPlantRadius = 90;
constexpr const int BOBSLED_CRASH_TIME = 150;
constexpr const int ZOMBIE_BACKUP_DANCER_RISE_HEIGHT = -200;
constexpr const int BOSS_FLASH_HEALTH_FRACTION = 10;
constexpr const int TICKS_BETWEEN_EATS = 4;
constexpr const int DAMAGE_PER_EAT = TICKS_BETWEEN_EATS;
constexpr const float THOWN_ZOMBIE_GRAVITY = 0.05f;
constexpr const float CHILLED_SPEED_FACTOR = 0.4f;
constexpr const float CLIP_HEIGHT_LIMIT = -100.0f;
constexpr const float CLIP_HEIGHT_OFF = -200.0f;
//const Color ZOMBIE_MINDCONTROLLED_COLOR = Color(128, 0, 192, 255);

enum ZombieAttackType
{
    ATTACKTYPE_CHEW,
    ATTACKTYPE_DRIVE_OVER,
    ATTACKTYPE_VAULT,
    ATTACKTYPE_LADDER
};

enum ZombieParts
{
    PART_BODY,
    PART_HEAD,
    PART_HEAD_EATING,
    PART_TONGUE,
    PART_ARM,
    PART_HAIR,
    PART_HEAD_YUCKY,
    PART_ARM_PICKAXE,
    PART_ARM_POLEVAULT,
    PART_ARM_LEASH,
    PART_ARM_FLAG,
    PART_POGO,
    PART_DIGGER
};

class ZombieDrawPosition
{
public:
    int                             mHeadX;
    int                             mHeadY;
    int                             mArmY;
    float                           mBodyY;
    float                           mImageOffsetX;
    float                           mImageOffsetY;
    float                           mClipHeight;
};

class Plant;
class Reanimation;
class TodParticleSystem;
class Zombie : public GameObject {
public:
    enum
    {
        ZOMBIE_WAVE_DEBUG = -1,
        ZOMBIE_WAVE_CUTSCENE = -2,
        ZOMBIE_WAVE_UI = -3,
        ZOMBIE_WAVE_WINNER = -4
    };

    ZombieType mZombieType;       // 13
    ZombiePhase mZombiePhase;    // 14
    float mPosX;                              // 15
    float mPosY;                              // 16
    float mVelX;                              // 17
    int mAnimCounter;                         // 18
    int mGroanCounter;                        // 19
    int mAnimTicksPerFrame;                   // 20
    int mAnimFrames;                          // 21
    int mFrame;                               // 22
    int mPrevFrame;                           // 23
    bool mVariant;                            // 96
    bool mIsEating;                           // 97
    int mJustGotShotCounter;                  // 25
    int mShieldJustGotShotCounter;            // 26
    int mShieldRecoilCounter;                 // 27
    int mZombieAge;                           // 28
    ZombieHeight mZombieHeight; // 29
    int mPhaseCounter;                        // 30
    int mFromWave;                            // 31
    bool mDroppedLoot;                        // 128
    int mZombieFade;                          // 33
    bool mFlatTires;                          // 136
    int mUseLadderCol;                        // 35
    int mTargetCol;                           // 36
    float mAltitude;                          // 37
    bool mHitUmbrella;                        // 152
    TRect mZombieRect;                        // 39 ~ 42
    TRect mZombieAttackRect;                  // 43 ~ 46
    int mChilledCounter;                      // 47
    int mButteredCounter;                     // 48
    int mIceTrapCounter;                      // 49
    bool mMindControlled;                     // 200
    bool mBlowingAway;                        // 201
    bool mHasHead;                            // 202
    bool mHasArm;                             // 203
    bool mHasObject;                          // 204
    bool mInPool;                             // 205
    bool mOnHighGround;                       // 206
    bool mYuckyFace;                          // 207
    int mYuckyFaceCounter;                    // 52
    HelmType::HelmType mHelmType;             // 53
    int mBodyHealth;                          // 54
    int mBodyMaxHealth;                       // 55
    int mHelmHealth;                          // 56
    int mHelmMaxHealth;                       // 57
    ShieldType::ShieldType mShieldType;       // 58
    int mShieldHealth;                        // 59
    int mShieldMaxHealth;                     // 60
    int mFlyingHealth;                        // 61
    int mFlyingMaxHealth;                     // 62
    bool mDead;                               // 252
    Zombie *mRelatedZombieID;                 // 64
    Zombie *mFollowerZombieID[MAX_ZOMBIE_FOLLOWERS];             // 65 ~ 68
    bool mPlayingSong;                        // 276
    int mParticleOffsetX;                     // 70
    int mParticleOffsetY;                     // 71
    int *mAttachmentID;                       // 72
    int mSummonCounter;                       // 73
    int mBodyReanimID;                        // 74
    float mScaleZombie;                       // 75
    float mVelZ;                              // 76
    float mOrginalAnimRate;                   // 77
    Plant *mTargetPlantID;                    // 78
    int mBossMode;                            // 79
    int mTargetRow;                           // 80
    int mBossBungeeCounter;                   // 81
    int mBossStompCounter;                    // 82
    int mBossHeadCounter;                     // 83
    int mBossFireBallReanimID;                // 84
    int mSpecialHeadReanimID;                 // 85
    int mFireballRow;                         // 86
    bool mIsFireBall;                         // 348
    int mMoweredReanimID;                     // 88
    int mLastPortalX;                         // 89
    bool mBloated;                            // 360
    int unkMems[6];                           // 91 ~ 96
    int mZombieID;                            // 97
    // 大小98个整数

    void ZombieInitialize(int theRow, ZombieType theType, bool theVariant, Zombie *theParentZombie, int theFromWave, bool isVisible);
    void Draw(Sexy::Graphics *g);
    void DieNoLoot();
    void Update();
    void UpdateZombiePeaHead();
    void UpdateZombieGatlingHead();
    void BurnRow(int theRow);
    void UpdateZombieJalapenoHead();
    void BossDestroyIceballInRow(int theRow);
    int GetDancerFrame();
    void RiseFromGrave(int theGridX, int theGridY);
    void EatPlant(Plant* thePlant);
    void DetachShield();
    void CheckForBoardEdge();
    void DrawBossPart(Sexy::Graphics *graphics, int theBossPart);
    void BossSpawnAttack();
    void DrawBungeeCord(Sexy::Graphics *graphics, int theOffsetX, int theOffsetY);
    bool IsTangleKelpTarget();
    void DrawReanim(Sexy::Graphics *graphics, ZombieDrawPosition *theZombieDrawPosition, int theBaseRenderGroup);
    void DropHead(unsigned int theDamageFlags);
};

class ZombieDefinition
{
public:
    ZombieType                      mZombieType;
    ReanimationType                 mReanimationType;
    int                             mZombieValue;
    int                             mStartingLevel;
    int                             mFirstAllowedWave;
    int                             mPickWeight;
    const SexyChar*                 mZombieName;
};
extern ZombieDefinition gZombieDefs[NUM_ZOMBIE_TYPES];

/*inline*/ ZombieDefinition&            GetZombieDefinition(ZombieType theZombieType);

/***************************************************************************************************************/
inline bool zombieBloated;
inline bool showZombieBodyHealth;
inline bool showGargantuarHealth;
inline bool showHelmAndShieldHealth;
inline int maidCheats; // 女仆秘籍
inline int boardEdgeAdjust;
inline int zombieSetScale;
inline ZombieDefinition gZombieTrashBinDef = {ZombieType::ZOMBIE_TRASH_BIN, ReanimationType::REANIM_ZOMBIE, 1, 99, 1, 4000, "TRASHCAN_ZOMBIE"};

inline void (*Zombie_ApplyBurn)(Zombie *zombie);

inline void (*Zombie_ApplyButter)(Zombie *zombie);

inline void (*Zombie_GetZombieRect)(TRect *a1, Zombie *a2);

inline bool (*Zombie_IsImmobilizied)(Zombie *zombie);

inline bool (*Zombie_EffectedByDamage)(Zombie *zombie, int flag);

inline void (*Zombie_RemoveColdEffects)(Zombie *zombie);

inline void (*Zombie_StartEating)(Zombie *);

inline void (*Zombie_TakeDamage)(Zombie *, int, unsigned int);

inline bool (*Zombie_IsWalkingBackwards)(Zombie *);

inline void (*Zombie_AddAttachedParticle)(Zombie *, int, int, int);

inline bool (*Zombie_CanBeFrozen)(Zombie *);

inline void (*Zombie_StopEating)(Zombie *);

inline void (*Zombie_DropArm)(Zombie *, unsigned int);

inline void (*Zombie_PlayZombieReanim)(Zombie *, const char *, int, int, float);

inline void (*Zombie_SetupReanimLayers)(Reanimation *, ZombieType);

inline void (*Zombie_SetupShieldReanims)(ZombieType, Reanimation *);

inline void (*Zombie_UpdateReanim)(Zombie *);

inline void (*Zombie_UpdateActions)(Zombie *);

inline void (*Zombie_UpdatePlaying)(Zombie *);

inline bool (*Zombie_IsDeadOrDying)(Zombie *);

inline bool (*Zombie_IsOnBoard)(Zombie *);

inline void (*Zombie_ReanimShowPrefix)(Zombie *, const char *, int);

inline void (*Zombie_ReanimShowTrack)(Zombie *, const char *, int);

inline void (*Zombie_TakeHelmDamage)(Zombie *, int, unsigned int);

inline bool (*Zombie_IsFlying)(Zombie *);

inline void (*Zombie_TakeFlyingDamage)(Zombie *, int, unsigned int);

inline void (*Zombie_TakeShieldDamage)(Zombie *, int, unsigned int);

inline void (*Zombie_TakeBodyDamage)(Zombie *, int, unsigned int);

inline void (*Zombie_UpdateDamageStates)(Zombie *, unsigned int);

inline int (*Zombie_GetShieldDamageIndex)(Zombie *);

inline int (*Zombie_GetHelmDamageIndex)(Zombie *);

inline int (*Zombie_GetBodyDamageIndex)(Zombie *);

inline void (*Zombie_GetTrackPosition)(Zombie *, const char *, float *, float *);

inline void (*Zombie_UpdateAnimationSpeed)(Zombie *);

inline void (*Zombie_HitIceTrap)(Zombie *);

inline void (*Zombie_Zombie)(Zombie *);


inline void (*old_Zombie_Update)(Zombie *a1);

inline void (*old_Zombie_UpdateZombiePeaHead)(Zombie *zombie);

inline void (*old_Zombie_UpdateZombieGatlingHead)(Zombie *zombie);

inline void (*old_Zombie_UpdateZombieJalapenoHead)(Zombie *zombie);

inline void (*old_Zombie_Draw)(Zombie *zombie, Sexy::Graphics *graphics);

inline void (*old_Zombie_DrawBossPart)(Zombie *a1, Sexy::Graphics *graphics, int theBossPart);

inline bool (*old_ZombieTypeCanGoInPool)(ZombieType zombieType);

inline void (*old_Zombie_RiseFromGrave)(Zombie *zombie, int gridX, int gridY);

inline void (*old_Zombie_EatPlant)(Zombie *a, Plant *a2);

inline void (*old_Zombie_DetachShield)(Zombie *zombie);

inline void (*old_Zombie_ZombieInitialize)(Zombie *zombie, int theRow, ZombieType theType, bool theVariant, Zombie *theParentZombie, int theFromWave, bool isVisible);

inline ZombieDefinition &(*old_GetZombieDefinition)(ZombieType type);

inline void (*old_Zombie_DieNoLoot)(Zombie *);

inline void (*old_Zombie_DrawReanim)(Zombie *zombie, Sexy::Graphics *graphics, ZombieDrawPosition *zombieDrawPosition, int theBaseRenderGroup);

inline void (*old_Zombie_DropHead)(Zombie *zombie, unsigned int a2);



void Zombie_AddButter(Zombie *zombieUnderButter);

bool ZombieTypeCanGoInPool(ZombieType theZombieType);

void Zombie_SetZombatarReanim(Zombie *zombie);

bool Zombie_IsZombatarZombie(ZombieType type);

void Zombie_SetupLostArmReanim(Zombie *zombie);

#endif // PVZ_TV_1_1_5_ZOMBIE_H
