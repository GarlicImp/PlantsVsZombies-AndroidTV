//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_TRASHBIN_H
#define PLANTSVSZOMBIES_ANDROIDTV_TRASHBIN_H

#include "PvZ/SexyAppFramework/Widget/Widget.h"

class TrashBin : public Sexy::Widget {
public:
    enum TrashPileType { PLANT_PILE = 0, ZOMBIE_PILE = 1 };

    TrashPileType mTrashPileType; // 64
    float mTrashHeight;           // 65
    Sexy::Image *mPileImage[10];  // 66 ~ 75
    bool mMirrorPile[10];         // 76 ~ 78
    int mRandomPileWeight[6];     // 79 ~ 84
    int mPileNum;                 // 85
    // 大小86个整数

    TrashBin(TrashPileType theTrashPileType, float theHeight);
    void Create(TrashPileType theTrashPileType, float theHeight);
    void Draw(Sexy::Graphics *g);
};

inline void (*TrashBin_Delete)(TrashBin *a1);

#endif // PLANTSVSZOMBIES_ANDROIDTV_TRASHBIN_H
