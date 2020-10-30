#version 330 core

//Inputs
layout(location = 0) in vec3 iverPosition;
layout(location = 1) in vec2 iverTexC;

//Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//Outputs
out vec2 verTexC;

void main()
{
   verTexC = iverTexC;
   gl_Position = projection * view * model * vec4(iverPosition, 1.0);
}