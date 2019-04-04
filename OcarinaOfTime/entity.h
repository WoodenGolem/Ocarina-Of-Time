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

	// Rendering
	GLvoid draw(GLuint shader_program, Camera* camera);

	// Transformation
	GLvoid scale(GLdouble x, GLdouble y, GLdouble z);
	GLvoid scale(glm::vec3 xyz);
	GLvoid rotate(GLfloat angle, GLdouble axis_x, GLdouble axis_y, GLdouble axis_z);
	GLvoid rotate(GLfloat angle, glm::vec3 axis);
	GLvoid translate(GLdouble x, GLdouble y, GLdouble z);
	GLvoid translate(glm::vec3 xyz);
	Mesh* get_mesh() const;
	glm::vec3 get_position() const;

	// Physics
	BoundingBox calcBoundingBox();
	GLvoid applyForce(glm::vec3 force);
	GLvoid update();
	GLvoid move(GLfloat deltaTime);
	GLvoid stop();
	glm::mat4 modelMatrix();

protected:
	// Rendering
	Mesh* mesh;
	Texture* texture;

	// Transformation
	glm::mat4 scaling;
	glm::mat4 rotation;
	glm::mat4 translation;

	// Physics
	std::vector<glm::vec3> forces;
	glm::vec3 velocity;
	GLfloat mass;
};


#endif // !ENTITY_H