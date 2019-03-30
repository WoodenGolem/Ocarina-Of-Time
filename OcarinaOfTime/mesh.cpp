#include "mesh.h"


Mesh::Mesh(std::string mesh_file_path)
{
	if (!this->mesh_is_loaded)
	{
		std::cout << "Loading Mesh..." << std::endl;
		this->loadMesh(mesh_file_path.c_str(), this->vertices, this->uvs, this->normals);

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
		glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

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

	for (int i = 0; i < this->vertices.size(); i++)
	{
		if (this->vertices[i].x > boundingBox.max_x) this->boundingBox.max_x = this->vertices[i].x;
		if (this->vertices[i].x < boundingBox.min_x) this->boundingBox.min_x = this->vertices[i].x;
		if (this->vertices[i].y > boundingBox.max_y) this->boundingBox.max_y = this->vertices[i].y;
		if (this->vertices[i].y < boundingBox.min_y) this->boundingBox.min_y = this->vertices[i].y;
		if (this->vertices[i].z > boundingBox.max_z) this->boundingBox.max_z = this->vertices[i].z;
		if (this->vertices[i].z < boundingBox.min_z) this->boundingBox.min_z = this->vertices[i].z;
	}
}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &this->normal_buffer);
	glDeleteBuffers(1, &this->vertex_buffer);
	glDeleteBuffers(1, &this->uv_buffer);
	glDeleteVertexArrays(1, &this->vertex_array_ID);
}

GLvoid Mesh::draw()
{
	glBindVertexArray(this->vertex_array_ID);
	glDrawArrays(GL_TRIANGLES, 0, GLsizei(this->vertices.size()));
}

BoundingBox Mesh::get_boundingBox()
{
	return this->boundingBox;
}
GLboolean Mesh::loadMesh(
	std::string file_path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE* file;
	FILE** pfile = &file;
	fopen_s(pfile, file_path.c_str(), "r");
	if (file == NULL)
	{
		printf("Impossible to open the file!\n");
		return false;
	}
	while (1)
	{
		char lineHeader[128];
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
		{
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by obj Parser!\n");
				return GL_FALSE;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}

	return GL_TRUE;
}

Plane Mesh::get_plane(GLuint index)
{
	Plane plane = { this->vertices[index * 3], this->normals[index * 3] };
	return plane;
}
GLuint Mesh::get_vertex_count() 
{
	return this->vertices.size();
}
