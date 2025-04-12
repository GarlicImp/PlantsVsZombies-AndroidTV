#include "PvZ/Misc.h"
#include "PvZ/GlobalVariable.h"
#include "PvZ/Lawn/Board.h"
#include "PvZ/Lawn/Challenge.h"
#include "PvZ/Lawn/LawnApp.h"
#include "PvZ/Lawn/Plant.h"
#include "PvZ/Lawn/Reanimation.h"
#include "PvZ/Lawn/Zombie.h"
#include "PvZ/SexyAppFramework/Graphics.h"
#include "PvZ/Symbols.h"

#include <cassert>

#include <algorithm>
#include <random>
#include <unordered_map>

#define HIBYTE(a) ((a) >> 24)
#define BYTE2(a) ((a) >> 16 & 0xFF)
#define BYTE1(a) ((a) >> 8 & 0xFF)
#define LOBYTE(a) ((a) & 0xFF)

int randomInt(int a, int b) {
    assert(a <= b);
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    std::uniform_int_distribution distrib{a, b};
    return distrib(gen);
}

void WaitForSecondPlayerDialog_WaitForSecondPlayerDialog(int *a, int *a2) {
    // 自动跳过等待2P对话框
    old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog(a, a2);
    WaitForSecondPlayerDialog_GameButtonDown(a, 6, 1);
    WaitForSecondPlayerDialog_GameButtonDown(a, 6, 1);
}

void CustomScrollbarWidget_RemoveScrollButtons(Sexy::CustomScrollbarWidget *scrollbarWidget) {
    // 修复点击图鉴介绍文本的滚动条时闪退的问题。将Remove改为Hide，从而解决缺少mUpButton、mDownButton导致的空指针闪退。
    scrollbarWidget->mUpButton->mVisible = false;
    scrollbarWidget->mDownButton->mVisible = false;
}

void Sexy_Image_PushTransform(Sexy::Image *image, int *transform, bool concatenate) {
    old_Sexy_Image_PushTransform(image, transform, concatenate);
}

void Sexy_Image_PopTransform(Sexy::Image *image) {
    old_Sexy_Image_PopTransform(image);
}

void Sexy_GLImage_PushTransform(Sexy::Image *image, int *transform, bool concatenate) {
    old_Sexy_GLImage_PushTransform(image, transform, concatenate);
}

void Sexy_GLImage_PopTransform(Sexy::Image *image) {
    old_Sexy_GLImage_PopTransform(image);
}

void Sexy_MemoryImage_PushTransform(Sexy::Image *image, int *transform, bool concatenate) {
    old_Sexy_MemoryImage_PushTransform(image, transform, concatenate);
}

void Sexy_MemoryImage_PopTransform(Sexy::Image *image) {
    old_Sexy_MemoryImage_PopTransform(image);
}

int SexyDialog_AddedToManager(void *instance, void *instance1) {
    // 记录当前游戏状态
    return old_SexyDialog_AddedToManager(instance, instance1);
}

int SexyDialog_RemovedFromManager(void *instance, void *instance1) {
    // 记录当前游戏状态
    return old_SexyDialog_RemovedFromManager(instance, instance1);
}

void LawnMower_Update(int *lawnMover) {
    if (requestPause) {
        return;
    }
    old_LawnMower_Update(lawnMover);
}

void Sexy_String_Delete(int *holder) {
    auto my_exchange_and_add = [](int *ptr, int value) -> int {
        int original_value = *ptr;
        *ptr += value;
        return original_value;
    };

    int ptr = holder[0] - 12;
    if (my_exchange_and_add((int *)(holder[0] - 4), -1) <= 0) {
        operator delete((int *)ptr);
    }
}

