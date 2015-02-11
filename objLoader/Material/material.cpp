#include "material.h"

Material::Material()
{

}

Material::~Material()
{

}

ProgramPtr& Material::GetProgram()
{
    return program_;
}


SolidColorMaterial::SolidColorMaterial(/*const vec3& color*/)
{
    program_ = std::make_shared<Program>("../shaders/solid_color.vs", "../shaders/solid_color.fs");
    program_->Build();
}

SolidColorMaterial::~SolidColorMaterial()
{

}

ShadedMaterial::ShadedMaterial()
{
    program_ = std::make_shared<Program>("../shaders/shaded.vs", "../shaders/shaded.fs");
    program_->Build();
}

ShadedMaterial::~ShadedMaterial()
{

}
