#include "PvZ/Lawn/MainMenu.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "Homura/Logger.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/Zombie.h"

#include <cstddef>

#include <algorithm>

namespace {

enum AchievementWidgetState {
    NOT_SHOWING = 0,
    SLIDING_IN = 1,
    SHOWING = 2,
    SLIDING_OUT = 3,
};

constexpr int gAchievementHoleLength = 136;
constexpr int gAchievementHoleWormPos = 0x10;
constexpr int gAchievementHoleGemsPos = 0x19;
constexpr int gAchievementHoleChuzzlePos = 0x26;
constexpr int gAchievementHoleBjornPos = 0x34;
constexpr int gAchievementHolePipePos = 0x45;
constexpr int gAchievementHoleTikiPos = 0x55;
constexpr int gAchievementHoleHeavyRocksPos = 0x65;
constexpr int gAchievementHoleDuWeiPos = 0x72;

constexpr int gKeyboardScrollTime = 20;
constexpr int gMainMenuHeight = 720 - 2; // 作用：将成就界面上升2个像素点，以更紧密地贴合主界面。奇怪，理论上720是严丝合缝，为什么实际有2像素偏差呢？

bool isPatched;
int gMainMenuAchievementCounter;
int gMainMenuAchievementsWidgetY;
int gMainMenuAchievementsKeyboardScrollWidgetY;
int gMainMenuAchievementKeyboardScrollCounter;
bool gMainMenuAchievementKeyboardScrollDirection;

AchievementWidgetState gAchievementState = NOT_SHOWING;
AchievementsWidget *gMainMenuAchievementsWidget;
Sexy::GameButton *gMainMenuAchievementsBack;
int gFoleyVolumeCounter;

} // namespace


static FoleyType MainMenu_GetFoleyTypeByScene(int scene) {
    FoleyType theType = FoleyType::FOLEY_MENU_CENTRE;
    switch (scene) {
        case 0:
            theType = FoleyType::FOLEY_MENU_LEFT;
            break;
        case 1:
            theType = FoleyType::FOLEY_MENU_CENTRE;
            break;
        case 2:
            theType = FoleyType::FOLEY_MENU_RIGHT;
    }
    return theType;
}

void MainMenu::Update() {
    // 成就界面处理
    isMainMenu = true;
    requestDrawShovelInCursor = false;
    requestDrawButterInCursor = false;

    if (!isPatched) {
        game_patches::autoPickupSeedPacketDisable.Modify();
        isPatched = true;
    }

    // 白噪音播放和淡入淡出
    if (mIsFading) {
        float num = mFadeCounterFloat + 0.005;
        mFadeCounterFloat = fmin(num, 1.0f);
    } else {
        if (MainMenu_InTransition(this)) {
            gFoleyVolumeCounter++;
            FoleyType aType = MainMenu_GetFoleyTypeByScene(mScene);
            FoleyType aNextType = MainMenu_GetFoleyTypeByScene(mSceneNext);
            if (!TodFoley_IsFoleyPlaying(mApp->mSoundSystem, aNextType)) {
                mApp->PlayFoley(aNextType);
                LawnApp_SetFoleyVolume(mApp, aNextType, 0);
            }
            float theVolume = TodAnimateCurveFloat(0, 93, gFoleyVolumeCounter, mApp->mPlayerInfo->mSoundVolume, 0, TodCurves::CURVE_BOUNCE_SLOW_MIDDLE);
            if (gFoleyVolumeCounter >= 46) {
                LawnApp_SetFoleyVolume(mApp, aNextType, theVolume);
                if (TodFoley_IsFoleyPlaying(mApp->mSoundSystem, aType)) {
                    TodFoley_StopFoley(mApp->mSoundSystem, aType);
                }
            } else {
                LawnApp_SetFoleyVolume(mApp, aType, theVolume);
            }
        } else {
            gFoleyVolumeCounter = 0;
            FoleyType aType = MainMenu_GetFoleyTypeByScene(mScene);
            if (gAchievementState == NOT_SHOWING) {
                if (!TodFoley_IsFoleyPlaying(mApp->mSoundSystem, aType) && mExitCounter == 0) {
//                    mApp->PlayFoley(aType);
                    LawnApp_SetFoleyVolume(mApp, aType, 0);
                }
                if (mEnterReanimationCounter > 0) {
                    float theVolume = TodAnimateCurveFloat(110, 0, mEnterReanimationCounter, 0, mApp->mPlayerInfo->mSoundVolume, TodCurves::CURVE_LINEAR);
                    LawnApp_SetFoleyVolume(mApp, aType, theVolume);
                }
            }
            if (gAchievementState == SLIDING_IN) {
                float theVolume = TodAnimateCurveFloat(100, 0, gMainMenuAchievementCounter, mApp->mPlayerInfo->mSoundVolume, 0, TodCurves::CURVE_LINEAR);
                LawnApp_SetFoleyVolume(mApp, aType, theVolume);
            }
            if (gAchievementState == SLIDING_OUT && gMainMenuAchievementCounter <= 100) {
                float theVolume = TodAnimateCurveFloat(100, 0, gMainMenuAchievementCounter, 0, mApp->mPlayerInfo->mSoundVolume, TodCurves::CURVE_LINEAR);
                LawnApp_SetFoleyVolume(mApp, aType, theVolume);
            }
        }
    }


    if (gMainMenuAchievementKeyboardScrollCounter != 0) {
        gMainMenuAchievementKeyboardScrollCounter--;
        if (gMainMenuAchievementsWidget != nullptr) {
            int theY = TodAnimateCurve(gKeyboardScrollTime, 0, gMainMenuAchievementKeyboardScrollCounter, 0, 192, TodCurves::CURVE_LINEAR);
            int theNewY = gMainMenuAchievementsKeyboardScrollWidgetY - (gMainMenuAchievementKeyboardScrollDirection ? theY : -theY);
            if (theNewY > gMainMenuHeight)
                theNewY = gMainMenuHeight;
            if (theNewY < 720 + gMainMenuHeight - (gAchievementHoleLength + 1) * addonImages.hole->mHeight)
                theNewY = 720 + gMainMenuHeight - (gAchievementHoleLength + 1) * addonImages.hole->mHeight;
            Sexy_Widget_Move(gMainMenuAchievementsWidget, gMainMenuAchievementsWidget->mX, theNewY);
        }
    }

    if (gAchievementState == SLIDING_IN) {
        gMainMenuAchievementCounter--;
        if (gMainMenuAchievementsWidget != nullptr) {
            int theY = TodAnimateCurve(100, 0, gMainMenuAchievementCounter, 660, -60, TodCurves::CURVE_EASE_IN_OUT);
            Sexy_Widget_Move(this, mX, -720 + theY);
        }
        if (gMainMenuAchievementCounter == 0) {
            gAchievementState = SHOWING;
            int holder1[1];
            TodStringTranslate(holder1, "[CLOSE]");
            gMainMenuAchievementsBack = MakeButton(ACHIEVEMENTS_BACK_BUTTON, &mButtonListener, this, holder1);
            GameButton_Resize(gMainMenuAchievementsBack, 1000, 564 + 720, 170, 50);
            Sexy_String_Delete(holder1);
            Sexy_Widget_AddWidget(this, gMainMenuAchievementsBack);
        }
    }

    if (gAchievementState == SLIDING_OUT) {
        gMainMenuAchievementCounter--;
        if (gMainMenuAchievementsWidget != nullptr) {
            if (gMainMenuAchievementCounter <= 100) {
                int theY = TodAnimateCurve(100, 0, gMainMenuAchievementCounter, -780, -60, TodCurves::CURVE_EASE_IN_OUT);
                Sexy_Widget_Move(this, mX, theY);
            } else {
                int theAchievementsY = TodAnimateCurve(150, 100, gMainMenuAchievementCounter, gMainMenuAchievementsWidgetY, gMainMenuHeight, TodCurves::CURVE_EASE_IN_OUT);
                Sexy_Widget_Move(gMainMenuAchievementsWidget, gMainMenuAchievementsWidget->mX, theAchievementsY);
            }
        }
        if (gMainMenuAchievementCounter == 0) {
            gAchievementState = NOT_SHOWING;
            Sexy_Widget_RemoveWidget(this, gMainMenuAchievementsWidget);
            MaskHelpWidget_Delete(gMainMenuAchievementsWidget);
            gMainMenuAchievementsWidget = nullptr;
            if (gMainMenuAchievementsBack != nullptr) {
                Sexy_Widget_RemoveWidget(this, gMainMenuAchievementsBack);
                GameButton_Delete(gMainMenuAchievementsBack);
                gMainMenuAchievementsBack = nullptr;
            }
            Sexy::Widget *achievementsButton = Sexy_Widget_FindWidget(this, ACHIEVEMENTS_BUTTON);
            mFocusedChildWidget = achievementsButton;
            if (!mIsFading)
                mApp->PlayFoley(FoleyType::FOLEY_MENU_CENTRE);
        }
    }
    if (gAchievementState == SHOWING) {
        return;
    }

    return old_MainMenu_Update(this);
}

void MainMenu::ButtonPress(MainMenuButtonId theSelectedButton) {
    // 按下按钮的声音
    LawnApp* gLawnApp = (LawnApp *)*gLawnApp_Addr;
    if (MainMenu_InTransition(gLawnApp->mGameSelector))
        return;

    switch (theSelectedButton) {
        case HOUSE_BUTTON:
        case ACHIEVEMENTS_BUTTON:
        case HELP_AND_OPTIONS_BUTTON:
        case UNLOCK_BUTTON:
        case RETURN_TO_ARCADE_BUTTON:
        case MORE_BUTTON:
        case BACK_POT_BUTTON:
        case STORE_BUTTON:
        case ZEN_BUTTON:
        case ALMANAC_BUTTON:
        case MAIL_BUTTON:
            //            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_CERAMIC_Addr);
            gLawnApp->PlayFoley(FoleyType::FOLEY_CERAMIC);
            break;
        default:
            LawnApp_PlaySample(gLawnApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
            break;
    }
}

void MainMenu::ButtonDepress(MainMenuButtonId theSelectedButton) {
    // 为1.1.5解锁触控或确认键进入“更多游戏模式”
    if (MainMenu_InTransition(this))
        return;
    if (mIsFading)
        return;
    if (mEnterReanimationCounter > 0)
        return;
    if (gAchievementState == SLIDING_IN || gAchievementState == SLIDING_OUT)
        return; // 在进入、退出成就时不允许玩家操作
    if (theSelectedButton == MORE_WAYS_BUTTON) {
        // 如果当前选中的按钮为"更多游戏方式"
        MainMenu_SetScene(this, MENUSCENE_MORE_WAYS);
        return;
    }

    // 为1.1.1添加触控或确认进入对战结盟模式，并检测是否解锁对战结盟
    switch (theSelectedButton) {
        case ADVENTURE_BUTTON:
        case START_ADVENTURE_BUTTON:
            MainMenu_StartAdventureMode(this);
            if (LawnPlayerInfo_GetFlag(mApp->mPlayerInfo, 4096) && mApp->mPlayerInfo->mLevel == 35) {
                mPressedButtonId = STORE_BUTTON;
                unkBool3 = true;
                (*(void (**)(MainMenu *))(*(uint32_t *)this + 496))(this);
            } else {
                mPressedButtonId = ADVENTURE_BUTTON;
                mApp->mGameMode = GameMode::GAMEMODE_ADVENTURE;
                (*(void (**)(MainMenu *))(*(uint32_t *)this + 496))(this);
            }
            return;
        case VS_BUTTON: // 如果按下了对战按钮
            if (mVSModeLocked) {
                // 如果没解锁结盟（冒险2-1解锁）
                LawnApp_LawnMessageBox(mApp, Dialogs::DIALOG_MESSAGE, "[MODE_LOCKED]", "[VS_LOCKED_MESSAGE]", "[DIALOG_BUTTON_OK]", "", 3);
                return;
            }
            mPressedButtonId = theSelectedButton;
            (*(int (**)(MainMenu *))(*(uint32_t *)this + 496))(this);
            return;
        case VS_COOP_BUTTON: // 如果按下了结盟按钮
            if (mCoopModeLocked) {
                // 如果没解锁结盟（冒险2-1解锁）
                LawnApp_LawnMessageBox(mApp, Dialogs::DIALOG_MESSAGE, "[MODE_LOCKED]", "[COOP_LOCKED_MESSAGE]", "[DIALOG_BUTTON_OK]", "", 3);
                return;
            }
            mPressedButtonId = theSelectedButton;
            (*(void (**)(MainMenu *))(*(uint32_t *)this + 496))(this);
            return;
        case ACHIEVEMENTS_BUTTON:
        case ACHIEVEMENTS_BACK_BUTTON:
            if (gMainMenuAchievementsWidget == nullptr) {
                gAchievementState = SLIDING_IN;
                gMainMenuAchievementCounter = 100;
                gMainMenuAchievementsWidget = (AchievementsWidget *)operator new(sizeof(AchievementsWidget));
                MaskHelpWidget_MaskHelpWidget(gMainMenuAchievementsWidget, mApp);
                gMainMenuAchievementsWidget->mIsScrolling = false;
                Sexy_Widget_Resize(gMainMenuAchievementsWidget, 0, gMainMenuHeight, 1280, addonImages.hole->mHeight * (gAchievementHoleLength + 1));
                gMainMenuAchievementsWidget->mWidgetId = ACHIEVEMENTS_BUTTON;
                Sexy_Widget_AddWidget(this, gMainMenuAchievementsWidget);
            } else {
                gAchievementState = SLIDING_OUT;
                gMainMenuAchievementCounter = gMainMenuAchievementsWidget->mY == gMainMenuHeight ? 100 : 150;
                gMainMenuAchievementsWidgetY = gMainMenuAchievementsWidget->mY;
            }
            return;
        case HOUSE_BUTTON:
            mPressedButtonId = theSelectedButton;
            (*(void (**)(MainMenu *))(*(uint32_t *)this + 496))(this);
            return;
        case UNLOCK_BUTTON:
            mPressedButtonId = theSelectedButton;
            (*(void (**)(MainMenu *))(*(uint32_t *)this + 496))(this);
            return;
        default:
            old_MainMenu_ButtonDepress(this, theSelectedButton);
            return;
    }
}

void MainMenu::KeyDown(Sexy::KeyCode theKeyCode) {
    // 为1.1.5解锁左方向键进入“更多游戏模式”
    if (MainMenu_InTransition(this))
        return;
    if (mIsFading)
        return;
    if (mEnterReanimationCounter > 0)
        return;

    if (gMainMenuAchievementsWidget != nullptr) {
        if (gAchievementState != SHOWING)
            return;
        if (theKeyCode == Sexy::Back || theKeyCode == Sexy::Back2) {
            MainMenu::ButtonDepress(ACHIEVEMENTS_BUTTON);
        } else if (theKeyCode == Sexy::Up || theKeyCode == Sexy::Down) {
            if (gMainMenuAchievementKeyboardScrollCounter != 0) {
                return;
                //                int theNewY = gMainMenuAchievementsKeyboardScrollWidgetY -(gMainMenuAchievementKeyboardScrollDirection ? 192 : -192);
                //                if (theNewY > gMainMenuHeight) theNewY = gMainMenuHeight;
                //                if (theNewY < 720 +gMainMenuHeight - (gAchievementHoleLength + 1) * addonImages.hole->mHeight) theNewY =  720 +gMainMenuHeight - (gAchievementHoleLength + 1) *
                //                addonImages.hole->mHeight; Sexy_Widget_Move(gMainMenuAchievementsWidget, gMainMenuAchievementsWidget->mX, theNewY);
            }
            gMainMenuAchievementKeyboardScrollCounter = gKeyboardScrollTime;
            gMainMenuAchievementsKeyboardScrollWidgetY = gMainMenuAchievementsWidget->mY;
            gMainMenuAchievementKeyboardScrollDirection = theKeyCode == Sexy::Down;
        }
        return;
    }

    MainMenuButtonId mSelectedButton = (MainMenuButtonId)mFocusedChildWidget->mWidgetId;
    if ((mSelectedButton == ADVENTURE_BUTTON || mSelectedButton == MORE_WAYS_BUTTON || mSelectedButton == START_ADVENTURE_BUTTON) && theKeyCode == Sexy::Left) {
        // 如果当前选中的按钮为"冒险模式"或者为"更多游戏方式"，同时玩家又按下了左方向键
        MainMenu_SetScene(this, MENUSCENE_MORE_WAYS);
        return;
    }

    old_MainMenu_KeyDown(this, theKeyCode);
}

void MainMenu_UpdateHouseReanim(MainMenu *mainMenu) {

    Reanimation *mMainMenuReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mMainMenuReanimID);
    if (mMainMenuReanim == nullptr)
        return;
    Reanimation_SetImageDefinition(mMainMenuReanim, "leaderboards", addonImages.leaderboards);
    if (!showHouse)
        return;
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood1", addonImages.hood1_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood2", addonImages.hood2_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood3", addonImages.hood3_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood4", addonImages.hood4_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "ground color copy", addonImages.house_hill_house);
    Reanimation *houseReanimation = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mHouseReanimID);
    if (houseReanimation == nullptr)
        return;
    LawnApp_SetHouseReanim(mainMenu->mApp, houseReanimation);
}

void MainMenu::SyncProfile(bool a2) {
    //    LOGD("MainMenu_SyncProfile");
    old_MainMenu_SyncProfile(this, a2);
    mApp->mNewIs3DAccelerated = mApp->mPlayerInfo == nullptr || !mApp->mPlayerInfo->mIs3DAcceleratedClosed;
}


constexpr int mZombatarButtonX = 2800;
constexpr int mZombatarButtonY = -20;

void MainMenu_EnableButtons(MainMenu *mainMenu) {
    Sexy::Widget *achievementsButton = Sexy_Widget_FindWidget(mainMenu, ACHIEVEMENTS_BUTTON);
    GameButton_SetDisabled((Sexy::GameButton *)achievementsButton, false);
    Sexy::Widget *leaderboardsButton = Sexy_Widget_FindWidget(mainMenu, HOUSE_BUTTON);
    Sexy_Widget_SetVisible(leaderboardsButton, true);
    Sexy::Widget *helpButton = Sexy_Widget_FindWidget(mainMenu, HELP_AND_OPTIONS_BUTTON);
    Sexy::Widget *backButton = Sexy_Widget_FindWidget(mainMenu, RETURN_TO_ARCADE_BUTTON);
    helpButton->mFocusLinks[3] = backButton;
    backButton->mFocusLinks[2] = helpButton;
    Sexy::Widget *zombatarButton = Sexy_Widget_FindWidget(mainMenu, UNLOCK_BUTTON);
    GameButton_SetDisabled((Sexy::GameButton *)zombatarButton, false);
    ((Sexy::GameButton *)zombatarButton)->mButtonImage = addonImages.SelectorScreen_WoodSign3;
    ((Sexy::GameButton *)zombatarButton)->mDownImage = addonImages.SelectorScreen_WoodSign3_press;
    ((Sexy::GameButton *)zombatarButton)->mOverImage = addonImages.SelectorScreen_WoodSign3_press;
    zombatarButton->mFocusLinks[0] = Sexy_Widget_FindWidget(mainMenu, BACK_POT_BUTTON);
    zombatarButton->mFocusLinks[1] = zombatarButton->mFocusLinks[0];
    zombatarButton->mFocusLinks[2] = zombatarButton->mFocusLinks[0];
    zombatarButton->mFocusLinks[3] = zombatarButton->mFocusLinks[0];
    Sexy_Widget_Resize(zombatarButton, addonImages.SelectorScreen_WoodSign3->mWidth / 2, 0, addonImages.SelectorScreen_WoodSign3->mWidth, addonImages.SelectorScreen_WoodSign3->mHeight);
    Reanimation *mainMenuReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mMainMenuReanimID);
    if (mainMenuReanim == nullptr)
        return;
    Reanimation_HideTrack(mainMenuReanim, "unlock stem", true);

    int index[3] = {Reanimation_FindTrackIndex(mainMenuReanim, "unlock"), Reanimation_FindTrackIndex(mainMenuReanim, "unlock pressed"), Reanimation_FindTrackIndex(mainMenuReanim, "unlock selected")};

    for (int i = 0; i < 3; ++i) {
        ReanimatorTrack *reanimatorTrack = mainMenuReanim->mDefinition->mTracks + index[i];
        int mTransformCount = reanimatorTrack->mTransformCount;
        for (int j = 0; j < mTransformCount; ++j) {
            reanimatorTrack->mTransforms[j].mTransX = mZombatarButtonX;
            reanimatorTrack->mTransforms[j].mTransY = mZombatarButtonY;
        }
    }

    //    if (mainMenu->mPressedButtonId == UNLOCK_BUTTON) {
    //        LOGD("123123213");
    //        Reanimation *mainMenuReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mMainMenuReanimID);
    //        if (mainMenuReanim != nullptr) {
    //            int index = Reanimation_FindTrackIndex(mainMenuReanim, "unlock");
    //            ReanimatorTrack *reanimatorTrack = mainMenuReanim->mDefinition->mTracks + index;
    //            int mTransformCount = reanimatorTrack->mTransformCount;
    //            int theX = mZombatarButtonX + addonImages.SelectorScreen_WoodSign3->mWidth;
    //            for (int j = 0; j < mTransformCount; ++j) {
    //                reanimatorTrack->mTransforms[j].mTransX = theX;
    //            }
    //        }
    //    }
}

