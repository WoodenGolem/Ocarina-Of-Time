#include "scene.h"
#include <iostream>

Scene::Scene()
{
	this->resources = new ResourceManager;
	this->resources->load();

	this->entities = new EntityManager;

	// PLAYER
	this->player = new Player(this->resources->texture(0), this->resources->mesh(5));
	this->player->translate(0, 0, 0);

	// CAM
	this->camera = new Camera;

	// LIGHT
	this->light_source = glGetUniformLocation(resources->shader(0), "LightPosition_worldspace");
}

GLvoid Scene::computeInputs(GLFWwindow* window)
{
	//this->player->computeInputs(window);
	this->camera->computeInputs(window);
}

GLvoid Scene::draw()
{
	glUniform3f(this->light_source, 0, 50, 50);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	player->draw(resources->shader(0), this->camera);

	glUseProgram(this->resources->shader(0));
}
