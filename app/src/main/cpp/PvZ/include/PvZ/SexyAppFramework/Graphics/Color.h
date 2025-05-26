//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_COLOR_H
#define PLANTSVSZOMBIES_ANDROIDTV_COLOR_H

#include "../Misc/Common.h"

namespace Sexy {

#pragma pack(push,1)
struct SexyRGBA {unsigned char b,g,r,a;};
#pragma pack(pop)

class Color {
public:
    int mRed;
    int mGreen;
    int mBlue;
    int mAlpha;

    static Color Black;
    static Color White;

    Color();
    Color(int theColor);
    Color(int theColor, int theAlpha);
    Color(int theRed, int theGreen, int theBlue);
    Color(int theRed, int theGreen, int theBlue, int theAlpha);
    Color(const SexyRGBA &theColor);
    Color(const uchar* theElements);
    Color(const int* theElements);

    int						GetRed() const;
    int						GetGreen() const;
    int						GetBlue() const;
    int						GetAlpha() const;
    ulong					ToInt() const;
    SexyRGBA				ToRGBA() const;

    int&					operator[](int theIdx);
    int						operator[](int theIdx) const;
};

bool operator==(const Color& theColor1, const Color& theColor2);
bool operator!=(const Color& theColor1, const Color& theColor2);

}


#endif // PLANTSVSZOMBIES_ANDROIDTV_COLOR_H
