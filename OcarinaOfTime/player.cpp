#include "player.h"
#include <iostream>

Player::Player(Texture* texture, Mesh* mesh)
	: Entity(texture, mesh)
{
	this->pos = { 7,0,7 };
	this->speed = 5.0f;

	this->translation = this->translation = glm::translate(glm::mat4(1.0f), this->pos);
}

GLvoid Player::computeInputs(GLFWwindow* window, std::vector<Entity*> entities)
{
	static GLdouble lastTime = glfwGetTime();
	GLdouble currentTime = glfwGetTime();
	GLfloat deltaTime = GLfloat(currentTime - lastTime);

	glm::vec3 dir = { 0, 0, -1 };
	glm::vec3 up = { 0, 1, 0 };
	glm::vec3 right = { 1, 0, 0 };

	// FORWARD
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		this->pos += dir * deltaTime * speed;
	}
	// BACKWARD
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		this->pos -= dir * deltaTime * speed;
	}
	// STRAFE LEFT
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		this->pos -= right * deltaTime * speed;
	}
	// STRAFE RIGHT
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		this->pos += right * deltaTime * speed;
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
