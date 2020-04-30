/*****************************************************************************
 * File: RayTracer.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include <iostream>
#include <chrono> 

#include "ColorBuffer.h"
#include "PhongShader.h"

#include "RayTracer.h"

using namespace std::chrono;

Intersection
RayTracer::get_closest_intersection(const Ray &ray, const World& world) const
{
    Intersection min{std::numeric_limits<double>::infinity()};
    for (const auto shape : world.shapes) {
        auto intersection = shape->intersect(ray);
        if (intersection < min) {
            min = intersection;
        }
    }
    return min;
}

Color
RayTracer::shade_intersection(const Intersection& inter, const Ray& ray, const LightSource &light_1) const
{
    Color color;
    if (nullptr != inter.getShape()) {
        // Shade intersection
        auto point = ray.point(inter.getDistance());
        auto normal = inter.getShape()->normal(point);
        if (inter.getType() == Intersection::OUTWARD) {
            normal = -normal;
        }
        color = inter.getShape()->getShader()->shade(point, normal, light_1.position);
    }
    return color;
}

void
RayTracer::render(PixelBuffer &buffer, const World& world) const
{
    // Timming start.
    auto start = high_resolution_clock::now();

    // Create primary rays.
    Ray r_base;
    r_base.min_t = 0.0;
    r_base.max_t = std::numeric_limits<double>::infinity();
    r_base.origin = glm::dvec3{0.0, 0.0, -2.0};
    r_base.direction = glm::dvec3{0.0, 0.0, 1.0};

    int half_width_i  = buffer.getWidth() / 2;
    int half_height_i = buffer.getHeight() / 2;
    auto half_width  = buffer.getWidth() * 0.5;
    auto half_height = buffer.getHeight() * 0.5;
    auto step_x = 1.0 / half_width;
    auto step_y = 1.0 / half_height;
    auto step = step_x > step_y ? step_x : step_y;
    std::vector<Ray> rays;
    rays.reserve(buffer.getWidth() * buffer.getHeight());
    for (int y = half_height_i; y > -half_height_i; --y) {
        for(int x = -half_width_i; x < half_width_i; ++x) {
            auto new_ray = r_base;
            new_ray.origin.x = step * x;
            new_ray.origin.y = step * y;
            rays.push_back(new_ray);
        }
    }

    LightSource light_1 = world.light_sources[0];

    // Calculate primary interssections
    std::vector<Intersection> intersections;
    intersections.reserve(buffer.getWidth() * buffer.getHeight());
    for (const auto& ray : rays) {
        intersections.push_back(get_closest_intersection(ray, world));
    }

    // Calculate which pixels will need antialias later on.
    // std::vector<bool> is_border(buffer.getWidth() * buffer.getHeight(), false);
    // unsigned int border_pixels = 0;
    // for (unsigned int y = 1; y < buffer.getHeight() - 1; ++y) {
    //     is_border.push_back(false);
    //     for(unsigned int x = 1; x < buffer.getWidth() - 1; ++x) {
    //         const auto &intersection = intersections[y * buffer.getWidth() + x];
    //         const auto &left  = intersections[y * buffer.getWidth() + x - 1];
    //         const auto &right = intersections[y * buffer.getWidth() + x + 1];
    //         const auto &up    = intersections[(y - 1) * buffer.getWidth() + x];
    //         const auto &down  = intersections[(y + 1) * buffer.getWidth() + x];
    //         is_border[y * buffer.getWidth() + x] =
    //             intersection.getShape() != left.getShape() ||
    //             intersection.getShape() != right.getShape() ||
    //             intersection.getShape() != up.getShape() ||
    //             intersection.getShape() != down.getShape();
    //         if (is_border[y * buffer.getWidth() + x]) {
    //             ++border_pixels;
    //         }
    //     }
    //     is_border.push_back(false);
    // }
    // std::cout << "border_pixels=" << border_pixels << std::endl;

    // Shade intersections
    ColorBuffer color_buffer{buffer.getWidth(), buffer.getHeight()};
    for (unsigned int y = 0; y < buffer.getHeight(); ++y) {
        for(unsigned int x = 0; x < buffer.getWidth(); ++x) {
            // if (is_border[y * buffer.getWidth() + x]) {
            //     continue;
            // }
            const auto &ray = rays[y * buffer.getWidth() + x];
            const auto &intersection = intersections[y * buffer.getWidth() + x];

            auto color = shade_intersection(intersection, ray, light_1);
            color_buffer.set(x, y, color);
            //buffer.setPixelColor(x, y, color.r(), color.g(), color.b());
        }
    }

    // // Shade antialias
    // for (unsigned int y = 0; y < buffer.getHeight(); ++y) {
    //     for(unsigned int x = 0; x < buffer.getWidth(); ++x) {
    //         if (is_border[y * buffer.getWidth() + x]) {
    //             const auto &ray = rays[y * buffer.getWidth() + x];
    //             Ray ray_a = ray;
    //             Ray ray_b = ray;
    //             Ray ray_c = ray;
    //             Ray ray_d = ray;
    //             auto quarter_step = step * 0.25;

    //             // Shift rays
    //             ray_a.origin.x += quarter_step;
    //             ray_a.origin.y += quarter_step;
    //             ray_b.origin.x += quarter_step;
    //             ray_b.origin.y -= quarter_step;
    //             ray_c.origin.x -= quarter_step;
    //             ray_c.origin.y -= quarter_step;
    //             ray_d.origin.x -= quarter_step;
    //             ray_d.origin.y += quarter_step;

    //             auto inter_a = get_closest_intersection(ray_a, world);
    //             auto inter_b = get_closest_intersection(ray_b, world);
    //             auto inter_c = get_closest_intersection(ray_c, world);
    //             auto inter_d = get_closest_intersection(ray_d, world);

    //             auto color_a = shade_intersection(inter_a, ray, light_1);
    //             auto color_b = shade_intersection(inter_b, ray, light_1);
    //             auto color_c = shade_intersection(inter_c, ray, light_1);
    //             auto color_d = shade_intersection(inter_d, ray, light_1);

    //             auto color = (color_a + color_b + color_c + color_d) * 0.25;
    //             buffer.setPixelColor(x, y, color.r(), color.g(), color.b());
    //         }
    //     }
    // }

    // Fill Pixel buffer
    for (unsigned int y = 0; y < buffer.getHeight(); ++y) {
        for(unsigned int x = 0; x < buffer.getWidth(); ++x) {
            auto color = color_buffer.get(x, y);
            buffer.setPixelColor(x, y, color.r(), color.g(), color.b());
        }
    }

    // Timming end.
    auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // std::cout << "Render time: " << duration.count() << "us" << std::endl; 
    auto duration_ms = duration_cast<milliseconds>(stop - start);
    std::cout << "Render time: " << duration_ms.count() << "ms" << std::endl; 
}
