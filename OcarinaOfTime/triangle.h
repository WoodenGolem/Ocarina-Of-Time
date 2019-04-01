#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "declarations.h"

class Triangle
{
public:
	Triangle(glm::vec3 p1,
			 glm::vec3 p2,
			 glm::vec3 p3,
			 glm::vec3 normal);
	
	GLdouble distance(glm::vec3 point);
	GLvoid transform(glm::mat4 matrix);
	GLvoid transform(glm::mat3 matrix);
	GLboolean PointInTriangle(glm::vec3 point);

	glm::vec3 get_normal() const;

private:
	glm::vec3 p1, p2, p3;
	glm::vec3 normal;
	GLdouble preCalculated[1];

	GLboolean SameSide(glm::vec3 p1,
					   glm::vec3 p2,
					   glm::vec3 a,
					   glm::vec3 b);
};

#endif // !TRIANGLE_H