void MainMenu::Enter() {
    old_MainMenu_Enter(this);
    MainMenu_UpdateHouseReanim(this);
    // 解除成就按钮的禁用状态
    MainMenu_EnableButtons(this);
}

bool MainMenu::UpdateExit() {
    return old_MainMenu_UpdateExit(this);
}

void MainMenu::Exit() {
    old_MainMenu_Exit(this);
    // 解除成就按钮的禁用状态
    MainMenu_EnableButtons(this);
}

void MainMenu::OnExit() {
    TodFoley_StopFoley(mApp->mSoundSystem, FoleyType::FOLEY_MENU_LEFT);
    TodFoley_StopFoley(mApp->mSoundSystem, FoleyType::FOLEY_MENU_CENTRE);
    TodFoley_StopFoley(mApp->mSoundSystem, FoleyType::FOLEY_MENU_RIGHT);

    if (mPressedButtonId == HOUSE_BUTTON) {
        LawnApp_KillMainMenu(mApp);
        LawnApp_ShowLeaderboards(mApp);
    }

    if (mPressedButtonId == UNLOCK_BUTTON) {
        LawnApp_KillMainMenu(mApp);
        LawnApp_ShowZombatarScreen(mApp);
    }

//    if (mPressedButtonId == VS_BUTTON) {
//        LawnApp_KillMainMenu(mApp);
////        TODO:为对战添加选择场景
//        LawnApp_ShowChallengeScreen(mApp, CHALLENGE_PAGE_VS);
//        return;
//    }

    old_MainMenu_OnExit(this);
}

void MainMenu::OnScene(int theScene) {
    return old_MainMenu_OnScene(this, theScene);
}

void MainMenu::SyncButtons() {
    // 解除成就按钮的禁用状态,同时刷新房子
    old_MainMenu_SyncButtons(this);
    MainMenu_UpdateHouseReanim(this);
    MainMenu_EnableButtons(this);
}

void MainMenu::Creat(LawnApp* theApp) {
    old_MainMenu_MainMenu(this, theApp);
}


namespace {
int theOffsetX = 1792;
int theOffsetY = 220;
int theOffsetX1 = 237;
int theOffsetY1 = 60;
} // namespace

void MainMenu::UpdateCameraPosition() {
    old_MainMenu_UpdateCameraPosition(this);
    if (showHouse) {
        Reanimation *houseAnim = LawnApp_ReanimationTryToGet(mApp, mHouseReanimID);
        if (houseAnim != nullptr) {
            Reanimation_SetPosition(houseAnim, mCameraPositionX + theOffsetX, mCameraPositionY + theOffsetY);
        }
    }
}

void MainMenu::AddedToManager(int* a2) {
    old_MainMenu_AddedToManager(this, a2);
    if (!showHouse)
        return;
    Reanimation *reanimation = LawnApp_AddReanimation(mApp, 0, 0, 0, ReanimationType::REANIM_LEADERBOARDS_HOUSE);
    //    Reanimation *reanimation = LawnApp_AddReanimation(mainMenu->mApp, mainMenu->mCameraPositionX + theOffsetX,mainMenu->mCameraPositionY + theOffsetY, 0, ReanimationType::REANIM_LEADERBOARDS_HOUSE);
    reanimation->mCustomFilterEffectColor = {142, 146, 232, 92};
    reanimation->mFilterEffect = FilterEffectType::FILTEREFFECT_CUSTOM;


    LawnApp_SetHouseReanim(mApp, reanimation);
    mHouseReanimID = LawnApp_ReanimationGetID(mApp, reanimation);
}

void MainMenu::RemovedFromManager(int* a2) {
    // 记录当前游戏状态
    if (gMainMenuAchievementsWidget != nullptr) {
        Sexy_Widget_RemoveWidget(this, gMainMenuAchievementsWidget);
    }
    if (gMainMenuAchievementsBack != nullptr) {
        Sexy_Widget_RemoveWidget(this, gMainMenuAchievementsBack);
    }
    old_MainMenu_RemovedFromManager(this, a2);
}

void MainMenu::Delete2() {
    old_MainMenu_Delete2(this);
    if (gMainMenuAchievementsWidget != nullptr) {
        MaskHelpWidget_Delete(gMainMenuAchievementsWidget);
        gMainMenuAchievementsWidget = nullptr;
    }

    if (gMainMenuAchievementsBack != nullptr) {
        GameButton_Delete(gMainMenuAchievementsBack);
        gMainMenuAchievementsBack = nullptr;
    }
}

void MainMenu::Draw(Sexy::Graphics* g) {
    // 实现绘制房子
    if (!showHouse)
        return old_MainMenu_Draw(this, g);

    if (mWidgetManager == nullptr)
        return;
    if ((*(int (**)(LawnApp *, int))(*(uint32_t *)mApp + 412))(mApp, 6) || (*(int (**)(LawnApp *, int))(*(uint32_t *)mApp + 412))(mApp, 5)
        || (*(int (**)(LawnApp *, int))(*(uint32_t *)mApp + 412))(mApp, 60))
        return;

    Reanimation *mainMenuReanim = LawnApp_ReanimationTryToGet(mApp, mMainMenuReanimID);
    if (mainMenuReanim == nullptr)
        return;
    Reanimation *skyReanim = LawnApp_ReanimationTryToGet(mApp, mSkyReanimID);
    Reanimation *sky2Reanim = LawnApp_ReanimationTryToGet(mApp, mSky2ReanimID);

    if (skyReanim != nullptr && sky2Reanim != nullptr) {
        Reanimation_DrawRenderGroup(skyReanim, g, 0);
        SexyTransform2D tmp = sky2Reanim->mOverlayMatrix;
        Sexy_SexyTransform2D_Scale(&sky2Reanim->mOverlayMatrix, 1.0, 0.4);
        sky2Reanim->mOverlayMatrix.m[0][1] = -0.4;
        Reanimation_DrawRenderGroup(sky2Reanim, g, 2);
        sky2Reanim->mOverlayMatrix = tmp;
    }
    Reanimation_DrawRenderGroup(mainMenuReanim, g, 1);
    Reanimation *houseAnim = LawnApp_ReanimationTryToGet(mApp, mHouseReanimID);
    if (houseAnim != nullptr) {

        int TrackIndex = Reanimation_FindTrackIndex(mainMenuReanim, "House");
        ReanimatorTransform v52;
        ReanimatorTransform_ReanimatorTransform(&v52);
        SexyTransform2D v48;
        Sexy_SexyTransform2D_SexyTransform2D(&v48);
        Reanimation_GetCurrentTransform(mainMenuReanim, TrackIndex, &v52);
        Reanimation_MatrixFromTransform(&v52, &v48);
        Sexy_SexyTransform2D_Translate(&v48, mCameraPositionX + theOffsetX1, mCameraPositionY + theOffsetY1);
        houseAnim->mOverlayMatrix = v48;
        Reanimation_DrawRenderGroup(houseAnim, g, 0);
    }
    Reanimation_DrawRenderGroup(mainMenuReanim, g, 0);
    if (mScene == 2) {
        Reanimation *butterFlyReanim = LawnApp_ReanimationTryToGet(mApp, mButterflyReanimID);
        if (butterFlyReanim != nullptr) {
            Reanimation_Draw(butterFlyReanim, g);
        }
    }
    Reanimation *crowReanim = LawnApp_ReanimationTryToGet(mApp, mCrowReanimID);
    if (crowReanim != nullptr && (!unkBool5 || mExitCounter <= 65)) {
        Reanimation_Draw(crowReanim, g);
    }
    Sexy_MenuWidget_Draw(this, g);
    Sexy_Widget_DeferOverlay(this, 0);
    if (!MainMenu_InTransition(this))
        (*((void (**)(MainMenu *, Sexy::Graphics *))vTable + 129))(this, g);
    SexyTransform2D v42;
    ReanimatorTransform v43;
    int mailAlertTrackIndex = Reanimation_FindTrackIndex(mainMenuReanim, "mail alert");
    if (mailAlertTrackIndex > 0 && Mailbox_GetNumUnseenMessages(mApp->mMailBox) > 0) {
        PlayerInfo *mPlayerInfo = mApp->mPlayerInfo;
        if (mPlayerInfo->mLevel > 0 || LawnPlayerInfo_GetFlag(mPlayerInfo, 1)) {
            ReanimatorTransform_ReanimatorTransform(&v43);
            Reanimation_GetCurrentTransform(mainMenuReanim, mailAlertTrackIndex, &v43);
            Sexy::Image *mailAlertImage = v43.mImage;
            Sexy_SexyTransform2D_SexyTransform2D(&v42);
            Reanimation_MatrixFromTransform(&v43, &v42);
            Sexy_SexyTransform2D_Translate(&v42, mCameraPositionX, mCameraPositionY);
            int v14 = mailAlertImage->mWidth;
            int v15 = v14 + 3;
            int v16 = v14 < 0;
            int v17 = v14 & ~(v14 >> 31);
            if (v16)
                v17 = v15;
            Sexy_SexyTransform2D_Translate(&v42, v17 >> 2, 0.0);
            int v18 = unkMems3[3];
            if (v18 > 99)
                v18 = 0;
            unkMems3[3] = v18;
            TodAnimateCurveFloat(0, 100, v18, 0.75, 0.8, TodCurves::CURVE_SIN_WAVE);
            TRect v38 = {0, 0, mailAlertImage->mWidth, mailAlertImage->mHeight};
            Sexy_Graphics_DrawImageMatrix(g, mailAlertImage, &v42, &v38, 0.0, 0.0, 1);
        }
    }
    int moreTrackIndex = Reanimation_FindTrackIndex(mainMenuReanim, "more");
    ReanimatorTransform_ReanimatorTransform(&v43);
    Reanimation_GetCurrentTransform(mainMenuReanim, moreTrackIndex, &v43);
    Sexy_SexyTransform2D_SexyTransform2D(&v42);
    Reanimation_MatrixFromTransform(&v43, &v42);
    Sexy_SexyTransform2D_Translate(&v42, mCameraPositionX, mCameraPositionY);
    Sexy_SexyTransform2D_Translate(&v42, 120.0, 200.0);

    TRect v37 = {0, 0, m2DMarkImage->mWidth, m2DMarkImage->mHeight};
    Sexy_Graphics_DrawImageMatrix(g, m2DMarkImage, &v42, &v37, 0.0, 0.0, 1);
    TRect v38 = {15, 15, 90, 90};
    Sexy_SexyTransform2D_Translate(&v42, -4.0, -16.0);
    Sexy_Graphics_DrawImageMatrix(g, mApp->mQRCodeImage, &v42, &v38, 0.0, 0.0, 1);
}

void MainMenu::DrawOverlay(Sexy::Graphics* g) {
    // 在成就界面存在时，不显示冒险关卡数
    if (gMainMenuAchievementsWidget != nullptr) {
        return;
    }
    return old_MainMenu_DrawOverlay(this, g);
}

void MainMenu::DrawFade(Sexy::Graphics *g) {
    // 修复主界面的退出动画在高帧率设备上的加速。原理是将计时器的更新从Draw移动至Update
    float num = mFadeCounterFloat;
    //    if (mainMenu->mFadeCounterFloat < 0.992) {
    //        mainMenu->mFadeCounterFloat -= 0.008;
    //    }
    old_MainMenu_DrawFade(this, g);
    mFadeCounterFloat = num;
}

void MaskHelpWidget_Draw(AchievementsWidget *achievementsWidget, Sexy::Graphics *graphics) {
    int theY = 0;
    int theDiffY = addonImages.hole->mHeight;
    for (int i = 0; i < gAchievementHoleLength; i++) {
        if (i == gAchievementHoleWormPos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_worm, 0, theY);
        } else if (i == gAchievementHoleGemsPos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_gems, 0, theY);
        } else if (i == gAchievementHoleChuzzlePos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_chuzzle, 0, theY);
        } else if (i == gAchievementHoleBjornPos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_bjorn, 0, theY);
        } else if (i == gAchievementHolePipePos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_pipe, 0, theY);
        } else if (i == gAchievementHoleTikiPos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_tiki, 0, theY);
        } else if (i == gAchievementHoleHeavyRocksPos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_heavyrocks, 0, theY);
        } else if (i == gAchievementHoleDuWeiPos) {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole_duwei, 0, theY);
        } else {
            Sexy_Graphics_DrawImage(graphics, addonImages.hole, 0, theY);
        }
        theY += theDiffY;
    }
    Sexy_Graphics_DrawImage(graphics, addonImages.hole_china, 0, theY);
    Sexy_Graphics_DrawImage(graphics, addonImages.hole_top, 0, 0);
    int theAchievementY = 300;
    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        if (!achievementsWidget->mApp->mPlayerInfo->mAchievements[i]) {
            Sexy_Graphics_SetColorizeImages(graphics, true);
            Sexy_Graphics_SetColor(graphics, &gray);
        }
        Sexy_Graphics_DrawImage(graphics, GetIconByAchievementId((AchievementId::AchievementId)i), 330, theAchievementY - 5);
        const char *theAchievementName = GetNameByAchievementId((AchievementId::AchievementId)i);
        int holder[1];
        int holder1[1];
        Sexy_StrFormat(holder, "[%s]", theAchievementName);
        Sexy_StrFormat(holder1, "[%s_TEXT]", theAchievementName);
        Color theColor = {0, 255, 0, 255};
        Color theColor1 = {255, 255, 255, 255};
        TRect rect = {460, theAchievementY + 60, 540, 0};
        TodDrawString(graphics, holder, 460, theAchievementY + 40, *Sexy_FONT_HOUSEOFTERROR28_Addr, theColor, DrawStringJustification::DS_ALIGN_LEFT);
        if (i == AchievementId::ACHIEVEMENT_SHOP) {
            int holder2[1];
            TodReplaceNumberString(holder2, holder1, "{coin}", achievementsWidget->mApp->mPlayerInfo->mUsedCoins * 10);
            TodDrawStringWrapped(graphics, holder2, &rect, *Sexy_FONT_HOUSEOFTERROR20_Addr, &theColor1, DrawStringJustification::DS_ALIGN_LEFT, false);
            Sexy_String_Delete(holder2);
        } else {
            TodDrawStringWrapped(graphics, holder1, &rect, *Sexy_FONT_HOUSEOFTERROR20_Addr, &theColor1, DrawStringJustification::DS_ALIGN_LEFT, false);
        }
        Sexy_String_Delete(holder);
        Sexy_String_Delete(holder1);
        Sexy_Graphics_SetColorizeImages(graphics, false);
        theAchievementY += theDiffY * 2 / 3;
    }
    int theAccomplishedNum = 0;
    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        if (achievementsWidget->mApp->mPlayerInfo->mAchievements[i]) {
            theAccomplishedNum++;
        }
    }
    int holder[1];
    Sexy_StrFormat(holder, "%d/%d", theAccomplishedNum, AchievementId::MAX_ACHIEVEMENTS);
    Color theColor = {255, 240, 0, 255};
    TodDrawString(graphics, holder, 1060, 173, *Sexy_FONT_DWARVENTODCRAFT18_Addr, theColor, DrawStringJustification::DS_ALIGN_CENTER);
    Sexy_String_Delete(holder);
}

void MaskHelpWidget_MouseDown(AchievementsWidget *achievementsWidget, int x, int y, int theClickCount) {
    achievementsWidget->mIsScrolling = false;
    achievementsWidget->mMouseDownY = y;
    achievementsWidget->mLastDownY = y;
    achievementsWidget->mLastDownY1 = achievementsWidget->mLastDownY;
    struct timeval tp;
    gettimeofday(&tp, nullptr);
    achievementsWidget->mLastTimeMs = tp.tv_sec * 1000 + tp.tv_usec / 1000; // Convert to milliseconds
    achievementsWidget->mLastTimeMs1 = achievementsWidget->mLastTimeMs;
}

void MaskHelpWidget_MouseDrag(AchievementsWidget *achievementsWidget, int x, int y) {
    if (gAchievementState != SHOWING)
        return;
    int theNewY = std::clamp(achievementsWidget->mY + (y - achievementsWidget->mMouseDownY), 720 + gMainMenuHeight - (gAchievementHoleLength + 1) * addonImages.hole->mHeight, gMainMenuHeight);
    Sexy_Widget_Move(achievementsWidget, achievementsWidget->mX, theNewY);
    achievementsWidget->mLastDownY1 = achievementsWidget->mLastDownY;
    achievementsWidget->mLastDownY = y;
    struct timeval tp;
    gettimeofday(&tp, nullptr);
    achievementsWidget->mLastTimeMs1 = achievementsWidget->mLastTimeMs;
    achievementsWidget->mLastTimeMs = tp.tv_sec * 1000 + tp.tv_usec / 1000; // Convert to milliseconds
}

void MaskHelpWidget_MouseUp(AchievementsWidget *achievementsWidget, int x, int y) {
    struct timeval tp;
    gettimeofday(&tp, nullptr);
    long currentTimeMs = tp.tv_sec * 1000 + tp.tv_usec / 1000; // Convert to milliseconds
    long deltaT = currentTimeMs - achievementsWidget->mLastTimeMs;
    int deltaX = achievementsWidget->mLastDownY - achievementsWidget->mMouseDownY;
    if (deltaT == 0) {
        deltaT = currentTimeMs - achievementsWidget->mLastTimeMs1;
        deltaX = achievementsWidget->mLastDownY1 - achievementsWidget->mMouseDownY;
    }
    if (deltaX != 0 && deltaT != 0) {
        achievementsWidget->mIsScrolling = true;
        achievementsWidget->mVelocity = 5.0f * deltaX / deltaT;
    }
    achievementsWidget->mLastTimeMs = currentTimeMs;
}

