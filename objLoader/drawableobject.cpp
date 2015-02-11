#include "drawableobject.h"

#include <glm/gtc/matrix_transform.hpp>

DrawableObject::DrawableObject(MaterialPtr& material)
{
    model_ = mat4(1);
    material_ = material;
}

MaterialPtr& DrawableObject::GetMaterial()
{
    return material_;
}

void DrawableObject::Move(float x, float y, float z)
{
    model_ = glm::translate(model_, vec3(x, y, z));
}

void DrawableObject::Scale(float x, float y, float z)
{
    model_ = glm::scale(model_, vec3(x, y, z));
}

void DrawableObject::Rotate(float angle, vec3 direction)
{
    model_ = glm::rotate(model_, angle, direction);
}

mat4& DrawableObject::Model()
{
    return model_;
}
