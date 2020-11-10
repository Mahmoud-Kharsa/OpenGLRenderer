#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:

	Camera();
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

	void Update(float deltaTime);

	void ProcessKeyboard(int key, int action);
	void ProcessMousePress(int button, int action);
	void ProcessMouseMove(float xoffset, float yoffset);
	void ProcessWheel(float yoffset);

	glm::mat4 GetViewMatrix();

private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 worldUP = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 direction = glm::normalize(position - target);
	glm::vec3 right = glm::normalize(glm::cross(worldUP, direction));
	glm::vec3 up = glm::normalize(glm::cross(direction, right));

	glm::vec3 movement = glm::vec3(0.0f, 0.0f, 0.0f);
	bool panningEnable = false;
	bool rotatingEnable = false;
	bool tiltingEnable = false;
	double yaw = 0.0f;
	double pitch = 0.0f;

};

