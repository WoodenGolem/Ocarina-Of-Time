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
	static GLfloat lastTime = glfwGetTime();
	GLfloat currentTime = glfwGetTime();
	GLfloat dTime = currentTime - lastTime;

	//if (dTime > 1)
		for (int i = 0; i < entity->get_mesh()->get_vertex_count() / 3; i++)
		{
			Plane plane = entity->get_mesh()->get_plane(i);
			// TODO: Static meshes should have the modelMatrix already applied for better performance

			// Transform Ellipsoid to eSpace
			plane.transform(entity->modelMatrix());
			plane.pos /= this->ellipsoid;
			plane.normal /= this->ellipsoid;

			//std::cout << std::endl << "NEAR" << std::endl;
			glm::vec3 v = this->velocity * deltaTime;
			v /= this->ellipsoid;
			//std::cout << v.x << " ";
			//std::cout << v.y << " ";
	        //std::cout << v.z << std::endl;
			//std::cout << "dTime: " << deltaTime << std::endl;
			//std::cout << "Dist: " << plane.distance(this->get_position()) << std::endl;
			GLfloat t0, t1;
			if (v != glm::vec3({ 0,0,0 })) 
			{
				t0 = (1 - plane.distance(this->get_position())) / (glm::dot(plane.normal, v)) * deltaTime;
				t1 = (-1 - plane.distance(this->get_position())) / (glm::dot(plane.normal, v)) * deltaTime;
			}
			else
			{
				return false;
			}
			
			//std::cout << "t0: " << t0 << std::endl;
			//std::cout << "t1: " << t1 << std::endl;

			if ((t0 < deltaTime*2 && t0 >= 0) || (t1 < deltaTime*2 && t1 >= 0))
			{
				return true;
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
	
