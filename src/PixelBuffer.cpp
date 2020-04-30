/*****************************************************************************
 * File: PixelBuffer.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include <cmath>
#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(unsigned int width, unsigned int height) :
    pixels{nullptr}, width{width}, height{height} {
    pixels = new uint32_t[width * height];
}

PixelBuffer::~PixelBuffer() {
    delete [] pixels;
}

void
PixelBuffer::setPixelColor(unsigned int x, unsigned int y, double red, double green, double blue) {
    pixels[(y * width) + x] = mixColors(red, green, blue);
}

void
PixelBuffer::setPixelColor(std::size_t idx, double red, double green, double blue) {
    pixels[idx] = mixColors(red, green, blue);
}

uint32_t*
PixelBuffer::getRawPixelBuffer() {
    return pixels;
}

double
PixelBuffer::clampZeroOne(double val) const {
    val = val > 0.0 ? val : 0.0;
    val = val < 1.0 ? val : 1.0;
    return val;
}

uint32_t
PixelBuffer::mixColors(double red, double green, double blue) const {
    red   = clampZeroOne(red);
    green = clampZeroOne(green);
    blue  = clampZeroOne(blue);
    uint32_t red_i   = ((uint32_t)lround(red   * 255.0)) & 0xFF;
    uint32_t green_i = ((uint32_t)lround(green * 255.0)) & 0xFF;
    uint32_t blue_i  = ((uint32_t)lround(blue  * 255.0)) & 0xFF;
    return 0xFF000000 | (red_i << 16) | (green_i << 8) | blue_i;
}

unsigned int
PixelBuffer::getWidth() {
    return width;
}

unsigned int
PixelBuffer::getHeight() {
    return height;
}
