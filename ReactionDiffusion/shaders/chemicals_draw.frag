#version 330 core

in vec2 uv;

uniform sampler2D tex;
uniform int resolutionX;
uniform int resolutionY;

out vec3 fragColor;

vec2 indexToUV(int x, int y) {
    return vec2(float(x) / float(resolutionX), float(y) / float(resolutionY));
}

vec3 calculateLighting(int x, int y) {
    vec3 eyePos = vec3(0, 0, 1);
    vec3 lightPos = vec3(0.9, 0.9, 1);
    vec3 surfaceColor = vec3(0.5, 1, 0.8);
    float shininess = 20; // TODO: adjust
    vec3 color = vec3(0.5, 0.0, 1.0);

    vec3 surfacePos = vec3(2.f * uv.x - 1.f, 2.f * uv.y - 1.f, 0);
    // Calculates surface normal based on the input texture
    vec4 derivative = texture(tex, indexToUV(x, y)) - texture(tex, indexToUV(x - 1, y - 1)); // TODO
    vec3 surfaceNormal = vec3(derivative.x * 5, 0, 1.0); // TODO
    vec3 surfaceToLightDir = normalize(lightPos - surfacePos);

    // Calculates diffuse lighting
    float diffuse = max(0, dot(surfaceNormal, surfaceToLightDir));

    // Calculates specular lighting
    vec3 reflectedLightDir = 2.f * surfaceNormal * dot(surfaceNormal, surfaceToLightDir) - surfaceToLightDir;
    vec3 lineOfSightDir = normalize(eyePos - surfacePos);
    float specularIntensity = max(0, dot(reflectedLightDir, lineOfSightDir));
    float specular = pow(specularIntensity, shininess);

    return (diffuse + specular) * color;
}

void main(){
    int x = int(uv.x * resolutionX);
    int y = int(uv.y * resolutionY);

    vec3 light = calculateLighting(x, y);

    fragColor = light;
}
