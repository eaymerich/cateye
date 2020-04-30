/*****************************************************************************
 * File: ColorBuffer.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include "ColorBuffer.h"

ColorBuffer::ColorBuffer(unsigned int width, unsigned int height)
    : width{width}, height{height}
{
    colors.resize(width * height);
}

void
ColorBuffer::set(unsigned int x, unsigned int y, const Color &color)
{
    colors[y * width + x] = color;
}

Color
ColorBuffer::get(unsigned int x, unsigned int y) const
{
    return colors[y * width + x];
}

void
ColorBuffer::clear(const Color &color)
{
    for (auto &col : colors) {
        col = color;
    }
}
