#include "scene.h"
#include <iostream>

Scene::Scene(GLFWwindow* window)
{
	// HIGHLY EXPERIMENTAL
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
	// Currently only deals camera movements
	// The physical movement of the player is handled in the Entity Manager
	this->camera->computeInputs(window);
}

GLvoid Scene::draw()
{
	// Send light position to shader
	glUniform3f(this->light_source, 0, 50, 50);

	// Solid polygon drawing
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// HEAVILY EXPERIMENTAL
	this->entities->update(resources->shader(0), this->camera);

	// Use the standard shader
	glUseProgram(this->resources->shader(0));
}
