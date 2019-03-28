#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <vector>
#include "declarations.h"

GLboolean loadMesh(
	std::string file_path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
);


#endif // !MESH_LOADER_H

