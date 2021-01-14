#version 330 core

//Inputs

//Uniforms
uniform vec3 lightColor;

//Outputs
out vec4 FragColor;

void main()
{
    FragColor = vec4(lightColor, 1.0);
}