//
// Created by 28636 on 2025/5/27.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_BASEGAMEPADCONTROLS_H
#define PLANTSVSZOMBIES_ANDROIDTV_BASEGAMEPADCONTROLS_H

#include "PvZ/Lawn/Board/GameObject.h"

class SeedBank;

class BaseGamepadControls {
public:
    int *mVtable;                    // 0
    GameObject mGameObject;          // 1 ~ 13
    Board *mBoard;                   // 14
    SeedBank *mSeedBank;             // 15
    float mUnkFirstHighlightRelated; // 16
    int mShovelRelated1;             // 17
    float mGamepadAccLeftX;
    float mGamepadAccLeftY;
    float mGridCenterPositionX;    // 20
    float mGridCenterPositionY;    // 21
    float mRightPositionX;         // 22
    float mRightPositionY;         // 23
    int mGamepadState;             // 24
    int unk1;                      // 25
    float mDigIndicatorPercentage; // 26 , 每按下一次铲除键就加2.3
    float mCursorPositionX;        // 27
    float mCursorPositionY;        // 28
    float mGamepadVelocityLeftX;   // 29
    float mGamepadVelocityLeftY;   // 30
    float mGamepadVelocityRightX;  // 31
    float mGamepadVelocityRightY;  // 32
    int unk2[4];                   // 33 ~ 36
    int mPlayerIndex1;             // 37
    int mPlayerIndex2;             // 38
    float mCursorPositionYJitter;  // 39
    float mUpdateAdd0Dot016;       // 40
    int unkMems[2];                // 41 ~ 42
    // 大小43个整数
public:
    void GetGamepadVelocity(float *horizontal, float *vertical);
};

#endif // PLANTSVSZOMBIES_ANDROIDTV_BASEGAMEPADCONTROLS_H
