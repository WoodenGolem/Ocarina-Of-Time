#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

#include "entity.h"
#include "declarations.h"
#include "mesh.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	GLvoid add(Texture* texture, Mesh* mesh);
	GLvoid add(Mesh* mesh, Texture* texture);

private:
	std::vector<Entity*> entities;
};

#endif // !ENTITY_MANAGER_H