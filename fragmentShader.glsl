#version 330 core

in vec2 TexCoords;
sampler2D texture_diffuse1;
sampler2D texture_specular1;
out vec4 FragColor;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}