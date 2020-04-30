/*****************************************************************************
 * File: RayTracer.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include "Color.h"
#include "Intersection.h"
#include "LightSource.h"
#include "PixelBuffer.h"
#include "Ray.h"
#include "World.h"

class RayTracer {
public:
    RayTracer() = default;
    ~RayTracer() = default;
    void render(PixelBuffer &buffer, const World& world) const;

private:
    Intersection get_closest_intersection(const Ray &ray, const World& world) const;
    Color shade_intersection(const Intersection& inter, const Ray& ray, const LightSource &light_1) const;
};

#endif // __RAY_TRACER_H__
