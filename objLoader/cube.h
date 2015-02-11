#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <memory>

#include "utility.h"
#include "drawableobject.h"
#include "Material/material.h"

class Cube : public DrawableObject
{
public:
    Cube(MaterialPtr& material,
         const glm::vec3& size = glm::vec3(1., 1., 1.));
    virtual ~Cube();

    virtual bool Draw();
private:
    enum class AXIS{XY, XZ, YZ};

    void UpdateIndecies(int width, int height, int startIndex, int stride);
    void GeneratePlane(float width , float height, float depth, float widthOffset, float heightOffset, float depthOffset, AXIS axis);
    void InitBuffers();

    typedef glm::mediump_ivec3 IndexType;
    std::vector<glm::vec3> data_;
    std::vector<IndexType> indecies_;
    std::vector<glm::vec3> color_;

    std::vector<vec3> normal_;

    GLuint VAO_;
};

typedef std::shared_ptr<Cube> CubePtr;

#endif // CUBE_H
