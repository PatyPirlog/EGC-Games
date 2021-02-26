#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateBalloon(std::string name, glm::vec3 leftBottomCorner, int nr_triangles, glm::vec3 color, bool fill);
	Mesh* CreateSemiCircle(std::string name, glm::vec3 leftBottomCorner, int nr_triangles, glm::vec3 color);
	Mesh* CreateArrow(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill);
	Mesh* CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateLine(std::string name, glm::vec3 leftBottomCorner, float line_length, glm::vec3 color, bool fill);
	Mesh* CreateHeart(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateStar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	bool checkCollisionCircle(float circle1X, float circle1Y, float circle2X, float circle2Y, float circle1radius, float circle2radius);
	bool checkCollisionPoint(float pointX, float pointY, float circleX, float circleY, float circleRadius);

}

