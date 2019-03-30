#include "player.h"
#include <iostream>

Player::Player(Texture* texture, Mesh* mesh)
	: Entity(texture, mesh)
{
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
bool Player::nearCollisionTest(Entity* entity)
{
	static GLdouble a = glfwGetTime();

	if (glfwGetTime() - a > 1)
	{
		for (int i = 0; i < entity->get_mesh()->get_vertex_count() / 3; i++)
		{
			Plane plane = entity->get_mesh()->get_plane(i);
			plane.transform(entity->modelMatrix());

			std::cout << plane.distance({ 0,1,0 }) << std::endl;
		}
		std::cout << std::endl;

		a = glfwGetTime();
	}

	return false;
}