void MaskHelpWidget_Update(AchievementsWidget *achievementsWidget) {
    // 实现滚动
    if (achievementsWidget->mIsScrolling) {
        int theNewY = std::clamp<int>(achievementsWidget->mY + achievementsWidget->mVelocity, 720 + gMainMenuHeight - (gAchievementHoleLength + 1) * addonImages.hole->mHeight, gMainMenuHeight);
        Sexy_Widget_Move(achievementsWidget, achievementsWidget->mX, theNewY);
        achievementsWidget->mVelocity *= 0.96;
        if (fabs(achievementsWidget->mVelocity) < 1.0f) {
            achievementsWidget->mIsScrolling = false;
        }
    }
    Sexy_Widget_MarkDirty(achievementsWidget);
}

Sexy::Image *TrashBin_GetZombieTrashPiece(TrashBin *trashBin, int level) {
    int v3; // r0
    int v4; // r2
    int v5; // r3
    int v6; // r3

    v3 = RandRangeInt(0, 100);
    v4 = *((uint32_t *)trashBin + 85);
    if (v4 >= 3)
        v5 = 3;
    else
        v5 = *((uint32_t *)trashBin + 85);
    if (v3 >= *((uint32_t *)trashBin + v5 + 79) && v3 <= *((uint32_t *)trashBin + v5 + 82)) {
        while (1) {
            v3 = RandRangeInt(0, 100);
            v4 = *((uint32_t *)trashBin + 85);
            v6 = v4 >= 3 ? 3 : *((uint32_t *)trashBin + 85);
            if (*((uint32_t *)trashBin + v6 + 79) > v3)
                break;
            if (*((uint32_t *)trashBin + v6 + 82) < v3) {
                if (!v4)
                    goto LABEL_11;
                goto LABEL_16;
            }
        }
    }
    if (v4) {
    LABEL_16:
        if (v4 == 1) {
            if (v3 <= 29) {
                *((uint32_t *)trashBin + 80) = 0;
                *((uint32_t *)trashBin + 83) = 30;
                return addonImages.zombie_pile02_stack02;
            } else if (v3 > 59) {
                *((uint32_t *)trashBin + 80) = 61;
                *((uint32_t *)trashBin + 83) = 100;
                return addonImages.zombie_pile02_stack03;
            } else {
                *((uint32_t *)trashBin + 80) = 31;
                *((uint32_t *)trashBin + 83) = 60;
                return addonImages.zombie_pile02_stack01;
            }
        } else if (v3 <= 29) {
            *((uint32_t *)trashBin + 81) = 0;
            *((uint32_t *)trashBin + 84) = 30;
            return addonImages.zombie_pile03_stack02;
        } else if (v3 <= 59) {
            *((uint32_t *)trashBin + 81) = 31;
            *((uint32_t *)trashBin + 84) = 60;
            return addonImages.zombie_pile03_stack03;
        } else {
            *((uint32_t *)trashBin + 81) = 61;
            *((uint32_t *)trashBin + 84) = 100;
            return addonImages.zombie_pile03_stack01;
        }
    } else {
    LABEL_11:
        if (v3 <= 29) {
            *((uint32_t *)trashBin + 82) = 30;
            *((uint32_t *)trashBin + 79) = v4;
            return addonImages.zombie_pile01_stack02;
        } else if (v3 > 59) {
            *((uint32_t *)trashBin + 79) = 61;
            *((uint32_t *)trashBin + 82) = 100;
            return addonImages.zombie_pile01_stack03;
        } else {
            *((uint32_t *)trashBin + 79) = 31;
            *((uint32_t *)trashBin + 82) = 60;
            return addonImages.zombie_pile01_stack01;
        }
    }
}

Sexy::Image *TrashBin_GetPlantTrashPiece(TrashBin *trashBin, int level) {
    int mPileNum = trashBin->mPileNum;
    if (mPileNum != 0) {
        if (mPileNum == 1) {
            if (RandRangeInt(trashBin->mRandomPileWeight[1], trashBin->mRandomPileWeight[4]) > 49) {
                trashBin->mRandomPileWeight[1] = 0;
                trashBin->mRandomPileWeight[4] = 50;
                return addonImages.plant_pile02_stack02;
            } else {
                trashBin->mRandomPileWeight[1] = 50;
                trashBin->mRandomPileWeight[4] = 100;
                return addonImages.plant_pile02_stack01;
            }
        } else if (RandRangeInt(trashBin->mRandomPileWeight[2], trashBin->mRandomPileWeight[5]) <= 49) {
            trashBin->mRandomPileWeight[2] = 50;
            trashBin->mRandomPileWeight[5] = 100;
            return addonImages.plant_pile03_stack01;
        } else {
            trashBin->mRandomPileWeight[2] = 0;
            trashBin->mRandomPileWeight[5] = 50;
            return addonImages.plant_pile03_stack02;
        }
    } else if (RandRangeInt(trashBin->mRandomPileWeight[0], trashBin->mRandomPileWeight[3]) > 49) {
        trashBin->mRandomPileWeight[3] = 50;
        trashBin->mRandomPileWeight[0] = 0;
        return addonImages.plant_pile01_stack02;
    } else {
        trashBin->mRandomPileWeight[0] = 50;
        trashBin->mRandomPileWeight[3] = 100;
        return addonImages.plant_pile01_stack01;
    }
}

TrashBin::TrashBin(TrashPileType theTrashPileType, float theHeight) {
    Create(theTrashPileType, theHeight);
}

constexpr int zombiePileHeight = 70;
constexpr int plantPileHeight = 100;

void TrashBin::Create(TrashPileType theTrashPileType, float theHeight) {
    old_TrashBin_TrashBin(this, theTrashPileType, theHeight);

    int thePileNum = theHeight / (theTrashPileType == TrashBin::ZOMBIE_PILE ? zombiePileHeight : plantPileHeight) + 1;
    if (thePileNum >= 10)
        thePileNum = 10;
    PlayerInfo *mPlayerInfo = ((LawnApp *)*gLawnApp_Addr)->mPlayerInfo;
    int level = mPlayerInfo->mLevel;
    if (LawnPlayerInfo_GetFlag(mPlayerInfo, 1) || LawnPlayerInfo_GetFlag(mPlayerInfo, 0x8000))
        level = 50;
    mPileNum = 0;
    for (int i = 0; i < thePileNum; ++i) {
        if (mTrashPileType == TrashBin::PLANT_PILE) {
            mPileImage[i] = TrashBin_GetPlantTrashPiece(this, level);
        } else {
            mPileImage[i] = TrashBin_GetZombieTrashPiece(this, level);
        }
        mMirrorPile[i] = RandRangeInt(0, 100) <= 49;
        mPileNum++;
    }
}

void TrashBin::Draw(Sexy::Graphics *g) {
    int thePileHeight = mTrashPileType == TrashBin::ZOMBIE_PILE ? zombiePileHeight : plantPileHeight;
    int thePileNum = mTrashHeight / thePileHeight;
    if (thePileNum >= 10)
        thePileNum = 10;
    if (mTrashPileType == TrashBin::PLANT_PILE) {
        Sexy_Graphics_DrawImageF(g, addonImages.plant_can, mX - 22, mY + 15);
    } else {
        Sexy_Graphics_DrawImageF(g, addonImages.zombie_can, mX, mY);
    }

    if (thePileNum != 10) {
        Sexy_Graphics_DrawImageMirror(g, mPileImage[thePileNum], mX, mHeight % thePileHeight - thePileHeight + mY - thePileHeight * thePileNum, mMirrorPile[thePileNum]);
    }
    if (thePileNum <= 0)
        return;
    for (int i = 0; i < thePileNum; ++i) {
        Sexy_Graphics_DrawImageMirror(g, mPileImage[i], mX, mHeight % thePileHeight - thePileHeight + mY - thePileHeight * i, mMirrorPile[i]);
    }

    //    int holder[1];
    //    int holder1[1];
    //    TodStringTranslate(holder,"[TRASH_HEIGHT]");
    //    TodReplaceNumberString(holder1,holder,"{HEIGHT}",(int)trashBin->mTrashHeight);
    //
    //    if (mTrashPileType == ZOMBIE_TRASH_BIN::PLANT_PILE) {
    //        TRect theRect ={317,658,120,50};
    //        Sexy::Font* theFont = *Sexy_FONT_CONTINUUMBOLD14_Addr;
    //        TodDrawStringWrapped(g, holder1, &theRect, theFont, &yellow, DrawStringJustification::DS_ALIGN_CENTER, false);
    //    }else {
    //        Sexy_Graphics_DrawImageF(g, addonImages.zombie_can, trashBin->mX, trashBin->mY);
    //    }
}

int LeaderboardsWidget_GetAchievementIdByReanimationType(ReanimationType type) {
    AchievementId::AchievementId id = AchievementId::ACHIEVEMENT_HOME_SECURITY;
    switch (type) {
        case ReanimationType::REANIM_ACHIEVEMENT_HOME_SECURITY:
            id = AchievementId::ACHIEVEMENT_HOME_SECURITY;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_MORTICULTURALIST:
            id = AchievementId::ACHIEVEMENT_MORTICULTURALIST;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_SMARTY_BRANCHES:
            id = AchievementId::ACHIEVEMENT_TREE;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_CRASH_OF_THE_TITAN:
            id = AchievementId::ACHIEVEMENT_GARG;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_Zffs4Evr:
            id = AchievementId::ACHIEVEMENT_COOP;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_ALIVE_AND_PLANTING:
            id = AchievementId::ACHIEVEMENT_IMMORTAL;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_VERSUS:
            id = AchievementId::ACHIEVEMENT_VERSUS;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_SOIL_YOUR_PLANTS:
            id = AchievementId::ACHIEVEMENT_SOILPLANTS;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_EXPLODONATOR:
            id = AchievementId::ACHIEVEMENT_EXPLODONATOR;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_CLOSE_SHAVE:
            id = AchievementId::ACHIEVEMENT_CLOSESHAVE;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_SHOP:
            id = AchievementId::ACHIEVEMENT_SHOP;
            break;
        case ReanimationType::REANIM_ACHIEVEMENT_NOM_NOM_NOM:
            id = AchievementId::ACHIEVEMENT_CHOMP;
            break;
    }
    return id - AchievementId::ACHIEVEMENT_HOME_SECURITY;
}

int LeaderboardsWidget_GetAchievementIdByDrawOrder(int drawOrder) {
    ReanimationType type = ReanimationType::REANIM_ACHIEVEMENT_HOME_SECURITY;
    switch (drawOrder) {
        case 0:
            type = ReanimationType::REANIM_ACHIEVEMENT_CLOSE_SHAVE;
            break;
        case 1:
            type = ReanimationType::REANIM_ACHIEVEMENT_SHOP;
            break;
        case 2:
            type = ReanimationType::REANIM_ACHIEVEMENT_EXPLODONATOR;
            break;
        case 3:
            type = ReanimationType::REANIM_ACHIEVEMENT_ALIVE_AND_PLANTING;
            break;
        case 4:
            type = ReanimationType::REANIM_ACHIEVEMENT_SMARTY_BRANCHES;
            break;
        case 5:
            type = ReanimationType::REANIM_ACHIEVEMENT_NOM_NOM_NOM;
            break;
        case 6:
            type = ReanimationType::REANIM_ACHIEVEMENT_SOIL_YOUR_PLANTS;
            break;
        case 7:
            type = ReanimationType::REANIM_ACHIEVEMENT_VERSUS;
            break;
        case 8:
            type = ReanimationType::REANIM_ACHIEVEMENT_Zffs4Evr;
            break;
        case 9:
            type = ReanimationType::REANIM_ACHIEVEMENT_CRASH_OF_THE_TITAN;
            break;
        case 10:
            type = ReanimationType::REANIM_ACHIEVEMENT_MORTICULTURALIST;
            break;
        case 11:
            type = ReanimationType::REANIM_ACHIEVEMENT_HOME_SECURITY;
            break;
    }
    return type - ReanimationType::REANIM_ACHIEVEMENT_HOME_SECURITY;
}

void LeaderboardsWidget_ButtonDepress(Sexy::ButtonListener *listener, int id) {
    if (id == 1000) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        LawnApp_KillLeaderboards(lawnApp);
        LawnApp_ShowMainMenuScreen(lawnApp);
    }
}

void LeaderboardsWidget_ButtonPress(Sexy::ButtonListener *listener, int id, int theCount) {}

void Sexy_ButtonListener_ButtonMouseEnter(Sexy::ButtonListener *listener, int id) {}

void Sexy_ButtonListener_ButtonMouseMove(Sexy::ButtonListener *listener, int id, int x, int y) {}

void Sexy_ButtonListener_ButtonMouseLeave(Sexy::ButtonListener *listener, int id) {}

void Sexy_ButtonListener_ButtonDownTick(Sexy::ButtonListener *listener, int id) {}


static float gLeaderboardAchievementsPosition[12][2] = {
    {198, 496},
    {210, 492},
    {222, 306},
    {405, 501},
    {368, 500},
    {690, 478},
    {615, 487},
    {524, 326},
    {756, 373},
    {678, 390},
    {791, 278},
    {430, 362},
};

void LeaderboardsWidget_LeaderboardsWidget(LeaderboardsWidget *this_, LawnApp *lawnApp) {
    DaveHelp_DaveHelp(this_, lawnApp);
    Sexy_Widget_Resize(this_, -240, -60, 1280, 720);
    this_->mLeaderboardReanimations = (LeaderboardReanimations *)operator new(sizeof(LeaderboardReanimations));
    for (int i = 0; i < 5; ++i) {
        Reanimation *reanim = (Reanimation *)operator new(sizeof(Reanimation));
        Reanimation_Reanimation(reanim);
        Reanimation_ReanimationInitializeType(reanim, 0.0, 0.0, (ReanimationType)(ReanimationType::REANIM_LEADERBOARDS_HOUSE + i));
        Reanimation_SetAnimRate(reanim, 0.0f);
        reanim->mLoopType = ReanimLoopType::REANIM_LOOP;
        if (i == 0) {
            LawnApp_SetHouseReanim(this_->mApp, reanim);
            Reanimation_SetPosition(reanim, 456.9f, 129.3f);
        }
        if (i == 1 || i == 2 || i == 3) {
            Reanimation_PlayReanim(reanim, "anim_idle", ReanimLoopType::REANIM_LOOP, 0, 12.0f);
        }
        if (i == 4) {
            Reanimation_PlayReanim(reanim, "anim_float", ReanimLoopType::REANIM_LOOP, 0, 2.0f); // 云儿飘得慢一些
        }
        Reanimation_Update(reanim); // 一次Update是必要的，否则绘制出来是Empty
        this_->mLeaderboardReanimations->backgroundReanim[i] = reanim;
    }
    this_->mLeaderboardReanimations->backgroundReanim[1]->AssignRenderGroupToTrack("survival button 1", 1);                   // 设置无尽模式按钮
    Reanimation_SetImageOverride(this_->mLeaderboardReanimations->backgroundReanim[1], "survival button 1", addonImages.survival_button); // 设置无尽模式按钮
    Reanimation_HideTrack(this_->mLeaderboardReanimations->backgroundReanim[1], "house 1", true);                                         // 隐藏默认房屋
    Reanimation_HideTrack(this_->mLeaderboardReanimations->backgroundReanim[1], "house achievements 1", true);                            // 隐藏默认房屋
    //    Reanimation_HideTrack(this_->mLeaderboardReanimations->backgroundReanim[1],"house 2",true); // 隐藏默认房屋
    //    Reanimation_HideTrack(this_->mLeaderboardReanimations->backgroundReanim[1],"house achievements 2",true); // 隐藏默认房屋

    int zombieTrackIndex = Reanimation_FindTrackIndex(this_->mLeaderboardReanimations->backgroundReanim[0], "PvZ/zombie_tra.h");
    SexyTransform2D zombieSexyTransform2D;
    Sexy_SexyTransform2D_SexyTransform2D(&zombieSexyTransform2D);
    Reanimation_GetTrackMatrix(this_->mLeaderboardReanimations->backgroundReanim[0], zombieTrackIndex, &zombieSexyTransform2D);
    this_->mZombieTrashBin = (TrashBin *)operator new(sizeof(TrashBin));
    this_->mZombieTrashBin->Create(TrashBin::ZOMBIE_PILE, lawnApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::ZOMBIES_KILLED] / 125.0f);
    Sexy_Widget_Move(this_->mZombieTrashBin, zombieSexyTransform2D.m[0][2], zombieSexyTransform2D.m[1][2]);

    int plantTrackIndex = Reanimation_FindTrackIndex(this_->mLeaderboardReanimations->backgroundReanim[0], "PvZ/plant_tra.h");
    SexyTransform2D plantSexyTransform2D;
    Sexy_SexyTransform2D_SexyTransform2D(&plantSexyTransform2D);
    Reanimation_GetTrackMatrix(this_->mLeaderboardReanimations->backgroundReanim[0], plantTrackIndex, &plantSexyTransform2D);
    this_->mPlantTrashBin = (TrashBin *)operator new(sizeof(TrashBin));
    this_->mPlantTrashBin->Create(TrashBin::PLANT_PILE, lawnApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::PLANTS_KILLED] / 125.0f);
    Sexy_Widget_Move(this_->mPlantTrashBin, plantSexyTransform2D.m[0][2], plantSexyTransform2D.m[1][2]);

    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        this_->mAchievements[i] =
            lawnApp->mPlayerInfo->mAchievements[LeaderboardsWidget_GetAchievementIdByReanimationType((ReanimationType)(ReanimationType::REANIM_ACHIEVEMENT_HOME_SECURITY + i))];
        Reanimation *reanim = (Reanimation *)operator new(sizeof(Reanimation));
        Reanimation_Reanimation(reanim);
        Reanimation_ReanimationInitializeType(reanim, 0.0, 0.0, (ReanimationType)(ReanimationType::REANIM_ACHIEVEMENT_HOME_SECURITY + i));
        Reanimation_SetPosition(reanim, gLeaderboardAchievementsPosition[i][0], gLeaderboardAchievementsPosition[i][1]);
        reanim->mLoopType = ReanimLoopType::REANIM_LOOP;
        Reanimation_Update(reanim); // 一次Update是必要的，否则绘制出来是Empty
        this_->mLeaderboardReanimations->achievementReanim[i] = reanim;
    }

    this_->mLongestRecordPool = lawnApp->mPlayerInfo->mChallengeRecords[GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_3 - 2];
    //    this_->mLongestRecordPool = lawnApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::ENDLESS_FLAGS];


    auto *mLeaderboardsListener = new Sexy::ButtonListener();
    this_->mButtonListener = mLeaderboardsListener;
    auto *mVTable = (Sexy::ButtonListenerVTable *)operator new(sizeof(Sexy::ButtonListenerVTable));
    mLeaderboardsListener->vTable = mVTable;
    //    mVTable->ButtonPress = (void *) LeaderboardsWidget_ButtonPress;
    mVTable->ButtonPress2 = (void *)LeaderboardsWidget_ButtonPress;
    mVTable->ButtonDepress = (void *)LeaderboardsWidget_ButtonDepress;
    mVTable->ButtonMouseEnter = (void *)Sexy_ButtonListener_ButtonMouseEnter;
    mVTable->ButtonMouseMove = (void *)Sexy_ButtonListener_ButtonMouseMove;
    mVTable->ButtonMouseLeave = (void *)Sexy_ButtonListener_ButtonMouseLeave;
    mVTable->ButtonDownTick = (void *)Sexy_ButtonListener_ButtonDownTick;
    int holder[1];
    TodStringTranslate(holder, "[CLOSE]");
    Sexy::GameButton *mBackButton = MakeButton(1000, mLeaderboardsListener, this_, holder);
    Sexy_String_Delete(holder);
    Sexy_Widget_Resize(mBackButton, 1040, 590, 120, 50);
    Sexy_Widget_AddWidget(this_, mBackButton);
    this_->mBackButton = mBackButton;
    this_->mFocusedAchievementIndex = 0;
    this_->mHighLightAchievement = false;
}