void DrawSeedPacket(Sexy::Graphics *graphics,
                    float x,
                    float y,
                    SeedType::SeedType seedType,
                    SeedType::SeedType imitaterType,
                    float coolDownPercent,
                    int grayness,
                    bool drawCostText,
                    bool isInGame,
                    bool isZombieSeed,
                    bool isSeedPacketSelected) {
    // 修复选中紫卡、模仿者卡时卡片背景变为普通卡片背景

    SeedType::SeedType realSeedType = imitaterType != SeedType::None && seedType == SeedType::Imitater ? imitaterType : seedType;
    if (grayness != 255) {
        Color theColor = {grayness, grayness, grayness, 255};
        Sexy_Graphics_SetColor(graphics, &theColor);
        Sexy_Graphics_SetColorizeImages(graphics, true);
    } else if (coolDownPercent > 0.0f) {
        Color theColor = {128, 128, 128, 255};
        Sexy_Graphics_SetColor(graphics, &theColor);
        Sexy_Graphics_SetColorizeImages(graphics, true);
    }
    int celToDraw;
    if (seedType == SeedType::Imitater) {
        celToDraw = 0;
    } else if (Plant_IsUpgrade(realSeedType)) {
        celToDraw = 1;
    } else if (seedType == SeedType::BeghouledButtonCrater) {
        celToDraw = 3;
    } else if (seedType == SeedType::BeghouledButtonShuffle) {
        celToDraw = 4;
    } else if (seedType == SeedType::SlotMachineSun) {
        celToDraw = 5;
    } else if (seedType == SeedType::SlotMachineDiamond) {
        celToDraw = 6;
    } else if (seedType == SeedType::ZombiquariumSnorkel) {
        celToDraw = 7;
    } else if (seedType == SeedType::ZombiquariumTrophy) {
        celToDraw = 8;
    } else {
        celToDraw = 2;
    }

    if (isSeedPacketSelected) {
        if (graphics->mScaleX > 1.0f && seedType <= SeedType::Leftpeater) {
            // 紫卡背景BUG就是在这里修复的
            if (celToDraw == 2) {
                TodDrawImageCelScaledF(graphics, *Sexy_IMAGE_SEEDPACKET_LARGER_Addr, x, y, 0, 0, graphics->mScaleX * 0.5f, graphics->mScaleY * 0.5f);
            } else {
                TodDrawImageCelScaledF(graphics, *Sexy_IMAGE_SEEDS_Addr, x, y, celToDraw, 0, graphics->mScaleX, graphics->mScaleY);
            }
        } else if (isZombieSeed) {
            float heightOffset = graphics->mScaleX > 1.2 ? -1.5f : 0.0f;
            TodDrawImageScaledF(graphics, *Sexy_IMAGE_ZOMBIE_SEEDPACKET_Addr, x, y + heightOffset, graphics->mScaleX, graphics->mScaleY);
        } else {
            TodDrawImageCelScaledF(graphics, *Sexy_IMAGE_SEEDS_Addr, x, y, celToDraw, 0, graphics->mScaleX, graphics->mScaleY);
        }
    }
    bool isPlant = seedType < SeedType::BeghouledButtonShuffle || seedType > SeedType::ZombiquariumTrophy;
    float offsetY, offsetX, theDrawScale;
    switch (realSeedType) {
        case SeedType::Tallnut:
            offsetY = 22.0;
            offsetX = 12.0;
            theDrawScale = 0.3;
            break;
        case SeedType::InstantCoffee:
            offsetY = 9.0;
            offsetX = 0.0;
            theDrawScale = 0.55;
            break;
        case SeedType::Cobcannon:
            offsetY = 22.0;
            offsetX = 6.0;
            theDrawScale = 0.26;
            break;
        case SeedType::Cactus:
            offsetY = 13.0;
            offsetX = 9.0;
            theDrawScale = 0.5;
            break;
        case SeedType::Magnetshroom:
            offsetY = 12.0;
            offsetX = 5.0;
            theDrawScale = 0.5;
            break;
        case SeedType::Twinsunflower:
        case SeedType::Gloomshroom:
            offsetY = 14.0;
            offsetX = 7.0;
            theDrawScale = 0.45;
            break;
        case SeedType::Cattail:
            offsetY = 13.0;
            offsetX = 8.0;
            theDrawScale = 0.45;
            break;
        case SeedType::Umbrella:
            offsetY = 10.0;
            offsetX = 5.0;
            theDrawScale = 0.5;
            break;
        case SeedType::Kernelpult:
            offsetY = 14.0;
            offsetX = 13.0;
            theDrawScale = 0.4;
            break;
        case SeedType::Cabbagepult:
            offsetY = 14.0;
            offsetX = 15.0;
            theDrawScale = 0.4;
            break;
        case SeedType::Gravebuster:
            offsetY = 15.0;
            offsetX = 10.0;
            theDrawScale = 0.4;
            break;
        case SeedType::Splitpea:
            offsetY = 12.0;
            offsetX = 12.0;
            theDrawScale = 0.45;
            break;
        case SeedType::Blover:
            offsetY = 17.0;
            offsetX = 8.0;
            theDrawScale = 0.4;
            break;
        case SeedType::Starfruit:
            offsetY = 8.0;
            offsetX = 6.0;
            theDrawScale = 0.5;
            break;
        case SeedType::Threepeater:
            offsetY = 10.0;
            offsetX = 5.0;
            theDrawScale = 0.5;
            break;
        case SeedType::Gatlingpea:
            offsetY = 8.0;
            offsetX = 2.0;
            theDrawScale = 0.5;
            break;
        case SeedType::ZombiePolevaulter:
            offsetY = -12.0;
            offsetX = -8.0;
            theDrawScale = 0.35;
            break;
        case SeedType::Melonpult:
        case SeedType::Wintermelon:
            offsetY = 19.0;
            offsetX = 18.0;
            theDrawScale = 0.35;
            break;
        case SeedType::Potatomine:
        case SeedType::Fumeshroom:
        case SeedType::Tanglekelp:
        case SeedType::Pumpkinshell:
        case SeedType::Chomper:
        case SeedType::Doomshroom:
        case SeedType::SEED_SQUASH:
        case SeedType::Hypnoshroom:
        case SeedType::Spikeweed:
        case SeedType::Spikerock:
        case SeedType::Plantern:
        case SeedType::Torchwood:
            offsetY = 12.0;
            offsetX = 8.0;
            theDrawScale = 0.4;
            break;
        case SeedType::ZombieNormal:
        case SeedType::ZombieNewsPaper:
        case SeedType::ZombieFlag:
        case SeedType::ZombieTrafficCone:
        case SeedType::ZombiePail:
        case SeedType::ZombieDancer:
            offsetY = -7.0;
            offsetX = -3.0;
            theDrawScale = 0.35;
            break;
        case SeedType::ZombieLadder:
        case SeedType::ZombieDigger:
        case SeedType::ZombieScreenDoor:
        case SeedType::ZombieTrashBin:
        case SeedType::ZombiePogo:
        case SeedType::ZombieJackInTheBox:
        case SeedType::ZombieDuckyTube:
            offsetY = -10.0;
            offsetX = -3.0;
            theDrawScale = 0.35;
            break;
        case SeedType::ZombieDolphinRider:
            offsetY = -12.0;
            offsetX = -3.0;
            theDrawScale = 0.35;
            break;
        case SeedType::ZombieSnorkel:
            offsetY = -8.0;
            offsetX = -3.0;
            theDrawScale = 0.32;
            break;
        case SeedType::ZombieBungee:
            offsetY = -1.0;
            offsetX = 1.0;
            theDrawScale = 0.3;
            break;
        case SeedType::ZombieFootball:
            offsetY = -9.0;
            offsetX = -7.0;
            theDrawScale = 0.33;
            break;
        case SeedType::ZombieBalloon:
            offsetY = -5.0;
            offsetX = -3.0;
            theDrawScale = 0.35;
            break;
        case SeedType::ZombieImp:
            offsetY = -17.0;
            offsetX = -12.0;
            theDrawScale = 0.4;
            break;
        case SeedType::Zomboni:
            offsetY = 3.0;
            offsetX = -5.0;
            theDrawScale = 0.23;
            break;
        case SeedType::ZombieCatapult:
            offsetY = 3.0;
            offsetX = 1.0;
            theDrawScale = 0.23;
            break;
        case SeedType::ZombieGargantuar:
        case SeedType::ZombieUnknown:
            offsetY = 3.0;
            offsetX = 4.0;
            theDrawScale = 0.23;
            break;
        default:
            offsetY = 8.0;
            offsetX = 5.0;
            theDrawScale = 0.5;
            break;
    }
    LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
    float v28, v29;
    if (lawnApp->mGameMode == GameMode::ChallengeBigTime) {
        if (realSeedType == SeedType::Sunflower || realSeedType == SeedType::Wallnut || realSeedType == SeedType::Marigold) {
            offsetY = 34.0;
            offsetX = 16.0;
        }
    }
    v28 = offsetX * graphics->mScaleX;
    v29 = (offsetY + 1.0f) * graphics->mScaleY;
    if (realSeedType == SeedType::GiantWallnut) {
        v29 = 59.0;
        theDrawScale = theDrawScale * 0.75;
        v28 = 52.0;
    }

    if (isPlant && isSeedPacketSelected)
        DrawSeedType(graphics, x, y, realSeedType, imitaterType, v28, v29, theDrawScale);

    if (coolDownPercent > 0.0) {
        float coolDownHeight = coolDownPercent * 68.0 + 2.5;
        Sexy::Graphics newGraphics;
        Sexy_Graphics_Graphics(&newGraphics, graphics);
        Color theColor = {64, 64, 64, 255};
        Sexy_Graphics_SetColor(&newGraphics, &theColor);
        Sexy_Graphics_SetColorizeImages(&newGraphics, true);
        Sexy_Graphics_ClipRect(&newGraphics, x, y, graphics->mScaleX * 50.0f, coolDownHeight * graphics->mScaleY);
        if (isSeedPacketSelected) {
            if (Challenge_IsMPSeedType(seedType)) {
                TodDrawImageScaledF(&newGraphics, *Sexy_IMAGE_ZOMBIE_SEEDPACKET_Addr, x, y, graphics->mScaleX, graphics->mScaleY);
            } else {
                TodDrawImageCelScaledF(&newGraphics, *Sexy_IMAGE_SEEDS_Addr, x, y, celToDraw, 0, graphics->mScaleX, graphics->mScaleY);
            }
        }
        if (isPlant && isSeedPacketSelected)
            DrawSeedType(&newGraphics, x, y, seedType, imitaterType, v28, v29, theDrawScale);
        Sexy_Graphics_Delete2(&newGraphics);
    }
    if (drawCostText) {
        int tmpHolder[1];
        Board *board = lawnApp->mBoard;
        if (board != nullptr && Board_PlantUsesAcceleratedPricing(board, realSeedType)) {
            if (isInGame) {
                int CurrentPlantCost = Board_GetCurrentPlantCost(board, seedType, imitaterType);
                Sexy_StrFormat(tmpHolder, "%d", CurrentPlantCost);
            } else {
                int Cost = Plant_GetCost(seedType, imitaterType);
                Sexy_StrFormat(tmpHolder, "%d+", Cost);
            }
        } else {
            int Cost = Plant_GetCost(seedType, imitaterType);
            Sexy_StrFormat(tmpHolder, "%d", Cost);
        }
        Sexy::Font *font = *Sexy_FONT_BRIANNETOD12_Addr;
        int width = 31 - (*((int (**)(Sexy::Font *, int *))font->vTable + 8))(font, tmpHolder);
        ;                                                                      // 33  ----- >  31，微调一下文字位置，左移2个像素点
        int height = 48 + (*((int (**)(Sexy::Font *))font->vTable + 2))(font); // 50  ---- >  48, 微调一下文字位置，上移2个像素点
        Color theColor = {0, 0, 0, 255};
        Sexy_Graphics_PushState(graphics);
        if (graphics->mScaleX == 1.0 && graphics->mScaleY == 1.0) {
            TodDrawString(graphics, tmpHolder, width + x, height + y, font, theColor, DrawStringJustification::Left);
        } else {
            int matrix[25];
            Sexy_SexyMatrix3_SexyMatrix3(matrix);
            TodScaleTransformMatrix(matrix, x + graphics->mTransX + width * graphics->mScaleX, y + graphics->mTransY + height * graphics->mScaleY - 1.0, graphics->mScaleX, graphics->mScaleY);
            if (graphics->mScaleX > 1.8) {
                Sexy_Graphics_SetLinearBlend(graphics, false);
            }
            TodDrawStringMatrix(graphics, font, matrix, tmpHolder, &theColor);
            Sexy_Graphics_SetLinearBlend(graphics, true);
        }
        Sexy_Graphics_PopState(graphics);
        Sexy_String_Delete(tmpHolder);
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
}

unsigned int AverageNearByPixels(Sexy::Image *theImage, unsigned int *aPixel, int y, int x) {
    int v6;                         // edx
    unsigned int *v8;               // eax
    uint32_t *v9;                   // eax
    uint32_t *v10;                  // eax
    int mWidth;                     // ecx
    int v12;                        // eax
    int v13;                        // esi
    int v14;                        // edi
    int v15;                        // ecx
    int v17;                        // eax
    int v18;                        // ebx
    int v19;                        // eax
    int v20;                        // esi
    int v21;                        // eax
    int v22;                        // ecx
    unsigned int aPixelAdjacent[8]; // [esp+Ch] [ebp-24h] BYREF
    int v24;                        // [esp+2Ch] [ebp-4h]

    memset(&aPixelAdjacent[1], 0, 28);
    v24 = 0;
    v6 = -1;
    v8 = aPixelAdjacent;
    do {
        if (v6) {
            v9 = v8 + 1;
            if (x) {
                if (y || v6 != -1) {
                    if (y == theImage->mHeight - 1 && v6 == 1)
                        *v9 = 0;
                    else
                        *v9 = aPixel[v6 * theImage->mWidth - 1];
                } else {
                    *v9 = 0;
                }
            } else {
                *v9 = 0;
            }
            v10 = v9 + 1;
            if (y || v6 != -1) {
                if (y == theImage->mHeight - 1 && v6 == 1)
                    *v10 = 0;
                else
                    *v10 = aPixel[v6 * theImage->mWidth];
            } else {
                *v10 = 0;
            }
            mWidth = theImage->mWidth;
            v8 = v10 + 1;
            if (x == mWidth - 1) {
                *v8 = 0;
            } else if (y || v6 != -1) {
                if (y == theImage->mHeight - 1 && v6 == 1)
                    *v8 = 0;
                else
                    *v8 = aPixel[v6 * mWidth + 1];
            } else {
                *v8 = 0;
            }
        }
        ++v6;
    } while (v6 <= 1);
    v12 = 0;
    v13 = 0;
    v14 = 0;
    v15 = 0;
    if (HIBYTE(aPixelAdjacent[1])) {
        v12 = BYTE2(aPixelAdjacent[1]);
        v13 = BYTE1(aPixelAdjacent[1]);
        v14 = LOBYTE(aPixelAdjacent[1]);
        v15 = 1;
    }
    if (HIBYTE(aPixelAdjacent[2])) {
        v12 += BYTE2(aPixelAdjacent[2]);
        v13 += BYTE1(aPixelAdjacent[2]);
        v14 += LOBYTE(aPixelAdjacent[2]);
        ++v15;
    }
    if (HIBYTE(aPixelAdjacent[3])) {
        v12 += BYTE2(aPixelAdjacent[3]);
        v13 += BYTE1(aPixelAdjacent[3]);
        v14 += LOBYTE(aPixelAdjacent[3]);
        ++v15;
    }
    if (HIBYTE(aPixelAdjacent[4])) {
        v12 += BYTE2(aPixelAdjacent[4]);
        v13 += BYTE1(aPixelAdjacent[4]);
        v14 += LOBYTE(aPixelAdjacent[4]);
        ++v15;
    }
    if (HIBYTE(aPixelAdjacent[5])) {
        v12 += BYTE2(aPixelAdjacent[5]);
        v13 += BYTE1(aPixelAdjacent[5]);
        v14 += LOBYTE(aPixelAdjacent[5]);
        ++v15;
    }
    if (HIBYTE(aPixelAdjacent[6])) {
        v12 += BYTE2(aPixelAdjacent[6]);
        v13 += BYTE1(aPixelAdjacent[6]);
        v14 += LOBYTE(aPixelAdjacent[6]);
        ++v15;
    }
    if (HIBYTE(aPixelAdjacent[7])) {
        v12 += BYTE2(aPixelAdjacent[7]);
        v13 += BYTE1(aPixelAdjacent[7]);
        v14 += LOBYTE(aPixelAdjacent[7]);
        ++v15;
    }
    if (HIBYTE(v24)) {
        v12 += BYTE2(v24);
        v13 += BYTE1(v24);
        v14 += LOBYTE(v24);
        ++v15;
    }
    if (!v15)
        return 0;
    v17 = v12 / v15;
    if (v17 > 0) {
        v18 = 255;
        if (v17 < 255)
            v18 = v17;
    } else {
        v18 = 0;
    }
    v19 = v13 / v15;
    if (v13 / v15 > 0) {
        v20 = 255;
        if (v19 < 255)
            v20 = v19;
    } else {
        v20 = 0;
    }
    v21 = v14 / v15;
    if (v14 / v15 <= 0)
        return (v20 | (v18 << 8)) << 8;
    v22 = 255;
    if (v21 < 255)
        v22 = v21;
    return v22 | ((v20 | (v18 << 8)) << 8);
}

void FixPixelsOnAlphaEdgeForBlending(Sexy::Image *theImage) {
    int v3; // eax
    int i;  // ebx
    int y;  // [esp+Ch] [ebp+4h]

    unsigned int *mBits = theImage->mBits;
    if (mBits != nullptr) {
        v3 = 0;
        y = 0;
        if (theImage->mHeight > 0) {
            do {
                for (i = 0; i < theImage->mWidth; ++i) {
                    unsigned int *v6 = mBits++;
                    if (!*((uint8_t *)v6 + 3)) {
                        *v6 = AverageNearByPixels(theImage, v6, v3, i);
                        v3 = y;
                    }
                }
                y = ++v3;
            } while (v3 < theImage->mHeight);
        }
        //++theImage->mBitsChangedCount;
        Sexy_MemoryImage_BitsChanged(theImage);
    }
}

Sexy::Image *FilterEffectCreateImage(Sexy::Image *image, FilterEffectType::FilterEffectType theFilterEffect) {
    Sexy::Image *memoryImage = Sexy_SexyAppBase_CopyImage((LawnApp *)*gLawnApp_Addr, image);
    memoryImage->mWidth = image->mWidth;
    memoryImage->mHeight = image->mHeight;
    FixPixelsOnAlphaEdgeForBlending(memoryImage);
    switch (theFilterEffect) {
        case FilterEffectType::WashedOut:
            FilterEffectDoWashedOut(memoryImage);
            break;
        case FilterEffectType::LessWashedOut:
            FilterEffectDoLessWashedOut(memoryImage);
            break;
        case FilterEffectType::White:
            FilterEffectDoWhite(memoryImage);
            break;
        case FilterEffectType::Custom:
            FilterEffectDoLumSat(memoryImage, 1.05, 0.8); // 仅MainMenu显示房子雾蒙蒙效果时用到。数值是自己瞎调的
            break;
    }
    //    ++memoryImage->mBitsChangedCount;
    Sexy_MemoryImage_BitsChanged(memoryImage);
    memoryImage->mNumCols = image->mNumCols;
    memoryImage->mNumRows = image->mNumRows;
    return memoryImage;
}


static std::unordered_map<Sexy::Image *, Sexy::Image *> gFilterEffectMaps[FilterEffectType::FilterEffectCount];

Sexy::Image *FilterEffectGetImage(Sexy::Image *image, FilterEffectType::FilterEffectType mFilterEffect) {
    // 变灰的植物贴图在这里处理
    if (!imitater) {
        return image;
    }
    if (mFilterEffect == FilterEffectType::None) {
        return image;
    }
    std::unordered_map<Sexy::Image *, Sexy::Image *> &currentMap = gFilterEffectMaps[mFilterEffect];
    auto it = currentMap.find(image);
    if (it != currentMap.end()) {
        return it->second;
    } else {
        Sexy::Image *theFilterEffectImage = FilterEffectCreateImage(image, mFilterEffect);
        currentMap.emplace(image, theFilterEffectImage);
        return theFilterEffectImage;
    }
}

void FilterEffectDisposeForApp() {}

void ReanimatorCache::LoadCachedImages() {
    // 此时尚未加载AddonImages！不可在此处替换贴图们
    old_ReanimatorCache_LoadCachedImages(this);
}

void ReanimatorCache::UpdateReanimationForVariation(Reanimation *theReanim, DrawVariation::DrawVariation theDrawVariation) {
    // 修复商店花盆不显示、修复花园花盆不显示、修复花园手套和推车预览不显示。原理就是Reanimation_Update。
    old_ReanimatorCache_UpdateReanimationForVariation(this, theReanim, theDrawVariation);
    float tmp = theReanim->mAnimRate;
    //    Reanimation_SetAnimRate(theReanim, 0.0f);
    Reanimation_Update(theReanim);
    //    Reanimation_SetAnimRate(theReanim, tmp);
}

void ReanimatorCache_DrawCachedPlant(ReanimatorCache *a1, Sexy::Graphics *graphics, float thePosX, float thePosY, SeedType::SeedType theSeedType, DrawVariation::DrawVariation drawVariation) {
    if (drawVariation == DrawVariation::ImitaterLess || drawVariation == DrawVariation::Imitater || drawVariation == DrawVariation::Normal) {
        Sexy::Image *image = a1->mPlantImages[theSeedType];
        if (image == nullptr) {
            return;
        }
        if (drawVariation == DrawVariation::Imitater) {
            image = FilterEffectGetImage(image, FilterEffectType::WashedOut);
        } else if (drawVariation == DrawVariation::ImitaterLess) {
            image = FilterEffectGetImage(image, FilterEffectType::LessWashedOut);
        }
        int a, b, c, d;
        ReanimatorCache_GetPlantImageSize(a1, theSeedType, &a, &b, &c, &d);
        float xScaled = graphics->mScaleX;
        float yScaled = graphics->mScaleY;
        // 修复关闭3D加速后SeedPacket上不显示植物
        //        if (Sexy_SexyAppBase_Is3DAccelerated(a1->mApp)) {
        TodDrawImageScaledF(graphics, image, thePosX + xScaled * a, thePosY + yScaled * b, xScaled, yScaled);
        //        } else {
        //            if (xScaled == 1.0 && yScaled == 1.0) {
        //                Sexy_Graphics_DrawImage(graphics, image, thePosX + a, thePosY + b);
        //                return;
        //            }
        //        }
    } else {
        return old_ReanimatorCache_DrawCachedPlant(a1, graphics, thePosX, thePosY, theSeedType, drawVariation);
    }
}

// 为红眼巨人增加SeedPacket图标
Sexy::Image *ReanimatorCache::MakeCachedZombieFrame(ZombieType theZombieType) {

    if (theZombieType != ZombieType::ZOMBIE_REDEYE_GARGANTUAR) {
        return old_ReanimatorCache_MakeCachedZombieFrame(this, theZombieType);
    }

    Sexy_MemoryImage_Delete(mZombieImages[theZombieType]);
    mZombieImages[theZombieType] = nullptr;

    Sexy::MemoryImage *BlankCanvasImage = ReanimatorCache_MakeBlankCanvasImage(this, (theZombieType == ZombieType::ZOMBIE_ZAMBONI ? 512 : 256), 256);
    Sexy::Graphics graphics;
    Sexy_Graphics_Graphics2(&graphics, BlankCanvasImage);
    Sexy_Graphics_SetLinearBlend(&graphics, 1);
    ZombieType zombieType_reanim = theZombieType != ZombieType::ZOMBIE_CACHED_POLEVAULTER_WITH_POLE ? theZombieType : ZombieType::ZOMBIE_POLEVAULTER;
    ReanimationType reanimationType = GetZombieDefinition(zombieType_reanim).mReanimationType;
    float x = 40;
    float y = 60;
    Reanimation reanimation;
    Reanimation_Reanimation(&reanimation);
    Reanimation_ReanimationInitializeType(&reanimation, x, y, reanimationType);
    Reanimation_SetFramesForLayer(&reanimation, "anim_idle");
    Zombie_SetupReanimLayers(&reanimation, zombieType_reanim);
    Reanimation_SetImageOverride(&reanimation, "anim_head1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_Addr);
    Reanimation_Update(&reanimation);
    Reanimation_Draw(&reanimation, &graphics);
    Reanimation_Delete2(&reanimation);
    mZombieImages[theZombieType] = BlankCanvasImage;
    Sexy_Graphics_Delete2(&graphics);
    return BlankCanvasImage;
}

void DrawSeedType(Sexy::Graphics *graphics, float x, float y, SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType, float xOffset, float yOffset, float scale) {
    // 和Plant_DrawSeedType配合使用，用于绘制卡槽内的模仿者SeedPacket变白效果。
    Sexy_Graphics_PushState(graphics);
    graphics->mScaleX = graphics->mScaleX * scale;
    graphics->mScaleY = graphics->mScaleY * scale;
    if (theSeedType == SeedType::ZombieTombsTone) {
        TodDrawImageCelScaledF(graphics, *Sexy_IMAGE_MP_TOMBSTONE_Addr, x + xOffset, y + yOffset, 0, 0, graphics->mScaleX, graphics->mScaleY);
    } else {
        if (theSeedType == SeedType::Imitater && theImitaterType != SeedType::None) {
            // 卡槽内的模仿者SeedPacket卡且为冷却状态，此时需要交换theImitaterType和theSeedType。
            Plant_DrawSeedType(graphics, theImitaterType, theSeedType, DrawVariation::Normal, x + xOffset, y + yOffset);
        } else {
            Plant_DrawSeedType(graphics, theSeedType, theImitaterType, DrawVariation::Normal, x + xOffset, y + yOffset);
        }
    }
    return Sexy_Graphics_PopState(graphics);
}

void HelpBarWidget_HelpBarWidget(Sexy::Widget *a) {
    // 缩小HelpBar，以防止它挡住触控区域。
    old_HelpBarWidget_HelpBarWidget(a);
    Sexy_Widget_Resize(a, 0, 0, 0, 0);
}

bool CursorObject_BeginDraw(CursorObject *cursorObject, Sexy::Graphics *graphics) {
    return old_CursorObject_BeginDraw(cursorObject, graphics);
}

void CursorObject_EndDraw(CursorObject *cursorObject, Sexy::Graphics *graphics) {
    return old_CursorObject_EndDraw(cursorObject, graphics);
}

void Sexy_ExtractLoadingSoundsResources(int *a, int *theManager) {
    old_Sexy_ExtractLoadingSoundsResources(a, theManager);
}

void BaseGamepadControls::GetGamepadVelocity(float *horizontal, float *vertical) {
    // 如果horizontal或vertical不为零，则会在重型武器中播放小推车移动动画。
    // 所以这里将vertical设置为非零，以播放动画；同时horizontal设置为0，以免小推车移动。
    *horizontal = 0.0f;
    *vertical = mPlayerIndex == TouchPlayerIndex::None ? 0.0f : 100.0f;
}

void PoolEffect_UpdateWaterEffect(PoolEffect *poolEffect) {
    int v2;            // eax
    unsigned int v4;   // ecx
    int v5;            // ebp
    int v6;            // eax
    unsigned int *v7;  // edi
    int v8;            // esi
    int v9;            // eax
    unsigned char v10; // cl
    int y;             // [esp+10h] [ebp-14h]
    int i;             // [esp+14h] [ebp-10h]
    int v13;           // [esp+18h] [ebp-Ch]
    unsigned int v;    // [esp+1Ch] [ebp-8h]
    int v15;           // [esp+20h] [ebp-4h]

    v2 = 0;
    for (i = 0;; v2 = i) {
        v13 = (256 - v2) << 17;
        v4 = v2 << 17;
        v5 = 0;
        v6 = v2 << 9;
        v = v4;
        for (y = v6;; v6 = y) {
            v7 = (unsigned int *)((char *)poolEffect->mCausticImage->mBits + v6);
            v8 = poolEffect->mPoolCounter << 16;
            v15 = (unsigned char)PoolEffect_BilinearLookupFixedPoint(poolEffect, v5 - (((unsigned short)poolEffect->mPoolCounter + 1) << 16) / 6, v13 + v8 / 8);
            v9 = ((unsigned char)PoolEffect_BilinearLookupFixedPoint(poolEffect, v5 + v8 / 10, v) + v15) / 2;
            if ((unsigned char)v9 < 0xA0u)
                v10 = (unsigned char)v9 < 0x80u ? 0 : 5 * (v9 + 0x80);
            else
                v10 = 63 - 2 * v9;
            y += 4;
            v5 += 0x20000;
            *v7 = (*v7 & 0xFFFFFF) + ((v10 / 3) << 24);
            if (v5 >= 0x1000000)
                break;
        }
        if (++i >= 64)
            break;
    }
    Sexy_MemoryImage_BitsChanged(poolEffect->mCausticImage);
}

void PoolEffect_PoolEffectDraw(PoolEffect *poolEffect, Sexy::Graphics *graphics, bool theIsNight) {
    float v6;                     // st7
    float v7;                     // st6
    float v8;                     // st5
    int v9;                       // ebx
    float v10;                    // st4
    float v11;                    // st3
    float *v12;                   // esi
    float v13;                    // rt0
    float v14;                    // st3
    float v15;                    // rt2
    float v16;                    // st3
    int v17;                      // edi
    float v18;                    // rt2
    float v19;                    // st3
    float v20;                    // rt0
    float v21;                    // st3
    float v22;                    // st2
    float v23;                    // st6
    float v24;                    // st4
    float v25;                    // st7
    float v26;                    // st6
    float v27;                    // st5
    float v28;                    // st4
    float v29;                    // st3
    float v30;                    // rt0
    float v31;                    // st3
    float v32;                    // st3
    float v33;                    // st5
    float v34;                    // rt0
    float v35;                    // st3
    float v36;                    // rt1
    float v37;                    // st7
    float v40;                    // st5
    int v41;                      // eax
    SexyVertex2D *v42;            // esi
    char *v43;                    // ecx
    int v44;                      // edi
    int v45;                      // ebx
    float v46;                    // st4
    int v47;                      // eax
    float v48;                    // st3
    int v49;                      // edi
    int v50;                      // ecx
    int v51;                      // eax
    int v52;                      // edx
    float v53;                    // st3
    int mX;                       // ecx
    int mY;                       // eax
    float v66;                    // [esp+Ch] [ebp-72F4h]
    float v67;                    // [esp+Ch] [ebp-72F4h]
    float v68;                    // [esp+Ch] [ebp-72F4h]
    float v69;                    // [esp+Ch] [ebp-72F4h]
    float v70;                    // [esp+Ch] [ebp-72F4h]
    float v71;                    // [esp+Ch] [ebp-72F4h]
    float v72;                    // [esp+Ch] [ebp-72F4h]
    float v73;                    // [esp+Ch] [ebp-72F4h]
    float v74;                    // [esp+Ch] [ebp-72F4h]
    float v75;                    // [esp+Ch] [ebp-72F4h]
    float v76;                    // [esp+Ch] [ebp-72F4h]
    float v77;                    // [esp+Ch] [ebp-72F4h]
    float v78;                    // [esp+Ch] [ebp-72F4h]
    float v79;                    // [esp+Ch] [ebp-72F4h]
    float v80;                    // [esp+Ch] [ebp-72F4h]
    float v81;                    // [esp+Ch] [ebp-72F4h]
    float v82;                    // [esp+Ch] [ebp-72F4h]
    float v83;                    // [esp+Ch] [ebp-72F4h]
    float v84;                    // [esp+Ch] [ebp-72F4h]
    float v85;                    // [esp+Ch] [ebp-72F4h]
    float v86;                    // [esp+Ch] [ebp-72F4h]
    float v87;                    // [esp+Ch] [ebp-72F4h]
    float v88;                    // [esp+Ch] [ebp-72F4h]
    float v89;                    // [esp+Ch] [ebp-72F4h]
    float v90;                    // [esp+Ch] [ebp-72F4h]
    float v91;                    // [esp+Ch] [ebp-72F4h]
    float v92;                    // [esp+Ch] [ebp-72F4h]
    float v93;                    // [esp+Ch] [ebp-72F4h]
    float v94;                    // [esp+Ch] [ebp-72F4h]
    float v95;                    // [esp+Ch] [ebp-72F4h]
    int v97;                      // [esp+10h] [ebp-72F0h]
    float v98;                    // [esp+10h] [ebp-72F0h]
    float v99;                    // [esp+10h] [ebp-72F0h]
    float v101;                   // [esp+14h] [ebp-72ECh]
    float v102;                   // [esp+14h] [ebp-72ECh]
    float v103;                   // [esp+14h] [ebp-72ECh]
    float v104;                   // [esp+14h] [ebp-72ECh]
    float v105;                   // [esp+18h] [ebp-72E8h]
    int j;                        // [esp+18h] [ebp-72E8h]
    float theTriangleCelWidtha;   // [esp+1Ch] [ebp-72E4h]
    float theTriangleCelWidth;    // [esp+1Ch] [ebp-72E4h]
    float theTriangleCelWidthb;   // [esp+1Ch] [ebp-72E4h]
    float theTriangleCelWidthc;   // [esp+1Ch] [ebp-72E4h]
    float v113;                   // [esp+20h] [ebp-72E0h]
    int k;                        // [esp+20h] [ebp-72E0h]
    int v115;                     // [esp+24h] [ebp-72DCh]
    float v116;                   // [esp+24h] [ebp-72DCh]
    float v117;                   // [esp+28h] [ebp-72D8h]
    int i;                        // [esp+28h] [ebp-72D8h]
    float _Ptra;                  // [esp+2Ch] [ebp-72D4h]
    char *_Ptr;                   // [esp+2Ch] [ebp-72D4h]
    float v121;                   // [esp+30h] [ebp-72D0h]
    float v122;                   // [esp+30h] [ebp-72D0h]
    float v123;                   // [esp+30h] [ebp-72D0h]
    float v124;                   // [esp+30h] [ebp-72D0h]
    float v125;                   // [esp+30h] [ebp-72D0h]
    float v126;                   // [esp+30h] [ebp-72D0h]
    float v127;                   // [esp+38h] [ebp-72C8h]
    float v128;                   // [esp+38h] [ebp-72C8h]
    float v129;                   // [esp+38h] [ebp-72C8h]
    float v130;                   // [esp+38h] [ebp-72C8h]
    float v131;                   // [esp+38h] [ebp-72C8h]
    float v132;                   // [esp+44h] [ebp-72BCh]
    float v133;                   // [esp+48h] [ebp-72B8h]
    float v135;                   // [esp+50h] [ebp-72B0h]
    float theTriangleCelHeight;   // [esp+54h] [ebp-72ACh]
    int v137[6];                  // [esp+58h] [ebp-72A8h]
    int v138[6];                  // [esp+70h] [ebp-7290h]
    SexyVertex2D v140[3][150][3]; // [esp+988h] [ebp-6978h] BYREF

    theTriangleCelWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_POOL_Addr) / 15.0;
    theTriangleCelHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_POOL_Addr) / 5.0;

    v6 = 0.0;
    float v139[576] = {0.0};
    v7 = 0.06666667014360428;
    v8 = 0.2;
    v9 = 0;
    v10 = 6.283185482025146;
    v115 = 0;
    v11 = 3.0;
    v12 = &v139[385];
    while (1) {
        v17 = 0;
        v97 = 0;
        v135 = (float)v115;
        v116 = v135 * v7;
        while (1) {
            *(v12 - 1) = v116;
            v98 = (float)v97;
            v22 = v98;
            v99 = v98 * v8;
            *v12 = v99;
            if (!v9 || v9 == 15 || !v17 || v17 == 5) {
                v30 = v11;
                *(v12 - 385) = v6;
                *(v12 - 384) = v6;
                *(v12 - 193) = v6;
                *(v12 - 192) = v6;
                v31 = v10;
                v28 = v6;
                v25 = v31;
                v32 = v8;
                v33 = v30;
                v34 = v32;
                v35 = v7;
                v26 = v34;
                v36 = v35;
                v29 = v33;
                v27 = v36;
            } else {
                v23 = v10;
                v24 = poolEffect->mPoolCounter * v10;
                v101 = v24 / 800.0;
                v133 = v101;
                v117 = v24 / 150.0;
                _Ptra = v24 / 900.0;
                v132 = v101;
                v102 = v24 / 110.0;
                v105 = v135 * v11 * v23 / 15.0;
                v113 = v22 * v11 * v23 / 5.0;
                v67 = v113 + v133;
                v68 = sin(v67);
                v127 = v68 * 0.005;
                v69 = v113 + v117;
                v70 = sin(v69);
                *(v12 - 385) = v70 * 0.002 + v127;
                v71 = v105 + v132;
                v72 = sin(v71);
                v128 = v72 * 0.005;
                v73 = v105 + _Ptra;
                v74 = sin(v73);
                v129 = v74 * 0.015 + v128;
                v75 = v105 + v102;
                v76 = sin(v75);
                *(v12 - 384) = v76 * 0.01 + v129;
                v130 = v113 * 0.2;
                v77 = v130 + v133;
                v78 = sin(v77);
                v121 = v78 * 0.012;
                v79 = v117 + v130;
                v80 = sin(v79);
                *(v12 - 193) = v80 * 0.015 + v121;
                v131 = v105 * 0.2;
                v81 = v131 + v132;
                v82 = sin(v81);
                v122 = v82 * 0.02;
                v83 = _Ptra + v131;
                v84 = sin(v83);
                v123 = v84 * 0.015 + v122;
                v85 = v102 + v131;
                v86 = sin(v85);
                *(v12 - 192) = v86 * 0.005 + v123;
                v87 = v117 * 1.5 + v113;
                v88 = sin(v87);
                v124 = v88 * 0.005;
                v89 = v133 * 1.5 + v113;
                v90 = sin(v89);
                *(v12 - 1) = v90 * 0.004 + v124 + v116;
                v91 = v105 * 3.0 + v132 * 2.5;
                v92 = sin(v91);
                v125 = v92 * 0.02;
                v93 = v105 + v105 + _Ptra * 2.5;
                v94 = sin(v93);
                v126 = v94 * 0.04 + v125;
                v95 = v105 * 4.0 + v102 * 2.5;
                v66 = sin(v95);
                *v12 = v66 * 0.005 + v126 + v99;
                v25 = 6.283185482025146;
                v26 = 0.2;
                v27 = 0.0666666;
                v28 = 0.0;
                v29 = 3.0;
            }
            ++v17;
            v12 += 2;
            v97 = v17;
            if (v17 > 5)
                break;
            v18 = v29;
            v19 = v25;
            v6 = v28;
            v20 = v19;
            v21 = v26;
            v7 = v27;
            v8 = v21;
            v11 = v18;
            v10 = v20;
        }
        v115 = ++v9;
        if (v9 > 15)
            break;
        v13 = v29;
        v14 = v25;
        v6 = v28;
        v15 = v14;
        v16 = v26;
        v7 = v27;
        v8 = v16;
        v11 = v13;
        v10 = v15;
    }
    v137[0] = 0;
    v137[1] = 0;
    v37 = v27;
    v137[3] = 0;
    v138[0] = 0;
    v138[3] = 0;
    v138[5] = 0;
    v137[2] = 1;
    v137[4] = 1;
    v137[5] = 1;
    v138[1] = 1;
    v138[2] = 1;
    v138[4] = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 150; ++j) {
            for (int k = 0; k < 3; ++k) {
                v140[i][j][k].color = 0;
            }
        }
    }
    v40 = theTriangleCelWidth;
    for (i = 0; i < 15; ++i) {
        for (j = 0; j < 5; ++j) {
            v41 = 0;
            for (k = 0;; v41 = k) {
                v42 = &v140[0][120 * v41][90 * v41 + 24 * i + 6 * i + 6 * j];
                v43 = 0;
                for (_Ptr = 0;; v43 = _Ptr) {
                    v44 = i + *(int *)((char *)v137 + (uint32_t)v43);
                    v45 = j + *(int *)((char *)v138 + (uint32_t)v43);
                    v103 = (float)v44;
                    v46 = v103;
                    if (v41 == 2) {
                        v52 = 3 * v44 + 96;
                        theTriangleCelWidthb = 46.93333435058594 * v46 + 45.0;
                        v53 = theTriangleCelWidthb;
                        v42->x = theTriangleCelWidthb;
                        v104 = (float)v45;
                        theTriangleCelWidthc = 30.0 * v104 + 288.0;
                        v42->y = theTriangleCelWidthc;
                        v42->u = v139[4 * v52 + 2 * v45] + v46 * v37;
                        v42->v = v139[4 * v52 + 1 + 2 * v45] + v104 * v26;
                        theTriangleCelWidth = (int)theTriangleCelWidthc;
                        mX = graphics->mClipRect.mX;
                        if ((int)v53 < mX)
                            goto LABEL_37;
                        if ((int)v53 < mX + graphics->mClipRect.mWidth && (mY = graphics->mClipRect.mY, theTriangleCelWidth >= mY) && theTriangleCelWidth < mY + graphics->mClipRect.mHeight) {
                            if (v44 && v44 != 15 && v45)
                                v42->color = theIsNight ? 0x30FFFFFF : v44 <= 7 ? 0xC0FFFFFF : 0x80FFFFFF;
                            else
                                v42->color = 0x20FFFFFF;
                        } else {
                        LABEL_37:
                            v42->color = 0xFFFFFF;
                        }
                    } else {
                        v47 = 2 * (v45 + 6 * (v44 + 16 * v41));
                        theTriangleCelWidtha = v46 * v40 + 35.0;
                        v42->color = -1;
                        v48 = theTriangleCelWidtha;
                        v42->x = theTriangleCelWidtha;
                        v104 = (float)v45;
                        theTriangleCelWidth = v104 * theTriangleCelHeight + 279.0;
                        v42->y = theTriangleCelWidth;
                        v42->u = v139[v47] + v46 * v37;
                        v42->v = v139[v47 + 1] + v104 * v26;
                        v49 = (int)theTriangleCelWidth;
                        v50 = graphics->mClipRect.mX;
                        if ((int)v48 < v50 || (int)v48 >= v50 + graphics->mClipRect.mWidth || (v51 = graphics->mClipRect.mY, v49 < v51) || v49 >= v51 + graphics->mClipRect.mHeight) {
                            v42->color = 0xFFFFFF;
                        }
                    }
                    v42++;
                    _Ptr += 4;
                    v41 = k;
                    if ((int)_Ptr >= 24)
                        break;
                }
                if (++k >= 3)
                    break;
            }
        }
    }
    if (theIsNight) {
        Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_BASE_NIGHT_Addr, v140[0], 150);
        Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_SHADING_NIGHT_Addr, v140[1], 150);
    } else {
        Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_BASE_Addr, v140[0], 150);
        Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_SHADING_Addr, v140[1], 150);
    }
    PoolEffect_UpdateWaterEffect(poolEffect);
    Sexy::Graphics newGraphics;
    Sexy_Graphics_Graphics(&newGraphics, graphics);
    Sexy_GLGraphics_SetWrapMode(&newGraphics, 0, 0);
    Sexy_Graphics_DrawTrianglesTex(&newGraphics, poolEffect->mCausticImage, v140[2], 150);
    Sexy_GLGraphics_SetWrapMode(&newGraphics, 1, 1);
    Sexy_Graphics_Delete2(&newGraphics);

    if (poolEffect->mApp->mGameMode == GameMode::ChallengePoolParty && poolEffect->mApp->mBoard != nullptr) {
        float theTmpTransY = graphics->mTransY;
        int thePoolOffsetY[2] = {164, -175};
        for (int i = 0; i < 2; ++i) {
            graphics->mTransY += thePoolOffsetY[i];
            if (theIsNight) {
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_POOL_NIGHT_Addr, 34, 278);
                Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_BASE_NIGHT_Addr, v140[0], 150);
                Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_SHADING_NIGHT_Addr, v140[1], 150);
            } else {
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_POOL_Addr, 34, 278);
                Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_BASE_Addr, v140[0], 150);
                Sexy_Graphics_DrawTrianglesTex(graphics, *Sexy_IMAGE_POOL_SHADING_Addr, v140[1], 150);
                TodParticleSystem *thePoolSparkle = LawnApp_ParticleTryToGet(poolEffect->mApp, poolEffect->mApp->mBoard->mPoolSparklyParticleID);
                if (thePoolSparkle != nullptr) {
                    TodParticleSystem_Draw(thePoolSparkle, graphics);
                }
            }
            Sexy::Graphics newGraphics;
            Sexy_Graphics_Graphics(&newGraphics, graphics);
            Sexy_GLGraphics_SetWrapMode(&newGraphics, 0, 0);
            Sexy_Graphics_DrawTrianglesTex(&newGraphics, poolEffect->mCausticImage, v140[2], 150);
            Sexy_GLGraphics_SetWrapMode(&newGraphics, 1, 1);
            Sexy_Graphics_Delete2(&newGraphics);
            graphics->mTransY = theTmpTransY;
        }
    }
}

