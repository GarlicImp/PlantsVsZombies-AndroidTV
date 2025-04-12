#include "PvZ/Lawn/Plant.h"
#include "PvZ/Symbols.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/Challenge.h"
#include "PvZ/Lawn/CutScene.h"
#include "PvZ/Lawn/GamepadControls.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/MagicAddr.h"
#include "PvZ/Lawn/GridItem.h"

#include <algorithm>

void Plant_DrawSeedType(Sexy::Graphics *graphics, SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType, DrawVariation::DrawVariation drawVariation, float thePosX, float thePosY) {
    // 用于绘制卡槽内的模仿者SeedPacket变白效果、模仿者变身后的植物被压扁的白色效果、模仿者变身前被压扁后绘制模仿者自己而非变身后的植物。
    int v38 = ((int *)graphics)[9];
    int v10 = ((int *)graphics)[8];
    int v11 = ((int *)graphics)[4];
    int v39 = ((int *)graphics)[10];
    int v12 = ((int *)graphics)[5];
    int v13 = ((int *)graphics)[6];
    int v40 = ((int *)graphics)[11];
    int v14 = ((int *)graphics)[7];
    int v15 = ((int *)graphics)[2];
    int v16 = ((int *)graphics)[3];
    int *theColor = Sexy_Graphics_GetColor(graphics);
    int v18 = theColor[1];
    int v19 = theColor[2];
    int v20 = theColor[3];
    Color color;
    color.mRed = *theColor;
    color.mGreen = v18;
    color.mBlue = v19;
    color.mAlpha = v20;
    bool ColorizeImages = Sexy_Graphics_GetColorizeImages(graphics);
    SeedType::SeedType theSeedType2 = theSeedType;

    if ((theSeedType == theImitaterType && theImitaterType != SeedType::None) ||    // seedPacket中的灰色模仿者卡片在冷却完成后
        (theImitaterType == SeedType::Imitater && theSeedType != SeedType::None)) { // 模仿者变身之后的植物被压扁
        switch (theSeedType2) {
            case SeedType::Potatomine:
            case SeedType::Hypnoshroom:
            case SeedType::Lilypad:
            case SeedType::SEED_SQUASH:
            case SeedType::Garlic:
                drawVariation = DrawVariation::ImitaterLess;
                break;
            case SeedType::Imitater:
                drawVariation = DrawVariation::Normal;
                break;
            default:
                drawVariation = DrawVariation::Imitater;
                break;
        }
    }
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    float v24, v25;
    if (lawnApp->mGameMode == GameMode::ChallengeBigTime && (theSeedType2 == SeedType::Sunflower || theSeedType2 == SeedType::Wallnut || theSeedType2 == SeedType::Marigold)) {
        v24 = -40.0;
        v25 = -20.0;
        graphics->mScaleX = graphics->mScaleX * 1.5;
        graphics->mScaleY = graphics->mScaleY * 1.5;
    } else {
        v24 = 0.0;
        v25 = 0.0;
    }
    if (theSeedType2 == SeedType::Leftpeater) {
        v25 = v25 + graphics->mScaleX * 80.0;
        graphics->mScaleX = -graphics->mScaleX;
    }
    if (Challenge_IsZombieSeedType(theSeedType2)) {
        ZombieType theZombieType = Challenge_IZombieSeedTypeToZombieType(theSeedType2);
        if (theZombieType != ZombieType::ZOMBIE_INVALID) {
            ReanimatorCache_DrawCachedZombie(lawnApp->mReanimatorCache, graphics, thePosX, thePosY, theZombieType);
        }
        return;
    } else {
        PlantDefinition plantDefinition = GetPlantDefinition(theSeedType2);
        if (theSeedType2 == SeedType::GiantWallnut) {
            graphics->mScaleX = graphics->mScaleX * 1.4;
            graphics->mScaleY = graphics->mScaleY * 1.4;
            TodDrawImageScaledF(graphics, *Sexy_IMAGE_REANIM_WALLNUT_BODY_Addr, thePosX - 53.0, thePosY - 56.0, graphics->mScaleX, graphics->mScaleY);
        } else if (plantDefinition.mReanimationType == -1) {
            int v29;
            if (theSeedType2 == SeedType::Kernelpult)
                v29 = 2;
            else
                v29 = theSeedType2 == SeedType::Twinsunflower;

            Sexy::Image *Image = Plant_GetImage(theSeedType2);
            int v31 = Image->mNumCols;
            int v32;
            if (v31 > 2)
                v32 = 2;
            else
                v32 = v31 - 1;
            TodDrawImageCelScaledF(graphics, Image, v25 + thePosX, v24 + thePosY, v32, v29, graphics->mScaleX, graphics->mScaleY);
        } else {
            ReanimatorCache_DrawCachedPlant(lawnApp->mReanimatorCache, graphics, v25 + thePosX, v24 + thePosY, theSeedType2, drawVariation);
        }
    }
    ((int *)graphics)[8] = v10;
    ((int *)graphics)[4] = v11;
    ((int *)graphics)[9] = v38;
    ((int *)graphics)[5] = v12;
    ((int *)graphics)[6] = v13;
    ((int *)graphics)[10] = v39;
    ((int *)graphics)[7] = v14;
    ((int *)graphics)[2] = v15;
    ((int *)graphics)[11] = v40;
    ((int *)graphics)[3] = v16;
    Sexy_Graphics_SetColor(graphics, &color);
    Sexy_Graphics_SetColorizeImages(graphics, ColorizeImages);
}

