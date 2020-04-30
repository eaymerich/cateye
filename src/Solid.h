/*****************************************************************************
 * File: Solid.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __SOLID_H__
#define __SOLID_H__

#include <vector>

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

#include "Shader.h"
#include "Shape.h"
#include "Segment.h"

class Solid : public Shape {
public:
    Solid(const Shader* shade) : Shape{shade} {};
    virtual ~Solid() = default;
    virtual SegmentList getSegments(const Ray &ray) const = 0;
};

#endif // __SOLID_H__
