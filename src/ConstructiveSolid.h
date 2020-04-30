/*****************************************************************************
 * File: ConstructiveSolid.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __CONSTRUCTIVE_SOLID_H__
#define __CONSTRUCTIVE_SOLID_H__

#include <functional>
#include "Solid.h"
#include "Shape.h"

class ConstructiveSolid : public Solid {
public:
    enum SolidOperation {
        UNION,
        INTERSECTION,
        DIFFERENCE
    };

    ConstructiveSolid(Solid *a, Solid *b, SolidOperation op);
    virtual ~ConstructiveSolid();
    virtual Intersection intersect(const Ray &ray) const override;
    virtual glm::dvec3 normal(const glm::dvec3 &point) const override;
    virtual SegmentList getSegments(const Ray &ray) const override;

private:
    Solid *a;
    Solid *b;
    SolidOperation op;
    std::function<SegmentList(const SegmentList&, const SegmentList&)> oper;
};

#endif // __CONSTRUCTIVE_SOLID_H__
