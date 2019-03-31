#include "entity_manager.h"



EntityManager::EntityManager(GLFWwindow* window, Texture* texture, Mesh* mesh){
	this->window = window;
	this->player = new Player(texture, mesh);
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
}
GLvoid EntityManager::add(Mesh* mesh, Texture* texture)
{
	this->entities.push_back(new Entity(texture, mesh));
}

// input functions
GLvoid EntityManager::computeInputs(Player* player)
{
	if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
		player->applyForce({ 0, 0, -1 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		player->applyForce({ 0, 0, 1 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		player->applyForce({ -1, 0, 0 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		player->applyForce({ 1, 0, 0 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS) {
		player->applyForce({ 0, -1, 0 });
	}

	// Gravity
	player->applyForce({ 0, -1, 0 });
}

GLvoid EntityManager::update(GLuint shader_program, Camera* camera)
{
	computeInputs(this->player);
	this->player->nearCollisionTest(this->entities[0]);

	this->player->update();
	this->player->debug();
	//this->player->move();
	this->player->draw(shader_program, camera);


	entities[0]->scale(10, 10, 10);
	entities[0]->draw(shader_program, camera);
}
