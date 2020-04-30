/*****************************************************************************
 * File: World.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __WORLD_H__
#define __WORLD_H__

#include <vector>

#include "LightSource.h"
#include "Shader.h"
#include "Shape.h"

class World {
public:
    World() = default;
    ~World() = default;
    void add_light(const LightSource& light);
    void add_shape(Shape* shape);
    void add_shader(Shader* shader);

    std::vector<LightSource> light_sources;
    std::vector<Shape*> shapes;
    std::vector<Shader*> shaders;
};

#endif // __WORLD_H__
