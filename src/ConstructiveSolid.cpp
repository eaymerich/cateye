/*****************************************************************************
 * File: ConstructiveSolid.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include <algorithm>
#include "ConstructiveSolid.h"

ConstructiveSolid::ConstructiveSolid(Solid *a, Solid *b, SolidOperation op)
    : Solid{nullptr}, a{a}, b{b}, op{op}
{
    if (op == UNION) {
        SegmentList (SegmentList::*mpf)(const SegmentList&) const = &SegmentList::uunion;
        oper = mpf;
    } else if (op == INTERSECTION) {
        SegmentList (SegmentList::*mpf)(const SegmentList&) const = &SegmentList::intersection;
        oper = mpf;
    } else if (op == DIFFERENCE) {
        SegmentList (SegmentList::*mpf)(const SegmentList&) const = &SegmentList::difference;
        oper = mpf;
    }
}


ConstructiveSolid::~ConstructiveSolid()
{}

Intersection
ConstructiveSolid::intersect(const Ray &ray) const
{
    auto result = getSegments(ray);

    if (result.size() == 0) {
        return Intersection(
            std::numeric_limits<double>::infinity(),
            this,
            Intersection::INWARD);
    }

    return result[0].a;
}

glm::dvec3
ConstructiveSolid::normal(const glm::dvec3 &point) const
{
    return glm::dvec3();
}

SegmentList
ConstructiveSolid::getSegments(const Ray &ray) const
{
    auto a_segments = a->getSegments(ray);
    auto b_segments = b->getSegments(ray);
    return oper(a_segments, b_segments);
}
