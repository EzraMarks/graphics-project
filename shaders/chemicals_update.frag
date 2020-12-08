#version 330 core

uniform sampler2D prevChemicals;
uniform int resolutionX;
uniform int resolutionY;

uniform float dt;
uniform float diffusionRateA;
uniform float diffusionRateB;
uniform float feedRate;
uniform float killRate;

// TODO remove
//const float diffusionRateA = 1.0;
//const float diffusionRateB = 0.5;
//const float feedRate = 0.055;
//const float killRate = 0.062;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 chemicals;

vec2 indexToUV(int x, int y) {
    return vec2(float(x) / float(resolutionX), float(y) / float(resolutionY));
}

vec4 laplace() {
    int x = int(uv.x * resolutionX);
    int y = int(uv.y * resolutionY);

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
    int indexX = int(uv.x * resolutionX);
    int indexY = int(uv.y * resolutionY);

    chemicals = updateChemicals();
}
