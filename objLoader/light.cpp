#include "light.h"

#include "cube.h"

Light::Light()
{
    InitRepr();
    SetDir(vec3(0., 0., 0.));
}

Light::Light(const vec3& dir)
{
    InitRepr();
    SetDir(dir);
}

void Light::SetDir(const vec3& dir)
{
    cube_->Model() = mat4();
    dir_ = vec4(dir.x, dir.y, dir.z, 0.);
    cube_->Move(-dir_.x, -dir_.y, -dir_.z);
    cube_->Scale(0.1, 0.1, 0.1);
}

vec4& Light::GetDir()
{
    return dir_;
}

Light::~Light()
{

}


#include "Material/material.h"

void Light::InitRepr()
{
    dir_ = vec4(0.);

    MaterialPtr material = std::make_shared<SolidColorMaterial>(/*vec3(0.5, 0.8, 0.2)*/);
    cube_ = std::make_shared<Cube>(material);

    //cube->Scale();
}

DrawableObjectPtr Light::GetRepr()
{
    return cube_;
}

