/*****************************************************************************
 * File: main.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "SDL2/SDL.h"

#define GLM_FORCE_CXX17
#include "glm/common.hpp"
#include "glm/geometric.hpp"

#include "PixelBuffer.h"
#include "Sphere.h"
#include "PhongShader.h"
#include "World.h"
#include "LightSource.h"
#include "RayTracer.h"

#include "ConstructiveSolid.h"
#include "Ball.h"

// glm::vec3
// shade(const Sphere &obj, const Ray &ray, const glm::dvec3 &light, double dist) {
//     // ambient
//     const glm::dvec3 ambient{0.1, 0.1, 0.1};

//     // Diffuse
//     auto point = ray.point(dist);
//     auto normal = obj.normal(point);
//     auto light_vector = glm::normalize(light - point);
//     auto intensity = glm::dot(normal, light_vector);
//     intensity = intensity >= 0.0 ? intensity : 0.0;
//     intensity *= 0.6;

//     // Specular
//     auto reflect_vector = glm::reflect(-light_vector, normal);
//     glm::dvec3 view_vector{0.0,0.0,-1.0};
//     auto specular_intensity = glm::pow(glm::max(glm::dot(view_vector, reflect_vector), 0.0), 32);
//     specular_intensity *= 0.3;

//     intensity += specular_intensity;
//     auto total = ambient + glm::dvec3{intensity, intensity, intensity};

//     return total; //glm::clamp(total, glm::vec3{0.0, 0.0, 0.0}, glm::vec3{1.0, 1.0, 1.0});
// }

int
main(int argc, char *argv[]) {
    const std::string greeting = "CatEye vAlpha";
    std::cout << greeting << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL_init() error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        greeting.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow() error: " << SDL_GetError() << std::endl;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer() error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, 640, 480);

    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        640, 480);
    if (texture == nullptr) {
        std::cerr << "SDL_CreateTexture() error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Clear window.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Shaders to color shapes later on.
    PhongShader grayish;
    PhongShader reddish{0.1, 0.6, 0.3, 16.0, {1.0, 0.2, 0.2}, {1.0, 0.2, 0.2}};
    PhongShader bluish{0.1, 0.6, 0.3, 16.0, {0.2, 0.2, 1.0}, {0.2, 0.2, 1.0}};

    // Create world.
    World world;
    LightSource light_1{glm::dvec3{10.0, 10.0, -15.0}};
    world.add_light(light_1);
    // Sphere s1{&grayish, {0.0, 0.0, 0.0}, 0.8};
    // Sphere s2{&bluish, {0.5, 0.0, -0.3}, 0.5};
    // world.add_shape(&s1);
    // world.add_shape(&s2);

    Ball b1{&grayish, {0.0, 0.0, 0.0}, 0.8};
    Ball b2{&reddish, {0.7, 0.0, -0.4}, 0.5};
    Ball b3{&reddish, {-0.7, 0.0, -0.4}, 0.5};
    Ball b4{&bluish, {0.0, 0.0, 0.0}, 0.75};
    ConstructiveSolid balls1{&b2, &b3, ConstructiveSolid::UNION};
    ConstructiveSolid balls2{&balls1, &b4, ConstructiveSolid::UNION};
    ConstructiveSolid solid1{&b1, &balls2, ConstructiveSolid::DIFFERENCE};
    world.add_shape(&solid1);

    // Draw something.
    PixelBuffer pixels{640, 480};
    RayTracer rt;
    rt.render(pixels, world);

    std::cout << "count=" << SegmentList::count << std::endl;
    std::cout << "count_des=" << SegmentList::count_des << std::endl;
    std::cout << "acu_size=" << SegmentList::acu_size << std::endl;
    std::cout << "average=" << SegmentList::acu_size / SegmentList::acu_size << std::endl;
    std::cout << "max=" << SegmentList::max << std::endl;

    // Update window.
    SDL_UpdateTexture(texture, NULL, pixels.getRawPixelBuffer(), pixels.getWidth() * sizeof (Uint32));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Wait until user quits window..
    bool goon = true;
    while (goon) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goon = false;
            } else if (event.type == SDL_KEYUP){
                // Scancodes are meant to be layout-independent. Think of this
                // as "the user pressed the Q key as it would be on a
                // US QWERTY keyboard" regardless of whether this is actually
                // a European keyboard or a Dvorak keyboard or whatever. The
                // scancode is always the same key position.
                // Keycodes are meant to be layout-dependent. Think of this as
                // "the user pressed the key that is labelled 'Q' on a
                // specific keyboard."
                // In example, if you pressed the key that's two keys to the
                // right of CAPS LOCK on a US QWERTY keyboard, it'll report a
                // scancode of SDL_SCANCODE_S and a keycode of SDLK_S. The
                // same key on a Dvorak keyboard, will report a scancode of
                // SDL_SCANCODE_S and a keycode of SDLK_O.
                // std::cout << "Scancode: " << event.key.keysym.scancode << std::endl;
                // std::cout << "Keycode:  " << event.key.keysym.sym << std::endl;

                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    goon = false;
                }
            }
        }
        SDL_Delay(30);
    }

    // Clean up.
    SDL_DestroyTexture(texture);
    texture = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();

    return 0;
}