bool Sexy_SexyAppBase_Is3DAccelerated(LawnApp *lawnApp) {
    // 修复关闭3D加速后MV错位
    return lawnApp->mNewIs3DAccelerated || lawnApp->mCreditScreen != nullptr;
}

void Sexy_SexyAppBase_Set3DAccelerated(LawnApp *lawnApp, bool isAccelerated) {
    lawnApp->mNewIs3DAccelerated = isAccelerated;
    lawnApp->mPlayerInfo->mIs3DAcceleratedClosed = !isAccelerated;
}

FoleyParams *LookupFoley(FoleyType::FoleyType theFoleyType) {
    // 新增三个Foley，用于主界面白噪音
    if (theFoleyType == FoleyType::MenuLeft) {
        return &gMenuLeftFoley;
    } else if (theFoleyType == FoleyType::MenuCenter) {
        return &gMenuCenterFoley;
    } else if (theFoleyType == FoleyType::MenuRight) {
        return &gMenuRightFoley;
    } else
        return old_LookupFoley(theFoleyType);
}

void MessageWidget_Draw(CustomMessageWidget *messageWidget, Sexy::Graphics *graphics) {
    // 用于绘制成就图标、在LevelIntro时显示“player的房子”、修复老虎机提示文字位置靠上
    if (messageWidget->mMessageStyle == MessageStyle::SlotMachine) {
        float tmpTransY = graphics->mTransY;
        graphics->mTransY += 8;
        old_MessageWidget_Draw(messageWidget, graphics);
        graphics->mTransY = tmpTransY;
    } else {
        old_MessageWidget_Draw(messageWidget, graphics);
    }

    if (messageWidget->mMessageStyle == MessageStyle::HouseName && messageWidget->mReanimType == ReanimationType::REANIM_NONE) {
        Sexy::Font *theFont = MessageWidget_GetFont(messageWidget);
        int num2 = 530; // 原版为550，此处改为530！
        Color theColor = {255, 255, 255, std::clamp(messageWidget->mDuration * 15, 0, 255)};
        int holder[1];
        Sexy_StrFormat(holder, messageWidget->mLabel);
        TRect theRect;
        theRect.mY = num2 - theFont->mAscent;
        theRect.mHeight = 600;
        theRect.mWidth = 800;
        theRect.mX = -messageWidget->mApp->mBoard->mX;
        TodDrawStringWrapped(graphics, holder, &theRect, theFont, &theColor, DrawStringJustification::Center, false);
        Sexy_String_Delete(holder);
    }
    if (messageWidget->mIcon != nullptr) {
        TodDrawImageCenterScaledF(graphics, messageWidget->mIcon, 100, 470, 0.55f, 0.55f);
    }
}

