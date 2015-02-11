#version 330

layout(location = 0) in vec3 a_coord;

uniform mat4 camera;
uniform mat4 ModelView;

void main(void)
{
    vec4 coord = vec4(a_coord.xyz, 1.);
    gl_Position = camera * ModelView * coord;
}
