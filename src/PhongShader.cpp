/*****************************************************************************
 * File: PhongShader.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#define GLM_FORCE_CXX17
#include "glm/common.hpp"
#include "glm/geometric.hpp"

#include "PhongShader.h"

PhongShader::PhongShader(double ambient_coefficient,
                         double diffuse_coefficient,
                         double specular_coefficient,
                         double specular_power,
                         const glm::dvec3 &ambient_color,
                         const glm::dvec3 &diffuse_color,
                         const glm::dvec3 &specular_color) :
    ambient_coefficient{ambient_coefficient},
    diffuse_coefficient{diffuse_coefficient},
    specular_coefficient{specular_coefficient},
    specular_power{specular_power},
    ambient_color{ambient_color},
    diffuse_color{diffuse_color},
    specular_color{specular_color}
{}

PhongShader::~PhongShader()
{}

Color
PhongShader::shade(const glm::dvec3 &point, const glm::dvec3 &normal, const glm::dvec3 &light) const 
{
    // Diffuse
    auto light_vector = glm::normalize(light - point);
    auto diffuse_intensity = glm::dot(normal, light_vector);
    diffuse_intensity = diffuse_intensity >= 0.0 ? diffuse_intensity : 0.0;

    // Specular
    auto reflect_vector = glm::reflect(-light_vector, normal);
    glm::dvec3 view_vector{0.0,0.0,-1.0};
    auto specular_intensity = glm::pow(
        glm::max(glm::dot(view_vector, reflect_vector), 0.0),
        specular_power);

    auto ambient_part = ambient_color;
    ambient_part *= ambient_coefficient;
    auto diffuse_part = diffuse_color;
    diffuse_part *= diffuse_intensity * diffuse_coefficient;
    auto specular_part = specular_color;
    specular_part *= specular_intensity * specular_coefficient;

    return Color(ambient_part + diffuse_part + specular_part);
}
