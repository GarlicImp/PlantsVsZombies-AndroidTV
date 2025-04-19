#include "PvZ/Lawn/GridItem.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/Challenge.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/ZenGarden.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/GamepadControls.h"

#include <numbers>

void GridItem_DrawScaryPot(GridItem *scaryPot, Sexy::Graphics *graphics) {
    // 修复路灯花照透罐子

    int theCelCol = scaryPot->mGridItemState - 3;
    int thePixelX = Board_GridToPixelX(scaryPot->mBoard, scaryPot->mGridX, scaryPot->mGridY) - 5;
    int thePixelY = Board_GridToPixelY(scaryPot->mBoard, scaryPot->mGridX, scaryPot->mGridY) - 15;
    TodDrawImageCelCenterScaledF(graphics, *Sexy_IMAGE_PLANTSHADOW2_Addr, thePixelX - 5.0, thePixelY + 72.0, 0, 1.3, 1.3);

    if (scaryPot->mTransparentCounter > 0) { // 如果罐子要被照透(透明度不为0)
        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SCARY_POT_Addr, thePixelX, thePixelY, theCelCol, 0);
        Sexy::Graphics newGraphics;
        Sexy_Graphics_Graphics(&newGraphics, graphics);
        ScaryPotType mScaryPotType = scaryPot->mScaryPotType;
        if (mScaryPotType == ScaryPotType::SCARYPOT_SEED) {
            newGraphics.mScaleX = 0.7f;
            newGraphics.mScaleY = 0.7f;
            DrawSeedPacket(&newGraphics, thePixelX + 23, thePixelY + 33, scaryPot->mSeedType, SeedType::SEED_NONE, 0.0, 255, false, false, false, true);
        } else if (mScaryPotType == ScaryPotType::SCARYPOT_ZOMBIE) {
            newGraphics.mScaleX = 0.4f;
            newGraphics.mScaleY = 0.4f;
            float theOffsetX = 6.0;
            float theOffsetY = 19.0;
            if (scaryPot->mZombieType == ZombieType::ZOMBIE_FOOTBALL) {
                theOffsetX = 1.0;
                theOffsetY = 16.0;
            } else if (scaryPot->mZombieType == ZombieType::ZOMBIE_GARGANTUAR) {
                theOffsetX = 15.0;
                theOffsetY = 26.0;
                newGraphics.mScaleX = 0.3f;
                newGraphics.mScaleY = 0.3f;
            }
            ReanimatorCache_DrawCachedZombie(scaryPot->mApp->mReanimatorCache, &newGraphics, theOffsetX + thePixelX, theOffsetY + thePixelY, scaryPot->mZombieType);
        } else if (mScaryPotType == ScaryPotType::SCARYPOT_SUN) {
            int theSunCount = Challenge_ScaryPotterCountSunInPot(scaryPot->mBoard->mChallenge, scaryPot);
            Reanimation newReanim;
            Reanimation_Reanimation(&newReanim);
            Reanimation_ReanimationInitializeType(&newReanim, 0.0, 0.0, ReanimationType::REANIM_SUN);
            Reanimation_OverrideScale(&newReanim, 0.5f, 0.5f);
            Reanimation_Update(&newReanim);                                                              // 一次Update是必要的，否则绘制出来是Empty
            newReanim.mFrameStart = (scaryPot->mBoard->mMainCounter / 10) % (newReanim.mFrameCount - 1); // 这行代码可让阳光动起来
            for (int i = 0; i < theSunCount; i++) {
                float theOffsetX = 42.0f;
                float theOffsetY = 62.0f;
                switch (i) {
                    case 1:
                        theOffsetX += 3.0f;
                        theOffsetY += -20.0f;
                        break;
                    case 2:
                        theOffsetX += -6.0f;
                        theOffsetY += -10.0f;
                        break;
                    case 3:
                        theOffsetX += 6.0f;
                        theOffsetY += -5.0f;
                        break;
                    case 4:
                        theOffsetX += 5.0f;
                        break;
                }
                Reanimation_SetPosition(&newReanim, thePixelX + theOffsetX, thePixelY + theOffsetY);
                Reanimation_Draw(&newReanim, graphics);
            }
            Reanimation_Delete2(&newReanim);
        }
        int theAlpha = TodAnimateCurve(0, 50, scaryPot->mTransparentCounter, 255, 58, TodCurves::CURVE_LINEAR);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        Color theColor = {255, 255, 255, theAlpha};
        Sexy_Graphics_SetColor(graphics, &theColor);
        Sexy_Graphics_Delete2(&newGraphics);
    }

    Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SCARY_POT_Addr, thePixelX, thePixelY, theCelCol, 1);
    if (scaryPot->mHighlighted) {
        Sexy_Graphics_SetDrawMode(graphics, DrawMode::DRAWMODE_ADDITIVE);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        if (scaryPot->mTransparentCounter == 0) {
            Color theColor = {255, 255, 255, 196};
            Sexy_Graphics_SetColor(graphics, &theColor);
        }
        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SCARY_POT_Addr, thePixelX, thePixelY, theCelCol, 1);
        Sexy_Graphics_SetDrawMode(graphics, DrawMode::DRAWMODE_NORMAL);
    }
    return Sexy_Graphics_SetColorizeImages(graphics, false);
}

