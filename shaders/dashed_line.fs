#version 330

in float v_distance;
out vec4 outputColor;

const float lineSize = 0.04;
const float gapSize = lineSize / 2;

void main(){


    if (mod (v_distance, lineSize) > gapSize)
    {
        discard;
    }

    outputColor = vec4(1., 1., 1., 1.);

}
