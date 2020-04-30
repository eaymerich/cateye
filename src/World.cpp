/*****************************************************************************
 * File: World.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include "World.h"

void
World::add_light(const LightSource& light) {
    light_sources.push_back(light);
}

void
World::add_shape(Shape* shape) {
    shapes.push_back(shape);
}

void
World::add_shader(Shader* shader) {
    shaders.push_back(shader);
}
