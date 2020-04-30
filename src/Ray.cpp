/*****************************************************************************
 * File: Ray.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#define GLM_FORCE_CXX17
#include "glm/common.hpp"

#include "Ray.h"

glm::dvec3
Ray::point(double distance) const {
    glm::dvec3 displacement = direction;
    displacement *= distance;
    return origin + displacement;
}
