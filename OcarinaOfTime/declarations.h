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
	GLuint data;
	GLuint id;
};

#endif // !DECLARATIONS_H

