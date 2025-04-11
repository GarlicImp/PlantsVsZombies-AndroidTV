#include "PvZ/Lawn/Projectile.h"
#include "PvZ/Symbols.h"
#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/Zombie.h"
#include "PvZ/Lawn/Plant.h"
#include "PvZ/Lawn/GridItem.h"

ProjectileDefinition gProjectileDefinition[] = {  //0x69F1C0
    { ProjectileType::PROJECTILE_PEA,           0,  20  },
    { ProjectileType::PROJECTILE_SNOWPEA,       0,  20  },
    { ProjectileType::PROJECTILE_CABBAGE,       0,  40  },
    { ProjectileType::PROJECTILE_MELON,         0,  80  },
    { ProjectileType::PROJECTILE_PUFF,          0,  20  },
    { ProjectileType::PROJECTILE_WINTERMELON,   0,  80  },
    { ProjectileType::PROJECTILE_FIREBALL,      0,  40  },
    { ProjectileType::PROJECTILE_STAR,          0,  20  },
    { ProjectileType::PROJECTILE_SPIKE,         0,  20  },
    { ProjectileType::PROJECTILE_BASKETBALL,    0,  75  },
    { ProjectileType::PROJECTILE_KERNEL,        0,  20  },
    { ProjectileType::PROJECTILE_COBBIG,        0,  300 },
    { ProjectileType::PROJECTILE_BUTTER,        0,  40  },
    { ProjectileType::PROJECTILE_ZOMBIE_PEA,    0,  20  }
};

int Projectile_ProjectileInitialize(Projectile *projectile, int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType) {
    //    projectile->mNewProjectileLastX = theX;
    //    projectile->mNewProjectileLastY = theY;
    if (!isOnlyTouchFireWood) {
        // 僵尸子弹与加农炮子弹NULL
        if (theProjectileType == ProjectileType::PROJECTILE_COBBIG || theProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA) {
            return old_Projectile_ProjectileInitialize(projectile, theX, theY, theRenderOrder, theRow, theProjectileType);
        }
        if (theProjectileType == ProjectileType::PROJECTILE_STAR && banStar) {
            return old_Projectile_ProjectileInitialize(projectile, theX, theY, theRenderOrder, theRow, theProjectileType);
        }
        if (isOnlyPeaUseable && theProjectileType != ProjectileType::PROJECTILE_PEA) {
            return old_Projectile_ProjectileInitialize(projectile, theX, theY, theRenderOrder, theRow, theProjectileType);
        }
        if (bulletSpinnerChosenNum != -1) {
            theProjectileType = (ProjectileType)bulletSpinnerChosenNum;
        }
        if (randomBullet) {
            theProjectileType = (ProjectileType)randomInt(1, 12);
        }
        if (theProjectileType == ProjectileType::PROJECTILE_COBBIG && banCobCannon) {
            theProjectileType = (ProjectileType)randomInt(1, 10); // 同时降低好友玉米黄油的概率!!
        }
    }
    return old_Projectile_ProjectileInitialize(projectile, theX, theY, theRenderOrder, theRow, theProjectileType);
}


void Projectile_ConvertToFireball(Projectile *projectile, int aGridX) {
    if (isOnlyTouchFireWood) {
        if (bulletSpinnerChosenNum != -1) {
            projectile->mProjectileType = (ProjectileType)bulletSpinnerChosenNum;
            return;
        }
        if (randomBullet) {
            projectile->mProjectileType = (ProjectileType)randomInt(1, 12);
            return;
        }
    }
    return old_Projectile_ConvertToFireball(projectile, aGridX);
}

void Projectile_ConvertToPea(Projectile *projectile, int aGridX) {
    if (ColdPeaCanPassFireWood) {
        if (projectile->mHitTorchwoodGridX != aGridX) {
            Attachment_AttachmentDie(projectile->mAttachmentID);
            projectile->mHitTorchwoodGridX = aGridX;
            projectile->mProjectileType = ProjectileType::PROJECTILE_SNOWPEA;
            LawnApp_PlayFoley(projectile->mApp, FoleyType::Throw);
        }
        return;
    }
    old_Projectile_ConvertToPea(projectile, aGridX);
}

