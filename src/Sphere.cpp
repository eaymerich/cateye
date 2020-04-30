/*****************************************************************************
 * File: Sphere.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include <cmath>
#include <limits>

#define GLM_FORCE_CXX17
#include "glm/geometric.hpp"

#include "Sphere.h"

Sphere::Sphere(const Shader *shader, glm::dvec3 center, double radius) :
    Shape{shader}, center{center}, radius{radius}
{}

Sphere::~Sphere()
{}

void Sphere::get_discriminant(
    const Ray &ray, double &discriminant, double &a, double &b) const {

    glm::dvec3 o_diff = ray.origin - center;
    a = glm::dot(ray.direction, ray.direction);
    b = 2.0 * glm::dot(o_diff, ray.direction);
    double c = glm::dot(o_diff, o_diff) - (radius * radius);
    discriminant = (b * b) - (4.0 * a * c);
}

Intersection
Sphere::intersect(const Ray &ray) const {
    double discriminant = 0.0;
    double a = 0.0;
    double b = 0.0;

    get_discriminant(ray, discriminant, a, b);

    if (discriminant < 0.0) {
        // There is no intersection.
        return Intersection{
            std::numeric_limits<double>::infinity(),
            this,
            Intersection::INWARD};
        //return std::numeric_limits<double>::infinity();
        //return std::numeric_limits<double>::quiet_NaN();
    }

    double t0 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (t0 > ray.min_t && t0 < ray.max_t) {
        return Intersection{t0, this, Intersection::INWARD};
        //return t0;
    }

    double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    if (t1 > ray.min_t && t1 < ray.max_t) {
        return Intersection{t1, this, Intersection::OUTWARD};
        //return t1;
    }

    // There is no intersection.
    return Intersection{
        std::numeric_limits<double>::infinity(),
        this,
        Intersection::INWARD};
    //return std::numeric_limits<double>::infinity();
    //return std::numeric_limits<double>::quiet_NaN();
}

glm::dvec3
Sphere::normal(const glm::dvec3 &point) const {
    return glm::normalize(point - center);
}
