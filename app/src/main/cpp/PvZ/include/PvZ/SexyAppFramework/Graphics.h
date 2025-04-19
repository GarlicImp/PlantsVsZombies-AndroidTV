#ifndef PVZ_SEXY_GRAPHICS_H
#define PVZ_SEXY_GRAPHICS_H

#include "PvZ/Enums.h"

inline Color black = {0, 0, 0, 255};

inline Color gray = {80, 80, 80, 255};

inline Color white = {255, 255, 255, 255};

inline Color blue = {0, 255, 255, 255};

inline Color yellow = {255, 255, 0, 255};

inline Color brown = {205, 133, 63, 255};

inline Color green = {0, 250, 154, 255};

inline Color gZombatarSkinColor[] = {
    {134, 147, 122, 255},
    {79, 135, 94, 255},
    {127, 135, 94, 255},
    {120, 130, 50, 255},
    {156, 163, 105, 255},
    {96, 151, 11, 255},
    {147, 184, 77, 255},
    {82, 143, 54, 255},
    {121, 168, 99, 255},
    {65, 156, 74, 255},
    {107, 178, 114, 255},
    {104, 121, 90, 255},
};

inline Color gZombatarAccessoryColor[] = {
    {151, 33, 33, 255},
    {199, 53, 53, 255},
    {220, 112, 47, 255},
    {251, 251, 172, 255},
    {240, 210, 87, 255},
    {165, 126, 65, 255},
    {106, 72, 32, 255},
    {72, 35, 5, 255},
    {50, 56, 61, 255},
    {0, 0, 10, 255},
    {197, 239, 239, 255},
    {63, 109, 242, 255},
    {14, 201, 151, 255},
    {158, 183, 19, 255},
    {30, 210, 64, 255},
    {225, 65, 230, 255},
    {128, 47, 204, 255},
    {255, 255, 255, 255},
};

inline Color gZombatarAccessoryColor2[] = {
    {238, 19, 24, 255},
    {247, 89, 215, 255},
    {239, 198, 253, 255},
    {160, 56, 241, 255},
    {86, 74, 241, 255},
    {74, 160, 241, 255},
    {199, 244, 251, 255},
    {49, 238, 237, 255},
    {16, 194, 66, 255},
    {112, 192, 33, 255},
    {16, 145, 52, 255},
    {248, 247, 41, 255},
    {227, 180, 20, 255},
    {241, 115, 25, 255},
    {248, 247, 175, 255},
    {103, 85, 54, 255},
    {159, 17, 20, 255},
    {255, 255, 255, 255},
};


inline void (*Sexy_Graphics_SetDrawMode)(Sexy::Graphics *a, DrawMode::DrawMode a2);

inline void (*Sexy_Graphics_SetColorizeImages)(Sexy::Graphics *a, bool a2);

inline bool (*Sexy_Graphics_GetColorizeImages)(Sexy::Graphics *);

inline void (*Sexy_Graphics_SetFont)(Sexy::Graphics *a, Sexy::Font *a2);

inline void (*Sexy_Graphics_PushState)(Sexy::Graphics *);

inline void (*Sexy_Graphics_PopState)(Sexy::Graphics *);

inline void (*Sexy_Graphics_SetLinearBlend)(Sexy::Graphics *, int);

inline void (*Sexy_Graphics_ClipRect)(Sexy::Graphics *, int, int, int, int);

inline void (*Sexy_Graphics_FillRect)(Sexy::Graphics *graphics, TRect *rect);

inline void (*Sexy_Graphics_DrawRect)(Sexy::Graphics *graphics, TRect *rect);

inline void (*Sexy_Graphics_DrawString)(Sexy::Graphics *a1, int *a2, int a3, int a4);

inline void (*Sexy_Graphics_DrawImage)(Sexy::Graphics *a1, Sexy::Image *a2, int a3, int a4);

inline void (*Sexy_Graphics_DrawImage2)(Sexy::Graphics *a1, Sexy::Image *a2, int a3, int a4, int *a5);

inline void (*Sexy_Graphics_DrawImageF)(Sexy::Graphics *a1, Sexy::Image *a2, float a3, float a4);

inline void (*Sexy_Graphics_DrawImageCel)(Sexy::Graphics *a1, Sexy::Image *a2, int a3, int a4, int a5, int a6);

inline void (*Sexy_Graphics_SetClipRect)(Sexy::Graphics *, int, int, int, int);

inline void (*Sexy_Graphics_ClearClipRect)(Sexy::Graphics *);

