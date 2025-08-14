#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture;
uniform bool useTexture;

void main()
{
    if (useTexture)
        FragColor = texture2D(texture, texCoord) * color;
    else
        FragColor = color;
}
