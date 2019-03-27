#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "mesh.h"
#include "camera.h"
#include "declarations.h"
#include "terrain.h"

class Player : public Entity
{
public:
	Player(Texture* texture, Mesh* mesh);

	GLvoid computeInputs(GLFWwindow* window, std::vector<Entity*> entities, Terrain* terrain);
	GLvoid terrainCollision(Terrain* terrain);
	bool collisionTest(Entity* entity);

private:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	GLfloat speed;
};


#endif // !PLAYER_H
