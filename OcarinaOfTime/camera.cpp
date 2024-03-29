#include "camera.h"



Camera::Camera(GLdouble p_fov)
{
	this->fov = p_fov;

	// Vogelperspektive 
/*	
	this->pos = { 0, 13, 0 };
	this->dir = { 0, -1, 0 };
	this->up  = { 0, 0, -1 };
*/	

	// FRONT
	this->pos = { 0, 2, 5 };
	this->dir = { 0, 0, -1 };
	this->up = { 0, 1, 0 };


	this->aspectRatio = 4 / 3;
	this->near_plane = 0.1;
	this->far_plane = 100.0;
}


glm::mat4 Camera::projectionMatrix()
{
	return glm::perspective(glm::radians(this->fov),
							this->aspectRatio,
							this->near_plane,
							this->far_plane);
}

glm::mat4 Camera::viewMatrix()
{
	return glm::lookAt(this->pos,
					   this->pos + this->dir,
					   this->up);
}

GLvoid Camera::computeInputs(GLFWwindow* window)
{
	static GLdouble lastTime = glfwGetTime();
	GLdouble currentTime = glfwGetTime();
	GLfloat deltaTime = GLfloat(currentTime - lastTime);

	GLdouble xpos, ypos;
	GLint width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width / 2, height / 2);

	this->horizontalAngle += this->mouseSpeed * GLfloat(width / 2 - xpos);
	this->verticalAngle += this->mouseSpeed * GLfloat(height / 2 - ypos);

	if (this->verticalAngle > 1.5) this->verticalAngle = 1.5;
	else if (this->verticalAngle < -1.5) this->verticalAngle = -1.5;

	this->dir = glm::vec3(
		cos(this->verticalAngle) * sin(this->horizontalAngle),
		sin(this->verticalAngle),
		cos(this->verticalAngle) * cos(this->horizontalAngle)
	);

	glm::vec3 rightVector = glm::vec3(
		sin(this->horizontalAngle - 3.14f / 2.0f),
		0,
		cos(this->horizontalAngle - 3.14f / 2.0f)
	);

	this->up = glm::cross(rightVector, dir);


	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		this->pos += glm::normalize(glm::vec3(this->dir.x, 0, this->dir.z)) * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		this->pos -= glm::normalize(glm::vec3(this->dir.x, 0, this->dir.z)) * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		this->pos += rightVector * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		this->pos -= rightVector * deltaTime * speed;
	}
	// Move Up
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->pos += glm::vec3(0, 1, 0) * deltaTime * speed;
	}
	// Move down
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		this->pos += glm::vec3(0, -1, 0) * deltaTime *speed;
	}

	lastTime = currentTime;
}
