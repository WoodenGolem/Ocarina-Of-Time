#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <string>
#include <vector>

#include "declarations.h"
#include "mesh.h"
#include "shader_loader.h"
#include "texture_loader.h"
#include "entity.h"


class Game
{
public:
	Game(GLuint width = 1024,
		 GLuint height = 768,
		 GLboolean fullscreen = GL_FALSE);
	~Game();

	// Experimental
	GLvoid mainLoop();

private:
	GLFWwindow* window;

	std::vector<GLuint> shader_programs;
	std::vector<Texture*> textures;
	std::vector<Mesh*> meshes;

	GLvoid loadResources();
};


#endif // !GAME_H