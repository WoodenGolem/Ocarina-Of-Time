#include "player.h"
#include <iostream>

Player::Player(Texture* texture, Mesh* mesh)
	: Entity(texture, mesh)
{
	BoundingBox boundingBox = this->mesh->get_boundingBox();
	this->ellipsoid = { boundingBox.max_x, boundingBox.max_y, boundingBox.max_z };

	boundingBox.print();
	this->translate(0, boundingBox.max_y + 0.01, 0);
	this->translate(0, 10, 0);
}

bool Player::broadCollisionTest(Entity* entity)
{
	// EXPERIMENTAL
	BoundingBox playerBox = this->calcBoundingBox();
	BoundingBox entityBox = entity->calcBoundingBox();

	if (not ((playerBox.max_x <= entityBox.max_x && playerBox.max_x >= entityBox.min_x) ||
		(playerBox.min_x <= entityBox.max_x && playerBox.min_x >= entityBox.min_x)))
	{
		return false;
	}

	if (not ((playerBox.max_y <= entityBox.max_y && playerBox.max_y >= entityBox.min_y) ||
		(playerBox.min_y <= entityBox.max_y && playerBox.min_y >= entityBox.min_y)))
	{
		return false;
	}

	if (not ((playerBox.max_z <= entityBox.max_z && playerBox.max_z >= entityBox.min_z) ||
		(playerBox.min_z <= entityBox.max_z && playerBox.min_z >= entityBox.min_z)))
	{
		return false;
	}

	return true;
}
bool Player::nearCollisionTest(Entity* entity, GLfloat deltaTime)
{
	glm::vec3 v;
	glm::mat3 ESpace = { { 1 / this->ellipsoid.x, 0, 0}, { 0, 1 / this->ellipsoid.y, 0 },{ 0, 0, 1 / this->ellipsoid.z } };
	glm::mat3 invESpace = { {this->ellipsoid.x, 0, 0}, {0, this->ellipsoid.y, 0},{0, 0, this->ellipsoid.z} };

	for (int i = 0; i < entity->get_mesh()->get_vertex_count() / 3; i++)
	{
		v = this->velocity * deltaTime;
		Triangle triangle = entity->get_mesh()->get_triangle(i);
		triangle.transform(entity->modelMatrix());
		triangle.transform(ESpace);

		GLfloat t0 = (1 - triangle.distance(this->get_position())) / glm::dot(triangle.get_normal(), v);
		if (t0 < deltaTime)
		{
			// Collision response
			triangle.transform(invESpace);
			if (triangle.PointInTriangle(this->get_position() + v))
			{
				this->velocity = this->velocity - (glm::dot(this->velocity, triangle.get_normal())) * triangle.get_normal();
				//return false;
			}
			//std::cout << this->velocity.x << " " << this->velocity.y << " " << this->velocity.z << std::endl;
		}
		else
		{

		}
	}
	
	return false;
}

GLvoid Player::debug()
{
	static GLdouble time = glfwGetTime();
	if (glfwGetTime() - time > 1)
	{
		std::cout << "Ellipsoid: " << this->ellipsoid.x << " " << this->ellipsoid.y << " " << this->ellipsoid.z << std::endl;
		std::cout << "V: " << glm::length(this->velocity) << std::endl;
		time = glfwGetTime();
	}
}
	
