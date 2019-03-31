#include "scene.h"
#include <iostream>

Scene::Scene(GLFWwindow* window)
{
	// Everthing in here needs to be moved to future sceneloader function
	this->resources = new ResourceManager;
	this->resources->load();

	this->entities = new EntityManager(window, this->resources->texture(0), this->resources->mesh(0));
	this->entities->add(this->resources->texture(1), this->resources->mesh(2));

	// CAM
	this->camera = new Camera;

	// LIGHT
	this->light_source = glGetUniformLocation(resources->shader(0), "LightPosition_worldspace");
}

GLvoid Scene::computeInputs(GLFWwindow* window)
{
	this->camera->computeInputs(window);
}

GLvoid Scene::draw()
{
	glUniform3f(this->light_source, 0, 50, 50);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	this->entities->update(resources->shader(0), this->camera);

	glUseProgram(this->resources->shader(0));
}
