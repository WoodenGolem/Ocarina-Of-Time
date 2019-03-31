#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "camera.h"
#include "player.h"
#include "resource_manager.h"
#include "entity_manager.h"


class Scene
{
public:
	Scene(GLFWwindow* window);
	GLvoid computeInputs(GLFWwindow* window);
	GLvoid draw();

private:
	ResourceManager* resources;
	EntityManager* entities;
	Camera* camera;

	GLuint light_source;
};

#endif // !SCENE_H