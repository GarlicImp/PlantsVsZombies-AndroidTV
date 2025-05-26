//
// Created by 28636 on 2025/5/26.
//

#ifndef PLANTSVSZOMBIES_ANDROIDTV_RECT_H
#define PLANTSVSZOMBIES_ANDROIDTV_RECT_H

#include "Common.h"
#include "Point.h"

#include <list>

namespace Sexy {
template <class _T>
class TRect {
public:
    _T mX;
    _T mY;
    _T mWidth;
    _T mHeight;

    TRect(_T theX, _T theY, _T theWidth, _T theHeight)
        : mX(theX)
        , mY(theY)
        , mWidth(theWidth)
        , mHeight(theHeight) {}

    TRect(const TRect<_T> &theTRect)
        : mX(theTRect.mX)
        , mY(theTRect.mY)
        , mWidth(theTRect.mWidth)
        , mHeight(theTRect.mHeight) {}

    TRect()
        : mX(0)
        , mY(0)
        , mWidth(0)
        , mHeight(0) {}

    bool Contains(_T theX, _T theY) const { return ((theX >= mX) && (theX < mX + mWidth) && (theY >= mY) && (theY < mY + mHeight)); }

        bool					Contains(const TPoint<_T>& thePoint) const
        {
            return ((thePoint.mX >= mX) && (thePoint.mX < mX + mWidth) &&
                    (thePoint.mY >= mY) && (thePoint.mY < mY + mHeight));
        }

    void Offset(_T theX, _T theY) {
        mX += theX;
        mY += theY;
    }

        void					Offset(const TPoint<_T>& thePoint)
        {
            mX += thePoint.mX;
            mY += thePoint.mY;
        }
};

typedef TRect<int> Rect;
typedef TRect<double> FRect;
} // namespace Sexy


#endif // PLANTSVSZOMBIES_ANDROIDTV_RECT_H
