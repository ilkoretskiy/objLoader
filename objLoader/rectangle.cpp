#include "rectangle.h"

#include <vector>

Rectangle::Rectangle(MaterialPtr& material, float width, float height):
    DrawableObject(material)
{
    InitBuffers(width, height);
}

bool Rectangle::Draw()
{
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, data_.size());
    glBindVertexArray(0);
}

Rectangle::~Rectangle()
{

}

void Rectangle::InitBuffers(float width, float height)
{
    glm::vec3 baseColor(0.5, 0.8, 0.2);

    float offsetX = width * 0.5;
    float offsetY = height * 0.5;

    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < height; col++)
        {
            color_.push_back(baseColor);
            data_.push_back(vec3(row - offsetX, col - offsetY, 0.));
            normal_.push_back(vec3(0., 0., 1));

            color_.push_back(baseColor);
            data_.push_back(glm::vec3(row + 1 - offsetX, col + 1 - offsetY, 0.));
            normal_.push_back(vec3(0., 0., 1));

            color_.push_back(baseColor);
            data_.push_back(glm::vec3(row + 1 - offsetX, col - offsetY, 0.));
            normal_.push_back(vec3(0., 0., 1));

            color_.push_back(baseColor);
            data_.push_back(glm::vec3(row - offsetX, col - offsetY, 0.));
            normal_.push_back(vec3(0., 0., 1));

            color_.push_back(baseColor);
            data_.push_back(glm::vec3(row + 1 - offsetX, col + 1 - offsetY, 0.));
            normal_.push_back(vec3(0., 0., 1));

            color_.push_back(baseColor);
            data_.push_back(glm::vec3(row - offsetX, col + 1 - offsetY, 0.));
            normal_.push_back(vec3(0., 0., 1));
        }
    }

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    GLuint buffer[3];

    glGenBuffers(3, buffer);

    // vertex
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    int vertexSize = data_.size() * sizeof(glm::vec3);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, &data_[0], GL_STATIC_DRAW );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    check_gl_error();

    // color
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    int colorSize = color_.size() * sizeof(glm::vec3);
    glBufferData(GL_ARRAY_BUFFER, colorSize , &color_[0], GL_STATIC_DRAW );
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    check_gl_error();

    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    int normalSize = normal_.size() * sizeof(glm::vec3);
    glBufferData(GL_ARRAY_BUFFER, normalSize, &normal_[0], GL_STATIC_DRAW );
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);
    check_gl_error();


    glBindVertexArray(0);

    glDeleteBuffers(3, buffer); check_gl_error();
}