void MessageWidget_ClearLabel(CustomMessageWidget *messageWidget) {
    // 用于绘制成就图标
    old_MessageWidget_ClearLabel(messageWidget);
    messageWidget->mIcon = nullptr;
}

void MessageWidget_SetLabel(CustomMessageWidget *messageWidget, int *label, MessageStyle::MessageStyle theStyle) {
    // 用于绘制成就图标
    old_MessageWidget_SetLabel(messageWidget, label, theStyle);
    messageWidget->mIcon = nullptr;
}

void MessageWidget_Update(CustomMessageWidget *messageWidget) {
    // 用于绘制成就图标
    if (messageWidget->mDuration == 1) {
        messageWidget->mIcon = nullptr;
    }
    old_MessageWidget_Update(messageWidget);
}

void LawnPlayerInfo_AddCoins(PlayerInfo *playerInfo, int theAmount) {
    // 用于 购物愉快 成就
    int theCoins = playerInfo->mCoins + theAmount;
    if (theCoins > 99999) {
        theCoins = 99999;
    }
    if (theCoins <= 0) {
        theCoins = 0;
    }
    playerInfo->mCoins = theCoins;
    if (theAmount < 0) {
        playerInfo->mUsedCoins -= theAmount;
        if (playerInfo->mUsedCoins >= 2500) {
            LawnApp_GrantAchievement((LawnApp *)*gLawnApp_Addr, AchievementId::ACHIEVEMENT_SHOP);
        }
    }
}

