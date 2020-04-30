/*****************************************************************************
 * File: Sphere.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __SPHERE_H__
#define __SPHERE_H__

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

#include "Ray.h"
#include "Shader.h"
#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(const Shader *shader, glm::dvec3 center, double radius);
    virtual ~Sphere();
    virtual Intersection intersect(const Ray &ray) const override;
    virtual glm::dvec3 normal(const glm::dvec3 &point) const override;

private:
    glm::dvec3 center;
    double radius;

    void get_discriminant(
        const Ray &ray, double &discriminant, double &a, double &b) const;
};

#endif // __SPHERE_H__
