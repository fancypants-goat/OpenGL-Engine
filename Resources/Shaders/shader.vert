#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTexCoord;
layout (location = 4) in mat4 aModel; // takes up location 4,5,6,7 :c

out vec4 color;
out vec2 texCoord;

uniform mat4 camera;

void main()
{
    gl_Position = camera * aModel * vec4(aPos, 1.0);
    
    color = aColor;
    texCoord = aTexCoord;
}
