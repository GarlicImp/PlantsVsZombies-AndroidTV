//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_IMAGE_H
#define PLANTSVSZOMBIES_ANDROIDTV_IMAGE_H

#include "../Misc/Common.h"
#include "../Misc/Point.h"
#include "../Misc/Rect.h"

#include "Color.h"

class LawnApp;

namespace Sexy {

class Image {
public:
    int *vTable;                      // 0
    int placeHolder[2];               // 1 ~ 2
    bool unkBool;                     // 12
    int unkMmWidthems1[2];            // 4 ~ 5
    int *stringUnk1;                  // 6
    int *stringUnk2;                  // 7
    int *stringUnk3;                  // 8
    int mWidth;                       // 9
    int mHeight;                      // 10
    int mPitch;                       // 11
    int mStride;                      // 12
    PixelFormat mFormat;              // 13
    int mPixelFormatHint;             // 14
    int mNumRows;                     // 15
    int mNumCols;                     // 16
    int *mAnimInfo;                   // 17
    int unk[6];                       // 18 ~ 23
    int mHorizonWrapMode;             // 24
    int mVertWrapMode;                // 25
    int mTag;                         // 26
    int unkMems3;                     // 27 ，实际上Sexy::Image就到这里，下面是MemoryImage的成员
    LawnApp *mApp;                    // 28
    int unkMems4;                     // 29
    unsigned int *mBits;              // 30
    int mBitsChangedCount;            // 31
    int unk1[4];                      // 32 ~ 35
    bool mUnkModeRelated;             // 144
    bool mUnkMode1;                   // 145
    bool mUnkMode2;                   // 146
    bool mUnkBool;                    // 147
    bool mVolatile;                   // 148
    int unk2[20];                     // 38 ~ 57
    // 大小58个整数
    int GetWidth() { return mWidth; };
    int GetHeight() { return mHeight; };
};

}


#endif // PLANTSVSZOMBIES_ANDROIDTV_IMAGE_H
