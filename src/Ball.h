/*****************************************************************************
 * File: Ball.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __BALL_H__
#define __BALL_H__

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

#include "Shader.h"
#include "Solid.h"

class Ball : public Solid {
public:
    Ball(const Shader *shader, glm::dvec3 center, double radius);
    virtual ~Ball() = default;
    virtual Intersection intersect(const Ray &ray) const override;
    virtual glm::dvec3 normal(const glm::dvec3 &point) const override;
    virtual SegmentList getSegments(const Ray &ray) const override;

protected:
    glm::dvec3 center;
    double radius;

    void get_discriminant(
        const Ray &ray, double &discriminant, double &a, double &b) const;
};

#endif
