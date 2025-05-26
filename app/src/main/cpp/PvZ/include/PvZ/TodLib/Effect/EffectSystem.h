//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_EFFECTSYSTEM_H
#define PLANTSVSZOMBIES_ANDROIDTV_EFFECTSYSTEM_H

#include "PvZ/SexyAppFramework/Graphics/Graphics.h"

#define MAX_TRIANGLES 256

class TodTriangleGroup {
public:
    Sexy::Image *mImage;
    TriVertex mVertArray[MAX_TRIANGLES][3];
    int mTriangleCount;
    int mDrawMode;

    //    TodTriangleGroup();
    //    void                        DrawGroup(Sexy::Graphics* g);
    //    void                        AddTriangle(Sexy::Graphics* g, Sexy::Image* theImage, const SexyMatrix3& theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect&
    //    theSrcRect);
};

#endif // PLANTSVSZOMBIES_ANDROIDTV_EFFECTSYSTEM_H
