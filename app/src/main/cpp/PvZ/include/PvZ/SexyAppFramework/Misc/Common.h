//
// Created by 28636 on 2025/4/29.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_COMMON_H
#define PLANTSVSZOMBIES_ANDROIDTV_COMMON_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <cstdlib>

#include "PvZ/Symbols.h"

typedef std::string SexyString; // 不确定，猜测是std::string
#define _S(x) x

typedef SexyString::value_type SexyChar;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#define LENGTH(anyarray) (sizeof(anyarray) / sizeof(anyarray[0]))

enum PixelFormat {
    kPixelFormat_None = -1,
    kPixelFormat_Automatic,
    kPixelFormat_RGBA8888,
    kPixelFormat_RGBA4444,
    kPixelFormat_RGBA5551,
    kPixelFormat_RGB565,
    kPixelFormat_RGB888,
    kPixelFormat_L8,
    kPixelFormat_A8,
    kPixelFormat_LA88,
    kPixelFormat_RGB_PVRTC2,
    kPixelFormat_RGB_PVRTC4,
    kPixelFormat_RGBA_PVRTC2,
    kPixelFormat_RGBA_PVRTC4
};

namespace Sexy {

inline int Rand(int range) { return reinterpret_cast<int (*)(int)>(Sexy_RandIntAddr)(range); }
inline float Rand(float range) { return reinterpret_cast<float (*)(float)>(Sexy_RandFloatAddr)(range); }

}

#endif // PLANTSVSZOMBIES_ANDROIDTV_COMMON_H
