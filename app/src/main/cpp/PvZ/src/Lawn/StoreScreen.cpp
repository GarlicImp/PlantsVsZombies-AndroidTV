#include "PvZ/Lawn/StoreScreen.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Misc.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Symbols.h"

void StoreScreen_AddedToManager(int *a, int a2) {

    return old_StoreScreen_AddedToManager(a, a2);
}

void StoreScreen_RemovedFromManager(int *a, int a2) {
    return old_StoreScreen_RemovedFromManager(a, a2);
}

void StoreScreen_Update(int a) {
    return old_StoreScreen_Update(a);
}

void StoreScreen_SetupPage(int *a) {
    old_StoreScreen_SetupPage(a);
    //    for (int i = 0; i < 8; ++i) {
    //        a::a StoreItemType = StoreScreen_GetStoreItemType(a, i);
    //        if (StoreScreen_IsPottedPlant(a, StoreItemType)) {
    //            Sexy::Image *theImage = *((Sexy::Image **) a + i + 217);
    //            Sexy::Graphics g;
    //            Sexy_Graphics_Graphics2(&g, theImage);
    //            Sexy_Graphics_ClearRect(&g, 0, 0, 100, 70);
    //            Sexy_Graphics_Translate(&g, -10, -50);
    //            Sexy_Graphics_DrawImage(&g, addonImages.seed_cached_52, 0, 0);
    //            Sexy_Graphics_Delete2(&g);
    //        }
    //    }
}

void StoreScreen_DrawItem(int *a1, Sexy::Graphics *a2, int a3, StoreItem item) {
    //    if (StoreScreen_IsItemUnavailable(a1, item)) return;
    //    if (StoreScreen_IsPottedPlant(a1, item)){
    //        int theX = 0;
    //        int theY = 0;
    //        int theCount = 0;
    //        Sexy::Image *theImage = nullptr;
    //        StoreScreen_GetStoreItemInfo(a1, 0, item, &theImage, &theX, &theY, &theCount);
    //        Sexy_Graphics_DrawImage(a2,addonImages.seed_cached_52,theX,theY);
    //    }
    old_StoreScreen_DrawItem(a1, a2, a3, item);
}

void StoreScreen_ButtonDepress(int *storeScreen, int buttonId) {
    //    if (!showHouse) return old_StoreScreen_ButtonDepress(storeScreen, buttonId);
    LawnApp *lawnApp = (LawnApp *)storeScreen[184];
    int newPageIndex;
    switch (buttonId) {
        case 100:
            storeScreen[181] = 1000;
            break;
        case 101:
            storeScreen[195] = 50;
            storeScreen[197] = 1;
            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_HATCHBACK_CLOSE_Addr);
            storeScreen[188] = 0;
            LawnApp_CrazyDaveStopTalking(lawnApp);
            StoreScreen_EnableButtons(storeScreen, false);
            do {
                newPageIndex = storeScreen[192] - 1;
                if (newPageIndex < 0) {
                    newPageIndex = 5;
                    storeScreen[192] = 5;
                } else if (newPageIndex == 4) {
                    newPageIndex = 3;
                    storeScreen[192] = 3;
                } else {
                    storeScreen[192] = newPageIndex;
                }
            } while (!StoreScreen_IsPageShown(storeScreen, newPageIndex));
            break;
        case 102:
            storeScreen[195] = 50;
            storeScreen[197] = 2;
            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_HATCHBACK_CLOSE_Addr);
            storeScreen[188] = 0;
            LawnApp_CrazyDaveStopTalking(lawnApp);
            StoreScreen_EnableButtons(storeScreen, false);
            do {
                newPageIndex = storeScreen[192] + 1;
                if (newPageIndex == 4) {
                    newPageIndex = 5;
                    storeScreen[192] = 5;
                } else if (newPageIndex > 4) {
                    newPageIndex = 0;
                    storeScreen[192] = 0;
                } else {
                    storeScreen[192] = newPageIndex;
                }
            } while (!StoreScreen_IsPageShown(storeScreen, newPageIndex));
            break;
    }
}

void StoreScreen_PurchaseItem(int *storeScreen, StoreItem item) {
    old_StoreScreen_PurchaseItem(storeScreen, item);
    LawnApp *lawnApp = (LawnApp *)storeScreen[184];
    PlayerInfo *mPlayerInfo = lawnApp->mPlayerInfo;

    // 检查植物全收集成就
    for (int i = StoreItem::STORE_ITEM_PLANT_GATLINGPEA; i <= StoreItem::STORE_ITEM_PLANT_IMITATER; ++i) {
        if (mPlayerInfo->mPurchases[i] == 0) {
            return;
        }
    }
    LawnApp_GrantAchievement(lawnApp, AchievementId::ACHIEVEMENT_MORTICULTURALIST);
}

void StoreScreen_Draw(int *storeScreen, Sexy::Graphics *a2) {
    // 绘制商店页数字符串
    old_StoreScreen_Draw(storeScreen, a2);
    int theTotalPages = 0;
    if (LawnApp_HasFinishedAdventure((LawnApp *)storeScreen[184]) && showHouse) {
        theTotalPages = 5;
    } else {
        for (int i = 0; i < 4; ++i) {
            if (StoreScreen_IsPageShown(storeScreen, i)) {
                theTotalPages++;
            }
        }
    }

    if (theTotalPages <= 1)
        return;
    int mPage = storeScreen[192] == 5 ? 5 : storeScreen[192] + 1;
    int holder[1];
    Sexy_StrFormat(holder, "%d/%d", mPage, theTotalPages);
    Color theColor = {200, 200, 200, 255};
    TodDrawString(a2, holder, 410, 512, *Sexy_FONT_BRIANNETOD16_Addr, theColor, DrawStringJustification::DS_ALIGN_CENTER);
    Sexy_String_Delete(holder);
}


