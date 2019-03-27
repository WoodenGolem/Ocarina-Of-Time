#include "entity.h"


Entity::Entity(Texture* p_texture,
			   Mesh* p_mesh)
{
	this->texture = p_texture;
	this->mesh = p_mesh;

	this->scaling	  = glm::scale(glm::vec3(1.0, 1.0, 1.0));
	this->rotation	  = glm::rotate(glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0));
	this->translation = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
}


GLvoid Entity::draw(GLuint shader_program, Camera* camera)
{
	// Not a Lightsource
	glUniform1f(glGetUniformLocation(shader_program, "alpha_value"), 1.0f);
	glUniform1i(glGetUniformLocation(shader_program, "is_source"), 0);

	GLuint mvp_matrix_ID = glGetUniformLocation(shader_program, "MVP");
	GLuint view_matrix_ID = glGetUniformLocation(shader_program, "V");
	GLuint model_matrix_ID = glGetUniformLocation(shader_program, "M");

	glm::mat4 mvp = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
	glUniformMatrix4fv(mvp_matrix_ID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(model_matrix_ID, 1, GL_FALSE, &this->modelMatrix()[0][0]);
	glUniformMatrix4fv(view_matrix_ID, 1, GL_FALSE, &camera->viewMatrix()[0][0]);


	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture->texture_id);
	//glUniform1i(this->texture->id, 0);

	this->mesh->draw();
}

GLvoid Entity::scale(GLdouble x, GLdouble y, GLdouble z)
{
	this->scaling = glm::scale(glm::vec3(x, y, z));
}
GLvoid Entity::scale(glm::vec3 xyz)
{
	this->scaling = glm::scale(xyz);
}
GLvoid Entity::rotate(GLfloat angle, GLdouble axis_x, GLdouble axis_y, GLdouble axis_z)
{
	this->rotation = glm::rotate(glm::radians(angle), glm::vec3(axis_x, axis_y, axis_z));
}
GLvoid Entity::rotate(GLfloat angle, glm::vec3 axis)
{
	this->rotation = glm::rotate(glm::radians(angle), axis);
}
GLvoid Entity::translate(GLdouble x, GLdouble y, GLdouble z)
{
	this->translation = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));
}
GLvoid Entity::translate(glm::vec3 xyz)
{
	this->translation = glm::translate(glm::mat4(1.0), xyz);
}

BoundingBox Entity::calcBoundingBox()
{
	BoundingBox boundingBox = this->mesh->get_boundingBox();
	glm::vec4 tmp_max = { boundingBox.max_x, boundingBox.max_y, boundingBox.max_z, 1.0f };
	tmp_max = this->modelMatrix() * tmp_max;

	glm::vec4 tmp_min = { boundingBox.min_x, boundingBox.min_y, boundingBox.min_z, 1.0f };
	tmp_min = this->modelMatrix() * tmp_min;

	boundingBox.max_x = tmp_max.x;
	boundingBox.max_y = tmp_max.y;
	boundingBox.max_z = tmp_max.z;
	boundingBox.min_x = tmp_min.x;
	boundingBox.min_y = tmp_min.y;
	boundingBox.min_z = tmp_min.z;

	return boundingBox;
}

glm::mat4 Entity::modelMatrix()
{
	return this->translation * this->rotation * this->scaling;
}