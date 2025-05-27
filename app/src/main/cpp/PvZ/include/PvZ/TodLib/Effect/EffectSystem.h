//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_EFFECTSYSTEM_H
#define PLANTSVSZOMBIES_ANDROIDTV_EFFECTSYSTEM_H

#include "../Common/DataArray.h"
#include "PvZ/SexyAppFramework/Graphics/Graphics.h"
#include "PvZ/SexyAppFramework/Graphics/Image.h"
#include "PvZ/SexyAppFramework/Misc/TriVertex.h"
#include "Reanimator.h"
#include "Trail.h"

#define MAX_TRIANGLES 256

class TodTriVertex {
public:
    float x;
    float y;
    float u;
    float v;
    unsigned long color;
};

class TodTriangleGroup {
public:
    Sexy::Image *mImage;
    Sexy::TriVertex mVertArray[MAX_TRIANGLES][3];
    int mTriangleCount;
    int mDrawMode;

    //    TodTriangleGroup();
    //    void                        DrawGroup(Sexy::Graphics* g);
    //    void                        AddTriangle(Sexy::Graphics* g, Sexy::Image* theImage, const SexyMatrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect&
    //    theSrcRect);
};

class Reanimation;
class TodParticleHolder;
class TrailHolder;
class ReanimationHolder;
class AttachmentHolder;
class EffectSystem {
public:
    TodParticleHolder *mParticleHolder;
    TrailHolder *mTrailHolder;
    ReanimationHolder *mReanimationHolder;
    AttachmentHolder *mAttachmentHolder;
};

#endif // PLANTSVSZOMBIES_ANDROIDTV_EFFECTSYSTEM_H