bool Plant::IsInPlay()
{
    return IsOnBoard() && mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN && mApp->mGameMode != GameMode::GAMEMODE_TREE_OF_WISDOM;
}

void Plant::Draw(Sexy::Graphics *g) {
    // 根据玩家的“植物显血”功能是否开启，决定是否在游戏的原始old_Plant_Draw函数执行完后额外绘制血量文本。

    Sexy_Graphics_SetDrawMode(g, DrawMode::DRAWMODE_NORMAL);
    int theCelRow = 0;
    float num = 0.0f;
    float num2 = PlantDrawHeightOffset(mBoard, 0, mSeedType, mPlantCol, mRow);
    if (Plant_IsFlying(mSeedType) && mSquished) {
        num2 += 30.0f;
    }
    int theCelCol = mFrame;
    Sexy::Image *image = Plant_GetImage(mSeedType);
    if (mSquished) {
        if (mSeedType == SeedType::Flowerpot) {
            num2 -= 15.0f;
        }
        if (mSeedType == SeedType::InstantCoffee) {
            num2 -= 20.0f;
        }
        float ratioSquished = 0.5f;
        Sexy_Graphics_SetScale(g, 1.0f, ratioSquished, 0.0f, 0.0f);
        Sexy_Graphics_SetColorizeImages(g, true);
        Color color = {255, 255, 255, (int)(255.0f * std::min(1.0f, mDisappearCountdown / 100.0f))};
        Sexy_Graphics_SetColor(g, &color);
        Plant_DrawSeedType(g, mSeedType, mImitaterType, DrawVariation::Normal, num, num2 + 85.0f * (1 - ratioSquished));
        Sexy_Graphics_SetScale(g, 1.0f, 1.0f, 0.0f, 0.0f);
        Sexy_Graphics_SetColorizeImages(g, false);
        return;
    }
    bool flag = false;
    Plant *thePlant = nullptr;
    if (IsOnBoard()) {
        thePlant = Board_GetPumpkinAt(mBoard, mPlantCol, mRow);
        if (thePlant != nullptr) {
            Plant *plant2 = Board_GetTopPlantAt(mBoard, mPlantCol, mRow, TopPlant::OnlyNormalPosition);
            if (plant2 != nullptr && plant2->mRenderOrder > thePlant->mRenderOrder) {
                plant2 = nullptr;
            }
            if (plant2 != nullptr && plant2->mOnBungeeState == PlantOnBungeeState::GETTING_GRABBED_BY_BUNGEE) {
                plant2 = nullptr;
            }
            if (plant2 == this) {
                flag = true;
            }
            if (plant2 == nullptr && mSeedType == SeedType::Pumpkinshell) {
                flag = true;
            }
        } else if (mSeedType == SeedType::Pumpkinshell) {
            flag = true;
            thePlant = this;
        }
    } else if (mSeedType == SeedType::Pumpkinshell) {
        flag = true;
        thePlant = this;
    }

    Plant_DrawShadow(this, g, num, num2);

    if (Plant_IsFlying(mSeedType)) {
        int num3;
        if (IsOnBoard()) {
            num3 = mBoard->mMainCounter;
        } else {
            num3 = mApp->mAppCounter;
        }
        float num4 = (num3 + mRow * 97 + mPlantCol * 61) * 0.03f;
        float num5 = sin(num4) * 2.0f;
        num2 += num5;
    }
    if (flag) {
        Reanimation *reanimation = LawnApp_ReanimationGet(mApp, thePlant->mBodyReanimID);
        Sexy::Graphics newGraphics;
        Sexy_Graphics_Graphics(&newGraphics, g);
        newGraphics.mTransX += thePlant->mX - mX;
        newGraphics.mTransY += thePlant->mY - mY;
        Reanimation_DrawRenderGroup(reanimation, &newGraphics, 1);
        Sexy_Graphics_Delete2(&newGraphics);
    }
    num += mShakeOffsetX;
    num2 += mShakeOffsetY;
    if (IsInPlay() && LawnApp_IsIZombieLevel(mApp)) {
        Challenge_IZombieDrawPlant(mBoard->mChallenge, g, this);
    } else if (mBodyReanimID != 0) {
        Reanimation *reanimation2 = LawnApp_ReanimationTryToGet(mApp, mBodyReanimID);
        if (reanimation2 != nullptr) {
            //            if (plant->mGloveGrabbed)
            //            {
            //                Sexy_Graphics_SetColorizeImages(g,true);
            //                Color color = {150, 255, 150, 255};
            //                Sexy_Graphics_SetColor(g,&color);
            //            }
            Reanimation_DrawRenderGroup(reanimation2, g, 0);
            //            if (plant->mGloveGrabbed)
            //            {
            //                Sexy_Graphics_SetColorizeImages(g,false);
            //            }
        }
    } else {
        SeedType::SeedType seedType = SeedType::None;
        SeedType::SeedType seedType2 = SeedType::None;
        if (mBoard != nullptr) {
            seedType = Board_GetSeedTypeInCursor(mBoard, 0);
            seedType2 = Board_GetSeedTypeInCursor(mBoard, 1);
        }
        if ((Plant_IsPartOfUpgradableTo(this, seedType) && Board_CanPlantAt(mBoard, mPlantCol, mRow, seedType) == PlantingReason::Ok)
            || (Plant_IsPartOfUpgradableTo(this, seedType2) && Board_CanPlantAt(mBoard, mPlantCol, mRow, seedType2) == PlantingReason::Ok)) {
            Sexy_Graphics_SetColorizeImages(g, true);
            Color color;
            GetFlashingColor(&color, mBoard->mMainCounter, 90);
            Sexy_Graphics_SetColor(g, &color);
        } else if ((seedType == SeedType::Cobcannon && Board_CanPlantAt(mBoard, mPlantCol - 1, mRow, seedType) == PlantingReason::Ok)
                   || (seedType2 == SeedType::Cobcannon && Board_CanPlantAt(mBoard, mPlantCol - 1, mRow, seedType2) == PlantingReason::Ok)) {
            Sexy_Graphics_SetColorizeImages(g, true);
            Color color;
            GetFlashingColor(&color, mBoard->mMainCounter, 90);
            Sexy_Graphics_SetColor(g, &color);
        } else if (mBoard != nullptr && mBoard->mTutorialState == TutorialState::ShovelDig) {
            Sexy_Graphics_SetColorizeImages(g, true);
            Color color;
            GetFlashingColor(&color, mBoard->mMainCounter, 90);
            Sexy_Graphics_SetColor(g, &color);
        }
        if (image != nullptr) {
            TodDrawImageCelF(g, image, num, num2, theCelCol, theCelRow);
        }
        //        if (mSeedType == SeedType::Sprout)
        //        {
        //            if (plant->mGloveGrabbed)
        //            {
        //                Sexy_Graphics_SetColorizeImages(g,true);
        //                Color color ={150, 255, 150, 255};
        //                Sexy_Graphics_SetColor(g, &color);
        //            }
        //            TodDrawImageCelF(g, AtlasResources.IMAGE_CACHED_MARIGOLD, Constants.ZenGarden_Marigold_Sprout_Offset.X, Constants.ZenGarden_Marigold_Sprout_Offset.Y, 0, 0);
        //            if (plant->mGloveGrabbed)
        //            {
        //                Sexy_Graphics_SetColorizeImages(g,false);
        //            }
        //        }
        Sexy_Graphics_SetColorizeImages(g, false);
        if (mHighlighted) {
            Sexy_Graphics_SetDrawMode(g, DrawMode::DRAWMODE_ADDITIVE);
            Sexy_Graphics_SetColorizeImages(g, true);
            Color color = {255, 255, 255, 196};
            Sexy_Graphics_SetColor(g, &color);
            if (image != nullptr) {
                TodDrawImageCelF(g, image, num, num2, theCelCol, theCelRow);
            }
            Sexy_Graphics_SetDrawMode(g, DrawMode::DRAWMODE_NORMAL);
            Sexy_Graphics_SetColorizeImages(g, false);
        } else if (mEatenFlashCountdown > 0) {
            Sexy_Graphics_SetDrawMode(g, DrawMode::DRAWMODE_ADDITIVE);
            Sexy_Graphics_SetColorizeImages(g, true);
            int theAlpha = std::clamp(mEatenFlashCountdown * 3, 0, 255);
            Color color = {255, 255, 255, theAlpha};
            Sexy_Graphics_SetColor(g, &color);
            if (image != nullptr) {
                TodDrawImageCelF(g, image, num, num2, theCelCol, theCelRow);
            }
            Sexy_Graphics_SetDrawMode(g, DrawMode::DRAWMODE_NORMAL);
            Sexy_Graphics_SetColorizeImages(g, false);
        }
    }
    if (mSeedType == SeedType::Magnetshroom && !Plant_DrawMagnetItemsOnTop(this)) {
        Plant_DrawMagnetItems(this, g);
    }


    if (showPlantHealth
        || (showNutGarlicSpikeHealth
            && (mSeedType == SeedType::Wallnut || mSeedType == SeedType::Tallnut || mSeedType == SeedType::Pumpkinshell || mSeedType == SeedType::Garlic
                || mSeedType == SeedType::Spikerock))) { // 如果玩家开了 植物显血
        int holder[1];
        Sexy_StrFormat(holder, "%d/%d", mPlantHealth, mPlantMaxHealth);
        Sexy_Graphics_SetFont(g, *Sexy_FONT_DWARVENTODCRAFT12_Addr);
        if (mSeedType == SeedType::Pumpkinshell) {
            Sexy_Graphics_SetColor(g, &yellow);
            Sexy_Graphics_DrawString(g, holder, 0, 52);
        } else if (mSeedType == SeedType::Flowerpot) {
            Sexy_Graphics_SetColor(g, &brown);
            Sexy_Graphics_DrawString(g, holder, 0, 93);
        } else if (mSeedType == SeedType::Lilypad) {
            Sexy_Graphics_SetColor(g, &green);
            Sexy_Graphics_DrawString(g, holder, 0, 100);
        } else if (mSeedType == SeedType::Cobcannon) {
            Sexy_Graphics_SetColor(g, &white);
            Sexy_Graphics_DrawString(g, holder, 40, 34);
        } else {
            Sexy_Graphics_SetColor(g, &white);
            Sexy_Graphics_DrawString(g, holder, 0, 34);
        }
        Sexy_String_Delete(holder);
        Sexy_Graphics_SetFont(g, nullptr);
    }
}

