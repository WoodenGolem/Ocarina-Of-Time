#ifndef TERRAIN_H
#define TERRAIN_H

#include "entity.h"

class Terrain : public Entity
{
public:
	Terrain(Texture* p_texture, Mesh* p_mesh);
	GLvoid scale(GLdouble edge, GLdouble height);
	GLvoid scale(glm::vec2 edge_height);

	GLdouble** get_terrain_height() const;
	GLuint get_edge_vertices() const;
	GLdouble get_size() const;

private:
	GLdouble** terrain_height;
	GLuint edge_vertices;
	GLdouble size;
};

#endif // !TERRAIN_H