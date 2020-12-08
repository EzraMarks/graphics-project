#version 330 core

uniform sampler2D prevChemicals;
uniform int width;
uniform int height;

uniform float dt;
uniform float diffusionRateA;
uniform float diffusionRateB;
uniform float feedRate;
uniform float killRate;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 chemicals;

vec2 indexToUV(float x, float y) {
    return vec2(x / width, y / height);
}

vec4 laplace() {
    float x = uv.x * width;
    float y = uv.y * height;

    vec4 sum = vec4(0);
    sum += texture(prevChemicals, indexToUV(x, y)) * -1;
    sum += texture(prevChemicals, indexToUV(x-1, y)) * 0.2;
    sum += texture(prevChemicals, indexToUV(x+1, y)) * 0.2;
    sum += texture(prevChemicals, indexToUV(x, y+1)) * 0.2;
    sum += texture(prevChemicals, indexToUV(x, y-1)) * 0.2;
    sum += texture(prevChemicals, indexToUV(x-1, y-1)) * 0.05;
    sum += texture(prevChemicals, indexToUV(x+1, y-1)) * 0.05;
    sum += texture(prevChemicals, indexToUV(x+1, y+1)) * 0.05;
    sum += texture(prevChemicals, indexToUV(x-1, y+1)) * 0.05;

    return sum;
}

vec4 updateChemicals() {
    vec4 chemicalsUV = texture(prevChemicals, uv);
    float chemicalA = chemicalsUV.x;
    float chemicalB = chemicalsUV.y;

    vec4 laplaceAB = laplace();

    float chemicalAPrime = chemicalA + (diffusionRateA * laplaceAB.x - chemicalA * pow(chemicalB, 2) + feedRate * (1 - chemicalA)) * dt;
    float chemicalBPrime = chemicalB + (diffusionRateB * laplaceAB.y + chemicalA * pow(chemicalB, 2) - (killRate + feedRate) * chemicalB) * dt;

    vec4 newChemicalsUV = vec4(chemicalAPrime, chemicalBPrime, 0, 0);

    return newChemicalsUV;
}

void main() {
    chemicals = updateChemicals();
}
