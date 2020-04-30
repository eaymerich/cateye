/*****************************************************************************
 * File: Shader.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __SHADER_H__
#define __SHADER_H__

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

#include "Color.h"
#include "Ray.h"

class Shader {
public:
    Shader() = default;
    virtual ~Shader() = default;
    virtual Color shade(
        const glm::dvec3 &point,
        const glm::dvec3 &normal,
        const glm::dvec3 &light) const = 0;
};

#endif // __SHADER_H__
