#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 objColor;

uniform sampler2D texture;
uniform bool useTexture;

void main() {
    vec4 color = vec4(objColor, 1);
    if (useTexture)
        color *= texture2D(texture, texCoord);

    FragColor = color;
}