static Sexy::GameButton *mCreditScreenBackButton;

void CreditScreen_CreditScreen(Sexy::Widget *creditScreen, LawnApp *a2, bool a3) {
    old_CreditScreen_CreditScreen(creditScreen, a2, a3);
    int holder[1];
    TodStringTranslate(holder, "[MAIN_MENU_BUTTON]");
    mCreditScreenBackButton = MakeButton(1000, (Sexy::ButtonListener *)creditScreen + 64, creditScreen, holder);
    GameButton_Resize(mCreditScreenBackButton, 725, 0, 170, 50);
    Sexy_String_Delete(holder);
    Sexy_Widget_AddWidget(creditScreen, mCreditScreenBackButton);
}

void CreditScreen_RemovedFromManager(Sexy::Widget *creditScreen, int a2) {
    creditScreen->mFocusedChildWidget = mCreditScreenBackButton; // 修复触摸CreditScreen后点击按钮退出就会闪退的BUG,虽然不知道为什么
    Sexy_Widget_RemoveWidget(creditScreen, mCreditScreenBackButton);
    return old_CreditScreen_RemovedFromManager(creditScreen, a2);
}

void CreditScreen_Delete2(Sexy::Widget *creditScreen) {
    old_CreditScreen_Delete2(creditScreen);
    GameButton_Delete(mCreditScreenBackButton);
    mCreditScreenBackButton = nullptr;
}

