#include "mesh.h"


Mesh::Mesh(std::string mesh_file_path)
{
	if (!this->mesh_is_loaded)
	{
		std::cout << "Loading Mesh..." << std::endl;
		loadMesh(mesh_file_path.c_str(), this->vertices, this->uvs, this->normals);

		// Vertex Array
		glGenVertexArrays(1, &this->vertex_array_ID);
		glBindVertexArray(this->vertex_array_ID);

		// Vertex Buffer
		glGenBuffers(1, &this->vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

		// UV Buffer
		glGenBuffers(1, &this->uv_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec3), &this->uvs[0], GL_STATIC_DRAW);

		// Normal Buffer
		glGenBuffers(1, &this->normal_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->normal_buffer);
		glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);


		// Vertex Buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
		glVertexAttribPointer(
			0,                  // matches layout in vertexshader.
			3,					// size
			GL_FLOAT,           // type
			GL_FALSE,
			0,
			nullptr
		);

		// UV Buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, this->uv_buffer);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			nullptr
		);

		// Normal Buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, this->normal_buffer);
		glVertexAttribPointer(
			2,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			nullptr
		);

		this->mesh_is_loaded = GL_TRUE;
	}
}

GLvoid Mesh::draw()
{
	//glBindVertexArray(this->vertex_array_ID);
	glDrawArrays(GL_TRIANGLES, 0, GLsizei(this->vertices.size()));
}
