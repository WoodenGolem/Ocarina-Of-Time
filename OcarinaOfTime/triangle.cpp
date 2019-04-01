#include "triangle.h"



Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 normal)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	this->normal = normal;

	this->preCalculated[0] = glm::dot(-this->normal, this->p1);
}

GLdouble Triangle::distance(glm::vec3 point)
{
	return glm::dot(this->normal, point) + this->preCalculated[0];
}

GLvoid Triangle::transform(glm::mat4 matrix)
{
	this->p1 = glm::vec4(this->p1, 1.0f) * matrix;
	this->p2 = glm::vec4(this->p2, 1.0f) * matrix;
	this->p3 = glm::vec4(this->p3, 1.0f) * matrix;
}

GLvoid Triangle::transform(glm::mat3 matrix)
{
	this->normal = this->normal * matrix;
}

GLboolean Triangle::PointInTriangle(glm::vec3 point)
{
	if (SameSide(point, this->p1, this->p2, this->p3) &&
		SameSide(point, this->p2, this->p1, this->p3) &&
		SameSide(point, this->p3, this->p1, this->p2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

glm::vec3 Triangle::get_normal() const
{
	return this->normal;
}

GLboolean Triangle::SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b)
{
	glm::vec3 cp1 = glm::cross(b - a, p1 - a);
	glm::vec3 cp2 = glm::cross(b - a, p2 - a);
	if (glm::dot(cp1, cp2) >= 0) {
		return true;
	}
	else
	{
		return false;
	}
}
