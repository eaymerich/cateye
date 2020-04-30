/*****************************************************************************
 * File: Intersect.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

class Shape;

class Intersection {
public:
    enum IntersectType {
        INWARD,
        OUTWARD
    };

    Intersection(double distance = 0.0, const Shape *shape = nullptr, IntersectType type = INWARD) :
        distance(distance), shape(shape), type(type)
    {};

    inline bool operator<(const Intersection& other) const {
        return distance < other.distance;
    };

    inline bool operator>(const Intersection& other) const {
        return distance > other.distance;
    };

    inline bool operator<=(const Intersection& other) const {
        return distance <= other.distance;
    };

    inline bool operator>=(const Intersection& other) const {
        return distance >= other.distance;
    };

    const Shape* getShape() const {
        return shape;
    };

    double getDistance() const {
        return distance;
    };

    double getType() const {
        return type;
    };

private:
    double distance;
    const Shape* shape;
    IntersectType type;
};

#endif // __INTERSECTION_H__
