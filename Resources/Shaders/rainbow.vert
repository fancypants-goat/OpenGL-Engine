#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aModel;

out vec2 texCoord;
out vec3 color;

uniform mat4 camera;

void main() {
    gl_Position = camera * aModel * vec4(aPos, 1);

    texCoord = aTexCoord;
    color = aPos;
}