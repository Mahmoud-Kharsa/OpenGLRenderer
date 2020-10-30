#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vShaderString;
	std::string fShaderString;
	std::stringstream strStream;

	//Read vertex shader
	std::ifstream vertexShaderFile(vertexPath);
	if (!vertexShaderFile.is_open())
	{
		std::cout << "ERROR::SHADER::VERTEX::FILE_READ_FAILD" << std::endl;
		return;
	}

	strStream << vertexShaderFile.rdbuf();
	vShaderString = strStream.str();
    vertexShaderFile.close();

	strStream = std::stringstream();
    std::stringstream strStream2;

	//Read fragment shader
	std::ifstream fragmentShaderFile(fragmentPath);
	if (!fragmentShaderFile.is_open())
	{
		std::cout << "ERROR::SHADER::FRAGMENT::FILE_READ_FAILD" << std::endl;
		return;
	}

	strStream2 << fragmentShaderFile.rdbuf();
	fShaderString = strStream2.str();

    fragmentShaderFile.close();
	strStream2 = std::stringstream();
	

    const char* vShaderCString = vShaderString.c_str();
    const char* fShaderCString = fShaderString.c_str();

	//Compile and link shaders
    //load vertex shader
    int  success;
    char infoLog[512];
    unsigned int verShader;
    verShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(verShader, 1, &vShaderCString, NULL);
    glCompileShader(verShader);
    //Check shader compile status
    glGetShaderiv(verShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(verShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(verShader);
        return;
    }

    //load fragment shader
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fShaderCString, NULL);
    glCompileShader(fragShader);
    //Check shader compile status
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(verShader);
        glDeleteShader(fragShader);
        return;
    }

    //create shader program
    ID = glCreateProgram();
    glAttachShader(ID, verShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteShader(verShader);
        glDeleteShader(fragShader);
        return;
    }

	//Free shaders
    glDeleteShader(verShader);
    glDeleteShader(fragShader);

	//Success
	valid = true;
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setUni(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setUni(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setUni(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}