#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec4 color;
out vec2 texCoord;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 camera;

void main()
{
    // matrix manipulation order:
    // scale: rotate: translate
    // calculation: (back to front, cus matrix work like that)
    // translation * rotation * scale
    mat4 trans = translation * rotation * scale;
    gl_Position = camera * trans * vec4(aPos, 1.0);
    
    color = vec4(aPos + 0.5f,1);
    texCoord = aTexCoord;
}
