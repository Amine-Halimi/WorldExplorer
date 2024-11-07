#version 330 core
//Defining the layout of
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

//Transitionning from one space to another
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Vectors to send to fragmentLightingShader.glsl
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));

    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
} 