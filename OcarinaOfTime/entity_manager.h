#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

#include "entity.h"
#include "declarations.h"
#include "mesh.h"

class EntityManager
{
public:
	EntityManager(GLFWwindow* window);
	~EntityManager();

	// Initialization
	GLvoid add(Texture* texture, Mesh* mesh);
	GLvoid add(Mesh* mesh, Texture* texture);

	// Input functions
	GLvoid computeInputs(Entity* entity);

	GLvoid update(GLuint shader_program, Camera* camera);

private:
	GLFWwindow* window;
	std::vector<Entity*> entities;
};

#endif // !ENTITY_MANAGER_H