#include "PvZ/Lawn/SeedBank.h"
#include "Homura/Logger.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/CutScene.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/SeedPacket.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Symbols.h"

SeedBank::SeedBank(bool thePlayerIndex) {
    Create(thePlayerIndex);
}

void SeedBank::Create(bool thePlayerIndex) {
    old_SeedBank_SeedBank(this, thePlayerIndex);
    //    LOG_DEBUG("this->mBoard: {}", (void*)this->mBoard);
}

void SeedBank::Draw(Sexy::Graphics *g) {
    //    LOG_INFO("this->mBoard: {}", (void*)this->mBoard);
    // 在对战模式取消0.9倍缩放
    if (mApp->mGameMode != GameMode::GAMEMODE_MP_VS) {
        return old_SeedBank_Draw(this, g);
    }
    Sexy_Graphics_PushState(g);
    //    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
    //        g->mTransX = 0;
    //        g->mTransY = 0;
    //        int transform[12];
    //        Sexy_SexyTransform2D_SexyTransform2D(transform);
    //        Sexy_SexyTransform2D_Scale(transform, 0.9, 0.9);
    //        int theOffsetX = *(uint8_t *) (*(uint32_t *) (*((uint32_t *) seedBank + 4) + 740) + 96) ? 240 : 80;
    //        float theTranslateX = seedBank->mX + theOffsetX;
    //        float theTranslateY = seedBank->mY + 60;
    //        Sexy_SexyTransform2D_Translate(transform, theTranslateX, theTranslateY);
    ////        Sexy_Graphics_PushTransform(g,transform, true);
    ////        Sexy_Image_PushTransform(g->mDestImage,transform,true);
    //        (*(void (**)(uint32_t, int *, bool))(**((uint32_t **)g + 1) + 140))(*((uint32_t *)g + 1),transform,true);
    //    }
    if (mApp->mGameScene != GameScenes::SCENE_PLAYING) {
        g->mTransX = g->mTransX - mBoard->mX;
        g->mTransY = g->mTransY - mBoard->mY;
    }
    CutScene *cutScene = mBoard->mCutScene;
    if (cutScene != nullptr && CutScene_IsBeforePreloading(cutScene)) {
        return;
    }
    if (LawnApp_IsSlotMachineLevel(mApp)) {
        Sexy_Graphics_DrawImage(g, *Sexy_IMAGE_SUNBANK_Addr, 0, 0);
    } else if (mBoard->HasConveyorBeltSeedBank(mIsZombie)) {
        if (LawnApp_IsCoopMode(mApp)) {
            Sexy_Graphics_DrawImage(g, *Sexy_IMAGE_CONVEYORBELT_BACKDROP_COOP_Addr, 0, 0);
            Sexy_Graphics_DrawImageCel(g, *Sexy_IMAGE_CONVEYORBELT_COOP_Addr, 7, 63, 0, mConveyorBeltCounter / 4 % 6);
            Sexy_Graphics_SetClipRect(g, 7, 0, 313, 600);
        } else {
            Sexy_Graphics_DrawImage(g, *Sexy_IMAGE_CONVEYORBELT_BACKDROP_Addr, 83, 0);
            Sexy_Graphics_DrawImageCel(g, *Sexy_IMAGE_CONVEYORBELT_Addr, 90, 63, 0, mConveyorBeltCounter / 4 % 6);
            Sexy_Graphics_SetClipRect(g, 90, 0, 501, 600);
        }
    } else if (LawnApp_IsCoopMode(mApp)) {
        Sexy_Graphics_DrawImage(g, *Sexy_IMAGE_SEEDBANK_COOP_Addr, 0, 0);
    } else if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS && mIsZombie) {
        int theSeedBankExtraWidth = mBoard->GetSeedBankExtraWidth();
        Sexy_Graphics_DrawImage(g, *Sexy_IMAGE_ZOMBIE_SEEDBANK_Addr, theSeedBankExtraWidth, 0);
    } else {
        Sexy::Image *seedBankImage = *Sexy_IMAGE_SEEDBANK_Addr;
        int theSeedBankExtraWidth = mBoard->GetSeedBankExtraWidth();
        int theRect[4];
        theRect[0] = seedBankImage->mWidth - 12 - theSeedBankExtraWidth;
        theRect[1] = 0;
        theRect[2] = theSeedBankExtraWidth + 12;
        theRect[3] = seedBankImage->mHeight;
        Sexy_Graphics_DrawImage(g, seedBankImage, 0, 0);
        Sexy_Graphics_DrawImage2(g, seedBankImage, seedBankImage->mWidth - 12, 0, theRect);
    }
    SeedPacket *seedPacket1 = nullptr;
    SeedPacket *seedPacket2 = nullptr;
    if (mNumPackets > 0) {
        for (int i = 0; i < mNumPackets; ++i) {
            SeedPacket *seedPacket = &(mSeedPackets[i]);
            if (seedPacket->mPacketType == SeedType::SEED_NONE) {
                continue;
            }
            if (!LawnApp_IsSlotMachineLevel(mApp)) {
                if (LawnApp_IsCoopMode(mApp) || mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
                    bool mPlayerIndex = mBoard->mSeedBank2 == this;
                    GamepadControls *gamepadControls = mPlayerIndex ? mBoard->mGamepadControls2 : mBoard->mGamepadControls1;
                    if (gamepadControls->mPlayerIndex2 != -1 && i == gamepadControls->mSelectedSeedIndex) {
                        if (mPlayerIndex) {
                            seedPacket2 = seedPacket;
                        } else {
                            seedPacket1 = seedPacket;
                        }
                        continue;
                    }
                } else {
                    GamepadControls *gamepadControls1 = mBoard->mGamepadControls1;
                    if (gamepadControls1->mPlayerIndex2 != -1 && i == gamepadControls1->mSelectedSeedIndex) {
                        seedPacket1 = seedPacket;
                        continue;
                    }
                    GamepadControls *gamepadControls2 = mBoard->mGamepadControls2;
                    if (gamepadControls2->mPlayerIndex2 != -1 && i == gamepadControls2->mSelectedSeedIndex) {
                        seedPacket2 = seedPacket;
                        continue;
                    }
                }
            }
            if (SeedPacket_BeginDraw(seedPacket, g)) {
                SeedPacket_DrawBackground(seedPacket, g);
                SeedPacket_EndDraw(seedPacket, g);
            }
        }
        for (int i = 0; i < mNumPackets; ++i) {
            SeedPacket *seedPacket = &(mSeedPackets[i]);
            if (seedPacket->mPacketType == SeedType::SEED_NONE) {
                continue;
            }
            if (seedPacket == seedPacket1 || seedPacket == seedPacket2) {
                continue;
            }
            if (SeedPacket_BeginDraw(seedPacket, g)) {
                SeedPacket_DrawMiddle(seedPacket, g);
                SeedPacket_EndDraw(seedPacket, g);
            }
        }

        for (int i = 0; i < mNumPackets; ++i) {
            SeedPacket *seedPacket = &(mSeedPackets[i]);
            if (seedPacket->mPacketType == SeedType::SEED_NONE) {
                continue;
            }
            if (seedPacket == seedPacket1 || seedPacket == seedPacket2) {
                continue;
            }
            if (SeedPacket_BeginDraw(seedPacket, g)) {
                seedPacket->DrawOverlay(g);
                SeedPacket_EndDraw(seedPacket, g);
            }
        }
    }
    g->mClipRect.mX -= 20;
    g->mClipRect.mY -= 20;
    g->mClipRect.mWidth += 20;
    g->mClipRect.mHeight += 30;
    if (seedPacket2 != nullptr && SeedPacket_BeginDraw(seedPacket2, g)) {
        seedPacket2->Draw(g);
        SeedPacket_EndDraw(seedPacket2, g);
    }
    if (seedPacket1 != nullptr && SeedPacket_BeginDraw(seedPacket1, g)) {
        seedPacket1->Draw(g);
        SeedPacket_EndDraw(seedPacket1, g);
    }
    Sexy_Graphics_ClearClipRect(g);
    if (LawnApp_IsSlotMachineLevel(mApp)) {
        if (mY > -(*(int (**)(Sexy::Image *))(*Sexy_IMAGE_SEEDBANK_Addr + 20))(*Sexy_IMAGE_SEEDBANK_Addr))
            Sexy_Graphics_DrawImage(g, *Sexy_IMAGE_SLOTMACHINE_OVERLAY_Addr, 189, -2);
    }
    if (!mBoard->HasConveyorBeltSeedBank(0)) {
        int theMoney;
        if (mIsZombie) {
            theMoney = mBoard->mDeathMoney & ~mBoard->mDeathMoney >> 31; // mDeathMoney
        } else {
            theMoney = mBoard->mSunMoney1 & ~mBoard->mSunMoney1 >> 31; // mSunMoney1
        }

        if (LawnApp_IsCoopMode(mApp) && mBoard->mSeedBank2 == this) {
            theMoney = mBoard->mSunMoney2 & ~mBoard->mSunMoney2 >> 31; // mSunMoney2
        }
        int holder[1];
        Color theColor = {0, 0, 0, 255};
        Sexy_StrFormat(holder, "%d", theMoney);
        int mOutOfMoneyCounter = mBoard->mOutOfMoneyCounter;
        if (mOutOfMoneyCounter > 0 && mOutOfMoneyCounter % 20 <= 9) {
            theColor.mRed = 255;
            theColor.mGreen = 0;
            theColor.mBlue = 0;
            theColor.mAlpha = 255;
        }
        TodDrawString(g, holder, mIsZombie ? (408 + mBoard->GetSeedBankExtraWidth()) : 38, 78, *Sexy_FONT_CONTINUUMBOLD14_Addr, theColor, DrawStringJustification::DS_ALIGN_CENTER);
        Sexy_String_Delete(holder);

        if (LawnApp_IsTwinSunbankMode(mApp)) {
            int holder1[1];
            Sexy_StrFormat(holder1, "%d", mBoard->mSunMoney2 & ~mBoard->mSunMoney2 >> 31);
            TodDrawString(g, holder1, 644, 49, *Sexy_FONT_CONTINUUMBOLD14_Addr, theColor, DrawStringJustification::DS_ALIGN_CENTER);
            Sexy_String_Delete(holder1);
        }
    }
    if (mApp->mGameScene != GameScenes::SCENE_PLAYING) {
        g->mTransX = g->mTransX + mBoard->mX;
        g->mTransY = g->mTransY + mBoard->mY;
    }
    //    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
    ////        Sexy_Graphics_PopTransform(g);
    ////        Sexy_Image_PopTransform(g->mDestImage);
    //        (*(void (**)(uint32_t))(**((uint32_t **)g + 1) + 144))(*((uint32_t *)g + 1));
    //    }
    Sexy_Graphics_PopState(g);
}

