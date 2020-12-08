#version 330 core

uniform sampler2D image;
uniform int imageWidth;
uniform int imageHeight;
uniform int canvasWidth;
uniform int canvasHeight;

// output from quad.vert
in vec2 uv;

layout(location = 0) out vec4 chemicals;

void main() {
    vec4 color;

    float imageAspectRatio = float(imageWidth) / float(imageHeight);
    float canvasAspectRatio = float(canvasWidth) / float(canvasHeight);
    float widthRatio = canvasAspectRatio / imageAspectRatio;

    // If canvas is wider than image
    if (widthRatio > 1) {
        float imageUOffset = (widthRatio - 1) / 2;
        float imageU = uv.x * widthRatio - imageUOffset;
        float imageV = -1 * uv.y;

        if (imageU >= 0 && imageU <= 1) {
            color = texture(image, vec2(imageU, imageV));
        } else {
            color = vec4(0, 0, 0, 1);
        }
    } else {
        float imageVOffset = (1 / widthRatio + 1) / 2;
        float imageU = uv.x;
        float imageV = -1 * uv.y / widthRatio + imageVOffset;

        if (imageV >= 0 && imageV <= 1) {
            color = texture(image, vec2(imageU, imageV));
        } else {
            color = vec4(0, 0, 0, 1);
        }
    }

    float A = length(color);
    float B = 1.f - A;
    chemicals = vec4(A, B, 0, 0);
}
