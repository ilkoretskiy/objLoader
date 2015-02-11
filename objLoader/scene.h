#ifndef SCENE_H
#define SCENE_H

#include <deque>

#include "drawableobject.h"
#include "light.h"

#define GLM_FORCE_RADIANS
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

class Scene
{
public:
    Scene();
    ~Scene();

    void SetLight(const LightPtr& light);
    bool AddObject(const DrawableObjectPtr& drawableObject);
    bool Draw(const glm::mat4 &projection, const glm::mat4 &view);

private:
    LightPtr light_;
    std::deque<DrawableObjectPtr> objects_;
};

#endif // SCENE_H
