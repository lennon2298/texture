#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

//uniform vec3 hPos;
//uniform mat4 transformPos;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

out vec3 ourColor;
out vec2 texCoords;

void main()
{
    gl_Position = projectionMat*viewMat*modelMat*vec4(aPos, 1.0);
    //ourColor = aPos;
    //gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    texCoords = aTexCoords;
}