#ifndef MESH_H
#define MESH_H

#include <vector>
#include "declarations.h"
#include "mesh_loader.h"


class Mesh
{
public:
	Mesh(std::string mesh_file_path);
	~Mesh();
	GLvoid draw();
	GLuint vertexCount();
	std::vector<glm::vec3> get_vertices();
	BoundingBox get_boundingBox();

private:
	GLboolean mesh_is_loaded;

	GLuint vertex_array_ID, vertex_buffer;
	GLuint uv_buffer;
	GLuint normal_buffer;

	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;

	BoundingBox boundingBox;
};


#endif // !MESH_H