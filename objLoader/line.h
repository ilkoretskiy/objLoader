#ifndef LINE_H
#define LINE_H

#include "geometry.h"

#include "utility.h"

#define GLM_FORCE_RADIANS
#include "glm/mat4x4.hpp"

#include "program.h"

class Line
{
public:
    Line(const PosF& start, const PosF& end);
    ~Line();

    void Draw(const glm::mat4& camera);

private:
    void InitBuffers();

    static const int VertexCount = 2;

    PosF buffer[VertexCount];
    float distances[VertexCount];

    GLuint VAO_;

    bool isValid;

    ProgramPtr program_;
};

#endif // LINE_H
