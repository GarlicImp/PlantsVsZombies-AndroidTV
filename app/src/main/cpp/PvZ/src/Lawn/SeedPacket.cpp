#include "PvZ/Lawn/SeedPacket.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/SeedBank.h"

void SeedPacket::Update() {
    if (mRefreshing && seedPacketFastCoolDown) {
        // 正在刷新的种子立即冷却完毕
        mActive = true;
        mRefreshing = false;
    }

    if (requestPause) {

        if (LawnApp_IsIZombieLevel(mApp)) {
            // 在IZ模式不暂停刷新种子卡片
            return old_SeedPacket_Update(this);
        }

        if (mApp->mGameScene == GameScenes::SCENE_PLAYING && mPacketType != SeedType::SEED_NONE) {
            mRefreshCounter--;
        }
        if (mSlotMachineCountDown > 0) {
            mSlotMachineCountDown++;
        }
    }

    return old_SeedPacket_Update(this);
}

void SeedPacket::UpdateSelected() {
    if (mApp->mGameMode == GameMode::GAMEMODE_TWO_PLAYER_VS || LawnApp_IsCoopMode(mApp)) {
        // 如果是双人模式关卡(对战或结盟)，则使用下面的逻辑来更新当前选中的卡片。用于修复1P和2P的卡片选择框同时出现在两个人各自的植物栏里(也就是植物栏一共出现四个选择框)的问题。
        int mSelectedSeedIndex1P = mBoard->mGamepadControls1->mSelectedSeedIndex;
        int mSelectedSeedIndex2P = mBoard->mGamepadControls2->mSelectedSeedIndex;
        bool playerIndex = SeedPacket_GetPlayerIndex(this);
        bool selectedBy1P = playerIndex == 0 && mIndex == mSelectedSeedIndex1P;
        bool selectedBy2P = playerIndex == 1 && mIndex == mSelectedSeedIndex2P;
        mSelectedBy1P = selectedBy1P || selectedBy2P;
        mSelectedBy2P = selectedBy2P;
        return;
    }
    return old_SeedPacket_UpdateSelected(this);
}

void SeedPacket::DrawOverlay(Sexy::Graphics* g) {
    // 绘制卡片冷却进度倒计时
    old_SeedPacket_DrawOverlay(this, g);

    if (mRefreshing && showCoolDown) {
        // 如果玩家开启了“显示冷却倒计时”，则绘制倒计时
        int holder[1];
        int coolDownRemaining = mRefreshTime - mRefreshCounter;
        Sexy_StrFormat(holder, "%1.1f", coolDownRemaining / 100.0f);
        Sexy_Graphics_SetColor(g, SeedPacket_GetPlayerIndex(this) ? &yellow : &blue);
        Sexy_Graphics_SetFont(g, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
        Sexy_Graphics_DrawString(g, holder, coolDownRemaining < 1000 ? 10 : 0, 39);
        Sexy_String_Delete(holder);
        Sexy_Graphics_SetFont(g, nullptr);
    }
}

void SeedPacket::Draw(Sexy::Graphics* g) {
    // 绘制卡片冷却进度倒计时
    old_SeedPacket_Draw(this, g);
}

void SeedPacket_MouseDown(SeedPacket *seedPacket, int x, int y, int c, int unk) {
    //    LOGD("SeedPacket_MouseDown:%d %d %d %d", x, y, c, unk);
    old_SeedPacket_MouseDown(seedPacket, x, y, c, unk);
}

bool SeedPacket_BeginDraw(SeedPacket *a, Sexy::Graphics *a2) {
    return old_SeedPacket_BeginDraw(a, a2);
}

void SeedPacket_EndDraw(SeedPacket *a, Sexy::Graphics *a2) {
    old_SeedPacket_EndDraw(a, a2);
}

void SeedPacket::FlashIfReady() {
    // 去除对战模式下的闪光效果的缩放

    if (!SeedPacket_CanPickUp(this)) {
        return;
    }
    if (mApp->mEasyPlantingCheat) {
        return;
    }

    int playerIndex = 0;
    if (mSeedBank != nullptr) {
        playerIndex = mSeedBank->mIsZombie;
    }
    if (!Board_HasConveyorBeltSeedBank(mBoard, playerIndex) && mSeedBank != nullptr) {
        LawnApp_AddTodParticle(mApp, mSeedBank->mX + mX, mSeedBank->mY + mY, 100000 + 2, ParticleEffect::PARTICLE_SEED_PACKET_FLASH);
    }
    TutorialState tutorialState = mBoard->mTutorialState;
    if (tutorialState == TutorialState::TUTORIAL_LEVEL_1_REFRESH_PEASHOOTER) {
        Board_SetTutorialState(mBoard, TutorialState::TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER);
        return;
    }
    if (tutorialState == TutorialState::TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER && mPacketType == SeedType::SEED_SUNFLOWER) {
        Board_SetTutorialState(mBoard, TutorialState::TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER);
        return;
    }
    if (tutorialState == TutorialState::TUTORIAL_MORESUN_REFRESH_SUNFLOWER && mPacketType == SeedType::SEED_SUNFLOWER) {
        Board_SetTutorialState(mBoard, TutorialState::TUTORIAL_MORESUN_PICK_UP_SUNFLOWER);
        return;
    }
}
