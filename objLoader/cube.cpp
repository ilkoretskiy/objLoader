#include "cube.h"

Cube::Cube(MaterialPtr &material, const glm::vec3& size):
    DrawableObject(material)
{
    float x = size.x;
    float y = size.y;
    float z = size.z;

    float widthOffset = x / 2.;
    float heightOffset = y / 2.;
    float depthOffset = z / 2.;
    GeneratePlane(x, y, 0, widthOffset, heightOffset, depthOffset, AXIS::XY);
    GeneratePlane(x, y, z, widthOffset, heightOffset, depthOffset, AXIS::XY);

    GeneratePlane(x, 0, z, widthOffset, heightOffset, depthOffset, AXIS::XZ);
    GeneratePlane(x, y, z, widthOffset, heightOffset, depthOffset, AXIS::XZ);

    GeneratePlane(0, y, z, widthOffset, heightOffset, depthOffset, AXIS::YZ);
    GeneratePlane(x, y, z, widthOffset, heightOffset, depthOffset, AXIS::YZ);

    InitBuffers();
}


void Cube::GeneratePlane(
        float width,
        float height,
        float depth,
        float widthOffset,
        float heightOffset,
        float depthOffset,
        AXIS axis)
{
    int startIndex = data_.size();

    glm::vec3 color(1., 1., 1.);

    vec3 normal(0);
    if (axis == AXIS::XY)
    {
        float fixed = depth - depthOffset;
        normal.z = fixed > 0 ? 1. : -1.;

        for (int j = 0; j <= height; ++j)
        {
            for (int i = 0; i <= width; ++i)
            {
                data_.push_back(glm::vec3(i - widthOffset, j - heightOffset, fixed));
                color_.push_back(color);
                normal_.push_back(normal);
            }
        }
        int stride = width + 1;
        UpdateIndecies(width, height, startIndex, stride);
    }
    else if (axis == AXIS::XZ)
    {
        float fixed = height - heightOffset;
        normal.y = fixed > 0 ? 1 : -1;

        //glm::vec3 color(0, 1., 0);
        for (int k = 0; k <= depth; ++k)
        {
            for (int i = 0; i <= width; ++i)
            {
                data_.push_back(glm::vec3(i - widthOffset, fixed, k - depthOffset));
                color_.push_back(color);
                normal_.push_back(normal);
            }
        }
        int stride = width + 1;
        UpdateIndecies(width, depth, startIndex, stride);
    }
    else if (axis == AXIS::YZ)
    {
        float fixed = width - widthOffset;
        normal.x = fixed > 0 ? 1 : -1;

        //glm::vec3 color(0, 0., 1.);
        for (int k = 0; k <= depth; ++k)
        {
            for (int j = 0; j <= height; ++j)
            {
                data_.push_back(glm::vec3(fixed, j - heightOffset, k - depthOffset));
                color_.push_back(color);
                normal_.push_back(normal);
            }
        }
        int stride = height + 1;
        UpdateIndecies(height, depth, startIndex, stride);
    }
}

void Cube::UpdateIndecies(int width, int height, int startIndex, int stride)
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            int a = startIndex + i + j * stride;
            int b = startIndex + i + 1 + j * stride;
            int c = startIndex + i + (j + 1) * stride;
            int d = startIndex + i + 1 + (j + 1) * stride;
            indecies_.push_back(IndexType(a, b, d));
            indecies_.push_back(IndexType(a, c, d) );        
        }
    }
}

void Cube::InitBuffers()
{
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    GLuint buffers[4];
    glGenBuffers(4, buffers);

    // vertecies
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    const int sizeVertex = data_.size() * sizeof(vec3);
    glBufferData(GL_ARRAY_BUFFER, sizeVertex, &data_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // indecies
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    const int sizeIndex = indecies_.size() * sizeof(IndexType);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndex, &indecies_[0], GL_STATIC_DRAW);


    // colors
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    const int sizeColor = color_.size() * sizeof(vec3);
    glBufferData(GL_ARRAY_BUFFER, sizeColor, &color_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // normals
    glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    const int sizeNormals = normal_.size() * sizeof(vec3);
    glBufferData(GL_ARRAY_BUFFER, sizeNormals, &normal_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    check_gl_error();

    glBindVertexArray(0);
    glDeleteBuffers(4, buffers);
}


Cube::~Cube()
{
}

bool Cube::Draw()
{
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, indecies_.size() * sizeof(IndexType), GL_UNSIGNED_INT, 0); check_gl_error();
    glBindVertexArray(0);
    return true;
}



