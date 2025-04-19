#include "PvZ/Lawn/AlmanacDialog.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/Enums.h"
#include "PvZ/Lawn//Plant.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/LawnApp.h"

#include <cstddef>

#include <numbers>

namespace {

constexpr int theBackId = 110;
constexpr int theCloseId = 111;

// ButtonX和ButtonY是按钮的左上角坐标.
constexpr int mAlmanacBackButtonX = -170;
constexpr int mAlmanacBackButtonY = 520;
constexpr int mAlmanacCloseButtonX = 800;
constexpr int mAlmanacCloseButtonY = 520;

// 按钮长度和宽度为150和50，两个按钮都读取此长宽.
constexpr int mAlmanacButtonWidth = 170;
constexpr int mAlmanacButtonHeight = 50;

constexpr int mAlmanacPlantRectX = 521 - 8;
constexpr int mAlmanacPlantRectY = 107 + 20;

Sexy::GameButton *mAlmanacBackButton;
Sexy::GameButton *mAlmanacCloseButton;

} // namespace


void AlmanacDialog_Delete2(AlmanacDialog *almanacDialog) {
    old_AlmanacDialog_Delete2(almanacDialog);
    GameButton_Delete(mAlmanacBackButton);
    GameButton_Delete(mAlmanacCloseButton);
    mAlmanacBackButton = nullptr;
    mAlmanacCloseButton = nullptr;
}

void AlmanacDialog_SetPage(AlmanacDialog *almanacDialog, int targetPage) {
    // 修复点击气球僵尸进植物图鉴、点击介绍文字进植物图鉴
    if (targetPage != 0) {
        // 在前往其他图鉴页面时，显示返回按钮
        if (mAlmanacBackButton != nullptr) {
            GameButton_Resize(mAlmanacBackButton, mAlmanacBackButtonX, mAlmanacBackButtonY, mAlmanacButtonWidth, mAlmanacButtonHeight);
            mAlmanacBackButton->mBtnNoDraw = false;
            mAlmanacBackButton->mDisabled = false;
        }
        // 在前往其他图鉴页面时，将按钮缩小为0x0
        GameButton_Resize(almanacDialog->mViewPlantButton, 0, 0, 0, 0);
        GameButton_Resize(almanacDialog->mViewZombieButton, 0, 0, 0, 0);
    } else {
        // 回到图鉴首页时，将返回按钮禁用
        if (mAlmanacBackButton != nullptr) {
            GameButton_Resize(mAlmanacBackButton, 0, 0, 0, 0);
            mAlmanacBackButton->mBtnNoDraw = true;
            mAlmanacBackButton->mDisabled = true;
        }
        // 回到图鉴首页时，将按钮恢复为正常大小
        GameButton_Resize(almanacDialog->mViewPlantButton, 130, 345, 156, 42);
        GameButton_Resize(almanacDialog->mViewZombieButton, 487, 345, 210, 48);
    }
    return old_AlmanacDialog_SetPage(almanacDialog, targetPage);
}


namespace {
int mAlmanacDialogTouchDownY;
bool isTouchDownInTextRect;
TRect mTextRect = {482, 360, 258, 173};
} // namespace

void AlmanacDialog_MouseDown(AlmanacDialog *almanacDialog, int x, int y, int a4) {
    // 修复点击气球僵尸进植物图鉴、点击介绍文字进植物图鉴
    if (almanacDialog->mOpenPage == 0) {
        // 如果当前的Page是Index Page
        if (GameButton_IsMouseOver(almanacDialog->mViewPlantButton))
            LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        if (GameButton_IsMouseOver(almanacDialog->mViewZombieButton))
            LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        return;
    } else if (TRect_Contains(&mTextRect, x, y)) {
        isTouchDownInTextRect = true;
        mAlmanacDialogTouchDownY = y;
    }

    SeedType seedType = AlmanacDialog_SeedHitTest(almanacDialog, x, y);
    if (seedType != SeedType::SEED_NONE && seedType != almanacDialog->mSelectedSeed) {
        almanacDialog->mSelectedSeed = seedType;
        AlmanacDialog_SetupPlant(almanacDialog);
        LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_TAP_Addr);
    }
    ZombieType zombieType = AlmanacDialog_ZombieHitTest(almanacDialog, x, y);
    if (zombieType != -1 && zombieType != almanacDialog->mSelectedZombie) {
        almanacDialog->mSelectedZombie = zombieType;
        AlmanacDialog_SetupZombie(almanacDialog);
        LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_TAP_Addr);
    }
}

