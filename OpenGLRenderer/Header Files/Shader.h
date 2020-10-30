#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	//Indicate if shader program is valid
	bool valid = false;

	//Shader program ID
	unsigned int ID = 0;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // destructor
    ~Shader();
    // use/activate the shader
    void use();
    // utility uniform functions
    void setUni(const std::string& name, bool value) const;
    void setUni(const std::string& name, int value) const;
    void setUni(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
};