void CreditScreen_ButtonDepress(Sexy::Widget *creditScreen, int id) {
    if (id == 1000) {
        LawnApp *lawnApp = (LawnApp *)*gLawnApp_Addr;
        CreditScreen_PauseCredits(lawnApp->mCreditScreen);
    }
}

void SaveGameContext_SyncReanimationDef(int *theSaveGameContext, ReanimatorDefinition **a2) {
    // 解决大头贴动画的读档问题
    if (*((uint8_t *)theSaveGameContext + 29)) {
        int reanimationType;
        SaveGameContext_SyncInt(theSaveGameContext, &reanimationType);
        if (reanimationType == -1) {
            *a2 = nullptr;
        } else if (reanimationType <= ReanimationType::ZombatarHead) {
            ReanimatorEnsureDefinitionLoaded((ReanimationType)reanimationType, true);
            ReanimatorDefinition *v6 = *gReanimatorDefArray_Addr; // r3
            *a2 = v6 + reanimationType;
        } else {
            *((uint8_t *)theSaveGameContext + 28) = true;
        }
    } else {
        int v3 = 0;
        int reanimationType = -1;
        ReanimatorDefinition *v5 = *a2;                       // r1
        ReanimatorDefinition *v6 = *gReanimatorDefArray_Addr; // r3
        while (v5 != v6++) {
            if (++v3 == ReanimationType::ZombatarHead + 1)
                goto LABEL_7;
        }
        reanimationType = v3;
    LABEL_7:
        SaveGameContext_SyncInt(theSaveGameContext, &reanimationType);
    }
}

