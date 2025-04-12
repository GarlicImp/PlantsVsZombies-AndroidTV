#include "PvZ/Lawn/Zombie.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/GridItem.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Plant.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Lawn/Projectile.h"

ZombieDefinition gZombieDefs[NUM_ZOMBIE_TYPES] = {  //0x69DA80
    { ZOMBIE_NORMAL,            REANIM_ZOMBIE,              1,      1,      1,      4000,   _S("ZOMBIE") },
    { ZOMBIE_FLAG,              REANIM_ZOMBIE,              1,      1,      1,      0,      _S("FLAG_ZOMBIE") },
    { ZOMBIE_TRAFFIC_CONE,      REANIM_ZOMBIE,              2,      3,      1,      4000,   _S("CONEHEAD_ZOMBIE") },
    { ZOMBIE_POLEVAULTER,       REANIM_POLEVAULTER,         2,      6,      5,      2000,   _S("POLE_VAULTING_ZOMBIE") },
    { ZOMBIE_PAIL,              REANIM_ZOMBIE,              4,      8,      1,      3000,   _S("BUCKETHEAD_ZOMBIE") },
    { ZOMBIE_NEWSPAPER,         REANIM_ZOMBIE_NEWSPAPER,    2,      11,     1,      1000,   _S("NEWSPAPER_ZOMBIE") },
    { ZOMBIE_DOOR,              REANIM_ZOMBIE,              4,      13,     5,      3500,   _S("SCREEN_DOOR_ZOMBIE") },
    { ZOMBIE_FOOTBALL,          REANIM_ZOMBIE_FOOTBALL,     7,      16,     5,      2000,   _S("FOOTBALL_ZOMBIE") },
    { ZOMBIE_DANCER,            REANIM_DANCER,              5,      18,     5,      1000,   _S("DANCING_ZOMBIE") },
    { ZOMBIE_BACKUP_DANCER,     REANIM_BACKUP_DANCER,       1,      18,     1,      0,      _S("BACKUP_DANCER") },
    { ZOMBIE_DUCKY_TUBE,        REANIM_ZOMBIE,              1,      21,     5,      0,      _S("DUCKY_TUBE_ZOMBIE") },
    { ZOMBIE_SNORKEL,           REANIM_SNORKEL,             3,      23,     10,     2000,   _S("SNORKEL_ZOMBIE") },
    { ZOMBIE_ZAMBONI,           REANIM_ZOMBIE_ZAMBONI,      7,      26,     10,     2000,   _S("ZOMBONI") },
    { ZOMBIE_BOBSLED,           REANIM_BOBSLED,             3,      26,     10,     2000,   _S("ZOMBIE_BOBSLED_TEAM") },
    { ZOMBIE_DOLPHIN_RIDER,     REANIM_ZOMBIE_DOLPHINRIDER, 3,      28,     10,     1500,   _S("DOLPHIN_RIDER_ZOMBIE") },
    { ZOMBIE_JACK_IN_THE_BOX,   REANIM_JACKINTHEBOX,        3,      31,     10,     1000,   _S("JACK_IN_THE_BOX_ZOMBIE") },
    { ZOMBIE_BALLOON,           REANIM_BALLOON,             2,      33,     10,     2000,   _S("BALLOON_ZOMBIE") },
    { ZOMBIE_DIGGER,            REANIM_DIGGER,              4,      36,     10,     1000,   _S("DIGGER_ZOMBIE") },
    { ZOMBIE_POGO,              REANIM_POGO,                4,      38,     10,     1000,   _S("POGO_ZOMBIE") },
    { ZOMBIE_YETI,              REANIM_YETI,                4,      40,     1,      1,      _S("ZOMBIE_YETI") },
    { ZOMBIE_BUNGEE,            REANIM_BUNGEE,              3,      41,     10,     1000,   _S("BUNGEE_ZOMBIE") },
    { ZOMBIE_LADDER,            REANIM_LADDER,              4,      43,     10,     1000,   _S("LADDER_ZOMBIE") },
    { ZOMBIE_CATAPULT,          REANIM_CATAPULT,            5,      46,     10,     1500,   _S("CATAPULT_ZOMBIE") },
    { ZOMBIE_GARGANTUAR,        REANIM_GARGANTUAR,          10,     48,     15,     1500,   _S("GARGANTUAR") },
    { ZOMBIE_IMP,               REANIM_IMP,                 10,     48,     1,      0,      _S("IMP") },
    { ZOMBIE_BOSS,              REANIM_BOSS,                10,     50,     1,      0,      _S("BOSS") },
    { ZOMBIE_PEA_HEAD,          REANIM_ZOMBIE,              1,      99,     1,      4000,   _S("ZOMBIE") },
    { ZOMBIE_WALLNUT_HEAD,      REANIM_ZOMBIE,              4,      99,     1,      3000,   _S("ZOMBIE") },
    { ZOMBIE_JALAPENO_HEAD,     REANIM_ZOMBIE,              3,      99,     10,     1000,   _S("ZOMBIE") },
    { ZOMBIE_GATLING_HEAD,      REANIM_ZOMBIE,              3,      99,     10,     2000,   _S("ZOMBIE") },
    { ZOMBIE_SQUASH_HEAD,       REANIM_ZOMBIE,              3,      99,     10,     2000,   _S("ZOMBIE") },
    { ZOMBIE_TALLNUT_HEAD,      REANIM_ZOMBIE,              4,      99,     10,     2000,   _S("ZOMBIE") },
    { ZOMBIE_REDEYE_GARGANTUAR, REANIM_GARGANTUAR,          10,     48,     15,     6000,   _S("REDEYED_GARGANTUAR") },
};

