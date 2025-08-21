#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture;
uniform bool useTexture;

uniform vec3 objColor;

void main() {
    vec4 color = vec4(objColor, 1);
    if (useTexture)
        color *= texture2D(texture, texCoord);

    FragColor = color;
}