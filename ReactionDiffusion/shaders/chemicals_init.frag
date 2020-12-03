#version 330 core

uniform sampler2D tex;

// output from quad.vert
in vec2 uv;

layout(location = 0) out vec4 chemicals;

void main() {
    vec4 texUV = texture(tex, vec2(uv.x, 1 - uv.y));
    float A = length(texUV);
    float B = 1.f - A;
    chemicals = vec4(A, B, 0, 0);
}
