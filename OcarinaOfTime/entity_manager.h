#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

#include "entity.h"
#include "player.h"
#include "declarations.h"
#include "mesh.h"

class EntityManager
{
public:
	EntityManager(GLFWwindow* window, Texture* texture, Mesh* mesh);
	~EntityManager();

	// Initialization
	GLvoid add(Texture* texture, Mesh* mesh);
	GLvoid add(Mesh* mesh, Texture* texture);

	// Input functions
	GLvoid computeInputs(Player* player);

	GLvoid update(GLuint shader_program, Camera* camera);

private:
	GLFWwindow* window;
	Player* player;
	std::vector<Entity*> entities;
};

#endif // !ENTITY_MANAGER_H