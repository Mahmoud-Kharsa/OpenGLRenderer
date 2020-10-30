#version 330 core

//Inputs
in vec2 verTexC;

uniform sampler2D texture1;
uniform sampler2D texture2;


//Outputs
out vec4 FragColor;

void main()
{
    FragColor = mix(texture(texture1, verTexC), texture(texture2, verTexC), 0.5);
}