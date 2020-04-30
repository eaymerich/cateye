/*****************************************************************************
 * File: Ball.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include <cmath>
#include <limits>

#define GLM_FORCE_CXX17
#include "glm/geometric.hpp"

#include "Ball.h"

Ball::Ball(const Shader *shader, glm::dvec3 center, double radius)
    : Solid{shader}, center{center}, radius{radius}
{}

void
Ball::get_discriminant(
    const Ray &ray, double &discriminant, double &a, double &b) const {

    glm::dvec3 o_diff = ray.origin - center;
    a = glm::dot(ray.direction, ray.direction);
    b = 2.0 * glm::dot(o_diff, ray.direction);
    double c = glm::dot(o_diff, o_diff) - (radius * radius);
    discriminant = (b * b) - (4.0 * a * c);
}

Intersection
Ball::intersect(const Ray &ray) const
{
    double discriminant = 0.0;
    double a = 0.0;
    double b = 0.0;

    get_discriminant(ray, discriminant, a, b);

    if (discriminant < 0.0) {
        // There is no intersection.
        return Intersection(
            std::numeric_limits<double>::infinity(),
            this,
            Intersection::INWARD);
    }

    double t0 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (t0 > ray.min_t && t0 < ray.max_t) {
        return Intersection(t0, this, Intersection::INWARD);;
    }

    double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    if (t1 > ray.min_t && t1 < ray.max_t) {
        return Intersection(t1, this, Intersection::OUTWARD);;
    }

    // There is no intersection in the ray's bounds.
    return Intersection(
        std::numeric_limits<double>::infinity(),
        this,
        Intersection::INWARD);
}

glm::dvec3
Ball::normal(const glm::dvec3 &point) const
{
    return glm::normalize(point - center);
}

SegmentList
Ball::getSegments(const Ray &ray) const
{
    double discriminant = 0.0;
    double a = 0.0;
    double b = 0.0;

    get_discriminant(ray, discriminant, a, b);

    if (discriminant < 0.0) {
        // There is no intersection.
        return SegmentList();
    }

    double t0 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    Segment segment(
        Intersection(t0, this, Intersection::INWARD),
        Intersection(t1, this, Intersection::OUTWARD));
    Segment ray_segment(
        Intersection(ray.min_t, this, Intersection::INWARD),
        Intersection(ray.max_t, this, Intersection::OUTWARD));

    return segment.intersection(ray_segment);
}