void DaveHelp_Update(LeaderboardsWidget *leaderboardsWidget) {
    for (Reanimation *&i : leaderboardsWidget->mLeaderboardReanimations->backgroundReanim) {
        Reanimation_Update(i);
    }

    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        if (!leaderboardsWidget->mAchievements[i])
            continue;
        Reanimation_Update(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[i]);
    }
    Sexy_Widget_MarkDirty(leaderboardsWidget);
}

void DaveHelp_Draw(LeaderboardsWidget *leaderboardsWidget, Sexy::Graphics *graphics) {
    for (int i = 4; i >= 0; i--) {
        Reanimation_DrawRenderGroup(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i], graphics, 0);
    }

    leaderboardsWidget->mPlantTrashBin->TrashBin::Draw(graphics);
    leaderboardsWidget->mZombieTrashBin->TrashBin::Draw(graphics);

    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        int num = LeaderboardsWidget_GetAchievementIdByDrawOrder(i);
        if (!leaderboardsWidget->mAchievements[num])
            continue;
        if (leaderboardsWidget->mHighLightAchievement && num == leaderboardsWidget->mFocusedAchievementIndex) {
            auto id = AchievementId::AchievementId(LeaderboardsWidget_GetAchievementIdByReanimationType(ReanimationType(num + ReanimationType::REANIM_ACHIEVEMENT_HOME_SECURITY))
                                                   + AchievementId::ACHIEVEMENT_HOME_SECURITY);
            Sexy::Image *image = GetIconByAchievementId(id);
            Color color;
            GetFlashingColor(&color, leaderboardsWidget->mApp->mAppCounter, 120);
            Sexy_Graphics_SetColorizeImages(graphics, true);
            Sexy_Graphics_SetColor(graphics, &color);
            Reanimation_Draw(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[num], graphics);
            Sexy_Graphics_SetColorizeImages(graphics, false);
            int offsetX = gLeaderboardAchievementsPosition[num][0] + 20;
            int offsetY = gLeaderboardAchievementsPosition[num][1] - 200;
            Sexy_Graphics_DrawImage(graphics, image, offsetX, offsetY);
            int holder[1];
            Sexy_StrFormat(holder, "[%s]", GetNameByAchievementId(id));
            TRect rect = {offsetX - 42, offsetY + 125, 200, 200};
            Color theColor = {0, 255, 0, 255};
            TodDrawStringWrapped(graphics, holder, &rect, *Sexy_FONT_HOUSEOFTERROR28_Addr, &theColor, DrawStringJustification::DS_ALIGN_CENTER, false);
            Sexy_String_Delete(holder);
        } else {
            Reanimation_Draw(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[num], graphics);
        }
    }

    if (LawnApp_HasFinishedAdventure(leaderboardsWidget->mApp)) {
        Reanimation_DrawRenderGroup(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1], graphics, 1);
        int holder[1];
        int holder1[1];
        TodStringTranslate(holder, "[LEADERBOARD_STREAK]");
        TodReplaceNumberString(holder1, holder, "{STREAK}", leaderboardsWidget->mLongestRecordPool);
        TRect theRect = {317, 658, 120, 50};
        Sexy::Font *theFont = *Sexy_FONT_CONTINUUMBOLD14_Addr;
        TodDrawStringWrapped(graphics, holder1, &theRect, theFont, &yellow, DrawStringJustification::DS_ALIGN_CENTER, false);
        Sexy_String_Delete(holder);
        Sexy_String_Delete(holder1);
    }

    //    Sexy_Graphics_DrawImage(graphics, addonImages.survival_button, 270, 579);

    int holder2[1];
    int holder3[1];
    int holder4[1];
    TRect theRect1 = {240, 70, 800, 70};
    TodStringTranslate(holder2, "[PLAYERS_HOUSE]");
    Sexy_StrFormat(holder3, "%s", leaderboardsWidget->mApp->mPlayerInfo->mName);
    TodReplaceString(holder4, holder2, "{PLAYER}", holder3);
    Sexy::Font *theFont1 = *Sexy_FONT_HOUSEOFTERROR28_Addr;
    TodDrawStringWrapped(graphics, holder4, &theRect1, theFont1, &white, DrawStringJustification::DS_ALIGN_CENTER, false);
    Sexy_String_Delete(holder2);
    Sexy_String_Delete(holder3);
    Sexy_String_Delete(holder4);

    //    int plantHeight = plantPileHeight * leaderboardsWidget->mPlantTrashBin->mPileNum;
    //    int zombieHeight = zombiePileHeight * leaderboardsWidget->mZombieTrashBin->mPileNum;
    //    TRect plantTrashBinRect = {leaderboardsWidget->mPlantTrashBin->mX,leaderboardsWidget->mPlantTrashBin->mY - plantHeight,addonImages.plant_can->mWidth,addonImages.plant_can->mHeight +
    //    plantHeight}; TRect zombieTrashBinRect = {leaderboardsWidget->mZombieTrashBin->mX,leaderboardsWidget->mZombieTrashBin->mY -
    //    zombieHeight,addonImages.zombie_can->mWidth,addonImages.zombie_can->mHeight + zombieHeight};
    //
    //    Sexy_Graphics_SetColor(graphics, &yellow);
    //    Sexy_Graphics_DrawRect(graphics, &plantTrashBinRect);
    //
    //    Sexy_Graphics_SetColor(graphics, &green);
    //    Sexy_Graphics_DrawRect(graphics, &zombieTrashBinRect);


    //    Sexy_Graphics_SetColor(graphics, &yellow);
    //    TRect rect = {xx,yy,xw,yh};
    //    Sexy_Graphics_DrawRect(graphics, &rect);
    //
    //    Sexy_Graphics_SetColor(graphics, &green);
    //    TRect rect2 = {xx1,yy1,xw1,yh1};
    //    Sexy_Graphics_DrawRect(graphics, &rect2);
    //    if (LawnApp_EarnedGoldTrophy(leaderboardsWidget->mApp)) {
    //        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SUNFLOWER_TROPHY_Addr, 1110, 290, 1, 0);
    //    } else if (LawnApp_HasFinishedAdventure(leaderboardsWidget->mApp)) {
    //        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SUNFLOWER_TROPHY_Addr, 1110, 290, 0, 0);
    //    }
}

void DaveHelp_Delete2(LeaderboardsWidget *leaderboardsWidget) {
    TrashBin_Delete(leaderboardsWidget->mZombieTrashBin);
    TrashBin_Delete(leaderboardsWidget->mPlantTrashBin);
    for (int i = 0; i < 5; ++i) {
        Reanimation_Delete2(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i]);
        operator delete(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i]);
    }
    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        Reanimation_Delete2(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[i]);
        operator delete(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[i]);
    }
    GameButton_Delete(leaderboardsWidget->mBackButton);
    operator delete(leaderboardsWidget->mButtonListener->vTable);
    operator delete(leaderboardsWidget->mButtonListener);
    operator delete(leaderboardsWidget->mLeaderboardReanimations);
    old_DaveHelp_Delete2(leaderboardsWidget);
}


static TRect gLeaderboardAchievementsRect[12][2] = {
    {{253, 594, 485, 62}, {833, 528, 198, 68}},
    {{209, 488, 91, 106}, {0, 0, 0, 0}},
    {{269, 330, 185, 122}, {298, 453, 91, 91}},
    {{452, 550, 151, 76}, {446, 512, 68, 37}},
    {{373, 504, 83, 34}, {389, 533, 63, 37}},
    {{744, 516, 86, 97}, {0, 0, 0, 0}},
    {{632, 490, 52, 40}, {636, 530, 60, 33}},
    {{561, 340, 77, 196}, {525, 404, 145, 56}},
    {{880, 384, 78, 82}, {891, 467, 26, 68}},
    {{715, 416, 104, 81}, {765, 384, 54, 35}},
    {{817, 332, 113, 171}, {850, 298, 46, 31}},
    {{456, 362, 43, 122}, {461, 484, 71, 30}},
};

void DaveHelp_MouseDown(LeaderboardsWidget *leaderboardsWidget, int x, int y, int theClickCount) {
    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        int num = LeaderboardsWidget_GetAchievementIdByDrawOrder(AchievementId::MAX_ACHIEVEMENTS - 1 - i);
        if (!leaderboardsWidget->mAchievements[num])
            continue;
        if (TRect_Contains(&gLeaderboardAchievementsRect[num][0], x, y) || TRect_Contains(&gLeaderboardAchievementsRect[num][1], x, y)) {
            if (leaderboardsWidget->mFocusedAchievementIndex == num && leaderboardsWidget->mHighLightAchievement) {
                leaderboardsWidget->mHighLightAchievement = false;
            } else {
                leaderboardsWidget->mFocusedAchievementIndex = num;
                leaderboardsWidget->mHighLightAchievement = true;
            }
            return;
        }
    }

    int plantHeight = plantPileHeight * leaderboardsWidget->mPlantTrashBin->mPileNum;
    TRect plantTrashBinRect = {
        leaderboardsWidget->mPlantTrashBin->mX, leaderboardsWidget->mPlantTrashBin->mY - plantHeight, addonImages.plant_can->mWidth, addonImages.plant_can->mHeight + plantHeight};

    if (TRect_Contains(&plantTrashBinRect, x, y)) {
        LawnApp_PlaySample(leaderboardsWidget->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        int holder1[1];
        int holder2[1];
        TodStringTranslate(holder1, "[PLANTS_KILLED]");
        TodReplaceNumberString(holder2, holder1, "{PLANTS}", leaderboardsWidget->mApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::PLANTS_KILLED]);
        LawnApp_LawnMessageBox(leaderboardsWidget->mApp, Dialogs::DIALOG_MESSAGE, (char *)*holder2, "", "[DIALOG_BUTTON_OK]", "", 3);
        Sexy_String_Delete(holder1);
        Sexy_String_Delete(holder2);
        return;
    }

    int zombieHeight = zombiePileHeight * leaderboardsWidget->mZombieTrashBin->mPileNum;
    TRect zombieTrashBinRect = {
        leaderboardsWidget->mZombieTrashBin->mX, leaderboardsWidget->mZombieTrashBin->mY - zombieHeight, addonImages.zombie_can->mWidth, addonImages.zombie_can->mHeight + zombieHeight};

    if (TRect_Contains(&zombieTrashBinRect, x, y)) {
        LawnApp_PlaySample(leaderboardsWidget->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        int holder1[1];
        int holder2[1];
        TodStringTranslate(holder1, "[ZOMBIES_KILLED]");
        TodReplaceNumberString(holder2, holder1, "{ZOMBIES}", leaderboardsWidget->mApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::ZOMBIES_KILLED]);
        LawnApp_LawnMessageBox(leaderboardsWidget->mApp, Dialogs::DIALOG_MESSAGE, (char *)*holder2, "", "[DIALOG_BUTTON_OK]", "", 3);
        Sexy_String_Delete(holder1);
        Sexy_String_Delete(holder2);
        return;
    }

    //    tmp = !tmp;
    //    if (tmp) {
    //        xx = x;
    //        yy = y;
    //        xw = 0;
    //        yh = 0;
    //        LOGD("%d %d", x, y);
    //    }else{
    //        xx1 = x;
    //        yy1 = y;
    //        xw1 = 0;
    //        yh1 = 0;
    //        LOGD("%d %d", x, y);
    //    }

    //    TRect rect = {1066, 574, 72, 72};
    //    if (TRect_Contains(&rect, x, y)) {
    //        leaderboardsWidget->mTouchDownInBackRect = true;
    //        LawnApp_PlaySample(leaderboardsWidget->mApp,*Sexy_SOUND_GRAVEBUTTON_Addr);
    //    }
}

void DaveHelp_MouseDrag(LeaderboardsWidget *leaderboardsWidget, int x, int y) {
    //    if (tmp) {
    //        xw = x - xx;
    //        yh = y - yy;
    //        LOGD("%d: %d, %d, %d, %d",leaderboardsWidget->mFocusedAchievementIndex,xx,yy,xw,yh);
    //    }else{
    //        xw1 = x - xx1;
    //        yh1 = y - yy1;
    //        LOGD("%d: %d, %d, %d, %d",leaderboardsWidget->mFocusedAchievementIndex,xx1,yy1,xw1,yh1);
    //    }
}

void DaveHelp_MouseUp(LeaderboardsWidget *leaderboardsWidget, int x, int y) {}

void DaveHelp_DealClick(LeaderboardsWidget *leaderboardsWidget, int id) {}

void DaveHelp_KeyDown(LeaderboardsWidget *leaderboardsWidget, int keyCode) {
    if (keyCode == Sexy::Back || keyCode == Sexy::Back2) {
        if (leaderboardsWidget->mHighLightAchievement) {
            leaderboardsWidget->mHighLightAchievement = false;
            return;
        }
        LawnApp_KillLeaderboards(leaderboardsWidget->mApp);
        LawnApp_ShowMainMenuScreen(leaderboardsWidget->mApp);
        return;
    }
    if (keyCode == Sexy::Up || keyCode == Sexy::Down || keyCode == Sexy::Left || keyCode == Sexy::Right) {
        bool flag = false;
        for (bool mAchievement : leaderboardsWidget->mAchievements) {
            if (mAchievement) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            return;
        }

        leaderboardsWidget->mHighLightAchievement = true;
        int mFocusedIndex = leaderboardsWidget->mFocusedAchievementIndex;
        if (keyCode == Sexy::Up || keyCode == Sexy::Left) {
            do {
                mFocusedIndex++;
                if (mFocusedIndex > 11) {
                    mFocusedIndex = 0;
                }
            } while (!leaderboardsWidget->mAchievements[mFocusedIndex]);
        } else {
            do {
                mFocusedIndex--;
                if (mFocusedIndex < 0) {
                    mFocusedIndex = 11;
                }
            } while (!leaderboardsWidget->mAchievements[mFocusedIndex]);
        }
        leaderboardsWidget->mFocusedAchievementIndex = mFocusedIndex;
        return;
    }
    if (keyCode == Sexy::Shovel) {
        LawnApp_PlaySample(leaderboardsWidget->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        int holder1[1];
        int holder2[1];
        TodStringTranslate(holder1, "[PLANTS_KILLED]");
        TodReplaceNumberString(holder2, holder1, "{PLANTS}", leaderboardsWidget->mApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::PLANTS_KILLED]);
        LawnApp_LawnMessageBox(leaderboardsWidget->mApp, Dialogs::DIALOG_MESSAGE, (char *)*holder2, "", "[DIALOG_BUTTON_OK]", "", 3);
        Sexy_String_Delete(holder1);
        Sexy_String_Delete(holder2);
        return;
    }
    if (keyCode == Sexy::Hammer) {
        LawnApp_PlaySample(leaderboardsWidget->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        int holder1[1];
        int holder2[1];
        TodStringTranslate(holder1, "[ZOMBIES_KILLED]");
        TodReplaceNumberString(holder2, holder1, "{ZOMBIES}", leaderboardsWidget->mApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::ZOMBIES_KILLED]);
        LawnApp_LawnMessageBox(leaderboardsWidget->mApp, Dialogs::DIALOG_MESSAGE, (char *)*holder2, "", "[DIALOG_BUTTON_OK]", "", 3);
        Sexy_String_Delete(holder1);
        Sexy_String_Delete(holder2);
        return;
    }
}

void ZombatarWidget_SetDefault(ZombatarWidget *zombatarWidget) {
    zombatarWidget->mSelectedTab = 0;
    zombatarWidget->mSelectedSkinColor = 0;
    zombatarWidget->mSelectedHair = 255;
    zombatarWidget->mSelectedHairColor = 255;
    zombatarWidget->mSelectedFHair = 255;
    zombatarWidget->mSelectedFHairColor = 255;
    zombatarWidget->mSelectedFHairPage = 0;
    zombatarWidget->mSelectedTidBit = 255;
    zombatarWidget->mSelectedTidBitColor = 255;
    zombatarWidget->mSelectedEyeWear = 255;
    zombatarWidget->mSelectedEyeWearColor = 255;
    zombatarWidget->mSelectedCloth = 255;
    zombatarWidget->mSelectedAccessory = 255;
    zombatarWidget->mSelectedAccessoryColor = 255;
    zombatarWidget->mSelectedHat = 255;
    zombatarWidget->mSelectedHatColor = 255;
    zombatarWidget->mSelectedBackground = 0;
    zombatarWidget->mSelectedBackgroundColor = 255;
    zombatarWidget->mSelectedBackgroundPage = 0;
    Reanimation_SetZombatarReanim(zombatarWidget->mZombatarReanim);
}

void ZombatarWidget_ButtonPress(ZombatarWidget *zombatarWidget, int id) {}

void ZombatarWidget_ButtonDepress(ZombatarWidget *zombatarWidget, int id) {
    if (id == 1000) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        LawnApp_KillZombatarScreen(lawnApp);
        LawnApp_ShowMainMenuScreen(lawnApp);
        return;
    }

    if (id == 1001) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        if (LawnApp_LawnMessageBox(
                lawnApp, Dialogs::DIALOG_MESSAGE, "[ZOMBATAR_FINISHED_WARNING_HEADER]", "[ZOMBATAR_FINISHED_WARNING_TEXT]", "[ZOMBATAR_FINISHED_BUTTON_TEXT]", "[ZOMBATAR_BACK_BUTTON_TEXT]", 1)
            == 1001)
            return;

        if (addonImages.zombatar_portrait != nullptr) {
            Sexy_MemoryImage_Delete(addonImages.zombatar_portrait);
        }
        Sexy::Image *image = (Sexy::Image *)operator new(sizeof(Sexy::Image));
        Sexy_MemoryImage_MemoryImage(image);
        Sexy_MemoryImage_Create(image, addonZombatarImages.zombatar_background_blank->mWidth, addonZombatarImages.zombatar_background_blank->mHeight);
        Sexy_MemoryImage_SetImageMode(image, true, true);
        image->mVolatile = true;
        Sexy::Graphics graphics;
        Sexy_Graphics_Graphics2(&graphics, image);
        TestMenuWidget_DrawPortrait(gMainMenuZombatarWidget, &graphics, 0, 0);
        int holder[1];
        Sexy_StrFormat(holder, "ZOMBATAR.PNG");
        Sexy_MemoryImage_WriteToPng(image, holder);
        Sexy_String_Delete(holder);
        addonImages.zombatar_portrait = image;
        gMainMenuZombatarWidget->mShowExistingZombatarPortrait = true;
        gMainMenuZombatarWidget->mShowZombieTypeSelection = false;

        PlayerInfo *playerInfo = lawnApp->mPlayerInfo;
        playerInfo->mZombatarHat = gMainMenuZombatarWidget->mSelectedHat;
        playerInfo->mZombatarHatColor = gMainMenuZombatarWidget->mSelectedHatColor;
        playerInfo->mZombatarHair = gMainMenuZombatarWidget->mSelectedHair;
        playerInfo->mZombatarHairColor = gMainMenuZombatarWidget->mSelectedHairColor;
        playerInfo->mZombatarFacialHair = gMainMenuZombatarWidget->mSelectedFHair;
        playerInfo->mZombatarFacialHairColor = gMainMenuZombatarWidget->mSelectedFHairColor;
        playerInfo->mZombatarAccessory = gMainMenuZombatarWidget->mSelectedAccessory;
        playerInfo->mZombatarAccessoryColor = gMainMenuZombatarWidget->mSelectedAccessoryColor;
        playerInfo->mZombatarTidBit = gMainMenuZombatarWidget->mSelectedTidBit;
        playerInfo->mZombatarTidBitColor = gMainMenuZombatarWidget->mSelectedTidBitColor;
        playerInfo->mZombatarEyeWear = gMainMenuZombatarWidget->mSelectedEyeWear;
        playerInfo->mZombatarEyeWearColor = gMainMenuZombatarWidget->mSelectedEyeWearColor;


        playerInfo->mZombatarEnabled = playerInfo->mZombatarHat != 255 || playerInfo->mZombatarHair != 255 || playerInfo->mZombatarFacialHair != 255 || playerInfo->mZombatarAccessory != 255
            || playerInfo->mZombatarTidBit != 255 || playerInfo->mZombatarEyeWear != 255;
        ZombatarWidget_SetDefault(gMainMenuZombatarWidget);
        return;
    }

    if (id == 1002) {
        if (addonImages.zombatar_portrait != nullptr) {
            gMainMenuZombatarWidget->mShowExistingZombatarPortrait = true;
            ZombatarWidget_SetDefault(gMainMenuZombatarWidget);
        }
        return;
    }

    if (id == 1003) {
        gMainMenuZombatarWidget->mShowExistingZombatarPortrait = false;
        return;
    }

    if (id == 1004) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        if (LawnApp_LawnMessageBox(lawnApp, Dialogs::DIALOG_MESSAGE, "[ZOMBATAR_DELETE_HEADER]", "[ZOMBATAR_DELETE_BODY]", "[BUTTON_OK]", "[BUTTON_CANCEL]", 1) == 1001)
            return;
        gMainMenuZombatarWidget->mShowExistingZombatarPortrait = false;
        if (addonImages.zombatar_portrait != nullptr) {
            Sexy_MemoryImage_Delete(addonImages.zombatar_portrait);
            addonImages.zombatar_portrait = nullptr;
            int holder[1];
            Sexy_StrFormat(holder, "ZOMBATAR.PNG");
            Sexy_SexyAppBase_EraseFile(lawnApp, holder);
            Sexy_String_Delete(holder);
        }
        return;
    }
}

