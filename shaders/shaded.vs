#version 330

layout(location = 0) in vec3 aCoord;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

uniform mat4 camera;
uniform mat4 ModelView;

out vec3 vColor;
out vec3 vNormal;

void main()
{
    vec4 coord = vec4(aCoord.x, aCoord.y, aCoord.z, 1.);
    gl_Position = camera * ModelView * coord;

    vColor = aColor;
    vNormal = aNormal;
}
