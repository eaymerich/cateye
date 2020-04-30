/*****************************************************************************
 * File: Ray.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __RAY_H__
#define __RAY_H__

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

class Ray {
public:
    glm::dvec3 point(double distance) const;
    glm::dvec3 origin;
    glm::dvec3 direction;
    double min_t;
    double max_t;
};

#endif // __RAY_H__
