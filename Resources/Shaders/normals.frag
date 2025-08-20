#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 color;

uniform sampler2D texture;
uniform bool useTexture;

void main() {
    vec4 objColor = vec4(color, 1);
    if (useTexture)
        objColor *= texture2D(texture, texCoord);

    FragColor = objColor;
}