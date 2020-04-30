/*****************************************************************************
 * File: ColorBuffer.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __COLOR_BUFFER_H__
#define __COLOR_BUFFER_H__

#include <vector>

#include "Color.h"

class ColorBuffer {
public:
    ColorBuffer(unsigned int width, unsigned int height);
    ~ColorBuffer() = default;
    void set(unsigned int x, unsigned int y, const Color &color);
    Color get(unsigned int x, unsigned int y) const;
    void clear(const Color &color);
    Color& operator[](std::size_t idx) { return colors[idx]; }
    const Color& operator[](std::size_t idx) const { return colors[idx]; }
    unsigned int getWidth() { return width; };
    unsigned int getHeight() { return height; };

private:
    std::vector<Color> colors;
    unsigned int width;
    unsigned int height;
};

#endif // __COLOR_BUFFER_H__
