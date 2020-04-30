/*****************************************************************************
 * File: LightSource.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __LIGHT_SOURCE_H__
#define __LIGHT_SOURCE_H__

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

class LightSource {
public:
    LightSource(const glm::dvec3 &position);
    ~LightSource() = default;

    glm::dvec3 position;
};

#endif // __LIGHT_SOURCE_H__
