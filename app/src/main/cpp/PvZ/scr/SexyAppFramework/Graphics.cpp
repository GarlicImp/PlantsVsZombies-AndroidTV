#include "PvZ/SexyAppFramework/Graphics.h"
#include "../../Lawn/Common/Enums.h"

void Sexy_Graphics_PushTransform(Sexy::Graphics *graphics, int *transform, bool concatenate) {
    old_Sexy_Graphics_PushTransform(graphics, transform, concatenate);
}

void Sexy_Graphics_PopTransform(Sexy::Graphics *graphics) {
    old_Sexy_Graphics_PopTransform(graphics);
}

void Sexy_Graphics_DrawTrianglesTex2(Sexy::Graphics *graphics, Sexy::Image *theTexture, TriVertex (*theVertices)[3], int theNumTriangles) {
    SexyVertex2D tmp[theNumTriangles][3];

    for (int i = 0; i < theNumTriangles; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int j = 0; j < 3; ++j) {
                tmp[i][j].x = theVertices[i][j].x;
                tmp[i][j].y = theVertices[i][j].y;
                tmp[i][j].u = theVertices[i][j].u;
                tmp[i][j].v = theVertices[i][j].v;
                tmp[i][j].color = theVertices[i][j].color;
            }
        }
        Sexy_Graphics_DrawTrianglesTex(graphics, theTexture, tmp, theNumTriangles);
    }
}

void Sexy_Graphics_DrawImageColorized(Sexy::Graphics *graphics, Sexy::Image *image, Color *color, int x, int y) {
    Sexy_Graphics_SetColor(graphics, color);
    Sexy_Graphics_SetColorizeImages(graphics, true);
    Sexy_Graphics_DrawImage(graphics, image, x, y);
    Sexy_Graphics_SetColorizeImages(graphics, false);
}

void Sexy_Graphics_DrawImageColorizedScaled(Sexy::Graphics *graphics, Sexy::Image *image, Color *color, float x, float y, float xScaled, float yScaled) {
    Sexy_Graphics_SetColor(graphics, color);
    Sexy_Graphics_SetColorizeImages(graphics, true);
    TodDrawImageScaledF(graphics, image, x, y, xScaled, yScaled);
    Sexy_Graphics_SetColorizeImages(graphics, false);
}