int Plant::GetRefreshTime(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType) {
    if (seedPacketFastCoolDown) {
        return 0;
    }
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
        int refreshTime;
        if (theSeedType == SeedType::Imitater && theImitaterType != SeedType::None) {
            theSeedType = theImitaterType;
        }
        if (Challenge_IsMPSeedType(theSeedType)) {
            switch (theSeedType) {
                case SeedType::ZombieTrashBin:
                case SeedType::ZombieTrafficCone:
                case SeedType::ZombiePolevaulter:
                case SeedType::ZombiePail:
                case SeedType::ZombieFlag:
                case SeedType::ZombieFootball:
                case SeedType::ZombieDancer:
                case SeedType::ZombieJackInTheBox:
                case SeedType::ZombieDigger:
                case SeedType::ZombieBungee:
                case SeedType::ZombieLadder:
                case SeedType::ZombieBalloon:
                    refreshTime = 3000;
                    break;
                case SeedType::ZombieNewsPaper:
                case SeedType::ZombieScreenDoor:
                    refreshTime = 1500;
                    break;
                case SeedType::Zomboni:
                case SeedType::ZombiePogo:
                case SeedType::ZombieCatapult:
                case SeedType::ZombieGargantuar:
                    refreshTime = 6000;
                    break;
                default:
                    refreshTime = 750;
                    break;
            }
        } else {
            switch (theSeedType) {
                case SeedType::Cherrybomb:
                case SeedType::Iceshroom:
                case SeedType::Doomshroom:
                case SeedType::Jalapeno:
                    refreshTime = 6000;
                    break;
                case SeedType::Gravebuster:
                case SeedType::SEED_SQUASH:
                    refreshTime = 3000;
                    break;
                case SeedType::Threepeater:
                case SeedType::Starfruit:
                case SeedType::Melonpult:
                    refreshTime = 1500;
                    break;
                default:
                    refreshTime = GetPlantDefinition(theSeedType).mRefreshTime;
                    break;
            }
        }
        if (Challenge_IsMPSuddenDeath(lawnApp->mBoard->mChallenge) && *Challenge_gVSSuddenDeathMode_Addr == 1) {
            if (theSeedType == SeedType::ZombieTombsTone || theSeedType == SeedType::Sunflower || theSeedType == SeedType::Tallnut || theSeedType == SeedType::Wallnut
                || theSeedType == SeedType::ZombieScreenDoor || theSeedType == SeedType::Pumpkinshell || theSeedType == SeedType::ZombieTrashBin) {
                return refreshTime;
            }
            refreshTime /= 3;
        }
        return refreshTime;
    }
    return old_Plant_GetRefreshTime(this, theSeedType, theImitaterType);
}


