/*****************************************************************************
 * File: PixelBuffer.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __PIXEL_BUFFER_H__
#define __PIXEL_BUFFER_H__

#include <cstdint>

class PixelBuffer {
public:
    PixelBuffer(unsigned int width, unsigned int height);
    ~PixelBuffer();
    void setPixelColor(unsigned int x, unsigned int y, double red, double green, double blue);
    void setPixelColor(std::size_t idx, double red, double green, double blue);
    uint32_t* getRawPixelBuffer();
    unsigned int getWidth();
    unsigned int getHeight();

private:
    double clampZeroOne(double val) const;
    uint32_t mixColors(double red, double green, double blue) const;

    uint32_t *pixels;
    unsigned int width;
    unsigned int height;
};

#endif // __PIXEL_BUFFER_H__