void AlmanacDialog_MouseDrag(AlmanacDialog *almanacDialog, int x, int y) {
    // 滚动图鉴文字

    if (isTouchDownInTextRect && mAlmanacDialogTouchDownY != y) {
        (*(void (**)(Sexy::Widget *, uint32_t, double))(*(uint32_t *)almanacDialog->mScrollTextView + 500))(
            almanacDialog->mScrollTextView, *(uint32_t *)(*(uint32_t *)almanacDialog->mScrollTextView + 500), *((double *)almanacDialog->mScrollTextView + 35) + 0.6 * (mAlmanacDialogTouchDownY - y));
        mAlmanacDialogTouchDownY = y;
    }
}

void AlmanacDialog_MouseUp(AlmanacDialog *almanacDialog, int x, int y, int a4) {
    // 空函数替换，修复点击图鉴Index界面中任何位置都会跳转植物图鉴的问题
    isTouchDownInTextRect = false;
}

void AlmanacDialog_RemovedFromManager(AlmanacDialog *almanacDialog, int *manager) {
    // 记录当前游戏状态
    old_AlmanacDialog_RemovedFromManager(almanacDialog, manager);
    Sexy_Widget_RemoveWidget(almanacDialog, mAlmanacBackButton);
    Sexy_Widget_RemoveWidget(almanacDialog, mAlmanacCloseButton);
}

void AlmanacDialog_AlmanacDialog(AlmanacDialog *almanacDialog, LawnApp *lawnApp) {
    // TODO: 解决部分植物的介绍文本显示不全问题

    old_AlmanacDialog_AlmanacDialog(almanacDialog, lawnApp);
    int holder[1];
    TodStringTranslate(holder, "[ALMANAC_INDEX]");
    mAlmanacBackButton = MakeButton(theBackId, &almanacDialog->mButtonListener, almanacDialog, holder);
    GameButton_Resize(mAlmanacBackButton, 0, 0, 0, 0);
    mAlmanacBackButton->mBtnNoDraw = true;
    mAlmanacBackButton->mDisabled = true;
    Sexy_String_Delete(holder);
    int holder1[1];
    TodStringTranslate(holder1, "[CLOSE]");
    mAlmanacCloseButton = MakeButton(theCloseId, &almanacDialog->mButtonListener, almanacDialog, holder1);
    GameButton_Resize(mAlmanacCloseButton, mAlmanacCloseButtonX, mAlmanacCloseButtonY, mAlmanacButtonWidth, mAlmanacButtonHeight);
    Sexy_String_Delete(holder1);
    Sexy_Widget_AddWidget(almanacDialog, mAlmanacBackButton);
    Sexy_Widget_AddWidget(almanacDialog, mAlmanacCloseButton);


    //   为泳池背景加入PoolEffect。这里挖空背景图，挖出一块透明方形
    Sexy::Image *gPlantBackImage = *Sexy_IMAGE_ALMANAC_PLANTBACK_Addr;
    Sexy::Image *gPoolBackImage = *Sexy_IMAGE_ALMANAC_GROUNDNIGHTPOOL_Addr;
    TRect blankRect = {mAlmanacPlantRectX + 240, mAlmanacPlantRectY + 60, gPoolBackImage->mWidth, gPoolBackImage->mHeight};
    Sexy_MemoryImage_ClearRect(gPlantBackImage, &blankRect);
}

void AlmanacDialog_ButtonDepress(AlmanacDialog *almanacDialog, int id) {
    if (id == 0) {
        AlmanacDialog_SetPage(almanacDialog, 1);
    } else if (id == 1) {
        AlmanacDialog_SetPage(almanacDialog, 2);
    } else if (id == theBackId) {
        AlmanacDialog_KeyDown(almanacDialog, 27);
    } else if (id == theCloseId) {
        LawnApp_KillAlmanacDialog(almanacDialog->mApp);
    }
}