void Sexy_Widget_MarkDirty(Sexy::Widget *widget) {
    (*((void (**)(Sexy::Widget *))widget->vTable + 25))(widget); // MarkDirty();
}

void Sexy_Widget_AddWidget(Sexy::Widget *parent, Sexy::Widget *child) {
    (*((void (**)(Sexy::Widget *, Sexy::Widget *))parent->vTable + 6))(parent, child); // AddWidget();
}

void Sexy_Widget_RemoveWidget(Sexy::Widget *parent, Sexy::Widget *child) {
    (*((void (**)(Sexy::Widget *, Sexy::Widget *))parent->vTable + 7))(parent, child); // RemoveWidget();
}

Sexy::Widget *Sexy_Widget_FindWidget(Sexy::Widget *parent, int id) {
    return (*((Sexy::Widget * (**)(Sexy::Widget *, int)) parent->vTable + 9))(parent, id); // FindWidget();
}

void Sexy_MemoryImage_ClearRect(Sexy::Image *a1, TRect *a2) {
    int mY;     // r4
    int *mBits; // r7
    int v7;     // r0

    mBits = (int *)(*((int (**)(Sexy::Image *))a1->vTable + 13))(a1);
    mY = a2->mY;
    if (mY < a2->mHeight + mY) {
        do {
            v7 = a2->mX + (*((int (**)(Sexy::Image *))a1->vTable + 6))(a1)*mY++;
            memset(&mBits[v7], 0, 4 * a2->mWidth);
        } while (a2->mHeight + a2->mY > mY);
    }
    (*((void (**)(Sexy::Image *))a1->vTable + 47))(a1);
}