inline void (*Sexy_Graphics_DrawImageCel2)(Sexy::Graphics *a1, Sexy::Image *a2, int a3, int a4, int a5);

inline void (*Sexy_Graphics_DrawImageMirror)(Sexy::Graphics *, Sexy::Image *, int, int, bool);

inline void *(*Sexy_Graphics_Graphics)(Sexy::Graphics *newGraphics, const Sexy::Graphics *graphics);

inline void (*Sexy_Graphics_Graphics2)(Sexy::Graphics *newGraphics, Sexy::Image *image);

inline void (*Sexy_Graphics_Delete2)(Sexy::Graphics *a);

inline void (*Sexy_Graphics_ClearRect)(Sexy::Graphics *a, int, int, int, int);

inline void (*Sexy_Graphics_Translate)(Sexy::Graphics *, int, int);

inline void (*Sexy_Graphics_SetColor)(Sexy::Graphics *a, Color *a2);

inline void (*Sexy_Graphics_DrawTrianglesTex)(Sexy::Graphics *graphics, Sexy::Image *theTexture, SexyVertex2D (*theVertices)[3], int theNumTriangles);

inline int *(*Sexy_Graphics_GetColor)(Sexy::Graphics *);

inline void (*Sexy_Graphics_SetScale)(Sexy::Graphics *, float, float, float, float);

inline void (*TodDrawImageCelF)(Sexy::Graphics *, Sexy::Image *, float, float, int, int);

inline int (*TodDrawImageCelCenterScaledF)(Sexy::Graphics *a1, Sexy::Image *a2, float a3, float a4, int a5, float a6, float a7);

inline void (*TodDrawImageScaledF)(Sexy::Graphics *g, Sexy::Image *image, float x, float y, float xScaled, float yScaled);

inline void (*TodDrawImageCelScaledF)(Sexy::Graphics *, Sexy::Image *, float, float, int, int, float, float);

inline void (*TodDrawImageCenterScaledF)(Sexy::Graphics *, Sexy::Image *, float, float, float, float);

inline void (*TodDrawString)(Sexy::Graphics *, int *, int, int, Sexy::Font *, Color color, DrawStringJustification);

inline void (*TodScaleTransformMatrix)(int *, float, float, float, float);

inline void (*TodDrawStringMatrix)(Sexy::Graphics *, Sexy::Font *, int *, int *, Color *);

inline int (*TodAnimateCurve)(int theTimeStart, int theTimeEnd, int theTimeAge, int thePositionStart, int thePositionEnd, TodCurves theCurve);

inline float (*TodAnimateCurveFloat)(int theTimeStart, int theTimeEnd, int theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve);

inline float (*TodAnimateCurveFloatTime)(float theTimeStart, float theTimeEnd, float theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve);

inline void (*TodDrawStringWrapped)(Sexy::Graphics *graphics, int *text, TRect *theRect, Sexy::Font *theFont, Color *theColor, DrawStringJustification justification, bool a7);

inline int (*TodDrawStringWrappedHelper)(
    Sexy::Graphics *pGraphics, int *pInt, TRect *pRect, Sexy::Font *pFont, Color color, DrawStringJustification justification, bool i1, bool i2);

inline void (*Sexy_GLGraphics_SetWrapMode)(Sexy::Graphics *graphics, int a2, int a3);

inline void (*Sexy_Graphics_DrawImageMatrix)(Sexy::Graphics *graphics, Sexy::Image *, Sexy::SexyMatrix3 *, TRect *, float, float, bool);


inline void (*old_Sexy_Graphics_PushTransform)(Sexy::Graphics *, int *, bool);

inline void (*old_Sexy_Graphics_PopTransform)(Sexy::Graphics *graphics);


void Sexy_Graphics_PushTransform(Sexy::Graphics *graphics, int *theTransform, bool concatenate);

void Sexy_Graphics_PopTransform(Sexy::Graphics *graphics);

void Sexy_Graphics_DrawTrianglesTex2(Sexy::Graphics *graphics, Sexy::Image *theTexture, TriVertex (*theVertices)[3], int theNumTriangles);

void Sexy_Graphics_DrawImageColorized(Sexy::Graphics *graphics, Sexy::Image *image, Color *color, int x, int y);

void Sexy_Graphics_DrawImageColorizedScaled(Sexy::Graphics *graphics, Sexy::Image *image, Color *color, float x, float y, float xScaled, float yScaled);

#endif // PVZ_SEXY_GRAPHICS_H