void Zombie::Update() {
    if (zombieBloated) {
        // 如果开启了“普僵必噎死”
        mBloated = mZombieType == ZombieType::ZOMBIE_NORMAL && !mInPool;
    }
    //    if (requestPause && zombie->mZombiePhase == ZombiePhase::RisingFromGrave) {
    //        // 试图修复高级暂停时IZ放僵尸只显示虚影。失败。
    //        Zombie_UpdatePlaying(zombie);
    //        return;
    //    }
    if (requestPause) {
        // 如果开了高级暂停
        return;
    }
    if (mZombieType == ZombieType::ZOMBIE_FLAG && mBossFireBallReanimID != 0) {
        Reanimation *reanimation = LawnApp_ReanimationTryToGet(mApp, mBossFireBallReanimID);
        if (reanimation != nullptr)
            Reanimation_Update(reanimation);
    }
    return old_Zombie_Update(this);
}

void Zombie::UpdateZombiePeaHead() {
    // 用于修复豌豆僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG、啃食时不发射子弹的BUG
    // 游戏原版逻辑是判断是否hasHead 且 是否isEating。这里去除对吃植物的判断

    if (!mHasHead)
        return;

    if (mPhaseCounter == 35) {
        Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(mApp, mSpecialHeadReanimID);
        Reanimation_PlayReanim(mSpecialHeadReanim, "anim_shooting", ReanimLoopType::PlayOnceAndHold, 20, 35.0f);
    } else if (mPhaseCounter <= 0) {
        Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(mApp, mSpecialHeadReanimID);
        Reanimation_PlayReanim(mSpecialHeadReanim, "anim_head_idle", ReanimLoopType::PlayOnceAndHold, 20, 15.0f);
        LawnApp_PlayFoley(mApp, FoleyType::Throw);

        Reanimation *mBodyReanim = LawnApp_ReanimationGet(mApp, mBodyReanimID);
        int index = Reanimation_FindTrackIndexById(mBodyReanim, *ReanimTrackId_anim_head1_Addr);
        ReanimatorTransform aTransForm;
        ReanimatorTransform_ReanimatorTransform(&aTransForm);
        Reanimation_GetCurrentTransform(mBodyReanim, index, &aTransForm);

        float aOriginX = mPosX + aTransForm.mTransX - 9.0f;
        float aOriginY = mPosY + aTransForm.mTransY + 6.0f - mAltitude;
#ifdef DO_FIX_BUGS
        if (mMindControlled) // 魅惑修复
        {
            aOriginX += 90.0f * mScaleZombie;
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_PEA);
            aProjectile->mDamageRangeFlags = 1;
        } else {
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_ZOMBIE_PEA);
            aProjectile->mMotionType = ProjectileMotion::MOTION_BACKWARDS;
        }
#else
        Projectile *projectile = Board_AddProjectile(mBoard, aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_ZOMBIE_PEA);
        projectile->mMotionType = ProjectileMotion::Backwards;
#endif

        mPhaseCounter = 150;
    }
}

void Zombie::UpdateZombieGatlingHead() {
    // 用于修复加特林僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG、啃食时不发射子弹的BUG
    // 游戏原版逻辑是判断是否hasHead 且 是否isEating。这里去除对吃植物的判断

    if (!mHasHead)
        return;

    if (mPhaseCounter == 100) {
        Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(mApp, mSpecialHeadReanimID);
        Reanimation_PlayReanim(mSpecialHeadReanim, "anim_shooting", ReanimLoopType::PlayOnceAndHold, 20, 35.0f);
    } else if (mPhaseCounter == 18 || mPhaseCounter == 35 || mPhaseCounter == 51 || mPhaseCounter == 68) {
        LawnApp_PlayFoley(mApp, FoleyType::Throw);

        Reanimation *mBodyReanim = LawnApp_ReanimationGet(mApp, mBodyReanimID);
        int index = Reanimation_FindTrackIndexById(mBodyReanim, *ReanimTrackId_anim_head1_Addr);
        ReanimatorTransform aTransForm;
        ReanimatorTransform_ReanimatorTransform(&aTransForm);
        Reanimation_GetCurrentTransform(mBodyReanim, index, &aTransForm);

        float aOriginX = mPosX + aTransForm.mTransX - 9.0f;
        float aOriginY = mPosY + aTransForm.mTransY + 6.0f - mAltitude;
#ifdef DO_FIX_BUGS
        if (mMindControlled) // 魅惑修复
        {
            aOriginX += 90.0f * mScaleZombie;
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_PEA);
            aProjectile->mDamageRangeFlags = 1;
        } else {
            Projectile *aProjectile = mBoard->AddProjectile(aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_ZOMBIE_PEA);
            aProjectile->mMotionType = ProjectileMotion::MOTION_BACKWARDS;
        }
#else
        Projectile *projectile = Board_AddProjectile(mBoard, aOriginX, aOriginY, mRenderOrder, mRow, ProjectileType::PROJECTILE_ZOMBIE_PEA);
        projectile->mMotionType = ProjectileMotion::Backwards;
#endif
    }
        else if (mPhaseCounter <= 0) {
            Reanimation *aHeadReanim = LawnApp_ReanimationGet(mApp, mSpecialHeadReanimID);
            Reanimation_PlayReanim(aHeadReanim, "anim_head_idle", ReanimLoopType::PlayOnceAndHold, 20, 15.0f);
            mPhaseCounter = 150;
        }
}

