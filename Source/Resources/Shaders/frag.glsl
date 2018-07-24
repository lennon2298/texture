#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoords;

//uniform vec4 gColor;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float gamma;

void main()
{
    FragColor = mix(texture(ourTexture1,texCoords),texture(ourTexture2,texCoords),gamma);
}