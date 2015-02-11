#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

using glm::vec4;
using glm::vec3;
using glm::vec2;
using glm::mat4;


namespace util
{
inline float ToRad(float degree)
{
    return degree * M_PI / 180.f;
}

template<typename T>
inline T sqr(const T& val)
{
    return val * val;
}

inline int round(double val)
{
    return static_cast<int>(val + 0.5);
}

}

class Size
{
public:
    Size(int width, int height )
    {
        width_ = width;
        height_ = height;
    }

    int width_;
    int height_;
};

template <typename T>
struct Pos
{
    T x;
    T y;

    Pos<T>& operator += (const Pos<T>& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    float DistanceTo(const Pos<T>& other) const
    {
        float result = 0.f;

        result = std::sqrt(util::sqr(other.x - x) + util::sqr(other.y - y));

        return result;
    }

    Pos(const T& x = T(0), const T& y = T(0)):x(x), y(y){}
};
typedef Pos<float> PosF;
typedef Pos<int> PosI;

template<typename T>
std::ostream& operator<<(std::ostream& str, const Pos<T>& obj)
{
    str << "x(" << obj.x << "), y("  <<  obj.y << ")";
    return str;
}


#endif // GEOMETRY_H