void Zombie::BossDestroyIceballInRow(int theRow) {
    if (theRow != mFireballRow)
        return;

    Reanimation* aFireBallReanim = LawnApp_ReanimationTryToGet(mApp, mBossFireBallReanimID);
    if (aFireBallReanim && !mIsFireBall)
    {
        LawnApp_AddTodParticle(mApp, mPosX + 80.0, mAnimCounter + 80.0, 400000, ParticleEffect::PARTICLE_ICEBALL_DEATH);

        Reanimation_ReanimationDie(aFireBallReanim);
        mBossFireBallReanimID = mIsFireBall;
        mBoard->RemoveParticleByType(ParticleEffect::PARTICLE_ICEBALL_TRAIL);
    }
}

void Zombie::BurnRow(int theRow) {
    // 辣椒僵尸被魅惑后的爆炸函数

    Zombie *aZombie = nullptr;
    while (Board_IterateZombies(mBoard, &aZombie)) {
        if ((aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mRow == theRow) && Zombie_EffectedByDamage(aZombie, 127))
        {
            Zombie_RemoveColdEffects(aZombie);
            Zombie_ApplyBurn(aZombie);
        }
    }

    GridItem *aGridItem = nullptr;
    while (Board_IterateGridItems(mBoard, &aGridItem)) {
        if (aGridItem->mGridY == theRow && aGridItem->mGridItemType == GridItemType::Ladder) {
            GridItem_GridItemDie(aGridItem);
        }
    }

    Zombie* aBossZombie = Board_GetBossZombie(mBoard);
    if (aBossZombie && aBossZombie->mFireballRow == theRow)
    {
        aBossZombie->BossDestroyIceballInRow(theRow);
    }
}

void Zombie::UpdateZombieJalapenoHead() {
    // 修复辣椒僵尸被魅惑后爆炸依然伤害植物的BUG

    if (!mHasHead)
        return;

    if (mPhaseCounter == 0)
    {
        LawnApp_PlayFoley(mApp, FoleyType::JalapenoIgnite);
        LawnApp_PlayFoley(mApp, FoleyType::Juicy);
        Board_DoFwoosh(mBoard, mRow);
        Board_ShakeBoard(mBoard, 3, -4);

#ifdef DO_FIX_BUGS
        if (mMindControlled)
        {
            BurnRow(mRow);
        }
        else
        {
            Plant* aPlant = nullptr;
            while (mBoard->IteratePlants(aPlant))
            {
                //Rect aPlantRect = aPlant->GetPlantRect();
                if (aPlant->mRow == mRow && !aPlant->NotOnGround())
                {
                    mBoard->mPlantsEaten++;
                    aPlant->Die();
                }
            }
        }
#else
        Plant* aPlant = nullptr;
        while (Board_IteratePlants(mBoard, &aPlant))
        {
            //Rect aPlantRect = aPlant->GetPlantRect();
            if (aPlant->mRow == mRow && !aPlant->NotOnGround())
            {
                mBoard->mPlantsEaten++;
                aPlant->Die();
            }
        }
#endif
    }
}

