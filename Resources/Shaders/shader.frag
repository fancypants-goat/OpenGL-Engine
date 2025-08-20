#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture;
uniform bool useTexture;

uniform vec4 objectColor;

void main() {
    vec4 color = objectColor;
    if (useTexture)
        color *= texture2D(texture, texCoord);

    FragColor = color;
}