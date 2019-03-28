#include "player.h"
#include <iostream>

Player::Player(Texture* texture, Mesh* mesh)
	: Entity(texture, mesh)
{
	this->pos = { 7,0,7 };
	this->dir = { 0,0,-1 };
	this->up = { 0,1,0 };
	this->right = { 1,0,0 };
	this->speed = 5.0f;

	this->translation = this->translation = glm::translate(glm::mat4(1.0f), this->pos);
}

GLvoid Player::computeInputs(GLFWwindow* window, std::vector<Entity*> entities, Terrain* terrain)
{
	static GLdouble lastTime = glfwGetTime();
	GLdouble currentTime = glfwGetTime();
	GLfloat deltaTime = GLfloat(currentTime - lastTime);

	// FORWARD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		this->pos += this->dir * deltaTime * speed;
	}
	// BACKWARD
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		this->pos -= this->dir * deltaTime * speed;
	}
	// STRAFE LEFT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		this->pos -= this->right * deltaTime * speed;
	}
	// STRAFE RIGHT
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		this->pos += this->right * deltaTime * speed;
	}

	for (int i = 0; i < entities.size(); i++)
	{
		if (this->broadCollisionTest(entities[i]))
		{
			std::cout << "Collision!" << std::endl;
		}	
	}
	
	this->translate(this->pos);
	lastTime = currentTime;
}

GLvoid Player::terrainCollision(Terrain* terrain)
{
	GLuint edge_vertices = terrain->get_edge_vertices();
	GLdouble size = terrain->get_size();

	GLdouble x = ((this->pos.x + (size / 2)) * edge_vertices) / size;
	GLdouble z = ((this->pos.z + (size / 2)) * edge_vertices) / size;

	if (x > edge_vertices) x = edge_vertices;
	else if (x < 0) x = 0;

	if (z > edge_vertices) z = edge_vertices;
	else if (z < 0) z = 0;

	this->pos.y = terrain->get_terrain_height()[int(round(z))][int(round(x))];
}

bool Player::broadCollisionTest(Entity* entity)
{
	BoundingBox playerBox = this->calcBoundingBox();
	BoundingBox entityBox = entity->calcBoundingBox();

	if (not ((playerBox.max_x <= entityBox.max_x && playerBox.max_x >= entityBox.min_x) ||
		(playerBox.min_x <= entityBox.max_x && playerBox.min_x >= entityBox.min_x)))
	{
		return false;
	}

	if (not ((playerBox.max_y <= entityBox.max_y && playerBox.max_y >= entityBox.min_y) ||
		(playerBox.min_y <= entityBox.max_y && playerBox.min_y >= entityBox.min_y)))
	{
		return false;
	}

	if (not ((playerBox.max_z <= entityBox.max_z && playerBox.max_z >= entityBox.min_z) ||
		(playerBox.min_z <= entityBox.max_z && playerBox.min_z >= entityBox.min_z)))
	{
		return false;
	}

	return true;
}
bool Player::nearCollisionTest(Entity* entity)
{
	return false;
}