Sexy::Image *ZombatarWidget_GetTabButtonImageByIndex(int index) {
    switch (index) {
        case ZombatarWidget::SKIN:
            return addonZombatarImages.zombatar_skin_button;
        case ZombatarWidget::HAIR:
            return addonZombatarImages.zombatar_hair_button;
        case ZombatarWidget::FHAIR:
            return addonZombatarImages.zombatar_fhair_button;
        case ZombatarWidget::TIDBIT:
            return addonZombatarImages.zombatar_tidbits_button;
        case ZombatarWidget::EYEWEAR:
            return addonZombatarImages.zombatar_eyewear_button;
        case ZombatarWidget::CLOTHES:
            return addonZombatarImages.zombatar_clothes_button;
        case ZombatarWidget::ACCESSORY:
            return addonZombatarImages.zombatar_accessory_button;
        case ZombatarWidget::HAT:
            return addonZombatarImages.zombatar_hats_button;
        case ZombatarWidget::BACKGROUND:
            return addonZombatarImages.zombatar_backdrops_button;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetTabButtonDownImageByIndex(int index) {
    switch (index) {
        case ZombatarWidget::SKIN:
            return addonZombatarImages.zombatar_skin_button_highlight;
        case ZombatarWidget::HAIR:
            return addonZombatarImages.zombatar_hair_button_highlight;
        case ZombatarWidget::FHAIR:
            return addonZombatarImages.zombatar_fhair_button_highlight;
        case ZombatarWidget::TIDBIT:
            return addonZombatarImages.zombatar_tidbits_button_highlight;
        case ZombatarWidget::EYEWEAR:
            return addonZombatarImages.zombatar_eyewear_button_highlight;
        case ZombatarWidget::CLOTHES:
            return addonZombatarImages.zombatar_clothes_button_highlight;
        case ZombatarWidget::ACCESSORY:
            return addonZombatarImages.zombatar_accessory_button_highlight;
        case ZombatarWidget::HAT:
            return addonZombatarImages.zombatar_hats_button_highlight;
        case ZombatarWidget::BACKGROUND:
            return addonZombatarImages.zombatar_backdrops_button_highlight;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetHairImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_hair_1;
        case 1:
            return addonZombatarImages.zombatar_hair_2;
        case 2:
            return addonZombatarImages.zombatar_hair_3;
        case 3:
            return addonZombatarImages.zombatar_hair_4;
        case 4:
            return addonZombatarImages.zombatar_hair_5;
        case 5:
            return addonZombatarImages.zombatar_hair_6;
        case 6:
            return addonZombatarImages.zombatar_hair_7;
        case 7:
            return addonZombatarImages.zombatar_hair_8;
        case 8:
            return addonZombatarImages.zombatar_hair_9;
        case 9:
            return addonZombatarImages.zombatar_hair_10;
        case 10:
            return addonZombatarImages.zombatar_hair_11;
        case 11:
            return addonZombatarImages.zombatar_hair_12;
        case 12:
            return addonZombatarImages.zombatar_hair_13;
        case 13:
            return addonZombatarImages.zombatar_hair_14;
        case 14:
            return addonZombatarImages.zombatar_hair_15;
        case 15:
            return addonZombatarImages.zombatar_hair_16;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetHairMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_hair_1_mask;
        case 1:
            return addonZombatarImages.zombatar_hair_2_mask;
        case 10:
            return addonZombatarImages.zombatar_hair_11_mask;
        case 11:
            return addonZombatarImages.zombatar_hair_12_mask;
        case 12:
            return addonZombatarImages.zombatar_hair_13_mask;
        case 13:
            return addonZombatarImages.zombatar_hair_14_mask;
        case 14:
            return addonZombatarImages.zombatar_hair_15_mask;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetFHairImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_facialhair_1;
        case 1:
            return addonZombatarImages.zombatar_facialhair_2;
        case 2:
            return addonZombatarImages.zombatar_facialhair_3;
        case 3:
            return addonZombatarImages.zombatar_facialhair_4;
        case 4:
            return addonZombatarImages.zombatar_facialhair_5;
        case 5:
            return addonZombatarImages.zombatar_facialhair_6;
        case 6:
            return addonZombatarImages.zombatar_facialhair_7;
        case 7:
            return addonZombatarImages.zombatar_facialhair_8;
        case 8:
            return addonZombatarImages.zombatar_facialhair_9;
        case 9:
            return addonZombatarImages.zombatar_facialhair_10;
        case 10:
            return addonZombatarImages.zombatar_facialhair_11;
        case 11:
            return addonZombatarImages.zombatar_facialhair_12;
        case 12:
            return addonZombatarImages.zombatar_facialhair_13;
        case 13:
            return addonZombatarImages.zombatar_facialhair_14;
        case 14:
            return addonZombatarImages.zombatar_facialhair_15;
        case 15:
            return addonZombatarImages.zombatar_facialhair_16;
        case 16:
            return addonZombatarImages.zombatar_facialhair_17;
        case 17:
            return addonZombatarImages.zombatar_facialhair_18;
        case 18:
            return addonZombatarImages.zombatar_facialhair_19;
        case 19:
            return addonZombatarImages.zombatar_facialhair_20;
        case 20:
            return addonZombatarImages.zombatar_facialhair_21;
        case 21:
            return addonZombatarImages.zombatar_facialhair_22;
        case 22:
            return addonZombatarImages.zombatar_facialhair_23;
        case 23:
            return addonZombatarImages.zombatar_facialhair_24;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetFHairMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_facialhair_1_mask;
        case 3:
            return addonZombatarImages.zombatar_facialhair_4_mask;
        case 7:
            return addonZombatarImages.zombatar_facialhair_8_mask;
        case 8:
            return addonZombatarImages.zombatar_facialhair_9_mask;
        case 9:
            return addonZombatarImages.zombatar_facialhair_10_mask;
        case 10:
            return addonZombatarImages.zombatar_facialhair_11_mask;
        case 11:
            return addonZombatarImages.zombatar_facialhair_12_mask;
        case 13:
            return addonZombatarImages.zombatar_facialhair_14_mask;
        case 14:
            return addonZombatarImages.zombatar_facialhair_15_mask;
        case 15:
            return addonZombatarImages.zombatar_facialhair_16_mask;
        case 17:
            return addonZombatarImages.zombatar_facialhair_18_mask;
        case 20:
            return addonZombatarImages.zombatar_facialhair_21_mask;
        case 21:
            return addonZombatarImages.zombatar_facialhair_22_mask;
        case 22:
            return addonZombatarImages.zombatar_facialhair_23_mask;
        case 23:
            return addonZombatarImages.zombatar_facialhair_24_mask;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetTidBitImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_tidbits_1;
        case 1:
            return addonZombatarImages.zombatar_tidbits_2;
        case 2:
            return addonZombatarImages.zombatar_tidbits_3;
        case 3:
            return addonZombatarImages.zombatar_tidbits_4;
        case 4:
            return addonZombatarImages.zombatar_tidbits_5;
        case 5:
            return addonZombatarImages.zombatar_tidbits_6;
        case 6:
            return addonZombatarImages.zombatar_tidbits_7;
        case 7:
            return addonZombatarImages.zombatar_tidbits_8;
        case 8:
            return addonZombatarImages.zombatar_tidbits_9;
        case 9:
            return addonZombatarImages.zombatar_tidbits_10;
        case 10:
            return addonZombatarImages.zombatar_tidbits_11;
        case 11:
            return addonZombatarImages.zombatar_tidbits_12;
        case 12:
            return addonZombatarImages.zombatar_tidbits_13;
        case 13:
            return addonZombatarImages.zombatar_tidbits_14;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetEyeWearImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_eyewear_1;
        case 1:
            return addonZombatarImages.zombatar_eyewear_2;
        case 2:
            return addonZombatarImages.zombatar_eyewear_3;
        case 3:
            return addonZombatarImages.zombatar_eyewear_4;
        case 4:
            return addonZombatarImages.zombatar_eyewear_5;
        case 5:
            return addonZombatarImages.zombatar_eyewear_6;
        case 6:
            return addonZombatarImages.zombatar_eyewear_7;
        case 7:
            return addonZombatarImages.zombatar_eyewear_8;
        case 8:
            return addonZombatarImages.zombatar_eyewear_9;
        case 9:
            return addonZombatarImages.zombatar_eyewear_10;
        case 10:
            return addonZombatarImages.zombatar_eyewear_11;
        case 11:
            return addonZombatarImages.zombatar_eyewear_12;
        case 12:
            return addonZombatarImages.zombatar_eyewear_13;
        case 13:
            return addonZombatarImages.zombatar_eyewear_14;
        case 14:
            return addonZombatarImages.zombatar_eyewear_15;
        case 15:
            return addonZombatarImages.zombatar_eyewear_16;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetEyeWearMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_eyewear_1_mask;
        case 1:
            return addonZombatarImages.zombatar_eyewear_2_mask;
        case 2:
            return addonZombatarImages.zombatar_eyewear_3_mask;
        case 3:
            return addonZombatarImages.zombatar_eyewear_4_mask;
        case 4:
            return addonZombatarImages.zombatar_eyewear_5_mask;
        case 5:
            return addonZombatarImages.zombatar_eyewear_6_mask;
        case 6:
            return addonZombatarImages.zombatar_eyewear_7_mask;
        case 7:
            return addonZombatarImages.zombatar_eyewear_8_mask;
        case 8:
            return addonZombatarImages.zombatar_eyewear_9_mask;
        case 9:
            return addonZombatarImages.zombatar_eyewear_10_mask;
        case 10:
            return addonZombatarImages.zombatar_eyewear_11_mask;
        case 11:
            return addonZombatarImages.zombatar_eyewear_12_mask;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetClothImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_clothes_1;
        case 1:
            return addonZombatarImages.zombatar_clothes_2;
        case 2:
            return addonZombatarImages.zombatar_clothes_3;
        case 3:
            return addonZombatarImages.zombatar_clothes_4;
        case 4:
            return addonZombatarImages.zombatar_clothes_5;
        case 5:
            return addonZombatarImages.zombatar_clothes_6;
        case 6:
            return addonZombatarImages.zombatar_clothes_7;
        case 7:
            return addonZombatarImages.zombatar_clothes_8;
        case 8:
            return addonZombatarImages.zombatar_clothes_9;
        case 9:
            return addonZombatarImages.zombatar_clothes_10;
        case 10:
            return addonZombatarImages.zombatar_clothes_11;
        case 11:
            return addonZombatarImages.zombatar_clothes_12;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetAccessoryImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_accessory_1;
        case 1:
            return addonZombatarImages.zombatar_accessory_2;
        case 2:
            return addonZombatarImages.zombatar_accessory_3;
        case 3:
            return addonZombatarImages.zombatar_accessory_4;
        case 4:
            return addonZombatarImages.zombatar_accessory_5;
        case 5:
            return addonZombatarImages.zombatar_accessory_6;
        case 6:
            return addonZombatarImages.zombatar_accessory_8;
        case 7:
            return addonZombatarImages.zombatar_accessory_9;
        case 8:
            return addonZombatarImages.zombatar_accessory_10;
        case 9:
            return addonZombatarImages.zombatar_accessory_11;
        case 10:
            return addonZombatarImages.zombatar_accessory_12;
        case 11:
            return addonZombatarImages.zombatar_accessory_13;
        case 12:
            return addonZombatarImages.zombatar_accessory_14;
        case 13:
            return addonZombatarImages.zombatar_accessory_15;
        case 14:
            return addonZombatarImages.zombatar_accessory_16;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetHatImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_hats_1;
        case 1:
            return addonZombatarImages.zombatar_hats_2;
        case 2:
            return addonZombatarImages.zombatar_hats_3;
        case 3:
            return addonZombatarImages.zombatar_hats_4;
        case 4:
            return addonZombatarImages.zombatar_hats_5;
        case 5:
            return addonZombatarImages.zombatar_hats_6;
        case 6:
            return addonZombatarImages.zombatar_hats_7;
        case 7:
            return addonZombatarImages.zombatar_hats_8;
        case 8:
            return addonZombatarImages.zombatar_hats_9;
        case 9:
            return addonZombatarImages.zombatar_hats_10;
        case 10:
            return addonZombatarImages.zombatar_hats_11;
        case 11:
            return addonZombatarImages.zombatar_hats_12;
        case 12:
            return addonZombatarImages.zombatar_hats_13;
        case 13:
            return addonZombatarImages.zombatar_hats_14;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetHatMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_hats_1_mask;
        case 2:
            return addonZombatarImages.zombatar_hats_3_mask;
        case 5:
            return addonZombatarImages.zombatar_hats_6_mask;
        case 6:
            return addonZombatarImages.zombatar_hats_7_mask;
        case 7:
            return addonZombatarImages.zombatar_hats_8_mask;
        case 8:
            return addonZombatarImages.zombatar_hats_9_mask;
        case 10:
            return addonZombatarImages.zombatar_hats_11_mask;
        default:
            return nullptr;
    }
}

Sexy::Image *ZombatarWidget_GetBackgroundImageByIndex(int index) {
    switch (index) {
        case 0:
            return addonZombatarImages.zombatar_background_blank;
        case 1:
            return addonZombatarImages.zombatar_background_hood;
        case 2:
            return addonZombatarImages.zombatar_background_hood_blue;
        case 3:
            return addonZombatarImages.zombatar_background_hood_brown;
        case 4:
            return addonZombatarImages.zombatar_background_hood_yellow;
        case 5:
            return addonZombatarImages.zombatar_background_crazydave;
        case 6:
            return addonZombatarImages.zombatar_background_crazydave_night;
        case 7:
            return addonZombatarImages.zombatar_background_menu_dos;
        case 8:
            return addonZombatarImages.zombatar_background_menu;
        case 9:
            return addonZombatarImages.zombatar_background_sky_day;
        case 10:
            return addonZombatarImages.zombatar_background_sky_night;
        case 11:
            return addonZombatarImages.zombatar_background_mausoleum;
        case 12:
            return addonZombatarImages.zombatar_background_day_RV;
        case 13:
            return addonZombatarImages.zombatar_background_night_RV;
        case 14:
            return addonZombatarImages.zombatar_background_pool_sunshade;
        case 15:
            return addonZombatarImages.zombatar_background_fog_sunshade;
        case 16:
            return addonZombatarImages.zombatar_background_roof;
        case 17:
            return addonZombatarImages.zombatar_background_roof_distant;
        case 18:
            return addonZombatarImages.zombatar_background_moon;
        case 19:
            return addonZombatarImages.zombatar_background_moon_distant;
        case 20:
            return addonZombatarImages.zombatar_background_aquarium;
        case 21:
            return addonZombatarImages.zombatar_background_garden_moon;
        case 22:
            return addonZombatarImages.zombatar_background_garden_mushrooms;
        case 23:
            return addonZombatarImages.zombatar_background_garden_hd;
        case 24:
            return addonZombatarImages.zombatar_background_sky_purple;
        case 25:
            return addonZombatarImages.zombatar_background_7;
        case 26:
            return addonZombatarImages.zombatar_background_8;
        case 27:
            return addonZombatarImages.zombatar_background_9;
        case 28:
            return addonZombatarImages.zombatar_background_10;
        case 29:
            return addonZombatarImages.zombatar_background_11;
        case 30:
            return addonZombatarImages.zombatar_background_11_1;
        case 31:
            return addonZombatarImages.zombatar_background_12;
        case 32:
            return addonZombatarImages.zombatar_background_12_1;
        case 33:
            return addonZombatarImages.zombatar_background_13;
        case 34:
            return addonZombatarImages.zombatar_background_13_1;
        case 35:
            return addonZombatarImages.zombatar_background_14;
        case 36:
            return addonZombatarImages.zombatar_background_14_1;
        case 37:
            return addonZombatarImages.zombatar_background_15;
        case 38:
            return addonZombatarImages.zombatar_background_15_1;
        case 39:
            return addonZombatarImages.zombatar_background_16;
        case 40:
            return addonZombatarImages.zombatar_background_16_1;
        case 41:
            return addonZombatarImages.zombatar_background_17;
        case 42:
            return addonZombatarImages.zombatar_background_17_1;
        case 43:
            return addonZombatarImages.zombatar_background_bej3_bridge_shroom_castles;
        case 44:
            return addonZombatarImages.zombatar_background_bej3_canyon_wall;
        case 45:
            return addonZombatarImages.zombatar_background_bej3_crystal_mountain_peak;
        case 46:
            return addonZombatarImages.zombatar_background_bej3_dark_cave_thing;
        case 47:
            return addonZombatarImages.zombatar_background_bej3_desert_pyramids_sunset;
        case 48:
            return addonZombatarImages.zombatar_background_bej3_fairy_cave_village;
        case 49:
            return addonZombatarImages.zombatar_background_bej3_floating_rock_city;
        case 50:
            return addonZombatarImages.zombatar_background_bej3_horse_forset_tree;
        case 51:
            return addonZombatarImages.zombatar_background_bej3_jungle_ruins_path;
        case 52:
            return addonZombatarImages.zombatar_background_bej3_lantern_plants_world;
        case 53:
            return addonZombatarImages.zombatar_background_bej3_lightning;
        case 54:
            return addonZombatarImages.zombatar_background_bej3_lion_tower_cascade;
        case 55:
            return addonZombatarImages.zombatar_background_bej3_pointy_ice_path;
        case 56:
            return addonZombatarImages.zombatar_background_bej3_pointy_ice_path_purple;
        case 57:
            return addonZombatarImages.zombatar_background_bej3_rock_city_lake;
        case 58:
            return addonZombatarImages.zombatar_background_bej3_snowy_cliffs_castle;
        case 59:
            return addonZombatarImages.zombatar_background_bej3_treehouse_waterfall;
        case 60:
            return addonZombatarImages.zombatar_background_bej3_tube_forest_night;
        case 61:
            return addonZombatarImages.zombatar_background_bej3_water_bubble_city;
        case 62:
            return addonZombatarImages.zombatar_background_bej3_water_fall_cliff;
        case 63:
            return addonZombatarImages.zombatar_background_bejblitz_6;
        case 64:
            return addonZombatarImages.zombatar_background_bejblitz_8;
        case 65:
            return addonZombatarImages.zombatar_background_bejblitz_main_menu;
        case 66:
            return addonZombatarImages.zombatar_background_peggle_bunches;
        case 67:
            return addonZombatarImages.zombatar_background_peggle_fever;
        case 68:
            return addonZombatarImages.zombatar_background_peggle_level1;
        case 69:
            return addonZombatarImages.zombatar_background_peggle_level4;
        case 70:
            return addonZombatarImages.zombatar_background_peggle_level5;
        case 71:
            return addonZombatarImages.zombatar_background_peggle_menu;
        case 72:
            return addonZombatarImages.zombatar_background_peggle_nights_bjorn3;
        case 73:
            return addonZombatarImages.zombatar_background_peggle_nights_bjorn4;
        case 74:
            return addonZombatarImages.zombatar_background_peggle_nights_claude5;
        case 75:
            return addonZombatarImages.zombatar_background_peggle_nights_kalah1;
        case 76:
            return addonZombatarImages.zombatar_background_peggle_nights_kalah4;
        case 77:
            return addonZombatarImages.zombatar_background_peggle_nights_master5;
        case 78:
            return addonZombatarImages.zombatar_background_peggle_nights_renfield5;
        case 79:
            return addonZombatarImages.zombatar_background_peggle_nights_tut5;
        case 80:
            return addonZombatarImages.zombatar_background_peggle_nights_warren3;
        case 81:
            return addonZombatarImages.zombatar_background_peggle_paperclips;
        case 82:
            return addonZombatarImages.zombatar_background_peggle_waves;
        default:
            return nullptr;
    }
}

int ZombatarWidget_GetTidBitImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 35;
        case 1:
            return 35;
        case 2:
            return 55;
        case 3:
            return 38;
        case 4:
            return 40;
        case 5:
            return 34;
        case 6:
            return 33;
        case 7:
            return 40;
        case 8:
            return 26;
        case 9:
            return 44;
        case 10:
            return 43;
        case 11:
            return 103;
        case 12:
            return 106;
        case 13:
            return 136;
        default:
            return 0;
    }
}

