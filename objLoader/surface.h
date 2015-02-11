#ifndef SURFACE_H
#define SURFACE_H

#include <vector>

#include "geometry.h"

#include "drawableobject.h"

#include "rectangle.h"

class Surface : public DrawableObject
{
public:
    Surface(MaterialPtr &material, float width, float height);

    virtual bool Draw();

    virtual ~Surface();

private:
    void InitBuffers();

private:
    std::vector<PosF> lines_;

    bool isValid;

    GLuint VAO_;
};

typedef std::shared_ptr<Surface> SurfacePtr;

#endif // SURFACE_H