int Plant_GetCost(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType) {
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
        if (theSeedType == SeedType::Imitater && theImitaterType != SeedType::None) {
            theSeedType = theImitaterType;
        }
        switch (theSeedType) {
            case SeedType::Cherrybomb:
            case SeedType::Snowpea:
            case SeedType::Repeater:
            case SeedType::ZombieFootball:
            case SeedType::ZombieDancer:
            case SeedType::ZombieDigger:
            case SeedType::ZombieLadder:
                return 150;
            case SeedType::SEED_SQUASH:
            case SeedType::Garlic:
            case SeedType::ZombieTrafficCone:
                return 75;
            case SeedType::Threepeater:
            case SeedType::ZombieCatapult:
                return 200;
            case SeedType::Jalapeno:
            case SeedType::Torchwood:
            case SeedType::ZombieBungee:
            case SeedType::ZombieSnorkel:
                return 125;
            case SeedType::Cactus:
            case SeedType::Cabbagepult:
            case SeedType::Kernelpult:
            case SeedType::ZombiePolevaulter:
            case SeedType::ZombiePail:
            case SeedType::ZombieScreenDoor:
            case SeedType::ZombieJackInTheBox:
            case SeedType::ZombieDuckyTube:
                return 100;
            case SeedType::Starfruit:
            case SeedType::Zomboni:
                return 175;
            case SeedType::InstantCoffee:
            case SeedType::ZombieNormal:
                return 25;
            case SeedType::Melonpult:
            case SeedType::ZombieFlag:
            case SeedType::ZombieBalloon:
                return 300;
            case SeedType::ZombieTombsTone:
            case SeedType::ZombieTrashBin:
            case SeedType::ZombieNewsPaper:
            case SeedType::ZombieImp:
                return 50;
            case SeedType::ZombiePogo:
                return 225;
            case SeedType::ZombieGargantuar:
            case SeedType::ZombieDolphinRider:
                return 250;
            default:
                return GetPlantDefinition(theSeedType).mSeedCost;
        }
    }
    return old_Plant_GetCost(theSeedType, theImitaterType);
}

