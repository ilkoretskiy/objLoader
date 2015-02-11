#include "model.h"

#include "wavefrontobjloader.h"

Model::Model(MaterialPtr& material, const std::string& path):
    DrawableObject(material)
{
    Open(path);
    InitBuffers();
}

Model::~Model()
{

}

bool Model::Draw()
{
    glBindVertexArray(VAO_);

    GLuint size = data_.size() * sizeof(vec3);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glBindVertexArray(0);

    return true;
}

void Model::Open(const std::string& path)
{
    WavefrontObjLoader objLoader;
    objLoader.Load(path);
    objLoader.Fill(data_, normals_, color_);
}

void Model::InitBuffers()
{
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    GLuint buffers[4];
    glGenBuffers(4, buffers);

    // vertecies
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    GLuint bufferVSize = data_.size() * sizeof(glm::vec3);
    glBufferData(GL_ARRAY_BUFFER, bufferVSize, &data_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // colours
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    GLuint bufferCSize = color_.size() * sizeof(glm::vec3);
    glBufferData(GL_ARRAY_BUFFER, bufferCSize, &color_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // normals
    glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    const int sizeNormals = normals_.size() * sizeof(vec3);
    glBufferData(GL_ARRAY_BUFFER, sizeNormals, &normals_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(4, buffers);
}
