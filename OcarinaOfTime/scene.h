#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "camera.h"
#include "terrain.h"
#include "player.h"
#include "resource_manager.h"


class Scene
{
public:
	Scene();
	GLvoid computeInputs(GLFWwindow* window);
	GLvoid draw();
	GLvoid test();

private:
	ResourceManager* resources;
	Camera* camera;
	Terrain* terrain;
	Player* player;
	GLuint light_source;

	std::vector<Entity*> entities;
};

#endif // !SCENE_H