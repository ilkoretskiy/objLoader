#ifndef LIGHT_H
#define LIGHT_H

#include <memory>
#include "geometry.h"
#include "cube.h"
#include "drawableobject.h"

class Light
{
public:
    Light();
    Light(const vec3& dir);
    virtual ~Light();

    void SetDir(const vec3& dir);
    vec4& GetDir();

    DrawableObjectPtr GetRepr();

private:
    void InitRepr();

    vec4 dir_;
    CubePtr cube_;
};

typedef std::shared_ptr<Light> LightPtr;

#endif // LIGHT_H
