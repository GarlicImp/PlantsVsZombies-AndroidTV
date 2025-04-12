#include "PvZ/Lawn/ChallengeScreen.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/Lawn/LawnApp.h"

static Sexy::GameButton *mChallengeScreenCloseButton;

void ChallengeScreen_ChallengeScreen(ChallengeScreen *challengeScreen, LawnApp *lawnApp, ChallengePage page) {
    // 去除按钮对触控的遮挡
    old_ChallengeScreen_ChallengeScreen(challengeScreen, lawnApp, page);
    for (auto *button : challengeScreen->mButtons) {
        // 把按钮全部缩小至长宽为0
        Sexy_Widget_Resize(button, button->mX, button->mY, 0, 0);
    }
}

void ChallengeScreen_Draw(ChallengeScreen *challengeScreen, Sexy::Graphics *graphics) {
    // 修复小游戏界面显示奖杯数不正确
    old_ChallengeScreen_Draw(challengeScreen, graphics);
    int mTotalTrophiesInPage = 0;
    switch (challengeScreen->mPage) {
        case ChallengePage::CHALLENGE_PAGE_SURVIVAL:
            mTotalTrophiesInPage = 10;
            break;
        case ChallengePage::CHALLENGE_PAGE_CHALLENGE:
            for (int i = 0; i < 94; ++i) {
                if (GetChallengeDefinition(i).mPage == ChallengePage::CHALLENGE_PAGE_CHALLENGE) {
                    mTotalTrophiesInPage++;
                }
            }
            break;
        case ChallengePage::CHALLENGE_PAGE_COOP:
            mTotalTrophiesInPage = 10;
            break;
        case ChallengePage::CHALLENGE_PAGE_PUZZLE:
            mTotalTrophiesInPage = 18;
            break;
    }

    int holder[1];
    Sexy_StrFormat(holder, "%d/%d", LawnApp_GetNumTrophies(challengeScreen->mApp, challengeScreen->mPage), mTotalTrophiesInPage);
    Color theColor = {255, 240, 0, 255};
    TodDrawString(graphics, holder, 711, 62, *Sexy_FONT_BRIANNETOD16_Addr, theColor, DrawStringJustification::Center);
    Sexy_String_Delete(holder);
}

void ChallengeScreen_AddedToManager(ChallengeScreen *challengeScreen, int a2) {
    // 记录当前游戏状态
    int holder[1];
    TodStringTranslate(holder, "[CLOSE]");
    mChallengeScreenCloseButton = MakeButton(1000, &challengeScreen->mButtonListener, challengeScreen, holder);
    GameButton_Resize(mChallengeScreenCloseButton, 800, 520, 170, 50);
    Sexy_String_Delete(holder);
    Sexy_Widget_AddWidget(challengeScreen, mChallengeScreenCloseButton);
    return old_ChallengeScreen_AddedToManager(challengeScreen, a2);
}

void ChallengeScreen_Update(ChallengeScreen *a) {
    // 记录当前游戏状态
    return old_ChallengeScreen_Update(a);
}

void ChallengeScreen_RemovedFromManager(ChallengeScreen *challengeScreen, int a2) {
    // 记录当前游戏状态
    old_ChallengeScreen_RemovedFromManager(challengeScreen, a2);
    if (mChallengeScreenCloseButton != nullptr) {
        Sexy_Widget_RemoveWidget(challengeScreen, mChallengeScreenCloseButton);
    }
}

void ChallengeScreen_Delete2(ChallengeScreen *challengeScreen) {
    // 删除按钮
    old_ChallengeScreen_Delete2(challengeScreen);
    if (mChallengeScreenCloseButton != nullptr) {
        GameButton_Delete(mChallengeScreenCloseButton);
        mChallengeScreenCloseButton = nullptr;
    }
}

void ChallengeScreen::ButtonPress(int theButtonId) {
    // 空函数替换，去除原有的点击进入关卡的功能
}

void ChallengeScreen_ButtonDepress(ChallengeScreen *challengeScreen, int buttonId) {
    // 去除原有的点击进入关卡的功能
    if (buttonId == 1000) {
        LawnApp_KillChallengeScreen(challengeScreen->mApp);
        LawnApp_DoBackToMain(challengeScreen->mApp);
    }
}

void ChallengeScreen_UpdateButtons(ChallengeScreen *challengeScreen) {
    // 空函数替换，去除默认选取第一个游戏的功能
}


