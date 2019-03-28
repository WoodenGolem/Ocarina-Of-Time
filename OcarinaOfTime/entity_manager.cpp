#include "entity_manager.h"



EntityManager::EntityManager(GLFWwindow* window){
	this->window = window;
}
EntityManager::~EntityManager()
{
	for (int i = 0; i < this->entities.size(); i++)
	{
		delete this->entities[i];
	}
}

// Initialization
GLvoid EntityManager::add(Texture* texture, Mesh* mesh)
{
	this->entities.push_back(new Entity(texture, mesh));
	this->entities[0]->translate(1, 1, 1);
}
GLvoid EntityManager::add(Mesh* mesh, Texture* texture)
{
	this->entities.push_back(new Entity(texture, mesh));
}

// input functions
GLvoid EntityManager::computeInputs(Entity* entity)
{
	if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
		entity->applyForce({ 0, 0, -1 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		entity->applyForce({ 0, 0, 1 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		entity->applyForce({ -1, 0, 0 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		entity->applyForce({ 1, 0, 0 });
	}
}

GLvoid EntityManager::update(GLuint shader_program, Camera* camera)
{
	computeInputs(entities[0]);
	entities[0]->update();
	entities[0]->draw(shader_program, camera);
}
