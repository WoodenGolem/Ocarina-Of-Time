#include "resource_manager.h"



ResourceManager::ResourceManager()
{
}

GLvoid ResourceManager::load()
{
	this->shader_programs.push_back(loadShader("resources/shader/vertex_shader.vert", "resources/shader/fragment_shader.frag"));

	this->meshes.push_back(new Mesh("resources/meshes/cube1x1.obj"));	// 0
	this->meshes.push_back(new Mesh("resources/meshes/terrain.obj"));	// 1
	this->meshes.push_back(new Mesh("resources/meshes/flat.obj"));		// 2
	this->meshes.push_back(new Mesh("resources/meshes/player.obj"));	// 3
	this->meshes.push_back(new Mesh("resources/meshes/suzanne.obj"));	// 4
	//this->meshes.push_back(new Mesh("resources/meshes/pyramid.obj"));	// 
	this->meshes.push_back(new Mesh("resources/meshes/link.obj"));		// 5
	this->meshes.push_back(new Mesh("resources/meshes/sphere1x1.obj"));	// 6


	this->textures.push_back(new Texture({ loadTexture("resources/textures/link.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
	this->textures.push_back(new Texture({ loadTexture("resources/textures/red.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
	this->textures.push_back(new Texture({ loadTexture("resources/textures/green.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
	this->textures.push_back(new Texture({ loadTexture("resources/textures/player.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
}

GLuint ResourceManager::shader(GLuint id) {
	if (id >= this->shader_programs.size() || id < 0) {
		return 0;
	}
	else {
		return this->shader_programs[id];
	}
}

Texture* ResourceManager::texture(GLuint id)
{
	if (id >= this->textures.size() || id < 0) {
		return 0;
	}
	else {
		return this->textures[id];
	}
}

Mesh* ResourceManager::mesh(GLuint id)
{
	if (id >= this->meshes.size() || id < 0) {
		return 0;
	}
	else {
		return this->meshes[id];
	}
}
