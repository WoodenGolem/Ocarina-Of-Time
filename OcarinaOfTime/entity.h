#ifndef ENTITY_H
#define ENTITY_H

#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/transform.hpp"

#include "declarations.h"
#include "mesh.h"
#include "camera.h"


class Entity
{
public:
	Entity(Texture* p_texture,
		   Mesh* p_mesh);

	GLvoid draw(GLuint shader_program, Camera* camera);
	GLvoid scale(GLdouble x, GLdouble y, GLdouble z);
	GLvoid scale(glm::vec3 xyz);
	GLvoid rotate(GLfloat angle, GLdouble axis_x, GLdouble axis_y, GLdouble axis_z);
	GLvoid rotate(GLfloat angle, glm::vec3 axis);
	GLvoid translate(GLdouble x, GLdouble y, GLdouble z);
	GLvoid translate(glm::vec3 xyz);

	BoundingBox calcBoundingBox();

protected:
	Mesh* mesh;
	Texture* texture;

	glm::mat4 scaling;
	glm::mat4 rotation;
	glm::mat4 translation;

	glm::mat4 modelMatrix();
};


#endif // !ENTITY_H