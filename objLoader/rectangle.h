#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <memory>

#include "utility.h"
#include "drawableobject.h"

class Rectangle : public DrawableObject
{
public:
    Rectangle(MaterialPtr &material, float width = 1., float height = 1.);
    virtual bool Draw();
    virtual ~Rectangle();

private:
    void InitBuffers(float width, float height);

    std::vector<vec3> data_;
    std::vector<vec3> color_;
    std::vector<vec3> normal_;

    GLuint VAO_;
};

typedef std::shared_ptr<Rectangle> RectanglePtr;

#endif // RECTANGLE_H
