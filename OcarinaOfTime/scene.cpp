#include "scene.h"
#include <iostream>

Scene::Scene()
{
	this->resources = new ResourceManager;
	this->resources->load();

	//CAM
	this->camera = new Camera;

	// LIGHT
	this->light_source = glGetUniformLocation(resources->shader(0), "LightPosition_worldspace");

	// PLAYER
	this->player = new Player(resources->texture(0), resources->mesh(5));

	// TERRAIN
	this->terrain = new Terrain(resources->texture(2), resources->mesh(2));
	this->terrain->scale(10, 15);

	// ENTITIES
	this->entities.push_back(new Entity(resources->texture(1), resources->mesh(0)));
	this->entities[0]->scale(5, 5, 5);

	this->entities.push_back(new Entity(resources->texture(1), resources->mesh(6)));

	this->player->translate(0, 0, 0);
	this->player->calcBoundingBox().print();
	this->entities[1]->scale(this->player->calcBoundingBox().max_x*2,
							 this->player->calcBoundingBox().max_y,
							 this->player->calcBoundingBox().max_z*2);
	this->entities[1]->translate(7, this->player->calcBoundingBox().max_y / 2, 7);
}

GLvoid Scene::computeInputs(GLFWwindow* window)
{
	this->player->computeInputs(window, this->entities, this->terrain);
	this->camera->computeInputs(window);
}

GLvoid Scene::draw()
{
	glUniform3f(this->light_source, 0, 50, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	player->draw(resources->shader(0), this->camera);

	this->entities[0]->draw(resources->shader(0), this->camera);

	terrain->draw(resources->shader(0), this->camera);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	this->entities[1]->draw(resources->shader(0), this->camera);

	glUseProgram(this->resources->shader(0));
}
