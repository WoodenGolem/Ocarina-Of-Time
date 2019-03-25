#include "texture_loader.h"

GLuint loadTexture(std::string imagepath)
{
	std::cout << "Loading Texture..." << std::endl;

	GLint width;
	GLint height;
	unsigned char* data = SOIL_load_image(imagepath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	
	GLuint texture_ID;
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	return texture_ID;
}
