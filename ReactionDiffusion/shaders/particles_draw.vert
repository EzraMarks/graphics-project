#version 330 core

uniform sampler2D chemicals;
uniform int resolutionX;
uniform int resolutionY;

out vec2 uv;
out vec3 color;

// Offsets and UVs for the triangle around the particle
const int NUM_VERTICES_PER_PARTICLE = 3;
const vec4 TRI_VERTS[NUM_VERTICES_PER_PARTICLE] = vec4[NUM_VERTICES_PER_PARTICLE](
//     TODO [Task 18] Calculate the triangle point offsets (see diagram in handout)
     vec4(0, 2, 0, 0), // p1
     vec4(0, 0, 0, 0), // p2
     vec4(2, 0, 0, 0) // p3
);

void main() {
    // TODO [Task 18] Which particle and triangle vertex are we dealing with?
    int flatIndex = int(floor(gl_VertexID / 3));
    int indexX = int(mod(flatIndex, resolutionX));
    int indexY = int(floor(flatIndex / resolutionX));

    int triID = int(mod(gl_VertexID, 3));

    // Pass the tex coords to the fragment shader
    uv = TRI_VERTS[triID].xy;

    // TODO [Task 18] sample pos and vel textures
    vec4 chemicalsTime = texture(chemicals,
                                 vec2(float(indexX) / float(resolutionX), float(indexY) / float(resolutionY)));

    // Calculate diameter based on age and lifetime
    float diameter = 0.008;

    // the offset to the points of the triangle
    vec4 triPos = diameter * TRI_VERTS[triID];

    // anchor point in clip space
    // TODO change multiplier to 2
    vec4 anchorPoint = vec4(((float(indexX) / float(resolutionX)) - 0.5) * 1,
                            ((float(indexY) / float(resolutionY)) - 0.5) * 1, 0, 1.0);

    color = vec3(chemicalsTime.y * 2);

    // Center the particle around anchorPoint
    gl_Position =  anchorPoint + triPos - diameter * vec4(0.5, 0.5, 0.0, 0.0);
}
