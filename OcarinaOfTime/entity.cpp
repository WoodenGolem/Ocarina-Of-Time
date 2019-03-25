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


GLvoid Entity::draw(GLuint shader_program, Camera& camera)
{
	// Not a Lightsource
	glUniform1f(glGetUniformLocation(shader_program, "alpha_value"), 1.0f);
	glUniform1i(glGetUniformLocation(shader_program, "is_source"), 0);

	GLuint mvp_matrix_ID = glGetUniformLocation(shader_program, "MVP");
	GLuint view_matrix_ID = glGetUniformLocation(shader_program, "V");
	GLuint model_matrix_ID = glGetUniformLocation(shader_program, "M");

	glm::mat4 mvp = camera.projectionMatrix() * camera.viewMatrix() * this->modelMatrix();
	glUniformMatrix4fv(mvp_matrix_ID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(model_matrix_ID, 1, GL_FALSE, &this->modelMatrix()[0][0]);
	glUniformMatrix4fv(view_matrix_ID, 1, GL_FALSE, &camera.viewMatrix()[0][0]);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture->data);
	glUniform1i(this->texture->id, 0);

	this->mesh->draw();
}


glm::mat4 Entity::modelMatrix()
{
	return this->translation * this->rotation * this->scaling;
}