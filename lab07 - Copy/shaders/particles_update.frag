#version 330 core

uniform float firstPass;
uniform sampler2D prevChemicals;
uniform int resolutionX;
uniform int resolutionY;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 chemicals;

const float dt = 0.0167; // 1 sec/60 fps

// A helpful procedural "random" number generator
float hash(float n) { return fract(sin(n)*753.5453123); }

vec4 initChemicals(int indexX, int indexY) {
    if (indexX > 246 && indexX < 266 && indexY > 118 && indexY < 138) {
        return vec4(1.0, 1.0, 0, 0);
    } else {
        return vec4(0.0, 0.0, 0, 0);
    }
}

vec4 updateChemicals() {
    vec4 chemicalsUV = texture(prevChemicals, uv);

    vec4 newChemicalsUV = vec4(chemicalsUV * 0.998);

    return newChemicalsUV;
}


void main() {
    int indexX = int(uv.x * resolutionX);
    int indexY = int(uv.y * resolutionY);

    if (firstPass > 0.5) {
        chemicals = initChemicals(indexX, indexY);
    } else {
        chemicals = updateChemicals();
    }
}
