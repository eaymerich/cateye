/*****************************************************************************
 * File: PhongShader.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __PHONG_SHADER_H__
#define __PHONG_SHADER_H__

#define GLM_FORCE_CXX17
#include "glm/vec3.hpp"

#include "Color.h"
#include "Ray.h"
#include "Shader.h"
#include "Shape.h"

class PhongShader : public Shader {
public:
    PhongShader(double ambient_coefficient = 0.1,
                double diffuse_coefficient = 0.5,
                double specular_coefficient = 0.4,
                double specular_power = 16.0,
                const glm::dvec3 &ambient_color = {1.0, 1.0, 1.0},
                const glm::dvec3 &diffuse_color = {1.0, 1.0, 1.0},
                const glm::dvec3 &specular_color = {1.0, 1.0, 1.0});
    virtual ~PhongShader();
    virtual Color shade(
        const glm::dvec3 &point,
        const glm::dvec3 &normal,
        const glm::dvec3 &light) const override;

private:
    double ambient_coefficient;
    double diffuse_coefficient;
    double specular_coefficient;
    double specular_power;
    glm::dvec3 ambient_color;
    glm::dvec3 diffuse_color;
    glm::dvec3 specular_color;
};

#endif // __PHONG_SHADER_H__
