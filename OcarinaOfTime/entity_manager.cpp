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

// Input functions
GLvoid EntityManager::computeInputs(Player* player)
{
	if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
		player->applyForce({ 0, 0, -5 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		player->applyForce({ 0, 0, 5 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		player->applyForce({ -5, 0, 0 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		player->applyForce({ 5, 0, 0 });
	}

	if (glfwGetKey(this->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
		player->applyForce({ 0, 5, 0 });
	}
}

// Update cycle
GLvoid EntityManager::update(GLuint shader_program, Camera* camera)
{
	static GLdouble lastTime = glfwGetTime();
	GLdouble currentTime = glfwGetTime();
	GLfloat deltaTime = GLfloat(currentTime - lastTime);

	// --- PROCESSING FORCES ---
	// Player movements
	computeInputs(this->player);
	// Gravity
	this->player->applyForce({ 0, -2, 0 });
	// Calculate current velocity + clear applied forces
	this->player->update();

	// --- COLLISION DETECTION ---
	if (this->player->nearCollisionTest(this->entities[0], deltaTime) )
	{
		// Stop if collision will happen
		this->player->stop();
	}
	else
	{
		// Move if no collision occurs
		this->player->move(deltaTime);
	}

	// --- RENDERING ---
	// Render the Player
	this->player->draw(shader_program, camera);

	// Render the plane
	entities[0]->scale(10, 10, 10);
	entities[0]->draw(shader_program, camera);

	lastTime = currentTime;
}
