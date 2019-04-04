#include "entity.h"


Entity::Entity(Texture* p_texture,
			   Mesh* p_mesh)
{
	// Rendering
	this->texture = p_texture;
	this->mesh = p_mesh;

	// Transforming
	this->scaling	  = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	this->rotation	  = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	// Physics
	this->velocity = { 0,0,0 };
	this->mass = 1;	// For later
}


// Rendering
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
glm::mat4 Entity::modelMatrix()
{
	return this->translation * this->rotation * this->scaling;
}

// Transforming
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
Mesh* Entity::get_mesh() const
{
	return this->mesh;
}
glm::vec3 Entity::get_position() const
{
	return glm::vec3(this->translation[3]);
}

// Physics
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
GLvoid Entity::applyForce(glm::vec3 force)
{
	this->forces.push_back(force);
}
GLvoid Entity::update()
{
	// Sum up applied forces
	glm::vec3 force = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i < this->forces.size(); i++) {
		force += this->forces[i];
	}

	// Add acceleration to velocity vector
	if (this->forces.size() > 0)
	{
		this->velocity += force / this->mass;
	}

	// Reducing velocity each frame if no forces were applied
	if (glm::length(force) == 0)
	{
		this->velocity *= 0.93f;
		if (glm::length(velocity) < 0.01)
		{
			this->velocity = { 0,0,0 };
		}
	}

	// Limit velocity to 5 units/second for each direction
	if (abs(this->velocity.x) > 5){
		this->velocity.x = (this->velocity.x / abs(this->velocity.x)) * 5;
	}
	if (abs(this->velocity.y) > 5){
		this->velocity.y = (this->velocity.y / abs(this->velocity.y)) * 5;
	}
	if (abs(this->velocity.z) > 5){
		this->velocity.z = (this->velocity.z / abs(this->velocity.z)) * 5;
	}

	// Clear forces vector
	this->forces.clear();
}
GLvoid Entity::move(GLfloat deltaTime)
{
	this->translate(glm::vec3(this->translation[3]) + this->velocity * deltaTime);
	if (this->translation[3].y < -10) {
		std::cout << "Respawn!" << std::endl;
		this->translate(0, 5, 0);
	}
	this->update();
}

GLvoid Entity::stop()
{
	this->velocity = { 0,0,0 };
}

