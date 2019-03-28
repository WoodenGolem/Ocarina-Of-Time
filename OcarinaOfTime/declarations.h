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

#endif // !DECLARATIONS_H

