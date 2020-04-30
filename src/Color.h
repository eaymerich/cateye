/*****************************************************************************
 * File: Color.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __COLOR_H__
#define __COLOR_H__

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

class Color {
public:
    Color(double r = 0.0, double g = 0.0, double b = 0.0) : color{r, g, b} {};
    Color(const glm::dvec3 &color) : color{color} {};
    ~Color() = default;
    double r() const { return color.r; };
    double g() const { return color.g; };
    double b() const { return color.b; };
    Color& operator+=(const Color &other) { color += other.color; return *this; };
    Color& operator*=(double other) { color *= other; return *this; };
    friend Color operator+(Color left, const Color &right) { left += right; return left; };
    friend Color operator*(Color left, double right) { left.color *= right; return left; };

    glm::dvec3 color;
};

#endif // __COLOR_H__
