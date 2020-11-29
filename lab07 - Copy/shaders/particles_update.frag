#version 330 core

uniform float firstPass;
uniform sampler2D prevPos;
uniform sampler2D prevVel;
uniform int resolutionX;
uniform int resolutionY;

// output from quad.vert
in vec2 uv;

// TODO [Task 15] setup the output locations
layout(location = 0) out vec4 pos;
layout(location = 1) out vec4 vel;

const float PI = 3.14159;
const float dt = 0.0167; // 1 sec/60 fps

/*
    A particle has the following properties:
        - pos.xyz = clip space position
        - pos.w = lifetime in seconds (doesn't change)
        - vel.xyz = clip space velocity
        - vel.w = current age in seconds
*/

// A helpful procedural "random" number generator
float hash(float n) { return fract(sin(n)*753.5453123); }

// Helper functions to procedurally generate lifetimes and initial velocities
// based on particle index
float calculateLifetime(int indexX, int indexY) {
    const float MAX_LIFETIME = 5.0;
    const float MIN_LIFETIME = 0.5;
    return MIN_LIFETIME + (MAX_LIFETIME - MIN_LIFETIME) * hash(indexY * resolutionX + indexX * 2349.2693);
}

vec2 calculateInitialVelocity(int indexX, int indexY) {
    float theta = PI * hash(indexY * resolutionX + indexX * 872.0238);
    const float MAX_VEL = 0.3;
    float velMag = MAX_VEL * hash(indexY * resolutionX + indexX * 98723.345);
    return velMag * vec2(cos(theta), sin(theta));
}

vec4 initPosition(int indexX, int indexY) {
    const vec3 spawn = vec3(0);
    return vec4(spawn, calculateLifetime(indexX, indexY));
}

vec4 initVelocity(int indexX, int indexY) {
    return vec4(calculateInitialVelocity(indexX, indexY), 0, 0);
}

vec4 updatePosition() {
    // TODO [Task 16]
    // - sample prevPos and prevVel at uv
    // - xyz: pos + vel * dt
    // - w component is lifetime, so keep it from the previous position

    vec4 posUV = texture(prevPos, uv);
    vec4 velUV = texture(prevVel, uv);

    vec4 newPosUV = vec4(posUV.x + velUV.x * dt,
                         posUV.y + velUV.y * dt,
                         posUV.z + velUV.z * dt,
                         posUV.w);

    return newPosUV;
}

vec4 updateVelocity() {
    const float G = -0.1;
    // TODO [Task 16]
    // - sample prevVel at uv
    // - only force is gravity in y direction.  Add G * dt.
    // - w component is age, so add dt

    vec4 velUV = texture(prevVel, uv);

    vec4 newVelUV = vec4(velUV.x,
                         velUV.y + G * dt,
                         velUV.z,
                         velUV.w + dt);

    return newVelUV;
}

void main() {
    int indexX = int(uv.x * resolutionX);
    int indexY = int(uv.y * resolutionY);

    if (firstPass > 0.5) {
        pos = initPosition(indexX, indexY);
        vel = initVelocity(indexX, indexY);
    } else {
        pos = updatePosition();
        vel = updateVelocity();

        if (pos.w < vel.w) {
            pos = initPosition(indexX, indexY);
            vel = initVelocity(indexX, indexY);
        }
    }
}