namespace {
ChallengeDefinition gButteredPopcornDef = {GameMode::ChallengeButteredPopcorn, 37, ChallengePage::CHALLENGE_PAGE_CHALLENGE, 6, 1, "[BUTTERED_POPCORN]"};
ChallengeDefinition gPoolPartyDef = {GameMode::ChallengePoolParty, 37, ChallengePage::CHALLENGE_PAGE_CHALLENGE, 6, 2, "[POOL_PARTY]"};
} // namespace

ChallengeDefinition &GetChallengeDefinition(int index) {
    if (index + 2 == GameMode::ChallengeButteredPopcorn) {
        return gButteredPopcornDef;
    }
    // if (index + 2 == GameMode::ChallengePoolParty) {
    //     return gPoolPartyDef;
    // }
    return old_GetChallengeDefinition(index);
}


namespace {
int mChallengeScreenTouchDownX;
int mChallengeScreenTouchDownY;
int mChallengeItemHeight;
int mChallengeScreenGameIndex;
bool mChallengeItemMoved;
bool mTouchOutSide;

constexpr int mPageTop = 75;
constexpr int mPageBottom = 555;
} // namespace

void ChallengeScreen::MouseDown(int x, int y, int theClickCount) {
    if (y > mPageBottom || y < mPageTop) {
        mTouchOutSide = true;
    }
    mChallengeScreenTouchDownX = x;
    mChallengeScreenTouchDownY = y;
    mChallengeItemHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_CHALLENGE_NAME_BACK_Addr) + 2; // 2为缝隙大小

    mChallengeScreenGameIndex = mScreenTopChallengeIndex;

    //    int totalGamesInThisPage = a[376];//如果这个值是33
    //    int currentSelectedGameIndex = ChallengeScreen_GetCurrentSelectedGameIndex(
    //            a);//这里取值就是0~32。种子雨是32。

    //    int firstGameInPageIndex = a->mScreenTopChallengeIndex;
    //    int firstGameInPageIndex2 = a[186];
    //    a->mSelectedMode = a[currentSelectedGameIndex + 1 + 188];//向下移动绿色光标，不可循环滚动
    //    a->mSelectedMode = a[currentSelectedGameIndex - 1 + 188];//向上移动绿色光标，不可循环滚动

    //    LOGD("dOWN:%d %d %d %d", x, y, firstGameInPageIndex, firstGameInPageIndex2);
}

void ChallengeScreen::MouseDrag(int x, int y) {
    if (mTouchOutSide)
        return;
    int triggerHeight = mChallengeItemHeight / 2; // 调节此处以修改小游戏列表的滚动速度。滚动太快就会有BUG，好烦。
    if (mChallengeScreenTouchDownY - y > triggerHeight) {
        int totalGamesInThisPage = mTotalGameInPage;
        mChallengeScreenGameIndex += 1;
        mChallengeScreenTouchDownY -= triggerHeight;
        int gameIndexToScroll = mChallengeScreenGameIndex >= totalGamesInThisPage - 4 ? totalGamesInThisPage - 4 : mChallengeScreenGameIndex;
        ChallengeScreen_SetScrollTarget(this, gameIndexToScroll);
        //        ChallengeScreen_UpdateButtons(a);
        mChallengeItemMoved = true;
    } else if (y - mChallengeScreenTouchDownY > triggerHeight) {
        mChallengeScreenGameIndex -= 1;
        mChallengeScreenTouchDownY += triggerHeight;
        int gameIndexToScroll = mChallengeScreenGameIndex <= 0 ? 0 : mChallengeScreenGameIndex;
        ChallengeScreen_SetScrollTarget(this, gameIndexToScroll);
        //        ChallengeScreen_UpdateButtons(a);
        mChallengeItemMoved = true;
    }
}

void ChallengeScreen::MouseUp(int x, int y) {
    if (!mTouchOutSide && !mChallengeItemMoved) {
        int gameIndex = mScreenTopChallengeIndex + (y - mPageTop) / mChallengeItemHeight;
        if (mSelectedMode == mUnk1[gameIndex]) {
            ChallengeScreen_KeyDown(this, 13);
        } else {
            LawnApp_PlaySample(mApp, *Sexy_SOUND_BUTTONCLICK_Addr);
            mSelectedMode = mUnk1[gameIndex];
        }
    }
    mTouchOutSide = false;
    mChallengeItemMoved = false;
}
