#include "PvZ/Lawn/Coin.h"
#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/Challenge.h"

#include <cmath>

void Coin_GamepadCursorOver(Coin *coin, int a2) {
    //*((uint32_t *)a + 29) == 16 则意味着是砸罐子种子雨老虎机中的植物卡片

    if (!keyboardMode && coin->mType == CoinType::COIN_USABLE_SEED_PACKET) {
        return;
    }
    old_Coin_GamepadCursorOver(coin, a2);
}

void Coin_Update(Coin *coin) {
    CoinType mCoinType = coin->mType;
    if (BanDropCoin && (mCoinType <= CoinType::COIN_LARGESUN || mCoinType == CoinType::COIN_COOP_DOUBLE_SUN || mCoinType == CoinType::COIN_VS_ZOMBIE_BRAIN)) {
        // 开启了"禁止掉落阳光金币"时
        Coin_Die(coin);
        return;
    }
    LawnApp *lawnApp = coin->mApp;
    Board *board = coin->mBoard;

    if (mCoinType == CoinType::COIN_VS_PLANT_TROPHY || mCoinType == CoinType::COIN_VS_ZOMBIE_TROPHY) {
        return old_Coin_Update(coin);
    }

    if (enableManualCollect) {
        // 如果开了手动拾取，则重置Coin的存在时间计数器为0，从而不会触发自动拾取。
        GameMode::GameMode mGameMode = lawnApp->mGameMode;
        // 在重型武器中、花园中依然自动收集；在关卡结束后依然自动收集。
        if (mGameMode != GameMode::ChallengeHeavyWeapon && mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN && mGameMode != GameMode::GAMEMODE_TREE_OF_WISDOM
            && lawnApp->mGameScene == GameScenes::Playing
            && board->mBoardFadeOutCounter <= 0) {
            coin->mCoinAge = 0;
        }
    } else if (mCoinType == CoinType::COIN_VS_ZOMBIE_BRAIN) {
        // 如果没有关闭自动拾取，则为对战模式的僵尸方阳光也加入自动拾取。
        if (coin->mCoinAge > 79 && !coin->mIsBeingCollected) {
            Coin_Collect(coin, 0);
        }
    }
    if (LawnApp_IsCoopMode(lawnApp) && (mCoinType == CoinType::COIN_SUN || mCoinType == CoinType::COIN_COOP_DOUBLE_SUN || mCoinType == CoinType::COIN_SMALLSUN || mCoinType == CoinType::COIN_LARGESUN)) {
        // 在结盟模式关闭阳光自动拾取。
        coin->mCoinAge = 0;
    }

    if (Coin_IsLevelAward(coin)) {
        // 为关卡结束后的奖励掉落物关闭自动拾取。
        coin->mCoinAge = 0;
    }

    old_Coin_Update(coin);
}

