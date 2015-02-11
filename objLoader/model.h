#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

#include "drawableobject.h"
#include "utility.h"

class Model : public DrawableObject
{
public:
    Model();

    Model(MaterialPtr &material, const std::string& path);

    virtual bool Draw();
    virtual ~Model();

private:
    void Open(const std::string& path);
    void InitBuffers();

    GLuint VAO_;

    typedef glm::mediump_ivec3 IndexType;
    std::vector<glm::vec3> data_;
    std::vector<glm::vec3> color_;
    std::vector<glm::vec3> normals_;
    std::vector<IndexType> indecies_;
};

typedef std::shared_ptr<Model> ModelPtr;

#endif // MODEL_H