bool Plant::IsOnBoard()
{
    if (!mIsOnBoard)
        return false;

    return true;
}

void Plant::Update() {
    // 用于修复植物受击闪光、生产发光、铲子下方植物发光，同时实现技能无冷却

    if (abilityFastCoolDown && mSeedType != SeedType::Spikeweed && mSeedType != SeedType::Spikerock) { // 修复地刺和地刺王开启技能无冷却后不攻击敌人
        if (mStateCountdown > 10) {
            mStateCountdown = 10;
        }
    }

    int mHighLightCounter = mEatenFlashCountdown;
    int cancelHighLightLimit = 999 - (speedUpMode > 0 ? 10 : 0); // 铲子的发光计数是1000。这段代码用于在铲子移走之后的1ms内取消植物发光
    if (mHighLightCounter >= 900 && mHighLightCounter <= cancelHighLightLimit) {
        mBeghouledFlashCountdown = 0;
        mEatenFlashCountdown = 0;
    } else if (mHighLightCounter > 0) {
        mBeghouledFlashCountdown = mHighLightCounter > 25 ? 25 : mHighLightCounter;
    }

    GameScenes::GameScenes mGameScene = mApp->mGameScene;

    if ((!IsOnBoard() || mGameScene != GameScenes::LevelIntro || !LawnApp_IsWallnutBowlingLevel(mApp)) && (!IsOnBoard() || mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN)
        && (!IsOnBoard() || !CutScene_ShouldRunUpsellBoard(mBoard->mCutScene)) && IsOnBoard() && mGameScene != GameScenes::Playing) {
        return;
    }

    if (requestPause) {
        // 如果开了高级暂停
        UpdateReanimColor();
        if (mHighLightCounter == 1000) {
            mBeghouledFlashCountdown = 0;
            mEatenFlashCountdown = 0;
        }
        return;
    }
    // 为了不影响改so，这里不是完全重写，而是执行旧函数
    //     Plant_UpdateAbilities(plant);
    //     Plant_Animate(plant);
    //     if (plant->mPlantHealth < 0)
    //         Plant_Die(plant);
    //     Plant_UpdateReanim(plant);

    old_Plant_Update(this);
}

