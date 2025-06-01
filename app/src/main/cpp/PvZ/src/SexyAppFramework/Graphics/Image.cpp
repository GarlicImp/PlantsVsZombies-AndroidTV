//
// Created by 28636 on 2025/5/26.
//

#include "PvZ/SexyAppFramework/Graphics/Image.h"

using namespace Sexy;

int Image::GetWidth()
{
    return mWidth;
}

int	Image::GetHeight()
{
    return mHeight;
}

int Image::GetCelHeight()
{
    return mHeight / mNumRows;
}

int Image::GetCelWidth()
{
    return mWidth / mNumCols;
}