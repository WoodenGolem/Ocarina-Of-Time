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
	// DEBUG
	static GLfloat lastTime = glfwGetTime();

	glm::mat3 ESpace = { { 1 / this->ellipsoid.x, 0, 0}, { 0, 1 / this->ellipsoid.y, 0 },{ 0, 0, 1 / this->ellipsoid.z } };
	glm::mat3 invESpace = { {this->ellipsoid.x, 0, 0}, {0, this->ellipsoid.y, 0},{0, 0, this->ellipsoid.z} };
	glm::vec3 v;
	glm::vec3 pos = this->get_position() * ESpace;
	glm::vec3 intersect;

	for (int i = 0; i < entity->get_mesh()->get_vertex_count() / 3; i++)
	{
		Triangle triangle = entity->get_mesh()->get_triangle(i);
		triangle.transform(entity->modelMatrix());
		triangle.transform(ESpace);

		v = this->velocity * deltaTime;
		v = v * ESpace;

		intersect = pos - triangle.get_normal();

		GLfloat t0 = (1 - triangle.distance(pos)) / glm::dot(triangle.get_normal(), v);

		// DEBUG
		if (glfwGetTime() - lastTime >= 10)
		{
			intersect += (v * t0);
			std::cout << v.x << " " << v.y << " " << v.z << std::endl;
			std::cout << intersect.x << " " << intersect.y << " " << intersect.z << std::endl;
			std::cout << t0 << std::endl;

			lastTime = glfwGetTime();
		}

		if (t0 < 1 && t0 > 0)
		{
			if (triangle.PointInTriangle(intersect + v * t0))
			{
				// Project the velocity vector onto the plane the player is colliding with
				this->velocity = this->velocity - glm::dot(this->velocity, triangle.get_normal()) * triangle.get_normal();
			}
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
	