void Plant::SetSleeping(bool theIsAsleep) {
    if (mushroomsNoSleep) {
        // 如果开启"蘑菇免唤醒"
        theIsAsleep = false;
    }
    return old_Plant_SetSleeping(this, theIsAsleep);
}

void Plant::UpdateReanimColor() {
    // 修复玩家选中但不拿起(gameState为1就是选中但不拿起，为7就是选中且拿起)某个紫卡植物时，相应的可升级绿卡植物也会闪烁的BUG。
    if (mBoard == nullptr) {
        return old_Plant_UpdateReanimColor(this);
    }
    if (!Plant_IsUpgrade(mSeedType)) {
        return old_Plant_UpdateReanimColor(this);
    }
    if (mSeedType == SeedType::ExplodeONut) {
        return old_Plant_UpdateReanimColor(this);
    }
    GamepadControls *gamePad = mBoard->mGamepadControls1;
    if (gamePad->mGamepadState != 7) {
        mSeedType = SeedType::Peashooter;
        old_Plant_UpdateReanimColor(this);
        return;
    }
    return old_Plant_UpdateReanimColor(this);
}

GridItem *Plant::FindTargetGridItem(PlantWeapon thePlantWeapon) {
    // 对战模式专用，植物索敌僵尸墓碑和靶子僵尸。
    // 原版函数BUG：植物还会索敌梯子和毁灭菇弹坑，故重写以修复BUG。
    GridItem *aGridItem = nullptr;
    GridItem *aTargetGridItem = nullptr;
    int aLastGridX = 0;
    if (mApp->mGameMode == GameMode::TwoPlayerVS) { // 如果是对战模式(关卡ID为76)
        int mRow = mStartRow;
        while (Board_IterateGridItems(mBoard, &aGridItem)) { // 遍历场上的所有GridItem

            GridItemType::GridItemType mGridItemType = aGridItem->mGridItemType;
            if (mGridItemType != GridItemType::Gravestone && mGridItemType != GridItemType::VSTargetZombie) {
                // 修复植物们攻击核坑和梯子
                continue;
            }
            int mGridX = aGridItem->mGridX;
            int mGridY = aGridItem->mGridY;
            if (mSeedType == SeedType::Threepeater ? abs(mGridY - mRow) > 1 : mGridY != mRow) {
                // 如果是三线射手，则索敌三行; 反之，索敌一行
                // 注释掉此行，就会发现投手能够命中三格内的靶子了，但会导致很多其他BUG。尚不清楚原因。
                continue;
            }


            if (aTargetGridItem == nullptr || mGridX < aLastGridX) {
                if (mSeedType == SeedType::Fumeshroom && mGridX - mPlantCol > 3) {
                    // 如果是大喷菇，则索敌三格以内的靶子或墓碑
                    continue;
                }
                if (mSeedType == SeedType::Puffshroom || mSeedType == SeedType::Seashroom) {
                    // 如果是小喷菇或水兵菇，则索敌三格以内的墓碑
                    if (mGridX - mPlantCol > 3) {
                        continue;
                    }
                    // 不主动攻击靶子
                    if (mGridItemType == GridItemType::VSTargetZombie) {
                        continue;
                    }
                }
                aTargetGridItem = aGridItem;
                aLastGridX = mGridX;
            }
        }
    }
    return aTargetGridItem;
}

