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

ProjectileDefinition gProjectileDefinition[] = {
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

int Projectile::ProjectileInitialize(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType) {
    //    projectile->mNewProjectileLastX = theX;
    //    projectile->mNewProjectileLastY = theY;
    if (!isOnlyTouchFireWood) {
        // 僵尸子弹与加农炮子弹NULL
        if (theProjectileType == ProjectileType::PROJECTILE_COBBIG || theProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA) {
            return old_Projectile_ProjectileInitialize(this, theX, theY, theRenderOrder, theRow, theProjectileType);
        }
        if (theProjectileType == ProjectileType::PROJECTILE_STAR && banStar) {
            return old_Projectile_ProjectileInitialize(this, theX, theY, theRenderOrder, theRow, theProjectileType);
        }
        if (isOnlyPeaUseable && theProjectileType != ProjectileType::PROJECTILE_PEA) {
            return old_Projectile_ProjectileInitialize(this, theX, theY, theRenderOrder, theRow, theProjectileType);
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

    return old_Projectile_ProjectileInitialize(this, theX, theY, theRenderOrder, theRow, theProjectileType);
}


void Projectile::ConvertToFireball(int theGridX) {
    if (isOnlyTouchFireWood) {
        if (bulletSpinnerChosenNum != -1) {
            mProjectileType = (ProjectileType)bulletSpinnerChosenNum;
            return;
        }
        if (randomBullet) {
            mProjectileType = (ProjectileType)randomInt(1, 12);
            return;
        }
    }

    return old_Projectile_ConvertToFireball(this, theGridX);
}

void Projectile::ConvertToPea(int theGridX) {
    if (ColdPeaCanPassFireWood) {
        if (mHitTorchwoodGridX != theGridX) {
            Attachment_AttachmentDie(mAttachmentID);
            mHitTorchwoodGridX = theGridX;
            mProjectileType = ProjectileType::PROJECTILE_SNOWPEA;
            LawnApp_PlayFoley(mApp, FoleyType::Throw);
        }
        return;
    }

    old_Projectile_ConvertToPea(this, theGridX);
}

void Projectile::Update() {
    if (requestPause) {
        // 如果开了高级暂停
        return;
    }
    return old_Projectile_Update(this);
}

void Projectile::DoImpact(Zombie* theZombie) {
    if (!projectilePierce) {
        return old_Projectile_DoImpact(this, theZombie);
    }
    // 负责 直线子弹帧伤
    Projectile_PlayImpactSound(this, theZombie);

    if (Projectile_IsSplashDamage(this, theZombie)) {
        if (theZombie && mProjectileType == ProjectileType::PROJECTILE_FIREBALL) {
            Zombie_RemoveColdEffects(theZombie);
        }

        Projectile_DoSplashDamage(this, theZombie, 0);
    } else if (theZombie) {
        unsigned int mDamageFlags = Projectile_GetDamageFlags(this, theZombie);
        Zombie_TakeDamage(theZombie, GetProjectileDef().mDamage, mDamageFlags);
    }

    float aLastPosX = mPosX - mVelX;
    float aLastPosY = mPosY + mPosZ - mVelY - mVelZ;
    ParticleEffect aEffect = ParticleEffect::PARTICLE_NONE;
    float aSplatPosX = mPosX + 12.0f;
    float aSplatPosY = mPosY + 12.0f;
    if (mProjectileType == ProjectileType::PROJECTILE_MELON) {
        LawnApp_AddTodParticle(mApp, aLastPosX + 30.0f, aLastPosY + 30.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_MELONSPLASH);
    } else if (mProjectileType == ProjectileType::PROJECTILE_WINTERMELON) {
        LawnApp_AddTodParticle(mApp, aLastPosX + 30.0f, aLastPosY + 30.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_WINTERMELON);
    } else if (mProjectileType == ProjectileType::PROJECTILE_COBBIG) {
        int aRenderOrder = Board_MakeRenderOrder(RenderLayer::RENDER_LAYER_GROUND, mCobTargetRow, 2);
        LawnApp_AddTodParticle(mApp, mPosX + 80.0f, mPosY + 40.0f, aRenderOrder, ParticleEffect::PARTICLE_BLASTMARK);
        LawnApp_AddTodParticle(mApp, mPosX + 80.0f, mPosY + 40.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_POPCORNSPLASH);
        LawnApp_PlaySample(mApp, *Sexy_SOUND_DOOMSHROOM_Addr);
        mBoard->ShakeBoard(3, -4);
    } else if (mProjectileType == ProjectileType::PROJECTILE_PEA) {
        aSplatPosX -= 15.0f;
        aEffect = ParticleEffect::PARTICLE_PEA_SPLAT;
    } else if (mProjectileType == ProjectileType::PROJECTILE_SNOWPEA) {
        aSplatPosX -= 15.0f;
        aEffect = ParticleEffect::PARTICLE_SNOWPEA_SPLAT;
    } else if (mProjectileType == ProjectileType::PROJECTILE_FIREBALL) {
        if (Projectile_IsSplashDamage(this, theZombie)) {
            Reanimation *aFireReanim = LawnApp_AddReanimation(mApp, mPosX + 38.0f, mPosY - 20.0f, mRenderOrder + 1, ReanimationType::REANIM_JALAPENO_FIRE);
            aFireReanim->mAnimTime = 0.25f;
            aFireReanim->mAnimRate = 24.0f;
            Reanimation_OverrideScale(aFireReanim, 0.7f, 0.4f);
        }
    } else if (mProjectileType == ProjectileType::PROJECTILE_STAR) {
        aEffect = ParticleEffect::PARTICLE_STAR_SPLAT;
    } else if (mProjectileType == ProjectileType::PROJECTILE_PUFF) {
        aSplatPosX -= 20.0f;
        aEffect = ParticleEffect::PARTICLE_PUFF_SPLAT;
    } else if (mProjectileType == ProjectileType::PROJECTILE_CABBAGE) {
        aSplatPosX = aLastPosX - 38.0f;
        aSplatPosY = aLastPosY + 23.0f;
        aEffect = ParticleEffect::PARTICLE_CABBAGE_SPLAT;
    } else if (mProjectileType == ProjectileType::PROJECTILE_BUTTER) {
        aSplatPosX = aLastPosX - 20.0f;
        aSplatPosY = aLastPosY + 63.0f;
        aEffect = ParticleEffect::PARTICLE_BUTTER_SPLAT;

        if (theZombie) {
            Zombie_ApplyButter(theZombie);
        }
    }

    if (aEffect != ParticleEffect::PARTICLE_NONE) {
        if (theZombie) {
            float aPosX = aSplatPosX + 52.0f - theZombie->mX;
            float aPosY = aSplatPosY - theZombie->mY;
            if (theZombie->mZombiePhase == ZombiePhase::PHASE_DOLPHIN_WALKING_IN_POOL || theZombie->mZombiePhase == ZombiePhase::PHASE_SNORKEL_WALKING_IN_POOL) {
                aPosY += 60.0f;
            }
            if (mMotionType == ProjectileMotion::MOTION_BACKWARDS) {
                aPosX -= 80.0f;
            } else if (mPosX > theZombie->mX + 40 && mMotionType != ProjectileMotion::MOTION_LOBBED) {
                aPosX -= 60.0f;
            }
            if (aPosY > 100.0f)
                aPosY = 100.0f;
            if (aPosY < 20.0f)
                aPosY = 20.0f;
            Zombie_AddAttachedParticle(theZombie, aPosX, aPosY, aEffect);
        } else {
            LawnApp_AddTodParticle(mApp, aSplatPosX, aSplatPosY, mRenderOrder + 1, aEffect);
        }
    }

    if (mMotionType == ProjectileMotion::MOTION_LOBBED && theZombie == nullptr) {
        // 如果玩家开启了“子弹帧伤”,且子弹是抛物线轨迹
        Projectile_Die(this);
        return;
    }
}

Zombie* Projectile::FindCollisionMindControlledTarget() {
    // 豌豆僵尸的子弹专用的寻敌函数，寻找被魅惑的僵尸。
    Zombie* aZombie = nullptr;
    Zombie* aBestZombie = nullptr;
    int aMinX = 0;
    TRect zombieRect;
    TRect projectileRect;
    Projectile_GetProjectileRect(&projectileRect, this);
    while (Board_IterateZombies(mBoard, &aZombie)) {
        if (!aZombie->mDead && aZombie->mRow == mRow && aZombie->mMindControlled) {
            Zombie_GetZombieRect(&zombieRect, aZombie);
            int rectOverlap = GetRectOverlap(&projectileRect, &zombieRect);
            if (rectOverlap >= 0 && (aBestZombie != nullptr || aZombie->mX > aMinX)) {
                aBestZombie = aZombie;
                aMinX = aZombie->mX;
            }
        }
    }

    return aBestZombie;
}

void Projectile::CheckForCollision() {
    // 修复豌豆僵尸的子弹无法击中魅惑僵尸、修复随即子弹飞出屏幕不自动消失导致闪退。
    if (mMotionType == ProjectileMotion::MOTION_PUFF && mProjectileAge >= 75) {
        Projectile_Die(this);
        return;
    }

    if (mPosX > 800.0f || mPosX + mWidth < 0.0f) {
        Projectile_Die(this);
        return;
    }

    if (mMotionType == ProjectileMotion::MOTION_HOMING) {
        Zombie* aZombie = Board_ZombieTryToGet(mBoard, mTargetZombieID);
        if (aZombie && Zombie_EffectedByDamage(aZombie, mDamageRangeFlags)) {
            TRect projectileRect;
            TRect zombieRect;
            Projectile_GetProjectileRect(&projectileRect, this);
            Zombie_GetZombieRect(&zombieRect, aZombie);
            int rectOverlap = GetRectOverlap(&projectileRect, &zombieRect);
            if (rectOverlap >= 0 && mPosY > zombieRect.mY && mPosY < zombieRect.mY + zombieRect.mHeight) {
                DoImpact(aZombie);
            }
        }
        return;
    }

    //        if (mProjectileType == ProjectileType::PROJECTILE_STAR && (mPosY > 600.0f || mPosY < 40.0f)) {
    //        Projectile_Die(projectile);
    //        return;
    //    }

    if (mMotionType == ProjectileMotion::MOTION_STAR && (mPosY > 600.0f || mPosY < 40.0f)) {
        // 将判断条件从mProjectileType改为mMotionType，从而修复随机杨桃子弹在Y方向出界后不消失导致的闪退
        Projectile_Die(this);
        return;
    }

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_HEAVY_WEAPON && (mPosY > 600.0f || mPosY < 40.0f)) {
        // 添加一段逻辑，让重型武器中所有Y方向出界的子弹都会消失。无论子弹种类。
        Projectile_Die(this);
        return;
    }


    if ((mProjectileType == ProjectileType::PROJECTILE_PEA || mProjectileType == ProjectileType::PROJECTILE_STAR) && mShadowY - mPosY > 90.0f) {
        return;
    }
    if (mMotionType == ProjectileMotion::MOTION_FLOAT_OVER) {
        return;
    }

    if (mProjectileType == ProjectileType::PROJECTILE_ZOMBIE_PEA) {
        Plant *aPlant = Projectile_FindCollisionTargetPlant(this);
        if (aPlant) {
            const ProjectileDefinition& aProjectileDef = GetProjectileDef();
            aPlant->mPlantHealth -= aProjectileDef.mDamage;
            aPlant->mEatenFlashCountdown = std::max(aPlant->mEatenFlashCountdown, 25);

            LawnApp_PlayFoley(mApp, FoleyType::Splat);
            LawnApp_AddTodParticle(mApp, mPosX - 3.0f, mPosY + 17.0f, mRenderOrder + 1, ParticleEffect::PARTICLE_PEA_SPLAT);
            Projectile_Die(this);
            return;
        }
        Zombie *aZombie = FindCollisionMindControlledTarget();
        if (aZombie) {
            if (aZombie->mOnHighGround && Projectile_CantHitHighGround(this)) {
                return;
            }
            mProjectileType = ProjectileType::PROJECTILE_PEA; // 将子弹类型修改为普通豌豆，从而修复子弹打到魅惑僵尸身上没有击中特效。
            DoImpact(aZombie);
        }
        return;
    }

    //    if ((mDamageRangeFlags & 1) == 0) { //TV的原版代码中存在这个，但是我这么写会导致仙人掌打不到气球。因此注释
    //        return;
    //    }

    Zombie* aZombie = Projectile_FindCollisionTarget(this);
    if (aZombie) {
        if (aZombie->mOnHighGround && Projectile_CantHitHighGround(this)) {
            return;
        }
        DoImpact(aZombie);
    } else if (mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS) {
        GridItem* aGridItem = Projectile_FindCollisionTargetGridItem(this);
        if (aGridItem) {
            Projectile_DoImpactGridItem(this, aGridItem);
        }
    }
}

ProjectileDefinition& Projectile::GetProjectileDef()
{
    ProjectileDefinition& aProjectileDef = gProjectileDefinition[(int)mProjectileType];

    return aProjectileDef;
}
