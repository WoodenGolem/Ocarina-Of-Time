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
	// HIGHLY EXPERIMENTAL
	static GLfloat lastTime = GLfloat(glfwGetTime());
	GLfloat currentTime = GLfloat(glfwGetTime());
	GLfloat dTime = currentTime - lastTime;

	if (this->get_position().y < -15) {
		std::cout << "Respawn!" << std::endl;
		this->translate(0, 5, 0);
	}

	glm::mat3 eSpace = { {1 / this->ellipsoid.x, 0,0}, {0,1 / this->ellipsoid.y, 0}, {0,0,1 / this->ellipsoid.z} };

	//if (dTime > 1)
		for (int i = 0; i < entity->get_mesh()->get_vertex_count() / 3; i++)
		{
			Triangle triangle = entity->get_mesh()->get_triangle(i);
			// TODO: Static meshes should have the modelMatrix already applied for better performance

			// Transform Ellipsoid to eSpace
			triangle.transform(entity->modelMatrix());
			triangle.transform(eSpace);

			glm::vec3 v = this->velocity * deltaTime;
			v = v * eSpace;
			GLfloat t0, t1 = 0;
			if (v != glm::vec3({ 0,0,0 })) 
			{
				t0 = (1 - triangle.distance(this->get_position())) / (glm::dot(triangle.get_normal(), v)) * deltaTime;
				t1 = (-1 - triangle.distance(this->get_position())) / (glm::dot(triangle.get_normal(), v)) * deltaTime;
			}
			else
			{
				return false;
			}

			if ((t0 < deltaTime*2 && t0 >= 0) || (t1 < deltaTime*2 && t1 >= 0))
			{
				if (triangle.PointInTriangle(this->get_position() + v))
				{
					return true;
				}
			}

			//std::cout << std::endl;
			lastTime = currentTime;
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
	