void Projectile::Update() {
    if (requestPause) {
        // 如果开了高级暂停
        return;
    }
    return old_Projectile_Update(this);
}

void Projectile_DoImpact(Projectile *projectile, Zombie *zombie) {
    // 负责 直线子弹帧伤
    if (!projectilePierce) {
        return old_Projectile_DoImpact(projectile, zombie);
    }
    ProjectileType mProjectileType = projectile->mProjectileType;
    ProjectileMotion::ProjectileMotion mMotionType = projectile->mMotionType;
    Projectile_PlayImpactSound(projectile, zombie);
    if (Projectile_IsSplashDamage(projectile, zombie)) {
        if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL && zombie != nullptr) {
            Zombie_RemoveColdEffects(zombie);
        }
        Projectile_DoSplashDamage(projectile, zombie, 0);
    } else if (zombie != nullptr) {
        int mProjectileDamage = Projectile_GetProjectileDef(projectile).mDamage;
        unsigned int mDamageFlags = Projectile_GetDamageFlags(projectile, zombie);
        Zombie_TakeDamage(zombie, mProjectileDamage, mDamageFlags);
    }
    float mPosX = projectile->mPosX;
    float mPosY = projectile->mPosY;
    float mPosZ = projectile->mPosZ;
    float mVelX = projectile->mVelX;
    float mVelY = projectile->mVelY;
    float mVelZ = projectile->mVelZ;
    LawnApp *lawnApp = projectile->mApp;
    Board *board = projectile->mBoard;
    int aRenderOrder = projectile->mRenderOrder + 1;
    float num = mPosX - mVelX;
    float num2 = mPosY + mPosZ - mVelY - mVelZ;
    ParticleEffect::ParticleEffect particleEffect = ParticleEffect::None;
    float num3 = mPosX + 12.0f;
    float num4 = mPosY + 12.0f;
    if (mProjectileType == ProjectileType::PROJECTILE_MELON) {
        LawnApp_AddTodParticle(lawnApp, num + 30.0f, num2 + 30.0f, aRenderOrder, ParticleEffect::Melonsplash);
    } else if (mProjectileType == ProjectileType::PROJECTILE_WINTERMELON) {
        LawnApp_AddTodParticle(lawnApp, num + 30.0f, num2 + 30.0f, aRenderOrder, ParticleEffect::Wintermelon);
    } else if (mProjectileType == ProjectileType::PROJECTILE_COBBIG) {
        int aRenderOrder2 = Board_MakeRenderOrder(20000, projectile->mCobTargetRow, 2);
        LawnApp_AddTodParticle(lawnApp, mPosX + 80.0f, mPosY + 40.0f, aRenderOrder2, ParticleEffect::Blastmark);
        LawnApp_AddTodParticle(lawnApp, mPosX + 80.0f, mPosY + 40.0f, aRenderOrder, ParticleEffect::Popcornsplash);
        LawnApp_PlaySample(lawnApp, *Sexy_SOUND_DOOMSHROOM_Addr);
        Board_ShakeBoard(board, 3, -4);
    } else if (mProjectileType == ProjectileType::PROJECTILE_PEA) {
        num3 -= 15.0f;
        particleEffect = ParticleEffect::PeaSplat;
    } else if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA) {
        num3 -= 15.0f;
        particleEffect = ParticleEffect::SnowpeaSplat;
    } else if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL) {
        if (Projectile_IsSplashDamage(projectile, zombie)) {
            Reanimation *reanimation = LawnApp_AddReanimation(lawnApp, mPosX + 38.0f, mPosY - 20.0f, aRenderOrder, ReanimationType::REANIM_JALAPENO_FIRE);
            reanimation->mAnimTime = 0.25f;
            Reanimation_SetAnimRate(reanimation, 24.0f);
            Reanimation_OverrideScale(reanimation, 0.7f, 0.4f);
        }
    } else if (mProjectileType == ProjectileType::PROJECTILE_STAR) {
        particleEffect = ParticleEffect::StarSplat;
    } else if (mProjectileType == ProjectileType::PROJECTILE_PUFF) {
        num3 -= 20.0f;
        particleEffect = ParticleEffect::PuffSplat;
    } else if (mProjectileType == ProjectileType::PROJECTILE_CABBAGE) {
        num3 = num - 38.0f;
        num4 = num2 + 23.0f;
        particleEffect = ParticleEffect::CabbageSplat;
    } else if (mProjectileType == ProjectileType::PROJECTILE_BUTTER) {
        num3 = num - 20.0f;
        num4 = num2 + 63.0f;
        particleEffect = ParticleEffect::ButterSplat;
        if (zombie != nullptr) {
            Zombie_ApplyButter(zombie);
        }
    }
    if (particleEffect != ParticleEffect::None) {
        if (zombie != nullptr) {
            int mZombieX = zombie->mX;
            int mZombieY = zombie->mY;
            ZombiePhase::ZombiePhase mZombiePhase = zombie->mZombiePhase;
            float num5 = num3 + 52.0f - mZombieX;
            float num6 = num4 - mZombieY;
            if (mZombiePhase == ZombiePhase::DolphinWalkingInPool || mZombiePhase == ZombiePhase::SnorkelWalkingInPool) {
                num6 += 60.0f;
            }
            if (mMotionType == ProjectileMotion::Backwards) {
                num5 -= 80.0f;
            } else if (mPosX > mZombieX + 40 && mMotionType != ProjectileMotion::Lobbed) {
                num5 -= 60.0f;
            }
            if (num6 > 100.0f)
                num6 = 100.0f;
            if (num6 < 20.0f)
                num6 = 20.0f;
            Zombie_AddAttachedParticle(zombie, num5, num6, particleEffect);
        } else {
            LawnApp_AddTodParticle(lawnApp, num3, num4, aRenderOrder, particleEffect);
        }
    }
    if (mMotionType == ProjectileMotion::Lobbed && zombie == nullptr) {
        // 如果玩家开启了“子弹帧伤”,且子弹是抛物线轨迹
        Projectile_Die(projectile);
        return;
    }
}

