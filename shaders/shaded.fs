#version 330

in vec3 vNormal;
in vec3 vColor;
out vec4 resultColor;

uniform mat4 ModelView;

uniform vec4 LightDirection;

void main()
{
    vec4 mv_normal = normalize( ModelView * vec4(vNormal.xyz, 0.));
    vec4 mv_lightDirection =  normalize( LightDirection);
    float intensity = clamp( -dot(mv_normal, mv_lightDirection), 0., 1.) ;
    resultColor = vec4((vColor * intensity).xyz, 1.);
}