bool SeedBank::MouseHitTest(int x, int y, HitResult *theHitResult) {
    LOG_INFO("this->mBoard: {}", (void *)this->mBoard);
    int relativeX = x - mX;
    int relativeY = y - mY;
    if (mWidth - 4 <= relativeX || mNumPackets <= 0) {
        theHitResult->mObject = nullptr;
        theHitResult->mObjectType = GameObjectType::OBJECT_TYPE_NONE;
        return false;
    }

    for (int i = 0; i < mNumPackets; i++) {
        if (SeedPacket_MouseHitTest(&mSeedPackets[i], relativeX, relativeY, theHitResult)) {
            return true;
        }
    }

    theHitResult->mObject = nullptr;
    theHitResult->mObjectType = GameObjectType::OBJECT_TYPE_NONE;
    return false;
}


void SeedBank::UpdateWidth() {
    //    LOG_DEBUG("this->mBoard: {}", (void*)this->mBoard);
    //    LOG_DEBUG("this->mApp: {}", (void*)this->mApp);
    //    LOG_DEBUG("this->mSeedPackets: {}", (void*)this->mSeedPackets);
    //    LOG_DEBUG("this->mNumPackets: {}", this->mNumPackets);
    //    LOG_DEBUG("this->mToolTipWidget: {}", (void*)this->mToolTipWidget);
    //    LOG_DEBUG("this->mX: {}", this->mX);
    //    LOG_DEBUG("this->mWidth: {}", this->mWidth);
    old_SeedBank_UpdateWidth(this);
}

