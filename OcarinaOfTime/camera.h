#ifndef CAMERA_H
#define CAMERA_H

#include "gtc/matrix_transform.hpp"

#include "declarations.h"


class Camera
{
public:
	Camera(GLdouble p_fov = 90);

	glm::mat4 projectionMatrix();
	glm::mat4 viewMatrix();
	GLvoid computeInputs(GLFWwindow* window);

private:
	GLdouble fov;
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;
	GLdouble aspectRatio;
	GLdouble near_plane;
	GLdouble far_plane;

	GLfloat horizontalAngle = 90.0f;
	GLfloat verticalAngle = 0.0f;
	GLfloat speed = 5.0f; // units / second
	GLfloat mouseSpeed = 0.005f;
};


#endif // !CAMERA_H