static StoreScreenTouchState::StoreScreenTouchState mStoreScreenTouchState = StoreScreenTouchState::None;

void StoreScreen_MouseDown(int *storeScreen, int x, int y, int theClickCount) {
    bool mBubbleClickToContinue = *((uint8_t *)storeScreen + 756);
    StoreItem mSelectedStoreItemType = *((StoreItem *)storeScreen + 194);
    if (mBubbleClickToContinue) {
        // 初次捡到戴夫车钥匙时会进入商店并且有一段戴夫对话，这里用于识别戴夫对话
        StoreScreen_AdvanceCrazyDaveDialog(storeScreen);
        return;
    }
    if (!StoreScreen_CanInteractWithButtons(storeScreen)) {
        // 翻页过程中无法触控
        return;
    }
    int mPrevButtonWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_STORE_PREVBUTTON_Addr);
    int mPrevButtonHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_STORE_PREVBUTTON_Addr);
    int mNextButtonWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_STORE_NEXTBUTTON_Addr);
    int mNextButtonHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_STORE_NEXTBUTTON_Addr);
    int mBackButtonWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_STORE_MAINMENUBUTTON_Addr);
    int mBackButtonHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_STORE_MAINMENUBUTTON_Addr);
    Sexy::Rect mPrevButtonRect = {storeScreen[198] + 172, storeScreen[199] + 375, mPrevButtonWidth, mPrevButtonHeight};
    Sexy::Rect mNextButtonRect = {storeScreen[198] + 573, storeScreen[199] + 373, mNextButtonWidth, mNextButtonHeight};
    Sexy::Rect mBackButtonRect = {storeScreen[198] + 305, storeScreen[199] + 510, mBackButtonWidth, mBackButtonHeight};

    if (TRect_Contains(&mBackButtonRect, x, y)) {
        mStoreScreenTouchState = StoreScreenTouchState::Back;
        return;
    }

    bool isPageShown = StoreScreen_IsPageShown(storeScreen, 1);
    if (isPageShown) {

        if (TRect_Contains(&mPrevButtonRect, x, y)) {
            mStoreScreenTouchState = StoreScreenTouchState::Prev;
            return;
        }

        if (TRect_Contains(&mNextButtonRect, x, y)) {
            mStoreScreenTouchState = StoreScreenTouchState::Next;
            return;
        }
    }

    //    StoreScreen_PurchaseItem(storeScreen, a::STORE_ITEM_BLUEPRINT_CHANGE);

    for (int i = 0; i < 8; i++) {
        StoreItem storeItemType = StoreScreen_GetStoreItemType(storeScreen, i);
        if (storeItemType != StoreItem::STORE_ITEM_INVALID) {
            int theX = 0;
            int theY = 0;
            int theCount = 0;
            Sexy::Image *theImage = nullptr;
            StoreScreen_GetStoreItemInfo(storeScreen, i, storeItemType, &theImage, &theX, &theY, &theCount);
            int theImageWidth = 80;
            int theImageHeight = 80;
            if (theImage != nullptr) {
                theImageWidth = Sexy_Image_GetWidth(theImage);
                theImageHeight = Sexy_Image_GetHeight(theImage);
            }

            //            LOGD("i:%d storeItemType:%d theX:%d theY:%d x:%d y:%d theImageWidth:%d theImageHeight:%d", i, storeItemType, theX, theY, x, y, theImageWidth,
            //                 theImageHeight);
            //            int theImageWidth = 80;
            //            int theImageHeight = 80;
            Sexy::Rect itemRect = {theX - theImageWidth / 2, theY - theImageHeight, theImageWidth, theImageHeight};
            if (TRect_Contains(&itemRect, x, y)) {
                if (mSelectedStoreItemType != storeItemType) {
                    StoreScreen_SetSelectedSlot((int)storeScreen, i);
                } else {
                    if (StoreScreen_IsItemSoldOut(storeScreen, storeItemType) || StoreScreen_IsItemUnavailable(storeScreen, storeItemType) || StoreScreen_IsComingSoon(storeScreen, storeItemType)) {
                        return;
                    }
                    StoreScreen_PurchaseItem(storeScreen, storeItemType);
                }
            }
        }
    }
}

void StoreScreen_MouseUp(int *storeScreen, int x, int y, int theClickCount) {
    switch (mStoreScreenTouchState) {
        case StoreScreenTouchState::Back:
            (*(void (**)(int *, int))(*storeScreen + 516))(storeScreen, 100); // StoreScreen_ButtonDepress(storeScreen,100)
            break;
        case StoreScreenTouchState::Prev:
            (*(void (**)(int *, int))(*storeScreen + 516))(storeScreen, 101); // StoreScreen_ButtonDepress(storeScreen,101)
            break;
        case StoreScreenTouchState::Next:
            (*(void (**)(int *, int))(*storeScreen + 516))(storeScreen, 102); // StoreScreen_ButtonDepress(storeScreen,102)
            break;
        default:
            break;
    }
    mStoreScreenTouchState = StoreScreenTouchState::None;
}