int ZombatarWidget_GetTidBitImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 76;
        case 1:
            return 76;
        case 2:
            return 133;
        case 3:
            return 74;
        case 4:
            return 70;
        case 5:
            return 79;
        case 6:
            return 86;
        case 7:
            return 66;
        case 8:
            return 91;
        case 9:
            return 86;
        case 10:
            return 84;
        case 11:
            return 110;
        case 12:
            return 60;
        case 13:
            return 137;
        default:
            return 0;
    }
}

int ZombatarWidget_GetEyeWearImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 34;
        case 1:
            return 38;
        case 2:
            return 34;
        case 3:
            return 34;
        case 4:
            return 37;
        case 5:
            return 36;
        case 6:
            return 61;
        case 7:
            return 39;
        case 8:
            return 44;
        case 9:
            return 37;
        case 10:
            return 37;
        case 11:
            return 46;
        case 12:
            return 36;
        case 13:
            return 41;
        case 14:
            return 50;
        case 15:
            return 41;
        default:
            return 0;
    }
}

int ZombatarWidget_GetEyeWearImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 87;
        case 1:
            return 101;
        case 2:
            return 84;
        case 3:
            return 94;
        case 4:
            return 91;
        case 5:
            return 92;
        case 6:
            return 107;
        case 7:
            return 84;
        case 8:
            return 120;
        case 9:
            return 89;
        case 10:
            return 80;
        case 11:
            return 113;
        case 12:
            return 97;
        case 13:
            return 77;
        case 14:
            return 78;
        case 15:
            return 78;
        default:
            return 0;
    }
}

int ZombatarWidget_GetAccessoryImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 124;
        case 1:
            return 130;
        case 2:
            return 103;
        case 3:
            return 157;
        case 4:
            return 158;
        case 5:
            return 158;
        case 6:
            return 126;
        case 7:
            return 144;
        case 8:
            return 74;
        case 9:
            return 52;
        case 10:
            return 163;
        case 11:
            return 94;
        case 12:
            return 83;
        case 13:
            return 160;
        case 14:
            return 16;
        default:
            return 0;
    }
}

int ZombatarWidget_GetAccessoryImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 132;
        case 1:
            return 132;
        case 2:
            return 135;
        case 3:
            return 115;
        case 4:
            return 120;
        case 5:
            return 120;
        case 6:
            return 132;
        case 7:
            return 80;
        case 8:
            return 141;
        case 9:
            return 119;
        case 10:
            return 110;
        case 11:
            return 157;
        case 12:
            return 174;
        case 13:
            return 84;
        case 14:
            return 48;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 42;
        case 1:
            return 61;
        case 2:
            return 54;
        case 3:
            return 46;
        case 4:
            return 85;
        case 5:
            return 59;
        case 6:
            return 16;
        case 7:
            return 54;
        case 8:
            return 51;
        case 9:
            return 54;
        case 10:
            return 52;
        case 11:
            return 35;
        case 12:
            return 52;
        case 13:
            return 23;
        case 14:
            return 76;
        case 15:
            return 76;
        case 16:
            return 52;
        case 17:
            return 71;
        case 18:
            return 55;
        case 19:
            return 137;
        case 20:
            return 141;
        case 21:
            return 18;
        case 22:
            return 71;
        case 23:
            return 46;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 129;
        case 1:
            return 132;
        case 2:
            return 132;
        case 3:
            return 126;
        case 4:
            return 174;
        case 5:
            return 135;
        case 6:
            return 128;
        case 7:
            return 125;
        case 8:
            return 126;
        case 9:
            return 134;
        case 10:
            return 105;
        case 11:
            return 125;
        case 12:
            return 131;
        case 13:
            return 122;
        case 14:
            return 174;
        case 15:
            return 168;
        case 16:
            return 132;
        case 17:
            return 115;
        case 18:
            return 110;
        case 19:
            return 96;
        case 20:
            return 102;
        case 21:
            return 104;
        case 22:
            return 174;
        case 23:
            return 129;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairMaskImageOffsetXByIndex(int index) {
    switch (index) {
        case 3:
            return 3;
        case 7:
            return 1;
        case 10:
            return 1;
        case 11:
            return 9;
        case 13:
            return 2;
        case 14:
            return 2;
        case 17:
            return 2;
        case 21:
            return 4;
        case 22:
            return 1;
        case 23:
            return 4;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairMaskImageOffsetYByIndex(int index) {
    switch (index) {
        case 3:
            return 1;
        case 9:
            return 1;
        case 10:
            return 3;
        case 11:
            return 1;
        case 13:
            return 1;
        case 17:
            return 2;
        case 21:
            return 3;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 28;
        case 1:
            return 29;
        case 2:
            return 28;
        case 3:
            return 35;
        case 4:
            return 44;
        case 5:
            return 47;
        case 6:
            return 61;
        case 7:
            return 33;
        case 8:
            return 154;
        case 9:
            return 27;
        case 10:
            return 30;
        case 11:
            return 60;
        case 12:
            return 39;
        case 13:
            return 9;
        case 14:
            return 55;
        case 15:
            return 31;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 0;
        case 1:
            return 31;
        case 2:
            return 36;
        case 3:
            return 17;
        case 4:
            return 45;
        case 5:
            return 16;
        case 6:
            return 26;
        case 7:
            return 17;
        case 8:
            return 66;
        case 9:
            return 37;
        case 10:
            return 22;
        case 11:
            return -5;
        case 12:
            return 16;
        case 13:
            return -2;
        case 14:
            return 4;
        case 15:
            return 23;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairMaskImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 10;
        case 1:
            return 2;
        case 10:
            return 2;
        case 11:
            return 2;
        case 12:
            return 2;
        case 13:
            return 2;
        case 14:
            return -1;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairMaskImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 2;
        case 1:
            return 3;
        case 10:
            return 2;
        case 11:
            return 2;
        case 12:
            return 1;
        case 13:
            return 5;
        default:
            return 0;
    }
}

int ZombatarWidget_GetClothImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return -addonZombatarImages.zombatar_clothes_1->mWidth + 2;
        case 1:
            return -addonZombatarImages.zombatar_clothes_2->mWidth + 11;
        case 2:
            return -addonZombatarImages.zombatar_clothes_3->mWidth + 1;
        case 3:
            return -addonZombatarImages.zombatar_clothes_4->mWidth + 1;
        case 4:
            return -addonZombatarImages.zombatar_clothes_5->mWidth + 0;
        case 5:
            return -addonZombatarImages.zombatar_clothes_6->mWidth - 20;
        case 6:
            return -addonZombatarImages.zombatar_clothes_7->mWidth + 3;
        case 7:
            return -addonZombatarImages.zombatar_clothes_8->mWidth + 2;
        case 8:
            return -addonZombatarImages.zombatar_clothes_9->mWidth + 10;
        case 9:
            return -addonZombatarImages.zombatar_clothes_10->mWidth + 3;
        case 10:
            return -addonZombatarImages.zombatar_clothes_11->mWidth + 1;
        case 11:
            return -addonZombatarImages.zombatar_clothes_12->mWidth + 3;
        default:
            return 0;
    }
}

int ZombatarWidget_GetClothImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return -addonZombatarImages.zombatar_clothes_1->mHeight + 0;
        case 1:
            return -addonZombatarImages.zombatar_clothes_2->mHeight + 6;
        case 2:
            return -addonZombatarImages.zombatar_clothes_3->mHeight + 0;
        case 3:
            return -addonZombatarImages.zombatar_clothes_4->mHeight + 2;
        case 4:
            return -addonZombatarImages.zombatar_clothes_5->mHeight + 2;
        case 5:
            return -addonZombatarImages.zombatar_clothes_6->mHeight - 24;
        case 6:
            return -addonZombatarImages.zombatar_clothes_7->mHeight + 2;
        case 7:
            return -addonZombatarImages.zombatar_clothes_8->mHeight + 4;
        case 8:
            return -addonZombatarImages.zombatar_clothes_9->mHeight + 3;
        case 9:
            return -addonZombatarImages.zombatar_clothes_10->mHeight + 2;
        case 10:
            return -addonZombatarImages.zombatar_clothes_11->mHeight + 2;
        case 11:
            return -addonZombatarImages.zombatar_clothes_12->mHeight + 3;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 33;
        case 1:
            return 58;
        case 2:
            return 44;
        case 3:
            return 12;
        case 4:
            return 49;
        case 5:
            return 22;
        case 6:
            return 64;
        case 7:
            return 4;
        case 8:
            return 45;
        case 9:
            return 17;
        case 10:
            return 76;
        case 11:
            return 51;
        case 12:
            return 22;
        case 13:
            return 28;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 5;
        case 1:
            return 14;
        case 2:
            return 25;
        case 3:
            return 12;
        case 4:
            return 20;
        case 5:
            return 5;
        case 6:
            return 21;
        case 7:
            return -1;
        case 8:
            return -1;
        case 9:
            return 56;
        case 10:
            return 10;
        case 11:
            return 16;
        case 12:
            return 0;
        case 13:
            return 6;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatMaskImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 1;
        case 2:
            return 18;
        case 5:
            return 5;
        case 7:
            return -3;
        case 8:
            return -1;
        case 10:
            return 1;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatMaskImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 1;
        case 5:
            return -2;
        case 6:
            return 17;
        case 7:
            return -3;
        case 8:
            return -2;
        case 10:
            return 16;
        default:
            return 0;
    }
}

bool ZombatarWidget_AccessoryIsColorized(int tab, int accessory) {
    switch (tab) {
        case ZombatarWidget::HAIR:
            return accessory != 2;
        case ZombatarWidget::FHAIR:
            return true;
        case ZombatarWidget::TIDBIT:
            return accessory == 0 || accessory == 1 || accessory == 2 || accessory == 9 || accessory == 10 || accessory == 11;
        case ZombatarWidget::EYEWEAR:
            return accessory <= 11;
        case ZombatarWidget::CLOTHES:
            return false;
        case ZombatarWidget::ACCESSORY:
            return accessory == 7 || accessory == 9 || accessory == 11 || accessory == 12;
        case ZombatarWidget::HAT:
            return accessory != 12;
        case ZombatarWidget::BACKGROUND:
            return accessory == 0;
        default:
            return false;
    }
}

void ZombatarWidget_ZombatarWidget(ZombatarWidget *zombatarWidget, LawnApp *lawnApp) {
    TestMenuWidget_TestMenuWidget(zombatarWidget);
    LawnApp_LoadZombatarResources(lawnApp);
    LawnApp_Load(lawnApp, "DelayLoad_Almanac");
    zombatarWidget->mApp = lawnApp;
    Sexy::ButtonListener *mZombatarListener = (Sexy::ButtonListener *)operator new(sizeof(Sexy::ButtonListener));
    zombatarWidget->mButtonListener = mZombatarListener;
    Sexy::ButtonListenerVTable *mVTable = (Sexy::ButtonListenerVTable *)operator new(sizeof(Sexy::ButtonListenerVTable));
    mZombatarListener->vTable = mVTable;
    //    mVTable->ButtonPress = (void *) ZombatarWidget_ButtonPress;
    mVTable->ButtonPress2 = (void *)ZombatarWidget_ButtonPress;
    mVTable->ButtonDepress = (void *)ZombatarWidget_ButtonDepress;
    mVTable->ButtonMouseEnter = (void *)Sexy_ButtonListener_ButtonMouseEnter;
    mVTable->ButtonMouseMove = (void *)Sexy_ButtonListener_ButtonMouseMove;
    mVTable->ButtonMouseLeave = (void *)Sexy_ButtonListener_ButtonMouseLeave;
    mVTable->ButtonDownTick = (void *)Sexy_ButtonListener_ButtonDownTick;

    int holder[1];
    Sexy_StrFormat(holder, "[CLOSE]");
    Sexy::GameButton *backButton = MakeButton(1000, mZombatarListener, zombatarWidget, holder);
    Sexy_String_Delete(holder);
    Sexy_Widget_Resize(backButton, 471, 628, addonZombatarImages.zombatar_mainmenuback_highlight->mWidth, addonZombatarImages.zombatar_mainmenuback_highlight->mHeight);
    Sexy_Widget_AddWidget(zombatarWidget, backButton);
    backButton->mDrawStoneButton = false;
    backButton->mButtonImage = *Sexy_IMAGE_BLANK_Addr;
    backButton->mDownImage = addonZombatarImages.zombatar_mainmenuback_highlight;
    backButton->mOverImage = addonZombatarImages.zombatar_mainmenuback_highlight;
    zombatarWidget->mBackButton = backButton;

    int holder1[1];
    Sexy_StrFormat(holder1, "[OK]");
    Sexy::GameButton *finishButton = MakeButton(1001, mZombatarListener, nullptr, holder1);
    Sexy_String_Delete(holder1);
    Sexy_Widget_Resize(finishButton, 160 + 523, 565, addonZombatarImages.zombatar_finished_button->mWidth, addonZombatarImages.zombatar_finished_button->mHeight);
    Sexy_Widget_AddWidget(zombatarWidget, finishButton);
    finishButton->mDrawStoneButton = false;
    finishButton->mButtonImage = addonZombatarImages.zombatar_finished_button;
    finishButton->mDownImage = addonZombatarImages.zombatar_finished_button_highlight;
    finishButton->mOverImage = addonZombatarImages.zombatar_finished_button_highlight;
    zombatarWidget->mFinishButton = finishButton;

    int holder2[1];
    Sexy_StrFormat(holder2, "[OK]");
    Sexy::GameButton *viewPortraitButton = MakeButton(1002, mZombatarListener, nullptr, holder2);
    Sexy_String_Delete(holder2);
    Sexy_Widget_Resize(viewPortraitButton, 160 + 75, 565, addonZombatarImages.zombatar_view_button->mWidth, addonZombatarImages.zombatar_view_button->mHeight);
    Sexy_Widget_AddWidget(zombatarWidget, viewPortraitButton);
    viewPortraitButton->mDrawStoneButton = false;
    viewPortraitButton->mButtonImage = addonZombatarImages.zombatar_view_button;
    viewPortraitButton->mDownImage = addonZombatarImages.zombatar_view_button_highlight;
    viewPortraitButton->mOverImage = addonZombatarImages.zombatar_view_button_highlight;
    zombatarWidget->mViewPortraitButton = viewPortraitButton;

    int holder3[1];
    Sexy_StrFormat(holder3, "[ZOMBATAR_NEW_BUTTON]");
    Sexy::GameButton *newButton = MakeButton(1003, mZombatarListener, nullptr, holder3);
    Sexy_String_Delete(holder3);
    Sexy_Widget_Resize(newButton, 578, 490, 170, 50);
    Sexy_Widget_AddWidget(zombatarWidget, newButton);
    zombatarWidget->mNewButton = newButton;

    int holder4[1];
    Sexy_StrFormat(holder4, "[ZOMBATAR_DELETE_BUTTON]");
    Sexy::GameButton *deleteButton = MakeButton(1004, mZombatarListener, nullptr, holder4);
    Sexy_String_Delete(holder4);
    Sexy_Widget_Resize(deleteButton, 314, 490, 170, 50);
    Sexy_Widget_AddWidget(zombatarWidget, deleteButton);
    zombatarWidget->mDeleteButton = deleteButton;

    Zombie *zombie = (Zombie *)operator new(sizeof(Zombie));
    Zombie_Zombie(zombie);
    zombie->mBoard = nullptr;
    zombie->ZombieInitialize(0, ZombieType::ZOMBIE_FLAG, false, nullptr, -3, true);
    Reanimation *aBodyReanim = zombie->mApp->ReanimationGet(zombie->mBodyReanimID);
    ReanimatorTrackInstance *aHeadTrackInstance = Reanimation_GetTrackInstanceByName(aBodyReanim, "anim_head1");
    aHeadTrackInstance->mImageOverride = *Sexy_IMAGE_BLANK_Addr;

    Reanimation *aZombatarHeadReanim = LawnApp_AddReanimation(lawnApp, 0, 0, 0, ReanimationType::REANIM_ZOMBATAR_HEAD);
    Reanimation_PlayReanim(aZombatarHeadReanim, "anim_head_idle", ReanimLoopType::REANIM_LOOP, 0, 15.0);
    aZombatarHeadReanim->AssignRenderGroupToTrack("anim_hair", -1);
    zombie->mBossFireBallReanimID = LawnApp_ReanimationGetID(zombie->mApp, aZombatarHeadReanim);
    AttachEffect *attachEffect = AttachReanim(&aHeadTrackInstance->mAttachmentID, aZombatarHeadReanim, 0.0f, 0.0f);
    TodScaleRotateTransformMatrix(&attachEffect->mOffset, -20.0, -1.0, 0.2, 1.0, 1.0);
    zombatarWidget->mZombatarReanim = aZombatarHeadReanim;
    zombie->ReanimShowPrefix("anim_hair", -1);
    zombie->ReanimShowPrefix("anim_head2", -1);
    zombie->Update();
    zombatarWidget->mPreviewZombie = zombie;

    zombatarWidget->mShowExistingZombatarPortrait = addonImages.zombatar_portrait != nullptr;
    gMainMenuZombatarWidget->mShowZombieTypeSelection = false;

    ZombatarWidget_SetDefault(zombatarWidget);
}

