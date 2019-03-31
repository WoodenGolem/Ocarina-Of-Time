#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <vector>
#include <fstream>
#include <sstream>

#include "declarations.h"
#include "mesh.h"

class ResourceManager
{
public:
	~ResourceManager();
	
	GLvoid loadResources();
	GLuint shader(GLuint id);
	Texture* texture(GLuint id);
	Mesh* mesh(GLuint id);

private:
	std::vector<GLuint> shader_programs;
	std::vector<Texture*> textures;
	std::vector<Mesh*> meshes;

	GLuint loadShader(std::string vertex_file, std::string fragment_file);
	GLuint loadTexture(std::string imagepath);
};

#endif // !RESOURCE_MANAGER_H