void GridItem_Update(GridItem *a1) {
    if (requestPause) {
        return; // 高级暂停
    }
    old_GridItem_Update(a1);
}

void GridItem_UpdateScaryPot(GridItem *scaryPot) {
    old_GridItem_UpdateScaryPot(scaryPot);
    if (transparentVase) { // 如果玩家开启“罐子透视”
        if (scaryPot->mTransparentCounter < 50) {
            // 透明度如果小于50，则为透明度加2
            scaryPot->mTransparentCounter += 2;
        }
    }
}

void GridItem_DrawStinky(GridItem *mStinky, Sexy::Graphics *graphics) {
    // 在玩家选取巧克力时，高亮显示光标下方且没喂巧克力的Stinky。
    // 从而修复Stinky无法在醒着时喂巧克力、修复Stinky在喂过巧克力后还能继续喂巧克力。
    // 因为游戏通过Stinky是否高亮来判断是否能喂Stinky。这个机制是为鼠标操作而生，但渡维不加改动地将其用于按键操作，导致无法在Stinky醒着时喂它。
    Board *board = mStinky->mBoard;
    GamepadControls *gamePad = board->mGamepadControls1;
    int mCursorX = gamePad->mCursorPositionX;
    int mCursorY = gamePad->mCursorPositionY;
    int mCursorGridX = Board_PixelToGridX(board, mCursorX, mCursorY);
    int mCursorGridY = Board_PixelToGridY(board, mCursorX, mCursorY);
    float mStinkyX = mStinky->mPosX;
    float mStinkyY = mStinky->mPosY;
    int mStinkyGridX = Board_PixelToGridX(board, mStinkyX, mStinkyY);
    int mStinkyGridY = Board_PixelToGridY(board, mStinkyX, mStinkyY);
    if (mStinkyGridX != mCursorGridX || mStinkyGridY != mCursorGridY) {
        // 如果Stinky不在光标位置处，则取消高亮。
        mStinky->mHighlighted = false;
        return old_GridItem_DrawStinky(mStinky, graphics);
    }
    // 如果Stinky在光标位置处
    CursorObject *cursorObject = board->mCursorObject1;
    CursorType mCursorType = cursorObject->mCursorType;
    if (mCursorType == CursorType::CURSOR_TYPE_CHOCOLATE) {
        // 如果光标类型为巧克力
        bool isStinkyHighOnChocolate = ZenGarden_IsStinkyHighOnChocolate(mStinky->mApp->mZenGarden);
        mStinky->mHighlighted = !isStinkyHighOnChocolate; // 为没喂巧克力的Stinky加入高亮效果
    }
    return old_GridItem_DrawStinky(mStinky, graphics);
}

