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

	GLvoid computeInputs(GLFWwindow* window, std::vector<Entity*> entities);
	bool broadCollisionTest(Entity* entity);
	bool nearCollisionTest(Entity* entity);

private:
	glm::vec3 pos;
	GLfloat speed;
};


#endif // !PLAYER_H
