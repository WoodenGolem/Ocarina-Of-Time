#ifndef DECLARATIONS_H
#define DECLARATIONS_H


// Commonly needed libraries
#include <iostream>

// OpenGL related libraries
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"

// Simple OpenGL Image Library
#include "SOIL.h"


struct Texture {
	GLuint texture_id;
	GLuint texture_sampler;
};

struct BoundingBox {
	GLdouble min_x = 0;
	GLdouble max_x = 0;
	GLdouble min_y = 0;
	GLdouble max_y = 0;
	GLdouble min_z = 0;
	GLdouble max_z = 0;

	GLvoid print() {
		std::cout << "X: " << min_x << " " << max_x << std::endl;
		std::cout << "Y: " << min_y << " " << max_y << std::endl;
		std::cout << "Z: " << min_z << " " << max_z << std::endl;
	}
};

struct Plane {
	glm::vec3 pos;
	glm::vec3 normal;

	GLdouble distance(glm::vec3 point)
	{
		return glm::dot(this->normal, point) + glm::dot(-this->normal, this->pos);
	}

	GLvoid transform(glm::mat4 matrix)
	{
		this->pos = glm::vec4(this->pos, 1.0f) * matrix;
	}
};

#endif // !DECLARATIONS_H

