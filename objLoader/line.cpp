#include "line.h"

#include "utility.h"
#include "glm/gtc/type_ptr.hpp"

Line::Line(const PosF &start, const PosF &end)
{
    buffer[0] = start;
    buffer[1] = end;

    distances[0] = 0.;
    distances[1] = end.DistanceTo(start);

    isValid = false;
}

Line::~Line()
{

}

void Line::Draw(const glm::mat4& camera)
{
    if (!isValid)
    {
        program_ =  std::make_shared<Program>("../shaders/dashed_line.vs", "../shaders/dashed_line.fs");
        program_->Build();

        InitBuffers();
    }
    program_->Use(); check_gl_error();

    glBindVertexArray(VAO_); check_gl_error();
    glUniformMatrix4fv(program_->Camera(), 1, GL_FALSE, glm::value_ptr(camera)); check_gl_error();
    GLsizei drawSize = sizeof(PosF) * VertexCount;

    glDrawArrays(GL_LINES, 0, drawSize);
    glBindVertexArray(0);
}

void Line::InitBuffers()
{
    glGenVertexArrays(1, &VAO_); check_gl_error();
    glBindVertexArray(VAO_);     check_gl_error();

    GLuint bufferID[2];
    glGenBuffers(2, bufferID); check_gl_error();

     // bind coordinates
        glBindBuffer(GL_ARRAY_BUFFER, bufferID[0]); check_gl_error();
        GLuint bufferSize = sizeof(PosF) * VertexCount;
        glBufferData(GL_ARRAY_BUFFER, bufferSize, &buffer[0], GL_STATIC_DRAW ); check_gl_error();
        glVertexAttribPointer(0, VertexCount, GL_FLOAT, GL_FALSE, 0, nullptr); check_gl_error();
        glEnableVertexAttribArray(0); check_gl_error();

    // bind distances
        glBindBuffer(GL_ARRAY_BUFFER, bufferID[1]); check_gl_error();
        GLuint distancesSize = sizeof(float) * VertexCount;
        glBufferData(GL_ARRAY_BUFFER, distancesSize, &distances[0], GL_STATIC_DRAW ); check_gl_error();
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, nullptr); check_gl_error();
        glEnableVertexAttribArray(1); check_gl_error();

    glBindVertexArray(0);             check_gl_error();
    glBindBuffer(GL_ARRAY_BUFFER, 0); check_gl_error();

    glDeleteBuffers(2, bufferID);

    isValid  = true;
}
