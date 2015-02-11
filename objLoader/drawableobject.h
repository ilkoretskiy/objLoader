#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <memory>

#include "program.h"
#include "geometry.h"

#include "Material/material.h"

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class DrawableObject
{

public:
    DrawableObject(MaterialPtr& material);
    virtual bool Draw() = 0;
    virtual ~DrawableObject(){}

    MaterialPtr &GetMaterial();

    void Move(float x, float y, float z);
    void Scale(float x, float y, float z);
    void Rotate(float angle, glm::vec3 direction);

    mat4& Model();


protected:
    MaterialPtr material_;
    glm::mat4 model_;
};

typedef std::shared_ptr<DrawableObject> DrawableObjectPtr;

#endif // DRAWABLEOBJECT_H

/*
TEST()
{
    ConstColorMaterial constColorMaterial(vec3(0.5, 0.2, 0.5));
    ShadedColorMaterial constColorMaterial(vec3(0.5, 0.2, 0.5));

    Cube cube(vec3(1., 1., 1), constColorMaterial);
}
*/
