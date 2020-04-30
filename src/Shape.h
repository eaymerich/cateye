/*****************************************************************************
 * File: Shape.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

#include "Intersection.h"
#include "Ray.h"
#include "Shader.h"

class Shape {
public:
    Shape(const Shader* shader) : shader{shader} {};
    virtual ~Shape() = default;
    virtual const Shader* getShader() const { return shader; };
    virtual Intersection intersect(const Ray &ray) const = 0;
    virtual glm::dvec3 normal(const glm::dvec3 &point) const = 0;

private:
    const Shader *shader;
};

#endif // __SHAPE_H__
