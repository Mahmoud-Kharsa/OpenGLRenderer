#version 330 core

//Inputs
in vec3 position;
in vec2 texCoord;
in vec3 normal;

//Uniforms
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 lightColor;
uniform vec3 lightPos;  
uniform vec3 cameraPos;

uniform bool normalView;
//Outputs
out vec4 FragColor;

void main()
{
    //Debug
    if (normalView){
        FragColor = vec4(normalize(normal), 1.0);
        return;
    }

    vec4 colour = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.5);

    //Ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse light
    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPos - position);
    vec3 diffuse = max(dot(norm, lightDirection), 0.0) * lightColor;

    //Specular light
    vec3 camDirection = normalize(cameraPos - position);
    vec3 halfVector = normalize(camDirection + lightDirection);
    vec3 spec = pow(max(dot(norm, halfVector), 0), 64) * lightColor;

    FragColor =  colour * vec4(ambient + diffuse + spec, 1.0);
}