void Coin_UpdateFallForAward(Coin *coin) {
    // 试图去除关卡掉落物在关卡结束后的自动收集。
    float v10;              // s15
    float v11;              // s14
    float num;              // s17
    float num2;             // s18
    Board *v22;             // r3
    float v24;              // r0
    float mScale;           // s14
    float v30;              // s12
    int mGroundY;           // s10
    float v34;              // s15
    float v40;              // s14
    float v41;              // s13
    float v42;              // s14
    float v43;              // s17
    float v44;              // s16
    float v45;              // s19
    float v46;              // s15
    float unk2;             // s12
    int RenderOrder;        // r0
    TodParticleSystem *v53; // r0
    float v55;              // [sp+8h] [bp-28h] BYREF
    float v56;              // [sp+Ch] [bp-24h] BYREF

    if (coin->unk3)
        return;
    LawnApp *mApp = coin->mApp;
    CoinMotion mCoinMotion = coin->mCoinMotion;
    CoinType mType = coin->mType;
    float mVelX = coin->mVelX;
    float mVelY = coin->mVelY;
    float mPosX = coin->mPosX;
    float mPosY = coin->mPosY;
    int mCoinAge = coin->mCoinAge;
    if (mCoinMotion == CoinMotion::COIN_MOTION_FROM_PRESENT) {
        coin->mPosX = mPosX + mVelX;
        coin->mPosY = mPosY + mVelY;
        coin->mVelY = mVelY * 0.95;
        coin->mVelX = mVelX * 0.95;
        if (mCoinAge >= 80) {
            Coin_Collect(coin, 0);
        }
    } else if (mCoinMotion == CoinMotion::COIN_MOTION_FROM_FROM_VS_WON) {
        v30 = mVelY + 0.2;
        mGroundY = coin->mGroundY;
        v34 = v30 + mPosY;
        coin->mPosY = v34;
        coin->mVelY = v30 * 0.95;
        coin->mVelX = mVelX * 0.95;
        coin->mPosX = mPosX + mVelX;
        if (v34 >= mGroundY) {
            if (sqrtf(mVelY * mVelY + mVelX * mVelX) > 0.5) {
                LawnApp_PlayFoley(mApp, FoleyType::Grassstep);
                coin->mVelY = -coin->mVelY;
            } else {
                coin->mPosY = mGroundY;
                coin->mVelY = 0.0;
            }
        }
        if (coin->mCoinAge > 199) {
            Coin_Collect(coin, 0);
        }
    } else if (mCoinMotion == CoinMotion::COIN_MOTION_FROM_NEAR_CURSOR) {
        int mPlayerIndex = coin->mPlayerIndex;
        if (mPlayerIndex >= 0) {
            GamepadControls *gamepadControls = Board_GetGamepadControlsByPlayerIndex(coin->mBoard, mPlayerIndex);
            v55 = gamepadControls->mCursorPositionX;
            v56 = gamepadControls->mCursorPositionY;
            v40 = (float)coin->mWidth / 2;
            v56 = v56 - ((float)coin->mHeight / 2);
            v41 = v56 - mPosY;
            v55 = v55 - v40;
            v42 = v55 - mPosX;
            if ((v41 * v41 + v42 * v42) < 1225.0) {
                Coin_Collect(coin, coin->mPlayerIndex);
                return;
            }
            v43 = v41 * 400.0;
            v44 = v42 * 400.0;
            v45 = sqrtf(v43 * v43 + v44 * v44);
            v46 = coin->unk2 + ((6.4 / (v45 / 100.0)) * (v45 / 100.0));
            if (v46 > 600.0)
                v46 = 600.0;
            coin->unk2 = v46;
            unk2 = coin->unk2;
            if (v45 != 0.0) {
                v43 = v43 / v45;
                v44 = v44 / v45;
            }
            coin->mPosX = mPosX + (unk2 * v44) * 0.016;
            coin->mPosY = mPosY + (unk2 * v43) * 0.016;
        }
    } else if (mPosY + mVelY < coin->mGroundY) {
        coin->mPosY = mPosY + mVelY;
        if (mCoinMotion == CoinMotion::COIN_MOTION_FROM_PLANT || mCoinMotion == CoinMotion::COIN_MOTION_FROM_FROM_GRAVE) {
            coin->mVelY = mVelY + 0.09;
        } else if (mCoinMotion == CoinMotion::COIN_MOTION_COIN || mCoinMotion == CoinMotion::COIN_MOTION_FROM_BOSS) {
            coin->mVelY = mVelY + 0.15;
        }

        v10 = coin->mPosX + coin->mVelX;
        v11 = 800 - coin->mWidth;
        coin->mPosX = v10;
        if (v10 <= v11 || mCoinMotion == CoinMotion::COIN_MOTION_FROM_BOSS) {
            if (v10 < 0.0)
                coin->mPosX = 0.0;
        } else {
            coin->mPosX = v11;
        }
    } else {
        if (coin->mNeedsBouncyArrow && !coin->mHasBouncyArrow) {
            num = (float)coin->mWidth / 2;
            num2 = (float)coin->mHeight / 2 - 60;
            if (mType == CoinType::COIN_TROPHY) {
                num = num + 2.0;
            } else if (mType == CoinType::COIN_VS_PLANT_TROPHY || mType == CoinType::COIN_VS_ZOMBIE_TROPHY) {
                num2 = num2 - 20.0;
                RenderOrder = Board_MakeRenderOrder(700000, coin->mRow, coin->mHasBouncyArrow);
                v53 = LawnApp_AddTodParticle(mApp, mPosX, mPosY, RenderOrder, ParticleEffect::TrophySparkle);
                AttachParticle(coin->mAttachment + 2, v53, 0, 0.0);
            } else if (mType == CoinType::COIN_AWARD_MONEY_BAG || mType == CoinType::COIN_AWARD_BAG_DIAMOND) {
                num2 = num2 - 2.0;
                num = num + 2.0;
            } else if (mType == CoinType::COIN_AWARD_PRESENT || Coin_IsPresentWithAdvice(coin)) {
                num2 = num2 - 20.0;
            } else if (mType == CoinType::COIN_AWARD_SILVER_SUNFLOWER || mType == CoinType::COIN_AWARD_GOLD_SUNFLOWER) {
                num = num - 6.0;
                num2 = num2 - 40.0;
            } else if (Coin_IsMoney(coin)) {
                num = num + 12.0;
                num2 = num2 + 21.0;
            }

            ParticleEffect::ParticleEffect theEffect;
            if (mType == CoinType::COIN_FINAL_SEED_PACKET) {
                theEffect = ParticleEffect::SeedPacket;
            } else if (Coin_IsMoney(coin)) {
                theEffect = ParticleEffect::CoinPickupArrow;
            } else {
                theEffect = ParticleEffect::AwardPickupArrow;
            }
            TodParticleSystem *theParticleSystem = LawnApp_AddTodParticle(mApp, mPosX + num, mPosY + num2, 0, theEffect);
            AttachParticle(coin->mAttachment, theParticleSystem, num, num2);
            coin->mHasBouncyArrow = true;
        }
        if (!coin->mHitGround) {
            coin->mHitGround = true;
            Coin_PlayGroundSound(coin);
        }

        coin->mPosY = coin->mGroundY;
        coin->mPosX = std::round(coin->mPosX);
        if ((coin->mApp->mGameMode != GameMode::ChallengeLastStand || (v22 = coin->mBoard) == nullptr || v22->mChallenge->mChallengeState == ChallengeState::STATECHALLENGE_LAST_STAND_ONSLAUGHT)
            && !Coin_IsLevelAward(coin) && !Coin_IsPresentWithAdvice(coin)) {
            ++coin->mDisappearCounter;
            if (Coin_GetDisappearTime(coin) <= coin->mDisappearCounter)
                Coin_StartFade(coin);
        }
    }


    if (mCoinMotion == CoinMotion::COIN_MOTION_FROM_PLANT || mCoinMotion == CoinMotion::COIN_MOTION_FROM_FROM_GRAVE) {
        v24 = Coin_GetSunScale(coin);
        mScale = coin->mScale;
        if (v24 <= mScale)
            coin->mScale = v24;
        else
            coin->mScale = mScale + 0.02;
    }
}

void Coin_UpdateFall(Coin *coin) {
    // 去除关卡掉落物在关卡结束后的自动收集。
    CoinType mType = coin->mType;
    if ((mType >= CoinType::COIN_AWARD_MONEY_BAG && mType <= CoinType::COIN_AWARD_GOLD_SUNFLOWER) || mType == CoinType::COIN_FINAL_SEED_PACKET) {
        return Coin_UpdateFallForAward(coin);
    }
    return old_Coin_UpdateFall(coin);
}

bool Coin_MouseHitTest(Coin *coin, int a2, int a3, int **hitResult, int a5) {
    // 去除在玩家按A键时的阳光金币检测，以防止玩家种植、铲除、发射加农炮时的操作被阳光金币遮挡。
    CoinType mCoinType = coin->mType;
    if (mCoinType <= CoinType::COIN_LARGESUN || mCoinType == CoinType::COIN_COOP_DOUBLE_SUN || mCoinType == CoinType::COIN_VS_ZOMBIE_BRAIN) {
        return false;
    }
    return old_Coin_MouseHitTest(coin, a2, a3, hitResult, a5);
}