void AlmanacDialog_DrawPlants_Unmodified(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics) {
    // old_AlmanacDialog_DrawPlants(almanacDialog,graphics);

    // TODO:解决PoolEffect图层问题，和部分植物的介绍文本显示不全问题
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_PLANTBACK_Addr, -240, -60);
    int theHeaderText[1];
    TodStringTranslate(theHeaderText, "[SUBURBAN_ALMANAC_PLANTS]");
    Color theHeaderColor = {213, 159, 43, 255};
    TodDrawString(graphics, theHeaderText, 400, 50, *Sexy_FONT_HOUSEOFTERROR20_Addr, theHeaderColor, DrawStringJustification::DS_ALIGN_CENTER);
    Sexy_String_Delete(theHeaderText);
    SeedType mSelectedSeed = almanacDialog->mSelectedSeed;
    int theAlpha = std::sin((almanacDialog->mUpdateCnt % 100) * 0.01 * std::numbers::pi) * 255.0;
    int x, y;
    for (int i = SeedType::SEED_PEASHOOTER; i < SeedType::NUM_SEEDS_IN_CHOOSER; ++i) {
        AlmanacDialog_GetSeedPosition(almanacDialog, i, &x, &y);
        if (i == SeedType::SEED_IMITATER) {
            bool tmp = Sexy_Graphics_GetColorizeImages(graphics);
            Sexy_Graphics_SetColorizeImages(graphics, true);
            if (mSelectedSeed == SeedType::SEED_IMITATER) {
                Color v39 = {255, 255, 0, theAlpha};
                Sexy_Graphics_SetColor(graphics, &v39);
            } else {
                Color v39 = {255, 255, 255, 64};
                Sexy_Graphics_SetColor(graphics, &v39);
            }
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_IMITATER_Addr, 18, 20);
            Sexy_Graphics_SetColor(graphics, &white);
            Sexy_Graphics_SetColorizeImages(graphics, tmp);
        } else {
            if (mSelectedSeed == i) {
                Sexy_Graphics_SetScale(graphics, 1.1, 1.1, x, y);
                DrawSeedPacket(graphics, x - 2, y - 4, mSelectedSeed, SeedType::SEED_NONE, 0.0, 255, true, false, false, true);
                bool tmp = Sexy_Graphics_GetColorizeImages(graphics);
                Sexy_Graphics_SetColorizeImages(graphics, true);
                Color v39 = {255, 255, 0, theAlpha};
                Sexy_Graphics_SetColor(graphics, &v39);
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SEEDPACKETFLASH_Addr, x - 3, y - 5);
                Sexy_Graphics_SetColor(graphics, &white);
                Sexy_Graphics_SetColorizeImages(graphics, tmp);
                Sexy_Graphics_SetScale(graphics, 1.0, 1.0, 0.0, 0.0);
            } else {
                DrawSeedPacket(graphics, x, y, (SeedType)i, SeedType::SEED_NONE, 0.0, 255, true, false, false, true);
            }
        }
    }

    if (Plant_IsAquatic(mSelectedSeed)) {
        if (Plant_IsNocturnal(mSelectedSeed)) {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDNIGHTPOOL_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY);
            if (Sexy_SexyAppBase_Is3DAccelerated(almanacDialog->mApp)) {
                Sexy_Graphics_SetClipRect(graphics, 475, 0, 397, 500);
                graphics->mTransY = graphics->mTransY - 145.0f;
                PoolEffect_PoolEffectDraw(almanacDialog->mApp->mPoolEffect, graphics, true);
                graphics->mTransY = graphics->mTransY + 145.0f;
                Sexy_Graphics_ClearClipRect(graphics);
            }
        } else {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDPOOL_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY);
            if (Sexy_SexyAppBase_Is3DAccelerated(almanacDialog->mApp)) {
                Sexy_Graphics_SetClipRect(graphics, 475, 0, 397, 500);
                graphics->mTransY = graphics->mTransY - 145.0f;
                PoolEffect_PoolEffectDraw(almanacDialog->mApp->mPoolEffect, graphics, false);
                graphics->mTransY = graphics->mTransY + 145.0f;
                Sexy_Graphics_ClearClipRect(graphics);
            }
        }
    } else if (Plant_IsNocturnal(mSelectedSeed) || mSelectedSeed == SeedType::SEED_GRAVEBUSTER || mSelectedSeed == SeedType::SEED_PLANTERN) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDNIGHT_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY);
    } else if (mSelectedSeed == SeedType::SEED_FLOWERPOT) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDROOF_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY);
    } else {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDDAY_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY);
    }


    if (almanacDialog->mPlant != nullptr) {
        Sexy_Graphics_PushState(graphics);
        Plant *mPlant = almanacDialog->mPlant;
        graphics->mTransX = graphics->mTransX + mPlant->mX;
        graphics->mTransY = graphics->mTransY + mPlant->mY;
        mPlant->Draw(graphics);
        Sexy_Graphics_PopState(graphics);
    }

    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_PLANTCARD_Addr, 459, 80);

    Color color = {213, 159, 43, 255};
    TodDrawString(graphics, (int *)&almanacDialog->mNameString, 617, 108, *Sexy_FONT_DWARVENTODCRAFT18_Addr, color, DrawStringJustification::DS_ALIGN_CENTER);

    if (mSelectedSeed != SeedType::SEED_IMITATER) {
        TodDrawStringWrapped(graphics, (int *)&almanacDialog->mCostString, &almanacDialog->mCostRect, *Sexy_FONT_BRIANNETOD16_Addr, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        TodDrawStringWrapped(graphics, (int *)&almanacDialog->mWaitTimeString, &almanacDialog->mWaitTimeRect, *Sexy_FONT_BRIANNETOD16_Addr, &white, DrawStringJustification::DS_ALIGN_RIGHT, false);
    }

    Sexy_Graphics_PushState(graphics);
    Sexy_Graphics_ClipRect(graphics, almanacDialog->mDescriptionRect.mX, almanacDialog->mDescriptionRect.mY - 14, almanacDialog->mDescriptionRect.mWidth, almanacDialog->mDescriptionRect.mHeight + 8);
    float v22 = almanacDialog->mScrollTextView->mValue * 0.01 * almanacDialog->mDescriptionRect.mY;
    float v23 = graphics->mTransY + 2.0 - v22;
    *(float *)almanacDialog->unk2 = -v22;
    graphics->mTransY = v23;
    Color v39 = {143, 67, 27, 255};
    TodDrawStringWrappedHelper(graphics, (int *)&almanacDialog->mDescriptionString, &almanacDialog->mDescriptionRect, *Sexy_FONT_BRIANNETOD16_Addr, v39, DrawStringJustification::DS_ALIGN_LEFT, true, true);
    Sexy_Graphics_PopState(graphics);
}