void GridItem_DrawSquirrel(GridItem *squirrel, Sexy::Graphics *graphics) {
    // 绘制松鼠
    float mSquirrelX = Board_GridToPixelX(squirrel->mBoard, squirrel->mGridX, squirrel->mGridY);
    float mSquirrelY = Board_GridToPixelY(squirrel->mBoard, squirrel->mGridX, squirrel->mGridY);
    switch (squirrel->mGridItemState) {
        case GridItemState::GRIDITEM_STATE_SQUIRREL_PEEKING:
            mSquirrelY += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, 0, -40.0f, TodCurves::CURVE_BOUNCE_SLOW_MIDDLE);
            break;
        case GridItemState::GRIDITEM_STATE_SQUIRREL_RUNNING_UP:
            mSquirrelY += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, 100, 0.0f, TodCurves::CURVE_EASE_IN);
            break;
        case GridItemState::GRIDITEM_STATE_SQUIRREL_RUNNING_DOWN:
            mSquirrelY += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, -100, 0.0f, TodCurves::CURVE_EASE_IN);
            break;
        case GridItemState::GRIDITEM_STATE_SQUIRREL_RUNNING_LEFT:
            mSquirrelX += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, 80, 0.0f, TodCurves::CURVE_EASE_IN);
            break;
        case GridItemState::GRIDITEM_STATE_SQUIRREL_RUNNING_RIGHT:
            mSquirrelX += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, -80, 0.0f, TodCurves::CURVE_EASE_IN);
            break;
    }
    Sexy_Graphics_DrawImage(graphics, addonImages.squirrel, mSquirrelX, mSquirrelY);
}

void GridItem_DrawCrater(GridItem *squirrel, Sexy::Graphics *graphics) {
    // 绘制屋顶月夜弹坑
    float num = Board_GridToPixelX(squirrel->mBoard, squirrel->mGridX, squirrel->mGridY) - 8.0f;
    float num2 = Board_GridToPixelY(squirrel->mBoard, squirrel->mGridX, squirrel->mGridY) + 40.0f;
    if (squirrel->mGridItemCounter < 25) {
        int theAlpha = TodAnimateCurve(25, 0, squirrel->mGridItemCounter, 255, 0, TodCurves::CURVE_LINEAR);
        Color color = {255, 255, 255, theAlpha};
        Sexy_Graphics_SetColor(graphics, &color);
        Sexy_Graphics_SetColorizeImages(graphics, true);
    }
    bool flag = squirrel->mGridItemCounter < 9000;
    Sexy::Image *theImageStrip = *Sexy_IMAGE_CRATER_Addr;
    int theCelCol = 0;
    if (Board_IsPoolSquare(squirrel->mBoard, squirrel->mGridX, squirrel->mGridY)) {
        if (Board_StageIsNight(squirrel->mBoard)) {
            theImageStrip = *Sexy_IMAGE_CRATER_WATER_NIGHT_Addr;
        } else {
            theImageStrip = *Sexy_IMAGE_CRATER_WATER_DAY_Addr;
        }
        if (flag) {
            theCelCol = 1;
        }
        float num3 = squirrel->mGridY * std::numbers::pi_v<float> + squirrel->mGridX * std::numbers::pi_v<float> * 0.25f;
        float num4 = squirrel->mBoard->mMainCounter * std::numbers::pi_v<float> * 2.0f / 200.0f;
        float num5 = sin(num3 + num4) * 2.0f;
        num2 += num5;
    } else if (Board_StageHasRoof(squirrel->mBoard)) {
        if (squirrel->mGridX < 5) {
            if (Board_StageIsNight(squirrel->mBoard)) {
                theImageStrip = addonImages.crater_night_roof_left;
            } else {
                theImageStrip = *Sexy_IMAGE_CRATER_ROOF_LEFT_Addr;
            }
            num += 16.0f;
            num2 += -16.0f;
        } else {
            if (Board_StageIsNight(squirrel->mBoard)) {
                theImageStrip = addonImages.crater_night_roof_center;
            } else {
                theImageStrip = *Sexy_IMAGE_CRATER_ROOF_CENTER_Addr;
            }
            num += 18.0f;
            num2 += -9.0f;
        }
        if (flag) {
            theCelCol = 1;
        }
    } else if (Board_StageIsNight(squirrel->mBoard)) {
        theCelCol = 1;
        if (flag) {
            theImageStrip = *Sexy_IMAGE_CRATER_FADING_Addr;
        }
    } else if (flag) {
        theImageStrip = *Sexy_IMAGE_CRATER_FADING_Addr;
    }
    TodDrawImageCelF(graphics, theImageStrip, num, num2, theCelCol, 0);
    Sexy_Graphics_SetColorizeImages(graphics, false);
}
