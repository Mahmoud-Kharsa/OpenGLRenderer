#version 330 core

//Inputs
layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec2 iTexCoord;
layout(location = 2) in vec3 iNormal;


//Uniforms
uniform mat4 model;
uniform mat4 modelNorm;
uniform mat4 view;
uniform mat4 projection;

//Outputs
out vec3 position;
out vec2 texCoord;
out vec3 normal;

void main()
{
	position = iPosition;
	texCoord = iTexCoord;
	normal = (modelNorm *  vec4(iNormal, 0.0)).xyz;
	gl_Position = projection * view * model * vec4(iPosition, 1.0);
}