Zombie *Projectile_FindCollisionMindControlledTarget(Projectile *projectile) {
    // 豌豆僵尸的子弹专用的寻敌函数，寻找被魅惑的僵尸。
    Zombie *zombie = nullptr;
    Zombie *resultZombie = nullptr;
    int num = 0;
    TRect zombieRect;
    TRect projectileRect;
    Board *board = projectile->mBoard;
    Projectile_GetProjectileRect(&projectileRect, projectile);
    while (Board_IterateZombies(board, &zombie)) {
        if (!zombie->mDead && zombie->mRow == projectile->mRow && zombie->mMindControlled) {
            Zombie_GetZombieRect(&zombieRect, zombie);
            int rectOverlap = GetRectOverlap(&projectileRect, &zombieRect);
            if (rectOverlap >= 0 && (resultZombie != nullptr || zombie->mX > num)) {
                resultZombie = zombie;
                num = zombie->mX;
            }
        }
    }
    return resultZombie;
}

void Projectile_CheckForCollision(Projectile *projectile) {
    // 修复豌豆僵尸的子弹无法击中魅惑僵尸、修复随即子弹飞出屏幕不自动消失导致闪退。
    ProjectileType mProjectileType = projectile->mProjectileType;
    ProjectileMotion::ProjectileMotion mMotionType = projectile->mMotionType;
    float mPosX = projectile->mPosX;
    float mPosY = projectile->mPosY;
    LawnApp *lawnApp = projectile->mApp;
    int mRenderOrder = projectile->mRenderOrder;

    if (mMotionType == ProjectileMotion::Puff && projectile->mProjectileAge >= 75) {
        Projectile_Die(projectile);
        return;
    }
    if (mPosX > 800.0f || mPosX + projectile->mWidth < 0.0f) {
        Projectile_Die(projectile);
        return;
    }
    if (mMotionType == ProjectileMotion::Homing) {
        Zombie *zombie = Board_ZombieTryToGet(projectile->mBoard, projectile->mTargetZombieID);
        if (zombie != nullptr && Zombie_EffectedByDamage(zombie, projectile->mDamageRangeFlags)) {
            TRect projectileRect;
            TRect zombieRect;
            Projectile_GetProjectileRect(&projectileRect, projectile);
            Zombie_GetZombieRect(&zombieRect, zombie);
            int rectOverlap = GetRectOverlap(&projectileRect, &zombieRect);
            if (rectOverlap >= 0 && mPosY > zombieRect.mY && mPosY < zombieRect.mY + zombieRect.mHeight) {
                Projectile_DoImpact(projectile, zombie);
            }
        }
        return;
    }

    //        if (mProjectileType == ProjectileType::PROJECTILE_STAR && (mPosY > 600.0f || mPosY < 40.0f)) {
    //        Projectile_Die(projectile);
    //        return;
    //    }

    if (mMotionType == ProjectileMotion::Star && (mPosY > 600.0f || mPosY < 40.0f)) {
        // 将判断条件从mProjectileType改为mMotionType，从而修复随机杨桃子弹在Y方向出界后不消失导致的闪退
        Projectile_Die(projectile);
        return;
    }

    if (projectile->mApp->mGameMode == GameMode::ChallengeHeavyWeapon && (mPosY > 600.0f || mPosY < 40.0f)) {
        // 添加一段逻辑，让重型武器中所有Y方向出界的子弹都会消失。无论子弹种类。
        Projectile_Die(projectile);
        return;
    }


    if ((mProjectileType == ProjectileType::PROJECTILE_PEA || mProjectileType == ProjectileType::PROJECTILE_STAR) && projectile->mShadowY - mPosY > 90.0f) {
        return;
    }
    if (mMotionType == ProjectileMotion::FloatOver) {
        return;
    }
    if (mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA) {
        Plant *plant = Projectile_FindCollisionTargetPlant(projectile);
        if (plant != nullptr) {
            int mProjectileDamage = Projectile_GetProjectileDef(projectile).mDamage;
            plant->mPlantHealth -= mProjectileDamage;
            plant->mEatenFlashCountdown = plant->mEatenFlashCountdown > 25 ? plant->mEatenFlashCountdown : 25;
            LawnApp_PlayFoley(lawnApp, FoleyType::Splat);
            LawnApp_AddTodParticle(lawnApp, mPosX - 3.0f, mPosY + 17.0f, mRenderOrder + 1, ParticleEffect::PeaSplat);
            Projectile_Die(projectile);
            return;
        }
        Zombie *zombie = Projectile_FindCollisionMindControlledTarget(projectile);
        if (zombie != nullptr) {
            if (zombie->mOnHighGround && Projectile_CantHitHighGround(projectile)) {
                return;
            }
            projectile->mProjectileType = ProjectileType::PROJECTILE_PEA; // 将子弹类型修改为普通豌豆，从而修复子弹打到魅惑僵尸身上没有击中特效。
            Projectile_DoImpact(projectile, zombie);
        }
        return;
    }

    //    if ((mDamageRangeFlags & 1) == 0) { //TV的原版代码中存在这个，但是我这么写会导致仙人掌打不到气球。因此注释
    //        return;
    //    }

    Zombie *zombie = Projectile_FindCollisionTarget(projectile);
    if (zombie != nullptr) {
        if (zombie->mOnHighGround && Projectile_CantHitHighGround(projectile)) {
            return;
        }
        Projectile_DoImpact(projectile, zombie);
    } else if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
        GridItem *gridItem = Projectile_FindCollisionTargetGridItem(projectile);
        if (gridItem != nullptr) {
            Projectile_DoImpactGridItem(projectile, gridItem);
        }
    }
}
