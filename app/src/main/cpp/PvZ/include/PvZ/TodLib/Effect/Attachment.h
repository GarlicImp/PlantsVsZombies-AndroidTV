//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_ATTACHMENT_H
#define PLANTSVSZOMBIES_ANDROIDTV_ATTACHMENT_H

#include "PvZ/Lawn/Common/ConstEnums.h"
#include "PvZ/SexyAppFramework/Misc/SexyMatrix.h"

class AttachEffect {
public:
    enum EffectType { Particle, Trail, Reanim, Attachment, Other };
    ReanimationID mEffectID;      // 0
    EffectType mEffectType;       // 1
    Sexy::SexyTransform2D mOffset;// 2 ~ 10
    bool mDontDrawIfParentHidden; // 44
    bool mDontPropogateColor;     // 45
}; // 大小12个整数

class Attachment {
public:
    int unk[4];                    // 0 ~ 3
    AttachEffect mEffectArray[16]; // 4 ~ 195
    int mNumEffects;               // 196
    bool mDead;                    //
    bool mActive;
    bool mUsesClipping;
    int mAttachmentID;
}; // 大小199个整数

class AttachmentHolder {};

#endif // PLANTSVSZOMBIES_ANDROIDTV_ATTACHMENT_H
