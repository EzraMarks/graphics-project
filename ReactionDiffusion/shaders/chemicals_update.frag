#version 330 core

uniform float firstPass;
uniform sampler2D prevChemicals;
uniform int resolutionX;
uniform int resolutionY;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 chemicals;

const float dt = 1.0;
const float diffusionRateA = 1.0;
const float diffusionRateB = 0.5;
const float feedRate = 0.055;
const float killRate = 0.062;

// A helpful procedural "random" number generator
float hash(float n) { return fract(sin(n)*753.5453123); }

vec4 initChemicals() {
    if (uv.x > 0.3 && uv.x < 0.7 && uv.y > 0.3 && uv.y < 0.7) {
        return vec4(0, 1, 0, 0);
    } else {
        return vec4(1, 0, 0, 0);
    }
}

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

    if (firstPass > 0.5) {
        chemicals = initChemicals();
    } else {
        chemicals = updateChemicals();
    }
}
