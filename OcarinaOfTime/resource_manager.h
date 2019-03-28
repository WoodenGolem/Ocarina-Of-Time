#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <vector>

#include "declarations.h"
#include "mesh.h"
#include "texture_loader.h"
#include "shader_loader.h"

class ResourceManager
{
public:
	ResourceManager();
	
	GLvoid load();
	GLuint shader(GLuint id);
	Texture* texture(GLuint id);
	Mesh* mesh(GLuint id);

private:
	std::vector<GLuint> shader_programs;
	std::vector<Texture*> textures;
	std::vector<Mesh*> meshes;
};

#endif // !RESOURCE_MANAGER_H