void Zombie::Draw(Sexy::Graphics *g) {
    // 根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_Draw函数执行完后额外绘制血量文本。
    old_Zombie_Draw(this, g);
    int drawHeightOffset = 0;
    int holder[1];
    if (showZombieBodyHealth || (showGargantuarHealth && (mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR))) { // 如果玩家开了"僵尸显血"
        Sexy_StrFormat(holder, "%d/%d", mBodyHealth, mBodyMaxHealth);
        Sexy_Graphics_SetColor(g, &white);
        Sexy_Graphics_SetFont(g, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
        if (mZombieType == ZombieType::ZOMBIE_BOSS) {
            // 如果是僵王,将血量绘制到僵王头顶。从而修复图鉴中僵王血量绘制位置不正确。
            // 此处仅在图鉴中生效,实战中僵王绘制不走Zombie_Draw()，走Zombie_DrawBossPart()
            g->mTransX = 780.0f;
            g->mTransY = 240.0f;
        }
        Sexy_Graphics_DrawString(g, holder, 0, drawHeightOffset);
        Sexy_String_Delete(holder);
        Sexy_Graphics_SetFont(g, nullptr);
        drawHeightOffset += 20;
    }
    if (showHelmAndShieldHealth) {
        if (mHelmHealth > 0) { // 如果有头盔，绘制头盔血量
            Sexy_StrFormat(holder, "%d/%d", mHelmHealth, mHelmMaxHealth);
            Sexy_Graphics_SetColor(g, &yellow);
            Sexy_Graphics_SetFont(g, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            Sexy_Graphics_DrawString(g, holder, 0, drawHeightOffset);
            Sexy_String_Delete(holder);
            Sexy_Graphics_SetFont(g, nullptr);
            drawHeightOffset += 20;
        }
        if (mShieldHealth > 0) { // 如果有盾牌，绘制盾牌血量
            Sexy_StrFormat(holder, "%d/%d", mShieldHealth, mShieldMaxHealth);
            Sexy_Graphics_SetColor(g, &blue);
            Sexy_Graphics_SetFont(g, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            Sexy_Graphics_DrawString(g, holder, 0, drawHeightOffset);
            Sexy_String_Delete(holder);
            Sexy_Graphics_SetFont(g, nullptr);
        }
    }
}

void Zombie::DrawBossPart(Sexy::Graphics *graphics, int theBossPart) {
    // 根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_DrawBossPart函数执行完后额外绘制血量文本。
    old_Zombie_DrawBossPart(this, graphics, theBossPart);
    if (theBossPart == 3) {
        // 每次绘制Boss都会调用四次本函数，且theBossPart从0到3依次增加，代表绘制Boss的不同Part。
        // 我们只在theBossPart==3时(绘制最后一个部分时)绘制一次血量，免去每次都绘制。
        if (showZombieBodyHealth) { // 如果玩家开了"僵尸显血"
            int holder[1];
            Sexy_StrFormat(holder, "%d/%d", mBodyHealth, mBodyMaxHealth);
            Sexy_Graphics_SetColor(graphics, &white);
            Sexy_Graphics_SetFont(graphics, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            float tmpTransX = graphics->mTransX;
            float tmpTransY = graphics->mTransY;
            graphics->mTransX = 800.0f;
            graphics->mTransY = 200.0f;
            Sexy_Graphics_DrawString(graphics, holder, 0, 0);
            Sexy_String_Delete(holder);
            graphics->mTransX = tmpTransX;
            graphics->mTransY = tmpTransY;
            Sexy_Graphics_SetFont(graphics, nullptr);
        }
    }
}

int Zombie::GetDancerFrame() {
    if (mFromWave == -3 || Zombie_IsImmobilizied(this))
        return 0;

    // 女仆秘籍
    switch (maidCheats) {
        case 1:
            return 11; // 保持前进 (DancerDancingLeft)
        case 2:
            return 18; // 跳舞 (DancerRaiseLeft1)
        case 3:
            return 12; // 召唤舞伴 (DancerWalkToRaise)
        default:
            break;
    }

    // 修复女仆秘籍问题、修复舞王和舞者的跳舞时间不吃高级暂停也不吃倍速
    // 关键就是用mBoard.mMainCounter代替mApp.mAppCounter做计时
    ZombiePhase::ZombiePhase mZombiePhase = mZombiePhase;
    int num1 = mZombiePhase == ZombiePhase::DancerDancingIn ? 10 : 20;
    int num2 = mZombiePhase == ZombiePhase::DancerDancingIn ? 110 : 460;
    return mBoard->mMainCounter % num2 / num1;
    // return *(uint32_t *) (lawnApp + 2368) % num2 / num1;
}

bool ZombieTypeCanGoInPool(ZombieType theZombieType) {
    // 修复泳池对战的僵尸们走水路时不攻击植物
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS && (VSBackGround == 3 || VSBackGround == 4 || VSBackGround == 9)) {
        return true;
    }
    return old_ZombieTypeCanGoInPool(theZombieType);
}

void Zombie::RiseFromGrave(int theGridX, int theGridY) {
    // 修复对战切换场地为泳池后的闪退BUG。但是仅仅是修复闪退，泳池对战还谈不上能玩的程度
    if (mApp->mGameMode == GameMode::TwoPlayerVS) {

        if (mBoard->mPlantRow[theGridY] == PlantRowType::Pool) {
            //                if (old_ZombieTypeCanGoInPool(mZombieType)) {
            DieNoLoot();
            Board_AddZombieInRow(mBoard, mZombieType, theGridY, mBoard->mCurrentWave, 1);
            return;
            //                }
        }

        BackgroundType::BackgroundType tmp = mBoard->mBackgroundType;
        mBoard->mBackgroundType = BackgroundType::Num1Day;
        old_Zombie_RiseFromGrave(this, theGridX, theGridY);
        mBoard->mBackgroundType = tmp;
        return;
    }
    old_Zombie_RiseFromGrave(this, theGridX, theGridY);
}

void Zombie::CheckForBoardEdge() {
    // 修复僵尸正常进家、支持调整僵尸进家线
    if (Zombie_IsWalkingBackwards(this) && mPosX > 850.0f) {
        DieNoLoot();
        return;
    }
    int boardEdge;
    if (mZombieType == ZombieType::ZOMBIE_POLEVAULTER || mZombieType == ZombieType::ZOMBIE_GARGANTUAR || mZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR) {
        // 如果是撑杆、巨人、红眼巨人
        boardEdge = -100;
    } else if (mZombieType == ZombieType::ZOMBIE_FOOTBALL || mZombieType == ZombieType::ZOMBIE_ZAMBONI || mZombieType == ZombieType::ZOMBIE_CATAPULT) {
        // 如果是橄榄球、冰车、篮球
        boardEdge = -125;
    } else if (mZombieType == ZombieType::ZOMBIE_DANCER || mZombieType == ZombieType::ZOMBIE_BACKUP_DANCER || mZombieType == ZombieType::ZOMBIE_SNORKEL) {
        // 如果是舞王、伴舞、潜水
        boardEdge = -80;
    } else {
        // 如果是除上述僵尸外的僵尸
        boardEdge = -50;
    }
    boardEdge -= boardEdgeAdjust; // 支持任意调整进家线
    if (mX <= boardEdge && mHasHead) {
        if (LawnApp_IsIZombieLevel(mApp)) {
            DieNoLoot();
        } else {
            Board_ZombiesWon(mBoard, this);
        }
    }
    if (mX <= boardEdge + 70 && !mHasHead) {
        Zombie_TakeDamage(this, 1800, 9u);
    }
}

void Zombie::EatPlant(Plant *thePlant) {
    // 修复正向出土的矿工不上梯子
    if (mZombiePhase == ZombiePhase::DancerDancingIn) {
        mPhaseCounter = 1;
        return;
    }
    if (mYuckyFace) {
        return;
    }
    int mPlantCol = thePlant->mPlantCol;
    int mRow = thePlant->mRow;
    if (Board_GetLadderAt(mBoard, mPlantCol, mRow) != nullptr && mZombieType == ZombieType::ZOMBIE_DIGGER && mZombiePhase == ZombiePhase::DiggerWalkingWithoutAxe
        && !Zombie_IsWalkingBackwards(this)) {
        Zombie_StopEating(this);
        if (mZombieHeight == ZombieHeight::ZombieNormal && mUseLadderCol != mPlantCol) {
            mZombieHeight = ZombieHeight::UpLadder;
            mUseLadderCol = mPlantCol;
        }
        return;
    }
    return old_Zombie_EatPlant(this, thePlant);
}

void Zombie::DetachShield() {
    // 修复梯子僵尸断手后掉梯子时手会恢复的BUG。
    old_Zombie_DetachShield(this);
    if (mShieldType == ShieldType::Ladder && !mHasArm) {
        Zombie_ReanimShowPrefix(this, "Zombie_outerarm", -1);
    }
}

void Zombie::BossSpawnAttack() {
    // 修复泳池僵王为六路放僵尸时闪退
    Zombie_RemoveColdEffects(this);
    mZombiePhase = ZombiePhase::BossSpawning;
    if (mBossMode == 0) {
        mSummonCounter = RandRangeInt(450, 550);
    } else if (mBossMode == 1) {
        mSummonCounter = RandRangeInt(350, 450);
    } else if (mBossMode == 2) {
        mSummonCounter = RandRangeInt(150, 250);
    }
    mTargetRow = Board_PickRowForNewZombie(mBoard, 0);
    switch (mTargetRow) {
        case 0:
            Zombie_PlayZombieReanim(this, "anim_spawn_1", 3, 20, 12.0);
            break;
        case 1:
            Zombie_PlayZombieReanim(this, "anim_spawn_2", 3, 20, 12.0);
            break;
        case 2:
            Zombie_PlayZombieReanim(this, "anim_spawn_3", 3, 20, 12.0);
            break;
        case 3:
            Zombie_PlayZombieReanim(this, "anim_spawn_4", 3, 20, 12.0);
            break;
        default:
            Zombie_PlayZombieReanim(this, "anim_spawn_5", 3, 20, 12.0);
            break;
    }
    LawnApp_PlayFoley(mApp, FoleyType::HydraulicShort);
}

void Zombie_AddButter(Zombie *zombieUnderButter) {
    if (Zombie_CanBeFrozen(zombieUnderButter) && zombieUnderButter->mZombieType != ZombieType::ZOMBIE_BOSS) {
        // Ban冰车 跳跳 僵王 飞翔的气球 跳跃的撑杆 即将跳水的潜水 等等
        if (zombieUnderButter->mButteredCounter <= 100) {
            if (zombieUnderButter->mButteredCounter == 0) {
                LawnApp_PlayFoley(zombieUnderButter->mApp, FoleyType::Butter);
            }
            Zombie_ApplyButter(zombieUnderButter);
        }
    }
}

void Zombie_SetZombatarReanim(Zombie *zombie) {
    PlayerInfo *playerInfo = zombie->mApp->mPlayerInfo;
    if (!playerInfo->mZombatarEnabled)
        return;
    Reanimation *aBodyReanim = LawnApp_ReanimationGet(zombie->mApp, zombie->mBodyReanimID);
    ReanimatorTrackInstance *aHeadTrackInstance = Reanimation_GetTrackInstanceByName(aBodyReanim, "anim_head1");
    aHeadTrackInstance->mImageOverride = *Sexy_IMAGE_BLANK_Addr;
    Reanimation *aZombatarHeadReanim = LawnApp_AddReanimation(zombie->mApp, 0, 0, 0, ReanimationType::ZombatarHead);
    Reanimation_SetZombatarHats(aZombatarHeadReanim, playerInfo->mZombatarHat, playerInfo->mZombatarHatColor);
    Reanimation_SetZombatarHair(aZombatarHeadReanim, playerInfo->mZombatarHair, playerInfo->mZombatarHairColor);
    Reanimation_SetZombatarFHair(aZombatarHeadReanim, playerInfo->mZombatarFacialHair, playerInfo->mZombatarFacialHairColor);
    Reanimation_SetZombatarAccessories(aZombatarHeadReanim, playerInfo->mZombatarAccessory, playerInfo->mZombatarAccessoryColor);
    Reanimation_SetZombatarEyeWear(aZombatarHeadReanim, playerInfo->mZombatarEyeWear, playerInfo->mZombatarEyeWearColor);
    Reanimation_SetZombatarTidBits(aZombatarHeadReanim, playerInfo->mZombatarTidBit, playerInfo->mZombatarTidBitColor);
    Reanimation_PlayReanim(aZombatarHeadReanim, "anim_head_idle", ReanimLoopType::Loop, 0, 15.0);
    Reanimation_AssignRenderGroupToTrack(aZombatarHeadReanim, "anim_hair", -1);
    zombie->mBossFireBallReanimID = LawnApp_ReanimationGetID(zombie->mApp, aZombatarHeadReanim);
    AttachEffect *attachEffect = AttachReanim(&aHeadTrackInstance->mAttachmentID, aZombatarHeadReanim, 0.0f, 0.0f);
    TodScaleRotateTransformMatrix(&attachEffect->mOffset, -20.0, -1.0, 0.2, 1.0, 1.0);
    Zombie_ReanimShowPrefix(zombie, "anim_hair", -1);
    Zombie_ReanimShowPrefix(zombie, "anim_head2", -1);
}

bool Zombie_IsZombatarZombie(ZombieType type) {
    // return type == ZombieType::ZOMBIE_FLAG || type == ZombieType::ZOMBIE_NORMAL || type == ZombieType::ZOMBIE_TRAFFIC_CONE || type == ZombieType::ZOMBIE_DOOR || type == ZombieType::ZOMBIE_TRASH_BIN || type == ZombieType::ZOMBIE_PAIL || type
    // == ZombieType::ZOMBIE_DUCKY_TUBE;
    return type == ZombieType::ZOMBIE_FLAG;
}

void Zombie::ZombieInitialize(int theRow, ZombieType theType, bool theVariant, Zombie *theParentZombie, int theFromWave, bool isVisible) {
    // TODO: 修复高级暂停时放的IZ僵尸只显示虚影
    old_Zombie_ZombieInitialize(this, theRow, theType, theVariant, theParentZombie, theFromWave, isVisible);
    //    if (requestPause) {
    //        old_Zombie_Update(zombie);
    //    }
    if (zombieSetScale != 0 && mZombieType != ZombieType::ZOMBIE_BOSS) {
        mScaleZombie = 0.2 * zombieSetScale;
        Zombie_UpdateAnimationSpeed(this);
        float theRatio = mScaleZombie * mScaleZombie;
        mBodyHealth *= theRatio;
        mHelmHealth *= theRatio;
        mShieldHealth *= theRatio;
        mFlyingHealth *= theRatio;
        mBodyMaxHealth = mBodyHealth;
        mHelmMaxHealth = mHelmHealth;
        mShieldMaxHealth = mShieldHealth;
        mFlyingMaxHealth = mFlyingHealth;
    }

    if (Zombie_IsZombatarZombie(theType) && theFromWave != -3) {
        Zombie_SetZombatarReanim(this);
    }
}

ZombieDefinition &GetZombieDefinition(ZombieType theZombieType) {
    if (theZombieType == ZombieType::ZOMBIE_TRASH_BIN)
        return gZombieTrashBinDef;
    return old_GetZombieDefinition(theZombieType);
}

void Zombie::DieNoLoot() {
    if (mZombieType == ZombieType::ZOMBIE_GARGANTUAR && mBoard != nullptr && mApp->mGameScene == GameScenes::Playing) {
        Board_GrantAchievement(mBoard, AchievementId::ACHIEVEMENT_GARG, true);
    }

    if (Zombie_IsZombatarZombie(mZombieType)) {
        // 大头贴
        LawnApp_RemoveReanimation(mApp, mBossFireBallReanimID);
    }
    old_Zombie_DieNoLoot(this);
}

void Zombie::DrawBungeeCord(Sexy::Graphics *graphics, int theOffsetX, int theOffsetY) {
    // 修复在Boss关的蹦极绳子不绑在Boss手上
    int aCordCelHeight = Sexy_Image_GetCelHeight(*Sexy_IMAGE_BUNGEECORD_Addr) * mScaleZombie;
    float aPosX = 0.0f;
    float aPosY = 0.0f;
    Zombie_GetTrackPosition(this, "Zombie_bungi_body", &aPosX, &aPosY);
    bool aSetClip = false;
    if (Zombie_IsOnBoard(this) && LawnApp_IsFinalBossLevel(mApp)) {
        Zombie *aBossZombie = Board_GetBossZombie(mBoard);
        int aClipAmount = 55;
        if (aBossZombie->mZombiePhase == ZombiePhase::BossBungeesLeave) {
            Reanimation *reanimation = LawnApp_ReanimationGet(mApp, aBossZombie->mBodyReanimID);
            aClipAmount = TodAnimateCurveFloatTime(0.0f, 0.2f, reanimation->mAnimTime, 55.0f, 0.0f, TodCurves::Linear);
        }
        if (mTargetCol >= aBossZombie->mTargetCol) { // ">" ------ > ">="，修复第一根手指蹦极不绑在手上
            if (mTargetCol > aBossZombie->mTargetCol) {
                aClipAmount += 60; // 55 ---- > 115，修复第2、3根手指蹦极不绑在手上
            }
            Sexy_Graphics_SetClipRect(graphics, -graphics->mTransX, aClipAmount - graphics->mTransY, 800, 600);
            aSetClip = true;
        }
    }

    for (float y = aPosY - aCordCelHeight; y > -60 - aCordCelHeight; y -= aCordCelHeight) {
        float thePosX = theOffsetX + 61.0f - 4.0f / mScaleZombie;
        float thePosY = y - mPosY;
        TodDrawImageScaledF(graphics, *Sexy_IMAGE_BUNGEECORD_Addr, thePosX, thePosY, mScaleZombie, mScaleZombie);
    }
    if (aSetClip) {
        Sexy_Graphics_ClearClipRect(graphics);
    }
}

bool Zombie::IsTangleKelpTarget() {
    // 修复水草拉僵尸有概率失效

    if (!Board_StageHasPool(mBoard)) {
        return false;
    }
    if (mZombieHeight == ZombieHeight::DraggedUnder) {
        return true;
    }
    Plant *aPlant = nullptr;
    while (Board_IteratePlants(mBoard, &aPlant)) {
        if (!aPlant->mDead && aPlant->mSeedType == SeedType::Tanglekelp && aPlant->mTargetZombieID == mZombieID) {
            return true;
        }
    }
    return false;
}

void Zombie::DrawReanim(Sexy::Graphics *graphics, ZombieDrawPosition *theZombieDrawPosition, int theBaseRenderGroup) {
    // 大头贴专门Draw一下
    old_Zombie_DrawReanim(this, graphics, theZombieDrawPosition, theBaseRenderGroup);
    if (Zombie_IsZombatarZombie(mZombieType)) {
        Reanimation *reanimation = LawnApp_ReanimationTryToGet(mApp, mBossFireBallReanimID);
        if (reanimation != nullptr) {
            Reanimation_Draw(reanimation, graphics);
        }
    }
}


void Zombie::DropHead(unsigned int theDamageFlags) {
    // 负责 大头贴掉头
    // TODO: 大头贴僵尸掉头时掉饰品(掉 hat 和 eyeWear)
    old_Zombie_DropHead(this, theDamageFlags);
    if (Zombie_IsZombatarZombie(mZombieType)) {
        Reanimation *reanimation = LawnApp_ReanimationTryToGet(mApp, mBossFireBallReanimID);
        if (reanimation != nullptr) {
            int index[2] = {Reanimation_GetZombatarHatTrackIndex(reanimation), Reanimation_GetZombatarEyeWearTrackIndex(reanimation)};
            for (int i = 0; i < 2; ++i) {
                if (index[i] == -1)
                    continue;
                ReanimatorTrackInstance *reanimatorTrackInstance = reanimation->mTrackInstances + index[i];
                ReanimatorTrack *reanimatorTrack = reanimation->mDefinition->mTracks + index[i];
                SexyTransform2D aSexyTransform2D;
                Reanimation_GetTrackMatrix(reanimation, index[i], &aSexyTransform2D);
                float aPosX = mPosX + aSexyTransform2D.m[0][2];
                float aPosY = mPosY + aSexyTransform2D.m[1][2];
                TodParticleSystem *todParticleSystem = LawnApp_AddTodParticle(mApp, aPosX, aPosY, mRenderOrder + 1, ParticleEffect::ZombieHead);
                TodParticleSystem_OverrideColor(todParticleSystem, nullptr, &reanimatorTrackInstance->mTrackColor);
                TodParticleSystem_OverrideImage(todParticleSystem, nullptr, reanimatorTrack->mTransforms[0].mImage);
            }
            LawnApp_RemoveReanimation(mApp, mBossFireBallReanimID);
            mBossFireBallReanimID = 0;
        }
    }
}

void Zombie_SetupLostArmReanim(Zombie *zombie) {
    switch (zombie->mZombieType) {
        case ZombieType::ZOMBIE_FOOTBALL:
            Zombie_ReanimShowPrefix(zombie, "Zombie_football_leftarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie, "Zombie_football_leftarm_hand", -1);
            break;
        case ZombieType::ZOMBIE_NEWSPAPER:
            Zombie_ReanimShowTrack(zombie, "Zombie_paper_hands", -1);
            Zombie_ReanimShowTrack(zombie, "Zombie_paper_leftarm_lower", -1);
            break;
        case ZombieType::ZOMBIE_POLEVAULTER:
            Zombie_ReanimShowTrack(zombie, "Zombie_polevaulter_outerarm_lower", -1);
            Zombie_ReanimShowTrack(zombie, "Zombie_outerarm_hand", -1);
            break;
        case ZombieType::ZOMBIE_DANCER:
            Zombie_ReanimShowPrefix(zombie, "Zombie_disco_outerarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie, "Zombie_disco_outerhand_point", -1);
            Zombie_ReanimShowPrefix(zombie, "Zombie_disco_outerhand", -1);
            Zombie_ReanimShowPrefix(zombie, "Zombie_disco_outerarm_upper", -1);
            break;
        case ZombieType::ZOMBIE_BACKUP_DANCER:
            Zombie_ReanimShowPrefix(zombie, "Zombie_disco_outerarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie, "Zombie_disco_outerhand", -1);
            break;
        default:
            Zombie_ReanimShowPrefix(zombie, "Zombie_outerarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie, "Zombie_outerarm_hand", -1);
            break;
    }
    Reanimation *reanimation = LawnApp_ReanimationTryToGet(zombie->mApp, zombie->mBodyReanimID);
    if (reanimation != nullptr) {
        switch (zombie->mZombieType) {
            case ZombieType::ZOMBIE_FOOTBALL:
                Reanimation_SetImageOverride(reanimation, "zombie_football_leftarm_hand", *Sexy_IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_NEWSPAPER:
                Reanimation_SetImageOverride(reanimation, "Zombie_paper_leftarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_POLEVAULTER:
                Reanimation_SetImageOverride(reanimation, "Zombie_polevaulter_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_BALLOON:
                Reanimation_SetImageOverride(reanimation, "zombie_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_IMP:
                Reanimation_SetImageOverride(reanimation, "Zombie_imp_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE_Addr);
                break;
            case ZombieType::ZOMBIE_DIGGER:
                Reanimation_SetImageOverride(reanimation, "Zombie_digger_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_BOBSLED:
                Reanimation_SetImageOverride(reanimation, "Zombie_dolphinrider_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_JACK_IN_THE_BOX:
                Reanimation_SetImageOverride(reanimation, "Zombie_jackbox_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2_Addr);
                break;
            case ZombieType::ZOMBIE_SNORKEL:
                Reanimation_SetImageOverride(reanimation, "Zombie_snorkle_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_DOLPHIN_RIDER:
                Reanimation_SetImageOverride(reanimation, "Zombie_dolphinrider_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_POGO:
                Reanimation_SetImageOverride(reanimation, "Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2_Addr);
                Reanimation_SetImageOverride(reanimation, "Zombie_pogo_stickhands", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2_Addr);
                Reanimation_SetImageOverride(reanimation, "Zombie_pogo_stick", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2_Addr);
                Reanimation_SetImageOverride(reanimation, "Zombie_pogo_stick2", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2_Addr);
                break;
            case ZombieType::ZOMBIE_FLAG: {
                Reanimation_SetImageOverride(reanimation, "Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_Addr);
                Reanimation *reanimation2 = LawnApp_ReanimationTryToGet(zombie->mApp, zombie->mSpecialHeadReanimID);
                if (reanimation2 != nullptr) {
                    Reanimation_SetImageOverride(reanimation2, "Zombie_flag", *Sexy_IMAGE_REANIM_ZOMBIE_FLAG3_Addr);
                }
                break;
            }
            case ZombieType::ZOMBIE_DANCER:
                Reanimation_SetImageOverride(reanimation, "Zombie_disco_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_BACKUP_DANCER:
                Reanimation_SetImageOverride(reanimation, "Zombie_disco_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_LADDER:
                Reanimation_SetImageOverride(reanimation, "Zombie_ladder_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::ZOMBIE_YETI:
                Reanimation_SetImageOverride(reanimation, "Zombie_yeti_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2_Addr);
                break;
            default:
                Reanimation_SetImageOverride(reanimation, "Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_Addr);
                break;
        }
    }
}
