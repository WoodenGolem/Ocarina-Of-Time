#include "scene.h"
#include <iostream>

Scene::Scene()
{
	this->resources = new ResourceManager;
	this->resources->load();

	this->camera = new Camera;

	this->player = new Player(resources->texture(1), resources->mesh(0));

	this->terrain = new Terrain(resources->texture(0), resources->mesh(2));
	this->terrain->scale(10, 15);

	this->light_source = glGetUniformLocation(resources->shader(0), "LightPosition_worldspace");


	this->entities.push_back(new Entity(resources->texture(1), resources->mesh(0)));
	this->entities.push_back(new Entity(resources->texture(1), resources->mesh(0)));
	this->entities.push_back(new Entity(resources->texture(1), resources->mesh(0)));
	this->entities.push_back(new Entity(resources->texture(1), resources->mesh(0)));
	this->entities[0]->translate(0, 0, 0);
	this->entities[1]->translate(2, 0, 0);
	this->entities[2]->translate(-2, 0, 0);
	this->entities[3]->translate(5, 0, 0);
}

GLvoid Scene::computeInputs(GLFWwindow* window)
{
	this->player->computeInputs(window, this->entities, this->terrain);
}

GLvoid Scene::draw()
{
	glUniform3f(this->light_source, 0, 10, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	player->draw(resources->shader(0), this->camera);

	this->entities[0]->draw(resources->shader(0), this->camera);
	this->entities[1]->draw(resources->shader(0), this->camera);
	this->entities[2]->draw(resources->shader(0), this->camera);
	this->entities[3]->draw(resources->shader(0), this->camera);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	terrain->draw(resources->shader(0), this->camera);

	glUseProgram(this->resources->shader(0));
}


GLvoid Scene::test()
{
	this->entities[0]->calcBoundingBox().print();
}
