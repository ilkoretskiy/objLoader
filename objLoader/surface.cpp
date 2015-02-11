#include "surface.h"

#include "utility.h"

Surface::Surface(MaterialPtr& material, float width, float height):
    DrawableObject(material)
{
    float offsetX = width * 0.5;
    float offsetY = height * 0.5;

    for (int row = 0; row <= height; row++)
    {
        PosF start(0 - offsetX, row - offsetY);
        PosF end(width - offsetX, row - offsetY);
        lines_.push_back(start);
        lines_.push_back(end);
    }

    for (int col = 0; col <= width; col++)
    {
        PosF start(col - offsetX, 0 - offsetY);
        PosF end(col - offsetX, height - offsetY);
        lines_.push_back(start);
        lines_.push_back(end);
    }

    isValid = false;
}

Surface::~Surface()
{

}

bool Surface::Draw()
{
    if (!isValid)
    {
        InitBuffers();
    }

    glBindVertexArray(VAO_);
    glDrawArrays(GL_LINES, 0, lines_.size());
    glBindVertexArray(0); check_gl_error();

    return true;
}

void Surface::InitBuffers()
{
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    GLuint buffer;
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer); check_gl_error();
    GLuint bufferSize = lines_.size() * sizeof(PosF);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, &lines_[0], GL_STATIC_DRAW); check_gl_error();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr); check_gl_error();
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &buffer); check_gl_error();

    isValid = true;
}
