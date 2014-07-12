#version 420 core
#pragma debug(on)

layout(std140) uniform UniformBlock {
    mat4 Model;
    vec4 light;
    vec4 color;
};

varying vec4 vNormal;
varying vec4 vPosition;

out vec4 outColor;

void main(void){
    // hardcoded light
    float diffuse = clamp(abs(dot(normalize(vNormal), normalize(light))), 0.0, 1.0);
    outColor = vPosition * diffuse;
}