void TestMenuWidget_Update(ZombatarWidget *zombatarWidget) {
    zombatarWidget->mPreviewZombie->Update();
    zombatarWidget->mFinishButton->mDisabled = zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mFinishButton->mBtnNoDraw = zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mViewPortraitButton->mDisabled = zombatarWidget->mShowExistingZombatarPortrait || addonImages.zombatar_portrait == nullptr;
    zombatarWidget->mViewPortraitButton->mBtnNoDraw = zombatarWidget->mShowExistingZombatarPortrait || addonImages.zombatar_portrait == nullptr;
    zombatarWidget->mNewButton->mDisabled = !zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mNewButton->mBtnNoDraw = !zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mDeleteButton->mDisabled = !zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mDeleteButton->mBtnNoDraw = !zombatarWidget->mShowExistingZombatarPortrait;
    Sexy_Widget_MarkDirty(zombatarWidget);
}

void TestMenuWidget_DrawZombieSelection(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    // TODO: 做僵尸选择功能
    ZombieType types[] = {ZombieType::ZOMBIE_NORMAL, ZombieType::ZOMBIE_FLAG, ZombieType::ZOMBIE_TRAFFIC_CONE, ZombieType::ZOMBIE_DOOR, ZombieType::ZOMBIE_TRASH_BIN, ZombieType::ZOMBIE_PAIL, ZombieType::ZOMBIE_DUCKY_TUBE};
}

void TestMenuWidget_DrawSkin(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 285 + (i % 9) * 30;
        int theY = 432 + i / 9 * 30;
        Color color = gZombatarSkinColor[i];
        if (zombatarWidget->mSelectedSkinColor != i) {
            color.mAlpha = 64;
        }
        Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
    }

    int holder[1];
    TodStringTranslate(holder, "[ZOMBATAR_START_TEXT]");
    TRect rect = {160 + 295, 211, 250, 100};
    Sexy::Font *font = *Sexy_FONT_DWARVENTODCRAFT18_Addr;
    TodDrawStringWrapped(graphics, holder, &rect, font, &yellow, DrawStringJustification::DS_ALIGN_CENTER, false);
    Sexy_String_Delete(holder);
}

void TestMenuWidget_DrawHair(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255, 255, 255, 64};
    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image *image = ZombatarWidget_GetHairImageByIndex(i);
        Sexy::Image *image1 = ZombatarWidget_GetHairMaskImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth, mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3)
            ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedHair == i) {
            Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
            if (image1 != nullptr) {
                int widthOffset2 = ZombatarWidget_GetHairMaskImageOffsetXByIndex(i);
                int heightOffset2 = ZombatarWidget_GetHairMaskImageOffsetYByIndex(i);
                TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
            }
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            if (image1 != nullptr) {
                int widthOffset2 = ZombatarWidget_GetHairMaskImageOffsetXByIndex(i);
                int heightOffset2 = ZombatarWidget_GetHairMaskImageOffsetYByIndex(i);
                Sexy_Graphics_DrawImageColorizedScaled(
                    graphics, image1, &theAlphaColor, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
            }
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedHair == 255) {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedHair)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor[i];
            if (zombatarWidget->mSelectedHairColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? addonZombatarImages.zombatar_colorpicker_none : addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawFHair(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    if (zombatarWidget->mSelectedFHairPage == 0) {
        Color theAlphaColor = {255, 255, 255, 64};
        for (int i = 0; i < 17; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            Sexy::Image *image = ZombatarWidget_GetFHairImageByIndex(i);
            Sexy::Image *image1 = ZombatarWidget_GetFHairMaskImageByIndex(i);
            int mWidth = image->mWidth;
            int mHeight = image->mHeight;
            int max = std::max(mWidth, mHeight);
            float ratio = 58.0 / max;
            if (ratio > 1.3)
                ratio = 1.3;
            float widthOffset = (58 - ratio * mWidth) / 2;
            float heightOffset = (58 - ratio * mHeight) / 2;

            if (zombatarWidget->mSelectedFHair == i) {
                Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
                if (image1 != nullptr) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i);
                    TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
                if (image1 != nullptr) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i);
                    Sexy_Graphics_DrawImageColorizedScaled(
                        graphics, image1, &theAlphaColor, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
        }
        int theX = 160 + 198 + (17 % 6) * 73;
        int theY = 162 + 17 / 6 * 79;
        Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);
        Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_prev_button, &theAlphaColor, 160 + 209, 436);
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_next_button, 160 + 588, 436);
    } else if (zombatarWidget->mSelectedFHairPage == 1) {
        Color theAlphaColor = {255, 255, 255, 64};
        for (int i = 0; i < 7; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            Sexy::Image *image = ZombatarWidget_GetFHairImageByIndex(i + 17);
            Sexy::Image *image1 = ZombatarWidget_GetFHairMaskImageByIndex(i + 17);
            int mWidth = image->mWidth;
            int mHeight = image->mHeight;
            int max = std::max(mWidth, mHeight);
            float ratio = 58.0 / max;
            if (ratio > 1.3)
                ratio = 1.3;
            float widthOffset = (58 - ratio * mWidth) / 2;
            float heightOffset = (58 - ratio * mHeight) / 2;

            if (zombatarWidget->mSelectedFHair == i + 17) {
                Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
                if (image1 != nullptr) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i + 17);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i + 17);
                    TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
                if (image1 != nullptr) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i + 17);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i + 17);
                    Sexy_Graphics_DrawImageColorizedScaled(
                        graphics, image1, &theAlphaColor, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
        }
        int theX = 160 + 198 + (7 % 6) * 73;
        int theY = 162 + 7 / 6 * 79;
        Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_prev_button, 160 + 209, 436);
        Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_next_button, &theAlphaColor, 160 + 588, 436);
    }

    if (zombatarWidget->mSelectedFHair == 255) {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedFHair)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor[i];
            if (zombatarWidget->mSelectedFHairColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? addonZombatarImages.zombatar_colorpicker_none : addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }

    int holder[1];
    Sexy_StrFormat(holder, "PAGE %d/%d", zombatarWidget->mSelectedFHairPage + 1, 2);
    TodDrawString(graphics, holder, 160 + 410, 525, *Sexy_FONT_BRIANNETOD16_Addr, black, DrawStringJustification::DS_ALIGN_CENTER);
    Sexy_String_Delete(holder);
}

void TestMenuWidget_DrawTidBit(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255, 255, 255, 64};
    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image *image = ZombatarWidget_GetTidBitImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth, mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3)
            ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedTidBit == i) {
            Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            if (i == 0) {
                TodDrawImageScaledF(graphics, ZombatarWidget_GetTidBitImageByIndex(2), theX + 23, theY + 44, ratio, ratio);
            }
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            if (i == 0) {
                Sexy_Graphics_DrawImageColorizedScaled(graphics, ZombatarWidget_GetTidBitImageByIndex(2), &theAlphaColor, theX + 23, theY + 44, ratio, ratio);
            }
        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedTidBit == 255) {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedTidBit)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedTidBitColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? addonZombatarImages.zombatar_colorpicker_none : addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawEyeWear(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255, 255, 255, 64};
    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image *image = ZombatarWidget_GetEyeWearImageByIndex(i);
        Sexy::Image *image1 = ZombatarWidget_GetEyeWearMaskImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth, mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3)
            ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedEyeWear == i) {
            Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
            if (image1 != nullptr) {
                TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            if (image1 != nullptr) {
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image1, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedEyeWear == 255) {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedEyeWear)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedEyeWearColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? addonZombatarImages.zombatar_colorpicker_none : addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawCloth(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255, 255, 255, 64};
    Color theAlphaColor2 = {255, 255, 255, 128};
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image *image = addonZombatarImages.zombatar_zombie_blank_part;
        Sexy::Image *image1 = ZombatarWidget_GetClothImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth, mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3)
            ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;
        int offsetX = addonZombatarImages.zombatar_zombie_blank_part->mWidth + ZombatarWidget_GetClothImageOffsetXByIndex(i);
        int offsetY = addonZombatarImages.zombatar_zombie_blank_part->mHeight + ZombatarWidget_GetClothImageOffsetYByIndex(i);
        if (zombatarWidget->mSelectedCloth == i) {
            Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics,
                                                   addonZombatarImages.zombatar_zombie_blank_skin_part,
                                                   &gZombatarSkinColor[zombatarWidget->mSelectedSkinColor],
                                                   theX + 12 + widthOffset,
                                                   theY + 12 + heightOffset,
                                                   ratio,
                                                   ratio);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            TodDrawImageScaledF(graphics, image1, theX + 12 + ratio * offsetX, theY + 12 + ratio * offsetY, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics,
                                                   addonZombatarImages.zombatar_zombie_blank_skin_part,
                                                   &gZombatarSkinColor[zombatarWidget->mSelectedSkinColor],
                                                   theX + 12 + widthOffset,
                                                   theY + 12 + heightOffset,
                                                   ratio,
                                                   ratio);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image1, &theAlphaColor2, theX + 12 + ratio * offsetX, theY + 12 + ratio * offsetY, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (12 % 6) * 73;
    int theY = 162 + 12 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedCloth == 255) {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawAccessory(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255, 255, 255, 64};
    for (int i = 0; i < 15; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image *image = ZombatarWidget_GetAccessoryImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth, mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3)
            ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedAccessory == i) {
            Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (15 % 6) * 73;
    int theY = 162 + 15 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedAccessory == 255) {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedAccessory)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedAccessoryColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? addonZombatarImages.zombatar_colorpicker_none : addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawHat(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255, 255, 255, 64};
    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image *image = ZombatarWidget_GetHatImageByIndex(i);
        Sexy::Image *image1 = ZombatarWidget_GetHatMaskImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth, mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3)
            ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;
        float widthOffset2 = ZombatarWidget_GetHatMaskImageOffsetXByIndex(i) * ratio;
        float heightOffset2 = ZombatarWidget_GetHatMaskImageOffsetYByIndex(i) * ratio;

        if (zombatarWidget->mSelectedHat == i) {
            Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
            if (image1 != nullptr) {
                TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2, theY + 12 + heightOffset + heightOffset2, ratio, ratio);
            }
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            if (image1 != nullptr) {
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image1, &theAlphaColor, theX + 12 + widthOffset + widthOffset2, theY + 12 + heightOffset + heightOffset2, ratio, ratio);
            }
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedHat == 255) {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedHat)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedHatColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? addonZombatarImages.zombatar_colorpicker_none : addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawBackground(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255, 255, 255, 64};
    if (zombatarWidget->mSelectedBackgroundPage == 0) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            if (zombatarWidget->mSelectedBackground == i) {
                Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
                TodDrawImageScaledF(graphics, ZombatarWidget_GetBackgroundImageByIndex(i), theX + 12, theY + 12, 58.0 / 216.0, 58.0 / 216.0);
            }
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, ZombatarWidget_GetBackgroundImageByIndex(i), &theAlphaColor, theX + 12, theY + 12, 58.0 / 216.0, 58.0 / 216.0);
        }
        Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_prev_button, &theAlphaColor, 160 + 209, 436);
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_next_button, 160 + 588, 436);
    } else if (zombatarWidget->mSelectedBackgroundPage == 4) {
        for (int i = 0; i < 11; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            if (zombatarWidget->mSelectedBackground == i + 18 * zombatarWidget->mSelectedBackgroundPage) {
                Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
                TodDrawImageScaledF(graphics, ZombatarWidget_GetBackgroundImageByIndex(i + 18 * zombatarWidget->mSelectedBackgroundPage), theX + 12, theY + 12, 58.0 / 216.0, 58.0 / 216.0);
            }
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(
                graphics, ZombatarWidget_GetBackgroundImageByIndex(i + 18 * zombatarWidget->mSelectedBackgroundPage), &theAlphaColor, theX + 12, theY + 12, 58.0 / 216.0, 58.0 / 216.0);
        }
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_prev_button, 160 + 209, 436);
        Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_next_button, &theAlphaColor, 160 + 588, 436);
    } else {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            if (zombatarWidget->mSelectedBackground == i + zombatarWidget->mSelectedBackgroundPage * 18) {
                Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_accessory_bg_highlight, theX, theY);
                TodDrawImageScaledF(graphics, ZombatarWidget_GetBackgroundImageByIndex(i + zombatarWidget->mSelectedBackgroundPage * 18), theX + 12, theY + 12, 58.0 / 216.0, 58.0 / 216.0);
            }
            Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_accessory_bg, &theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(
                graphics, ZombatarWidget_GetBackgroundImageByIndex(i + zombatarWidget->mSelectedBackgroundPage * 18), &theAlphaColor, theX + 12, theY + 12, 58.0 / 216.0, 58.0 / 216.0);
        }
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_prev_button, 160 + 209, 436);
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_next_button, 160 + 588, 436);
    }


    if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedBackground)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedBackgroundColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? addonZombatarImages.zombatar_colorpicker_none : addonZombatarImages.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288, 445, 250, 100};
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics, holder, &rect, font, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        Sexy_String_Delete(holder);
    }

    int holder[1];
    Sexy_StrFormat(holder, "PAGE %d/%d", zombatarWidget->mSelectedBackgroundPage + 1, 5);
    TodDrawString(graphics, holder, 160 + 410, 525, *Sexy_FONT_BRIANNETOD16_Addr, black, DrawStringJustification::DS_ALIGN_CENTER);
    Sexy_String_Delete(holder);
}

void TestMenuWidget_DrawPortrait(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics, int x, int y) {
    Sexy::Image *backgroundImage = ZombatarWidget_GetBackgroundImageByIndex(zombatarWidget->mSelectedBackground);
    if (ZombatarWidget_AccessoryIsColorized(ZombatarWidget::BACKGROUND, zombatarWidget->mSelectedBackground) && zombatarWidget->mSelectedBackgroundColor != 255) {
        Sexy_Graphics_DrawImageColorized(graphics, backgroundImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedBackgroundColor], x, y);
    } else {
        Sexy_Graphics_DrawImage(graphics, backgroundImage, x, y);
    }
    Sexy_Graphics_DrawImageColorized(graphics, addonZombatarImages.zombatar_zombie_blank_skin, &gZombatarSkinColor[zombatarWidget->mSelectedSkinColor], x + 46, y + 48);
    Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_zombie_blank, x + 46, y + 48);

    Sexy::Image *clothImage = ZombatarWidget_GetClothImageByIndex(zombatarWidget->mSelectedCloth);
    if (clothImage != nullptr) {
        int offsetX = addonZombatarImages.zombatar_background_blank->mWidth + ZombatarWidget_GetClothImageOffsetXByIndex(zombatarWidget->mSelectedCloth);
        int offsetY = addonZombatarImages.zombatar_background_blank->mHeight + ZombatarWidget_GetClothImageOffsetYByIndex(zombatarWidget->mSelectedCloth);
        Sexy_Graphics_DrawImage(graphics, clothImage, x + offsetX, y + offsetY);
    }

    Sexy::Image *tidBitImage = ZombatarWidget_GetTidBitImageByIndex(zombatarWidget->mSelectedTidBit);
    if (tidBitImage != nullptr) {
        int offsetX = ZombatarWidget_GetTidBitImageOffsetXByIndex(zombatarWidget->mSelectedTidBit);
        int offsetY = ZombatarWidget_GetTidBitImageOffsetYByIndex(zombatarWidget->mSelectedTidBit);
        if (zombatarWidget->mSelectedTidBitColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::TIDBIT, zombatarWidget->mSelectedTidBit) && zombatarWidget->mSelectedTidBit != 0) {
            Sexy_Graphics_DrawImageColorized(graphics, tidBitImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedTidBitColor], x + offsetX, y + offsetY);
        } else {
            Sexy_Graphics_DrawImage(graphics, tidBitImage, x + offsetX, y + offsetY);
        }
    }
    if (zombatarWidget->mSelectedTidBit == 0) {
        Sexy::Image *tidBitImage = ZombatarWidget_GetTidBitImageByIndex(2);
        if (tidBitImage != nullptr) {
            int offsetX = ZombatarWidget_GetTidBitImageOffsetXByIndex(2);
            int offsetY = ZombatarWidget_GetTidBitImageOffsetYByIndex(2);
            if (zombatarWidget->mSelectedTidBitColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::TIDBIT, 2)) {
                Sexy_Graphics_DrawImageColorized(graphics, tidBitImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedTidBitColor], x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, tidBitImage, x + offsetX, y + offsetY);
            }
        }
    }

    Sexy::Image *eyeWearImage = ZombatarWidget_GetEyeWearImageByIndex(zombatarWidget->mSelectedEyeWear);
    if (eyeWearImage != nullptr) {
        int offsetX = ZombatarWidget_GetEyeWearImageOffsetXByIndex(zombatarWidget->mSelectedEyeWear);
        int offsetY = ZombatarWidget_GetEyeWearImageOffsetYByIndex(zombatarWidget->mSelectedEyeWear);
        Sexy::Image *eyeWearMaskImage = ZombatarWidget_GetEyeWearMaskImageByIndex(zombatarWidget->mSelectedEyeWear);
        if (zombatarWidget->mSelectedEyeWearColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::EYEWEAR, zombatarWidget->mSelectedEyeWear)) {
            if (eyeWearMaskImage != nullptr) {
                Sexy_Graphics_DrawImageColorized(graphics, eyeWearMaskImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedEyeWearColor], x + offsetX, y + offsetY);
                Sexy_Graphics_DrawImage(graphics, eyeWearImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, eyeWearImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedEyeWearColor], x + offsetX, y + offsetY);
            }
        } else {
            if (eyeWearMaskImage != nullptr) {
                Sexy_Graphics_DrawImage(graphics, eyeWearMaskImage, x + offsetX, y + offsetY);
                Sexy_Graphics_DrawImage(graphics, eyeWearImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, eyeWearImage, x + offsetX, y + offsetY);
            }
        }
    }

    Sexy::Image *accessoryImage = ZombatarWidget_GetAccessoryImageByIndex(zombatarWidget->mSelectedAccessory);
    if (accessoryImage != nullptr) {
        int offsetX = ZombatarWidget_GetAccessoryImageOffsetXByIndex(zombatarWidget->mSelectedAccessory);
        int offsetY = ZombatarWidget_GetAccessoryImageOffsetYByIndex(zombatarWidget->mSelectedAccessory);
        if (zombatarWidget->mSelectedAccessoryColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::ACCESSORY, zombatarWidget->mSelectedAccessory)) {
            Sexy_Graphics_DrawImageColorized(graphics, accessoryImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedAccessoryColor], x + offsetX, y + offsetY);
        } else {
            Sexy_Graphics_DrawImage(graphics, accessoryImage, x + offsetX, y + offsetY);
        }
    }

    Sexy::Image *fHairImage = ZombatarWidget_GetFHairImageByIndex(zombatarWidget->mSelectedFHair);
    if (fHairImage != nullptr) {
        int offsetX = ZombatarWidget_GetFHairImageOffsetXByIndex(zombatarWidget->mSelectedFHair);
        int offsetY = ZombatarWidget_GetFHairImageOffsetYByIndex(zombatarWidget->mSelectedFHair);
        int offsetX2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(zombatarWidget->mSelectedFHair);
        int offsetY2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(zombatarWidget->mSelectedFHair);
        Sexy::Image *fHairMaskImage = ZombatarWidget_GetFHairMaskImageByIndex(zombatarWidget->mSelectedFHair);
        if (zombatarWidget->mSelectedFHairColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::FHAIR, zombatarWidget->mSelectedFHair)) {
            if (fHairMaskImage != nullptr) {
                Sexy_Graphics_DrawImageColorized(graphics, fHairMaskImage, &gZombatarAccessoryColor[zombatarWidget->mSelectedFHairColor], x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics, fHairImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, fHairImage, &gZombatarAccessoryColor[zombatarWidget->mSelectedFHairColor], x + offsetX, y + offsetY);
            }
        } else {
            if (fHairMaskImage != nullptr) {
                Sexy_Graphics_DrawImage(graphics, fHairMaskImage, x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics, fHairImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, fHairImage, x + offsetX, y + offsetY);
            }
        }
    }


    Sexy::Image *hairImage = ZombatarWidget_GetHairImageByIndex(zombatarWidget->mSelectedHair);
    if (hairImage != nullptr) {
        int offsetX = ZombatarWidget_GetHairImageOffsetXByIndex(zombatarWidget->mSelectedHair);
        int offsetY = ZombatarWidget_GetHairImageOffsetYByIndex(zombatarWidget->mSelectedHair);
        int offsetX2 = ZombatarWidget_GetHairMaskImageOffsetXByIndex(zombatarWidget->mSelectedHair);
        int offsetY2 = ZombatarWidget_GetHairMaskImageOffsetYByIndex(zombatarWidget->mSelectedHair);
        Sexy::Image *hairMaskImage = ZombatarWidget_GetHairMaskImageByIndex(zombatarWidget->mSelectedHair);
        if (zombatarWidget->mSelectedHairColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::HAIR, zombatarWidget->mSelectedHair)) {
            if (hairMaskImage != nullptr) {
                Sexy_Graphics_DrawImageColorized(graphics, hairMaskImage, &gZombatarAccessoryColor[zombatarWidget->mSelectedHairColor], x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics, hairImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, hairImage, &gZombatarAccessoryColor[zombatarWidget->mSelectedHairColor], x + offsetX, y + offsetY);
            }
        } else {
            if (hairMaskImage != nullptr) {
                Sexy_Graphics_DrawImage(graphics, hairMaskImage, x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics, hairImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, hairImage, x + offsetX, y + offsetY);
            }
        }
    }

    Sexy::Image *hatImage = ZombatarWidget_GetHatImageByIndex(zombatarWidget->mSelectedHat);
    if (hatImage != nullptr) {
        int offsetX = ZombatarWidget_GetHatImageOffsetXByIndex(zombatarWidget->mSelectedHat);
        int offsetY = ZombatarWidget_GetHatImageOffsetYByIndex(zombatarWidget->mSelectedHat);
        int offsetX2 = ZombatarWidget_GetHatMaskImageOffsetXByIndex(zombatarWidget->mSelectedHat);
        int offsetY2 = ZombatarWidget_GetHatMaskImageOffsetYByIndex(zombatarWidget->mSelectedHat);
        Sexy::Image *hatMaskImage = ZombatarWidget_GetHatMaskImageByIndex(zombatarWidget->mSelectedHat);
        if (zombatarWidget->mSelectedHatColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::HAT, zombatarWidget->mSelectedHat)) {
            if (hatMaskImage != nullptr) {
                Sexy_Graphics_DrawImageColorized(graphics, hatMaskImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedHatColor], x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics, hatImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, hatImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedHatColor], x + offsetX, y + offsetY);
            }
        } else {
            if (hatMaskImage != nullptr) {
                Sexy_Graphics_DrawImage(graphics, hatMaskImage, x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics, hatImage, x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, hatImage, x + offsetX, y + offsetY);
            }
        }
    }
}

