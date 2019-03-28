#include "terrain.h"

Terrain::Terrain(Texture* p_texture, Mesh* p_mesh)
	: Entity(p_texture, p_mesh)
{
	this->size = 2;
	this->edge_vertices = GLuint(sqrt(this->mesh->vertexCount() / 6));
	this->terrain_height = new GLdouble*[edge_vertices + 1];
	
	for (int i = 0; i <= edge_vertices; i++)
	{
		this->terrain_height[i] = new GLdouble[edge_vertices + 1];
	}

	std::vector<glm::vec3> vertices = this->mesh->get_vertices();
	for (int i = 0; i < this->mesh->get_vertices().size(); i++)
	{
		int tmp = int(vertices[i].x + 1);
		int col = round((vertices[i].x + 1) / (2.0f / edge_vertices));
		int row = round((vertices[i].z + 1) / (2.0f / edge_vertices));

		this->terrain_height[row][col] = vertices[i].y;
	}
}

GLvoid Terrain::scale(GLdouble edge, GLdouble height)
{
	this->scaling = glm::scale(glm::vec3(edge, height, edge));
	this->size = edge * 2;

	for (int row = 0; row <= this->edge_vertices; row++) {
		for (int col = 0; col <= this->edge_vertices; col++) {
			this->terrain_height[row][col] *= height;
		}
	}
}

GLvoid Terrain::scale(glm::vec2 edge_height)
{
	this->scaling = glm::scale(glm::vec3(edge_height, edge_height.x));
	this->size = edge_height.x * 2;

	for (int row = 0; row <= this->edge_vertices; row++) {
		for (int col = 0; col <= this->edge_vertices; col++) {
			this->terrain_height[row][col] *= edge_height.y;
		}
	}
}

GLdouble** Terrain::get_terrain_height() const
{
	return this->terrain_height;
}

GLuint Terrain::get_edge_vertices() const
{
	return this->edge_vertices;
}

GLdouble Terrain::get_size() const
{
	return this->size;
}
