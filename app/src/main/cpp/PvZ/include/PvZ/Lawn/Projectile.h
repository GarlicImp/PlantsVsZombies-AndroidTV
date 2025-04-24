#ifndef PVZ_LAWN_PROJECTILE_H
#define PVZ_LAWN_PROJECTILE_H

#include "PvZ/Enums.h"

class Plant;
class Zombie;
class GridItem;

class ProjectileDefinition
{
public:
    ProjectileType          mProjectileType;
    int                     mImageRow;
    int                     mDamage;
};
extern ProjectileDefinition gProjectileDefinition[NUM_PROJECTILES];

class Projectile : public GameObject {
public:
    int mFrame;                                     // 13
    int mNumFrames;                                 // 14
    int mAnimCounter;                               // 15
    float mPosX;                                    // 16
    float mPosY;                                    // 17
    float mPosZ;                                    // 18
    float mVelX;                                    // 19
    float mVelY;                                    // 20
    float mVelZ;                                    // 21
    float mAccZ;                                    // 22
    float mShadowY;                                 // 23
    bool mDead;                                     // 96
                                                    //    short mNewProjectileLastX; // 在对齐空隙新增成员，98 ~ 99
    int mAnimTicksPerFrame;                         // 25
    ProjectileMotion mMotionType; // 26
    ProjectileType mProjectileType; // 27
    int mProjectileAge;                             // 28
    int mClickBackoffCounter;                       // 29
    float mRotation;                                // 30
    float mRotationSpeed;                           // 31
    bool mOnHighGround;                             // 128
                                                    //    short mNewProjectileLastY; // 在对齐空隙新增成员，130 ~ 131
    int mDamageRangeFlags;                          // 33
    int mHitTorchwoodGridX;                         // 34
    int *mAttachmentID;                             // 35
    float mCobTargetX;                              // 36
    int mCobTargetRow;                              // 37
    Zombie *mTargetZombieID;                        // 38
    int mLastPortalX;                               // 39
    int unkInt;                                     // 40
    // 大小41个整数

    int ProjectileInitialize(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType);
    void ConvertToFireball(int theGridX);
    void ConvertToPea(int theGridX);
    void Update();
    void DoImpact(Zombie* theZombie);
    void CheckForCollision();
    Zombie* FindCollisionMindControlledTarget();
    ProjectileDefinition&   GetProjectileDef();
};

/***************************************************************************************************************/
// 随机子弹
inline bool randomBullet;
inline int bulletSpinnerChosenNum = -1;
inline bool isOnlyPeaUseable;
inline bool banCobCannon;
inline bool banStar;
inline bool isOnlyTouchFireWood;
inline bool ColdPeaCanPassFireWood;


inline void (*Projectile_Die)(Projectile *a);

inline void (*Projectile_GetProjectileRect)(TRect *a1, Projectile *a2);

inline Plant *(*Projectile_FindCollisionTargetPlant)(Projectile *a1);

inline bool (*Projectile_CantHitHighGround)(Projectile *a);

inline Zombie *(*Projectile_FindCollisionTarget)(Projectile *a);

inline GridItem *(*Projectile_FindCollisionTargetGridItem)(Projectile *a);

inline void (*Projectile_DoImpactGridItem)(Projectile *a, GridItem *a2);

inline void (*Projectile_PlayImpactSound)(Projectile *, Zombie *);

inline bool (*Projectile_IsSplashDamage)(Projectile *, Zombie *);

inline void (*Projectile_DoSplashDamage)(Projectile *, Zombie *, int);

unsigned inline int (*Projectile_GetDamageFlags)(Projectile *, Zombie *);

inline bool (*Projectile_PeaAboutToHitTorchwood)(Projectile *);


inline int (*old_Projectile_ProjectileInitialize)(Projectile *projectile, int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType);

inline void (*old_Projectile_ConvertToFireball)(Projectile *projectile, int aGridX);

inline void (*old_Projectile_ConvertToPea)(Projectile *projectile, int aGridX);

inline void (*old_Projectile_Update)(Projectile *a);

inline void (*old_Projectile_DoImpact)(Projectile *a1, Zombie *a2);

#endif // PVZ_LAWN_PROJECTILE_H
