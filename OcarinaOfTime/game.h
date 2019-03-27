#ifndef GAME_H
#define GAME_H

#include <Windows.h>
#include <string>
#include <vector>

#include "declarations.h"
#include "scene.h"


class Game
{
public:
	Game(GLuint width = 1024,
		 GLuint height = 768,
		 GLboolean fullscreen = GL_FALSE);
	~Game();


	GLvoid mainLoop();

private:
	GLFWwindow* window;
};


#endif // !GAME_H