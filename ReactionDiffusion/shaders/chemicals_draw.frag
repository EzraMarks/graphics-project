#version 330 core

in vec2 uv;

uniform sampler2D tex;
uniform int width;
uniform int height;
uniform vec3 color;

out vec3 fragColor;

vec2 indexToUV(float x, float y) {
    return vec2(x / width, y / height);
}

bool approximatelyEqual(float x, float y) {
    float epsilon = 0.01;
    return x < (y + epsilon) && x > (y - epsilon);
}

vec3 calculateLighting(float x, float y) {
    // TODO: Adjust these constants
    vec3 lightPos = vec3(0, 0, 1);
    float shininess = 20;
    float bumpIntensity = 2;
    float diffuseMultiplier = 1.23;
    float specularMultiplier = 0.41;

    vec3 eyePos = vec3(0, 0, 1);
    vec3 surfacePos = vec3(2.f * uv.x - 1.f, 2.f * uv.y - 1.f, 0);
    vec3 surfaceToLightDir = normalize(lightPos - surfacePos);

    // Calculates surface normal based on the input texture
    vec4 derivativeX1 = texture(tex, indexToUV(x, y)) - texture(tex, indexToUV(x - 1, y));
    vec4 derivativeX2 = texture(tex, indexToUV(x + 1, y)) - texture(tex, indexToUV(x, y));
    float normalX = bumpIntensity * (derivativeX1.x + derivativeX2.x);
    vec4 derivativeY1 = texture(tex, indexToUV(x, y)) - texture(tex, indexToUV(x, y - 1));
    vec4 derivativeY2 = texture(tex, indexToUV(x, y + 1)) - texture(tex, indexToUV(x, y - 1));
    float normalY = bumpIntensity * (derivativeY1.x + derivativeY2.x);
    vec3 surfaceNormal = normalize(vec3(normalX, normalY, 1.0));

    // Calculates diffuse lighting
    float diffuse = max(0, dot(surfaceNormal, surfaceToLightDir));

    // Calculates specular lighting
    vec3 reflectedLightDir = 2.f * surfaceNormal * dot(surfaceNormal, surfaceToLightDir) - surfaceToLightDir;
    vec3 lineOfSightDir = normalize(eyePos);
    float specularIntensity = max(0, dot(reflectedLightDir, lineOfSightDir));
    float specular = pow(specularIntensity, shininess);

    return (diffuseMultiplier * diffuse + specularMultiplier * specular) * color;
}

void main(){
    float x = uv.x * width;
    float y = uv.y * height;

    vec3 light = calculateLighting(x, y);

    float chemicalConcentration = texture(tex, indexToUV(x, y)).y;
    float fadeMultiplier = pow(chemicalConcentration, 0.4);

    fragColor = light * (0.6 + 0.25 * fadeMultiplier);
}
