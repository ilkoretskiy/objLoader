#version 330

layout(location = 0) in vec2 a_coord;
layout(location = 1) in float a_distance;

uniform mat4 camera;
uniform mat4 view;

out float v_distance;

void main(void)
{
    vec4 coord = vec4(a_coord.x, a_coord.y, 1., 1.);
    gl_Position = camera * view * coord;

    v_distance = a_distance;
}