bool SeedBank_ContainsPoint(SeedBank *seedBank, int theX, int theY) {
    LOG_INFO("this->mBoard: {}", (void *)seedBank->mBoard);
    return theX >= seedBank->mX && theX < seedBank->mX + seedBank->mWidth && theY >= seedBank->mY && theY < seedBank->mY + seedBank->mHeight;
}

void SeedBank::Move(int x, int y) {
    LOG_INFO("this->mBoard: {}", (void *)this->mBoard);
    // 在对战模式 错开双方的Bank
    mX = x;
    mY = y;
    if (mApp->mGameMode == GameMode::GAMEMODE_MP_VS) {
        int theSeedBankExtraWidth = mBoard->GetSeedBankExtraWidth();
        if (mIsZombie) {
            mX += (5 - theSeedBankExtraWidth / 2);
        } else {
            mX -= (45 + theSeedBankExtraWidth / 2);
        }
    }
}

bool SeedBank_BeginDraw(SeedBank *seedBank, Sexy::Graphics *graphics) {
    LOG_INFO("this->mBoard: {}", (void *)seedBank->mBoard);
    return old_SeedBank_BeginDraw(seedBank, graphics);
}


void SeedBank_EndDraw(SeedBank *seedBank, Sexy::Graphics *graphics) {
    LOG_INFO("this->mBoard: {}", (void *)seedBank->mBoard);
    old_SeedBank_EndDraw(seedBank, graphics);
}
