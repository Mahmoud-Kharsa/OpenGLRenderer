#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 position_, glm::vec3 target_, glm::vec3 worldUP_)
{
	position = position_;
	target = target_;
	worldUP = glm::normalize(worldUP_);

	direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(worldUP, direction));
	up = glm::normalize(glm::cross(direction, right));
}

void Camera::Update(float deltaTime)
{
	float cameraSpeed = 2.5f * deltaTime;

	position += cameraSpeed * glm::mat3(direction, right, worldUP) * movement;

	target = position;

	target -= 3.0f * direction * (float)cos(glm::radians(yaw)) * (float)cos(glm::radians(pitch));
	target += 3.0f * right * (float)sin(glm::radians(yaw)) * (float)cos(glm::radians(pitch));
	target += 3.0f * up * (float)sin(glm::radians(pitch));


	direction = glm::normalize(position - target);
	right = glm::normalize(glm::cross(worldUP, direction));
	up = glm::normalize(glm::cross(direction, right));

	yaw = 0;
	pitch = 0;
}

void Camera::ProcessKeyboard(int key, int action)
{
	float dir = 0;
	if (action == GLFW_PRESS)
		dir = 1;
	if (action == GLFW_RELEASE)
		dir = -1;

	if (key == GLFW_KEY_W)
		movement -= glm::vec3(1.0f, 0.0f, 0.0f) * dir;
	else if (key == GLFW_KEY_S)
		movement += glm::vec3(1.0f, 0.0f, 0.0f) * dir;
	else if (key == GLFW_KEY_A)
		movement -= glm::vec3(0.0f, 1.0f, 0.0f) * dir;
	else if (key == GLFW_KEY_D)
		movement += glm::vec3(0.0f, 1.0f, 0.0f) * dir;
	else if (key == GLFW_KEY_Q)
		movement += glm::vec3(0.0f, 0.0f, 1.0f) * dir;
	else if (key == GLFW_KEY_E)
		movement -= glm::vec3(0.0f, 0.0f, 1.0f) * dir;
}

void Camera::ProcessMousePress(int button, int action)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		panningEnable = action;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		rotatingEnable = action;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		tiltingEnable = action;
	}
}

void Camera::ProcessMouseMove(float xoffset, float yoffset)
{
	if (panningEnable) {
		position -= right * xoffset * 0.004f;
		target -= right * xoffset * 0.004f;

		position -= up * yoffset * 0.004f;
		target -= up * yoffset * 0.004f;
	}
	else if (tiltingEnable) {
		yaw += xoffset * 0.1;
		pitch += yoffset * 0.1;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
}

void Camera::ProcessWheel(float yoffset)
{
	position -= direction * yoffset * 0.4f;
	target -= direction * yoffset * 0.4f;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, target, up);
}