void Plant::DoSpecial() {
    // 试图修复辣椒爆炸后反而在本行的末尾处产生冰道。失败。

    if (mSeedType == SeedType::Cherrybomb) {
        // 用于成就
        int num1 = Board_GetLiveZombiesCount(mBoard);
        old_Plant_DoSpecial(this);
        int num2 = Board_GetLiveZombiesCount(mBoard);
        if (num1 - num2 >= 10 && !LawnApp_IsLittleTroubleLevel(mApp)) {
            Board_GrantAchievement(mBoard, AchievementId::ACHIEVEMENT_EXPLODONATOR, true);
        }
        return;
    }
    return old_Plant_DoSpecial(this);
}

void Plant::PlantInitialize(int theGridX, int theGridY, SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType, int a6) {
    // 在初始化植物后更新一次动画，以解决开场前存在的植物只绘制阴影而不绘制植物本体的问题
    old_Plant_PlantInitialize(this, theGridX, theGridY, theSeedType, theImitaterType, a6);
    Plant_UpdateReanim(this);

    // 在对战模式修改指定植物的血量
    if (mApp->mGameMode == GameMode::TwoPlayerVS) {
        switch (theSeedType) {
            case SeedType::Sunflower:
                mPlantMaxHealth = 300;
                break;
            case SeedType::Peashooter:
                mPlantMaxHealth = 300;
                break;
        }
        mPlantHealth = mPlantMaxHealth;
    }
}


bool Plant_IsUpgrade(SeedType::SeedType theSeedType) {
    // 修复机枪射手在SeedBank光标移动到shop栏后变为绿卡。
    if (theSeedType == SeedType::Gatlingpea) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        Board *board = lawnApp->mBoard;
        if (board == nullptr) {
            return old_Plant_IsUpgrade(theSeedType); // 等价于直接return true;但方便改版修改所以返回旧函数
        }
        if (lawnApp->mSeedChooserScreen != nullptr) {
            return true;
        }
        GamepadControls *gamePad = board->mGamepadControls1;
        return !(gamePad->mGamepadState == 7 && gamePad->mIsInShopSeedBank);
    }
    return old_Plant_IsUpgrade(theSeedType);
}

void Plant_SetImitaterFilterEffect(Plant *plant) {
    SeedType::SeedType mSeedType = plant->mSeedType;
    FilterEffectType::FilterEffectType aFilterEffect = GetFilterEffectTypeBySeedType(mSeedType);
    LawnApp *lawnApp = plant->mApp;
    Reanimation *mBodyReanim = LawnApp_ReanimationTryToGet(lawnApp, plant->mBodyReanimID);
    if (mBodyReanim != nullptr)
        mBodyReanim->mFilterEffect = aFilterEffect;
    Reanimation *mHeadReanim = LawnApp_ReanimationTryToGet(lawnApp, plant->mHeadReanimID);
    if (mHeadReanim != nullptr)
        mHeadReanim->mFilterEffect = aFilterEffect;
    Reanimation *mHeadReanim2 = LawnApp_ReanimationTryToGet(lawnApp, plant->mHeadReanimID2);
    if (mHeadReanim2 != nullptr)
        mHeadReanim2->mFilterEffect = aFilterEffect;
    Reanimation *mHeadReanim3 = LawnApp_ReanimationTryToGet(lawnApp, plant->mHeadReanimID3);
    if (mHeadReanim3 != nullptr)
        mHeadReanim3->mFilterEffect = aFilterEffect;
}

// void (*old_Plant_CobCannonFire)(Plant* Plant,int x,int y);
//
// void Plant_CobCannonFire(Plant *plant, int x, int y) {
//     LOGD("fire:%d %d",x,y);
//     old_Plant_CobCannonFire(plant,x,y);
// }

bool Plant::NotOnGround() {
    if (mSeedType == SeedType::SEED_SQUASH) {
        if (mState == PlantState::STATE_SQUASH_RISING || mState == PlantState::STATE_SQUASH_FALLING || mState == PlantState::STATE_SQUASH_DONE_FALLING)
            return true;
    }

    return mSquished || mOnBungeeState == PlantOnBungeeState::RISING_WITH_BUNGEE || mDead;
}

void Plant::Die() {
    old_Plant_Die(this);
}
