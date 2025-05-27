//
// Created by 28636 on 2025/5/27.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_TODPARTICLE_H
#define PLANTSVSZOMBIES_ANDROIDTV_TODPARTICLE_H

#include "PvZ/TodLib/Common/TodList.h"
#include "PvZ/TodLib/Common/DataArray.h"
#include "PvZ/SexyAppFramework/Misc/SexyVector.h"

class TodParticleSystem {
public:
    int *vTable;                // 0
    int unk1[3];                // 1 ~ 3
    ParticleEffect mEffectType; // 4
    int *mParticleDef;          // 5
    int *mParticleHolder;       // 6
    int mEmitterList[4];        // 7 ~ 10
    bool mDead;                 // 44
    bool mIsAttachment;         // 45
    int mRenderOrder;           // 12
    bool mDontUpdate;           // 52
    bool mActive;               // 53
    int mParticleId;            // 14
}; // 大小15个整数

class TodParticleHolder {};


#endif // PLANTSVSZOMBIES_ANDROIDTV_TODPARTICLE_H