void TestMenuWidget_DrawPreView(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDDAY_Addr, 160 + 729, 376);
    float tmpX = graphics->mTransX;
    float tmpY = graphics->mTransY;
    graphics->mTransX += 160 + 778;
    graphics->mTransY += 434;
    zombatarWidget->mPreviewZombie->Draw(graphics);
    graphics->mTransX = tmpX;
    graphics->mTransY = tmpY;
}

void TestMenuWidget_Draw(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {

    Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_main_bg, 0, 0);
    Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_widget_bg, 160 + 26, 27);

    if (zombatarWidget->mShowExistingZombatarPortrait && addonImages.zombatar_portrait != nullptr) {
        Sexy_Graphics_DrawImage(graphics, addonImages.zombatar_portrait, 160 + 260, 210);
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_VIEW_PORTRAIT]");
        TRect rect = {160 + 178, 450, 400, 100};
        TodDrawStringWrapped(graphics, holder, &rect, *Sexy_FONT_BRIANNETOD16_Addr, &white, DrawStringJustification::DS_ALIGN_CENTER, false);
        Sexy_String_Delete(holder);
    } else if (zombatarWidget->mShowZombieTypeSelection) {
        TestMenuWidget_DrawZombieSelection(zombatarWidget, graphics);
    } else {
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_widget_inner_bg, 160 + 179, 148);
        for (int i = 0; i < ZombatarWidget::MaxTabNum; ++i) {
            Sexy_Graphics_DrawImage(graphics, i == zombatarWidget->mSelectedTab ? ZombatarWidget_GetTabButtonDownImageByIndex(i) : ZombatarWidget_GetTabButtonImageByIndex(i), 160 + 67, 152 + i * 43);
        }
        Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_colors_bg, 160 + 260, 394);
        switch (zombatarWidget->mSelectedTab) {
            case ZombatarWidget::SKIN:
                TestMenuWidget_DrawSkin(zombatarWidget, graphics);
                break;
            case ZombatarWidget::HAIR:
                TestMenuWidget_DrawHair(zombatarWidget, graphics);
                break;
            case ZombatarWidget::FHAIR:
                TestMenuWidget_DrawFHair(zombatarWidget, graphics);
                break;
            case ZombatarWidget::TIDBIT:
                TestMenuWidget_DrawTidBit(zombatarWidget, graphics);
                break;
            case ZombatarWidget::EYEWEAR:
                TestMenuWidget_DrawEyeWear(zombatarWidget, graphics);
                break;
            case ZombatarWidget::CLOTHES:
                TestMenuWidget_DrawCloth(zombatarWidget, graphics);
                break;
            case ZombatarWidget::ACCESSORY:
                TestMenuWidget_DrawAccessory(zombatarWidget, graphics);
                break;
            case ZombatarWidget::HAT:
                TestMenuWidget_DrawHat(zombatarWidget, graphics);
                break;
            case ZombatarWidget::BACKGROUND:
                TestMenuWidget_DrawBackground(zombatarWidget, graphics);
                break;
        }
    }

    TestMenuWidget_DrawPortrait(zombatarWidget, graphics, 160 + 708, 140);
    TestMenuWidget_DrawPreView(zombatarWidget, graphics);

    Sexy_Graphics_DrawImage(graphics, addonZombatarImages.zombatar_display_window, 160 + 0, 0);
}


void TestMenuWidget_RemovedFromManager(ZombatarWidget *zombatarWidget, int *manager) {
    old_TestMenuWidget_RemovedFromManager(zombatarWidget, manager);
    Sexy_Widget_RemoveWidget(zombatarWidget, zombatarWidget->mBackButton);
    Sexy_Widget_RemoveWidget(zombatarWidget, zombatarWidget->mFinishButton);
    Sexy_Widget_RemoveWidget(zombatarWidget, zombatarWidget->mViewPortraitButton);
    Sexy_Widget_RemoveWidget(zombatarWidget, zombatarWidget->mNewButton);
    Sexy_Widget_RemoveWidget(zombatarWidget, zombatarWidget->mDeleteButton);
}

void TestMenuWidget_Delete2(ZombatarWidget *zombatarWidget) {
    // TODO:解决五个按钮的内存泄露问题。GameButton_Delete会闪退，暂不清楚原因。
    zombatarWidget->mPreviewZombie->DieNoLoot();
    (*((void (**)(Zombie *))zombatarWidget->mPreviewZombie->vTable + 1))(zombatarWidget->mPreviewZombie); // Delete();

    (*((void (**)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 7))(zombatarWidget, zombatarWidget->mBackButton);
    zombatarWidget->mBackButton->mDrawStoneButton = true;
    zombatarWidget->mBackButton->mButtonImage = nullptr;
    zombatarWidget->mBackButton->mDownImage = nullptr;
    zombatarWidget->mBackButton->mOverImage = nullptr;
    // GameButton_Delete(zombatarWidget->mBackButton);

    (*((void (**)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 7))(zombatarWidget, zombatarWidget->mFinishButton);
    zombatarWidget->mFinishButton->mDrawStoneButton = true;
    zombatarWidget->mFinishButton->mButtonImage = nullptr;
    zombatarWidget->mFinishButton->mDownImage = nullptr;
    zombatarWidget->mFinishButton->mOverImage = nullptr;
    // GameButton_Delete(zombatarWidget->mFinishButton);


    (*((void (**)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 7))(zombatarWidget, zombatarWidget->mViewPortraitButton);
    zombatarWidget->mViewPortraitButton->mDrawStoneButton = true;
    zombatarWidget->mViewPortraitButton->mButtonImage = nullptr;
    zombatarWidget->mViewPortraitButton->mDownImage = nullptr;
    zombatarWidget->mViewPortraitButton->mOverImage = nullptr;
    // GameButton_Delete(zombatarWidget->mViewPortraitButton);

    // GameButton_Delete(zombatarWidget->mNewButton);
    // GameButton_Delete(zombatarWidget->mDeleteButton);
    operator delete(zombatarWidget->mButtonListener->vTable);
    operator delete(zombatarWidget->mButtonListener);
    old_TestMenuWidget_Delete2(zombatarWidget);
}

void TestMenuWidget_Delete(ZombatarWidget *zombatarWidget) {
    TestMenuWidget_Delete2(zombatarWidget);
    delete zombatarWidget;
}

void TestMenuWidget_MouseDownSkin(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 285 + (i % 9) * 30;
        int theY = 432 + i / 9 * 30;
        TRect rect = {theX, theY, 30, 30};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedSkinColor = i;
            return;
        }
    }
}

void TestMenuWidget_MouseDownHair(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedHair = i;
            Reanimation_SetZombatarHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHair, zombatarWidget->mSelectedHairColor);
            return;
        }
    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedHair = 255;
        Reanimation_SetZombatarHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHair, zombatarWidget->mSelectedHairColor);
        return;
    }
    if (zombatarWidget->mSelectedHair != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedHair)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedHairColor = i;
                Reanimation_SetZombatarHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHair, zombatarWidget->mSelectedHairColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownFHair(ZombatarWidget *zombatarWidget, int x, int y) {
    if (zombatarWidget->mSelectedFHairPage == 0) {
        for (int i = 0; i < 17; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedFHair = i;
                Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
                return;
            }
        }
        int theX = 160 + 198 + (17 % 6) * 73;
        int theY = 162 + 17 / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedFHair = 255;
            Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
            return;
        }
        TRect next = {160 + 588, 436, addonZombatarImages.zombatar_next_button->mWidth, addonZombatarImages.zombatar_next_button->mHeight};
        if (TRect_Contains(&next, x, y)) {
            zombatarWidget->mSelectedFHairPage++;
            return;
        }
    } else if (zombatarWidget->mSelectedFHairPage == 1) {
        for (int i = 0; i < 7; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedFHair = i + 17;
                Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
                return;
            }
        }
        int theX = 160 + 198 + (7 % 6) * 73;
        int theY = 162 + 7 / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedFHair = 255;
            Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
            return;
        }
        TRect prev = {160 + 209, 436, addonZombatarImages.zombatar_next_button->mWidth, addonZombatarImages.zombatar_next_button->mHeight};
        if (TRect_Contains(&prev, x, y)) {
            zombatarWidget->mSelectedFHairPage--;
            return;
        }
    }

    if (zombatarWidget->mSelectedFHair != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedFHair)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedFHairColor = i;
                Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownTidBit(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedTidBit = i;
            Reanimation_SetZombatarTidBits(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedTidBit, zombatarWidget->mSelectedTidBitColor);
            return;
        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedTidBit = 255;
        Reanimation_SetZombatarTidBits(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedTidBit, zombatarWidget->mSelectedTidBitColor);
        return;
    }

    if (zombatarWidget->mSelectedTidBit != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedTidBit)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedTidBitColor = i;
                Reanimation_SetZombatarTidBits(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedTidBit, zombatarWidget->mSelectedTidBitColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownEyeWear(ZombatarWidget *zombatarWidget, int x, int y) {

    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedEyeWear = i;
            Reanimation_SetZombatarEyeWear(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedEyeWear, zombatarWidget->mSelectedEyeWearColor);
            return;
        }
    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedEyeWear = 255;
        Reanimation_SetZombatarEyeWear(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedEyeWear, zombatarWidget->mSelectedEyeWearColor);
        return;
    }

    if (zombatarWidget->mSelectedEyeWear != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedEyeWear)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedEyeWearColor = i;
                Reanimation_SetZombatarEyeWear(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedEyeWear, zombatarWidget->mSelectedEyeWearColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownCloth(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedCloth = i;
            return;
        }
    }
    int theX = 160 + 198 + (12 % 6) * 73;
    int theY = 162 + 12 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedCloth = 255;
        return;
    }
}

void TestMenuWidget_MouseDownAccessory(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 15; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedAccessory = i;
            Reanimation_SetZombatarAccessories(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedAccessory, zombatarWidget->mSelectedAccessoryColor);
            return;
        }
    }
    int theX = 160 + 198 + (15 % 6) * 73;
    int theY = 162 + 15 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedAccessory = 255;
        Reanimation_SetZombatarAccessories(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedAccessory, zombatarWidget->mSelectedAccessoryColor);
        return;
    }

    if (zombatarWidget->mSelectedAccessory != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedAccessory)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedAccessoryColor = i;
                Reanimation_SetZombatarAccessories(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedAccessory, zombatarWidget->mSelectedAccessoryColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownHat(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedHat = i;
            Reanimation_SetZombatarHats(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHat, zombatarWidget->mSelectedHatColor);
            return;
        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedHat = 255;
        Reanimation_SetZombatarHats(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHat, zombatarWidget->mSelectedHatColor);
        return;
    }

    if (zombatarWidget->mSelectedHat != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedHat)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedHatColor = i;
                Reanimation_SetZombatarHats(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHat, zombatarWidget->mSelectedHatColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownBackground(ZombatarWidget *zombatarWidget, int x, int y) {
    if (zombatarWidget->mSelectedBackgroundPage == 0) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackground = i;
                return;
            }
        }
        TRect next = {160 + 588, 436, addonZombatarImages.zombatar_next_button->mWidth, addonZombatarImages.zombatar_next_button->mHeight};
        if (TRect_Contains(&next, x, y)) {
            zombatarWidget->mSelectedBackgroundPage++;
            return;
        }
    } else if (zombatarWidget->mSelectedBackgroundPage == 4) {
        for (int i = 0; i < 11; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackground = i + 18 * zombatarWidget->mSelectedBackgroundPage;
                return;
            }
        }
        TRect prev = {160 + 209, 436, addonZombatarImages.zombatar_next_button->mWidth, addonZombatarImages.zombatar_next_button->mHeight};
        if (TRect_Contains(&prev, x, y)) {
            zombatarWidget->mSelectedBackgroundPage--;
            return;
        }
    } else {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackground = i + 18 * zombatarWidget->mSelectedBackgroundPage;
                return;
            }
        }
        TRect next = {160 + 588, 436, addonZombatarImages.zombatar_next_button->mWidth, addonZombatarImages.zombatar_next_button->mHeight};
        if (TRect_Contains(&next, x, y)) {
            zombatarWidget->mSelectedBackgroundPage++;
            return;
        }
        TRect prev = {160 + 209, 436, addonZombatarImages.zombatar_next_button->mWidth, addonZombatarImages.zombatar_next_button->mHeight};
        if (TRect_Contains(&prev, x, y)) {
            zombatarWidget->mSelectedBackgroundPage--;
            return;
        }
    }


    if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab, zombatarWidget->mSelectedBackground)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackgroundColor = i;
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDown(ZombatarWidget *zombatarWidget, int x, int y) {
    xx = x;
    yy = y;
    //    Sexy_Widget_Move(zombatarWidget->mBackButton,xx,yy);
    //    zombatarWidget->mPreviewZombie->mX = x;
    //    zombatarWidget->mPreviewZombie->mY = y;
    LOG_DEBUG("{} {}", x, y);

    if (gMainMenuZombatarWidget->mShowExistingZombatarPortrait) {
        return;
    }
    for (char i = 0; i < ZombatarWidget::MaxTabNum; ++i) {
        TRect rect = {160 + 67, 152 + i * 43, 125, 47};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedTab = i;
            zombatarWidget->mSelectedFHairPage = 0;
            zombatarWidget->mSelectedBackgroundPage = 0;
            return;
        }
    }

    switch (zombatarWidget->mSelectedTab) {
        case ZombatarWidget::SKIN:
            TestMenuWidget_MouseDownSkin(zombatarWidget, x, y);
            break;
        case ZombatarWidget::HAIR:
            TestMenuWidget_MouseDownHair(zombatarWidget, x, y);
            break;
        case ZombatarWidget::FHAIR:
            TestMenuWidget_MouseDownFHair(zombatarWidget, x, y);
            break;
        case ZombatarWidget::TIDBIT:
            TestMenuWidget_MouseDownTidBit(zombatarWidget, x, y);
            break;
        case ZombatarWidget::EYEWEAR:
            TestMenuWidget_MouseDownEyeWear(zombatarWidget, x, y);
            break;
        case ZombatarWidget::CLOTHES:
            TestMenuWidget_MouseDownCloth(zombatarWidget, x, y);
            break;
        case ZombatarWidget::ACCESSORY:
            TestMenuWidget_MouseDownAccessory(zombatarWidget, x, y);
            break;
        case ZombatarWidget::HAT:
            TestMenuWidget_MouseDownHat(zombatarWidget, x, y);
            break;
        case ZombatarWidget::BACKGROUND:
            TestMenuWidget_MouseDownBackground(zombatarWidget, x, y);
            break;
    }
}

void TestMenuWidget_MouseDrag(ZombatarWidget *zombatarWidget, int x, int y) {
    xx = x;
    yy = y;
    //    Sexy_Widget_Move(zombatarWidget->mBackButton,xx,yy);
    //    zombatarWidget->mPreviewZombie->mX = x;
    //    zombatarWidget->mPreviewZombie->mY = y;
    LOG_DEBUG("{} {}", x, y);
}

void TestMenuWidget_MouseUp(ZombatarWidget *zombatarWidget, int x, int y) {}

void TestMenuWidget_KeyDown(ZombatarWidget *zombatarWidget, int keyCode) {
    if (keyCode == Sexy::Back || keyCode == Sexy::Back2) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        LawnApp_KillZombatarScreen(lawnApp);
        LawnApp_ShowMainMenuScreen(lawnApp);
        return;
    }
    if (keyCode == Sexy::Up) {
        yy--;
        LOG_DEBUG("{} {}", xx, yy);
    }
    if (keyCode == Sexy::Down) {
        yy++;
        LOG_DEBUG("{} {}", xx, yy);
    }
    if (keyCode == Sexy::Left) {
        xx--;
        LOG_DEBUG("{} {}", xx, yy);
    }
    if (keyCode == Sexy::Right) {
        xx++;
        LOG_DEBUG("{} {}", xx, yy);
    }
    if (keyCode == Sexy::Up || keyCode == Sexy::Down || keyCode == Sexy::Left || keyCode == Sexy::Right) {
        return;
    }
}