void AlmanacDialog_DrawPlants(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics) {
    //    return old_AlmanacDialog_DrawPlants(almanacDialog,graphics);
    //   为泳池背景加入PoolEffect。此函数改变了原版绘制顺序，将背景图放在泳池的后面绘制

    SeedType mSelectedSeed = almanacDialog->mSelectedSeed;
    if (Plant_IsAquatic(mSelectedSeed)) {
        if (Plant_IsNocturnal(mSelectedSeed)) {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDNIGHTPOOL_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY + 10);
            if (Sexy_SexyAppBase_Is3DAccelerated(almanacDialog->mApp)) {
                //                Sexy_Graphics_SetClipRect(graphics, 475, 0, 397, 500);
                graphics->mTransY = graphics->mTransY - 115;
                PoolEffect_PoolEffectDraw(almanacDialog->mApp->mPoolEffect, graphics, true);
                graphics->mTransY = graphics->mTransY + 115;
                //                Sexy_Graphics_ClearClipRect(graphics);
            }
        } else {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDPOOL_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY + 10);
            if (Sexy_SexyAppBase_Is3DAccelerated(almanacDialog->mApp)) {
                //                Sexy_Graphics_SetClipRect(graphics, 475, 0, 397, 500);
                graphics->mTransY = graphics->mTransY - 115;
                PoolEffect_PoolEffectDraw(almanacDialog->mApp->mPoolEffect, graphics, false);
                graphics->mTransY = graphics->mTransY + 115;
                //                Sexy_Graphics_ClearClipRect(graphics);
            }
        }
    } else if (Plant_IsNocturnal(mSelectedSeed) || mSelectedSeed == SeedType::SEED_GRAVEBUSTER || mSelectedSeed == SeedType::SEED_PLANTERN) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDNIGHT_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY);
    } else if (mSelectedSeed == SeedType::SEED_FLOWERPOT) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDROOF_Addr, mAlmanacPlantRectX + 10, mAlmanacPlantRectY + 12);
    } else {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDDAY_Addr, mAlmanacPlantRectX, mAlmanacPlantRectY);
    }

    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_PLANTBACK_Addr, -240, -60);
    int theHeaderText[1];
    TodStringTranslate(theHeaderText, "[SUBURBAN_ALMANAC_PLANTS]");
    Color theHeaderColor = {213, 159, 43, 255};
    TodDrawString(graphics, theHeaderText, 400, 50, *Sexy_FONT_HOUSEOFTERROR20_Addr, theHeaderColor, DrawStringJustification::DS_ALIGN_CENTER);
    Sexy_String_Delete(theHeaderText);

    int theAlpha = sin((almanacDialog->mUpdateCnt % 100) * 0.01 * std::numbers::pi) * 255.0;
    int x, y;
    for (int i = SeedType::SEED_PEASHOOTER; i < SeedType::NUM_SEEDS_IN_CHOOSER; ++i) {
        AlmanacDialog_GetSeedPosition(almanacDialog, i, &x, &y);
        if (i == SeedType::SEED_IMITATER) {
            bool tmp = Sexy_Graphics_GetColorizeImages(graphics);
            Sexy_Graphics_SetColorizeImages(graphics, true);
            if (mSelectedSeed == SeedType::SEED_IMITATER) {
                Color v39 = {255, 255, 0, theAlpha};
                Sexy_Graphics_SetColor(graphics, &v39);
            } else {
                Color v39 = {255, 255, 255, 64};
                Sexy_Graphics_SetColor(graphics, &v39);
            }
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_IMITATER_Addr, 18, 20);
            Sexy_Graphics_SetColor(graphics, &white);
            Sexy_Graphics_SetColorizeImages(graphics, tmp);
        } else {
            if (mSelectedSeed == i) {
                Sexy_Graphics_SetScale(graphics, 1.1, 1.1, x, y);
                DrawSeedPacket(graphics, x - 2, y - 4, mSelectedSeed, SeedType::SEED_NONE, 0.0, 255, true, false, false, true);
                bool tmp = Sexy_Graphics_GetColorizeImages(graphics);
                Sexy_Graphics_SetColorizeImages(graphics, true);
                Color v39 = {255, 255, 0, theAlpha};
                Sexy_Graphics_SetColor(graphics, &v39);
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SEEDPACKETFLASH_Addr, x - 3, y - 5);
                Sexy_Graphics_SetColor(graphics, &white);
                Sexy_Graphics_SetColorizeImages(graphics, tmp);
                Sexy_Graphics_SetScale(graphics, 1.0, 1.0, 0.0, 0.0);
            } else {
                DrawSeedPacket(graphics, x, y, (SeedType)i, SeedType::SEED_NONE, 0.0, 255, true, false, false, true);
            }
        }
    }

    if (almanacDialog->mPlant != nullptr) {
        Sexy_Graphics_PushState(graphics);
        Plant *mPlant = almanacDialog->mPlant;
        graphics->mTransX = graphics->mTransX + mPlant->mX;
        graphics->mTransY = graphics->mTransY + mPlant->mY;
        mPlant->Draw(graphics);
        Sexy_Graphics_PopState(graphics);
    }

    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_PLANTCARD_Addr, 459, 80);

    Color color = {213, 159, 43, 255};
    TodDrawString(graphics, (int *)&almanacDialog->mNameString, 617, 108, *Sexy_FONT_DWARVENTODCRAFT18_Addr, color, DrawStringJustification::DS_ALIGN_CENTER);

    if (mSelectedSeed != SeedType::SEED_IMITATER) {
        TodDrawStringWrapped(graphics, (int *)&almanacDialog->mCostString, &almanacDialog->mCostRect, *Sexy_FONT_BRIANNETOD16_Addr, &white, DrawStringJustification::DS_ALIGN_LEFT, false);
        TodDrawStringWrapped(graphics, (int *)&almanacDialog->mWaitTimeString, &almanacDialog->mWaitTimeRect, *Sexy_FONT_BRIANNETOD16_Addr, &white, DrawStringJustification::DS_ALIGN_RIGHT, false);
    }

    Sexy_Graphics_PushState(graphics);
    Sexy_Graphics_ClipRect(graphics, almanacDialog->mDescriptionRect.mX, almanacDialog->mDescriptionRect.mY - 14, almanacDialog->mDescriptionRect.mWidth, almanacDialog->mDescriptionRect.mHeight + 8);
    float v22 = almanacDialog->mScrollTextView->mValue * 0.01 * almanacDialog->mDescriptionRect.mY;
    float v23 = graphics->mTransY + 2.0 - v22;
    *(float *)almanacDialog->unk2 = -v22;
    graphics->mTransY = v23;
    Color v39 = {143, 67, 27, 255};
    TodDrawStringWrappedHelper(graphics, (int *)&almanacDialog->mDescriptionString, &almanacDialog->mDescriptionRect, *Sexy_FONT_BRIANNETOD16_Addr, v39, DrawStringJustification::DS_ALIGN_LEFT, true, true);
    Sexy_Graphics_PopState(graphics);
}

void AlmanacDialog_SetupLayoutPlants(AlmanacDialog *almanacDialog, Sexy::Graphics *graphics) {
    // 修复介绍文字过长时的显示不全
    old_AlmanacDialog_SetupLayoutPlants(almanacDialog, graphics);
    if (almanacDialog->unk2[1] > 398) {
        // 文字过长
        almanacDialog->unk2[1] *= 1.15;
        Sexy_ScrollbarWidget_SetMaxValue(almanacDialog->mScrollTextView, 115);
    } else {
        Sexy_ScrollbarWidget_SetMaxValue(almanacDialog->mScrollTextView, 100);
    }
}
