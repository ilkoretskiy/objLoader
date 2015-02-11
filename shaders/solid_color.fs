#version 330

out vec4 outputColor;

const float intensity = 1.1;

void main(){
    vec3 color = vec3(0.5, 0.8, 0.2);
    vec3 gammedColor = clamp(color * intensity, 0., 1.);
    outputColor = vec4(gammedColor, 1.);
}
