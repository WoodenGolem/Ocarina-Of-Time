#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "mesh.h"
#include "camera.h"
#include "declarations.h"

class Player : public Entity
{
public:
	Player(Texture* texture, Mesh* mesh);

	bool broadCollisionTest(Entity* entity);
	bool nearCollisionTest(Entity* entity, GLfloat deltaTime);

	GLvoid debug();

private:
	glm::vec3 ellipsoid;
};


#endif // !PLAYER_H
