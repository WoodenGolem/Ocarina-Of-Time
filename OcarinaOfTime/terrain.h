#ifndef TERRAIN_H
#define TERRAIN_H

#include "declarations.h"
#include "mesh.h"
#include "camera.h"

class Terrain
{
public:
	Terrain(Texture* p_texture,
			Mesh* p_mesh);

	GLvoid draw(GLuint shader_program, Camera& camera);

private:
	Mesh* mesh;
	Texture* texture;

	glm::vec3 scaling;
	glm::vec3 tranlation;

	glm::mat4 modelMatrix();
};

#endif // !TERRAIN_H