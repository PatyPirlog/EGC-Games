#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	square->SetDrawMode(GL_LINE_LOOP);
	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateBalloon(std::string name, glm::vec3 leftBottomCorner, int nr_triangles, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	//corner += glm::vec3(0, 2.0f * M_PI * float(nr_triangles) / float(nr_triangles), 0);

	std::vector<VertexFormat> vertices_circle;

	vertices_circle.push_back(VertexFormat(corner, color));
	for (int i = 0; i <= nr_triangles + 1; i++)
	{
		float angle = 2 * M_PI * float(i) / float(nr_triangles);

		float x = cosf(angle), y = sinf(angle);

		vertices_circle.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
	}

	std::vector<ushort> circle_indices;

	for (int i = 2; i <= nr_triangles + 1; i++)
	{
		circle_indices.push_back(0);
		circle_indices.push_back(i - 1);
		circle_indices.push_back(i);
	};

	// add the last triangle
	circle_indices.push_back(0);
	circle_indices.push_back(nr_triangles + 1);
	circle_indices.push_back(1);

	Mesh* circle = new Mesh(name);

	circle->SetDrawMode(GL_TRIANGLE_FAN);
	circle->InitFromData(vertices_circle, circle_indices);
	return circle;
}

Mesh* Object2D::CreateLine(std::string name, glm::vec3 leftBottomCorner, float line_length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0 , -0.5 * line_length , 0), color),
		VertexFormat(corner + glm::vec3(0, -2 * line_length, 0), color),
		VertexFormat(corner + glm::vec3(- 10, -2 *line_length - 10, 0), color),
		VertexFormat(corner + glm::vec3(0 , -2 *line_length - 20, 0), color),
		VertexFormat(corner + glm::vec3(- 10, -2 *line_length - 30, 0), color),
		VertexFormat(corner + glm::vec3(0 , -2 *line_length - 40, 0), color),
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5};

	if (!fill) {
		line->SetDrawMode(GL_LINE_STRIP);
	}
	line->InitFromData(vertices, indices);
	return line;
}


Mesh* Object2D::CreateSemiCircle(std::string name, glm::vec3 leftBottomCorner, int nr_triangles, glm::vec3 color)
{	
	glm::vec3 corner = leftBottomCorner;
	//corner += glm::vec3(0, 2.0f * M_PI * float(nr_triangles) / float(nr_triangles), 0);

	std::vector<VertexFormat> vertices_circle;

	vertices_circle.push_back(VertexFormat(corner, color));
	for (int i = 0; i <= nr_triangles + 1; i++)
	{
		float angle = M_PI * float(i) / float(nr_triangles);

		float x = cosf(angle), y = sinf(angle);

		vertices_circle.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
	}

	std::vector<ushort> circle_indices;

	for (int i = 2; i <= nr_triangles + 1; i++)
	{
		//circle_indices.push_back(0);
		circle_indices.push_back(i - 1);
		circle_indices.push_back(i);
	};
	
	// add the last triangle
	//circle_indices.push_back(0);
	circle_indices.push_back(nr_triangles + 1);
	circle_indices.push_back(1);
	
	Mesh* circle = new Mesh(name);

	circle->SetDrawMode(GL_LINE_STRIP);
	circle->InitFromData(vertices_circle, circle_indices);
	return circle;
}


Mesh* Object2D::CreateArrow(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(height, 0, 0), color),
		VertexFormat(corner + glm::vec3(height, width, 0), color),

		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(height, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color),

		VertexFormat(corner + glm::vec3(height ,  -20, 0), color),
		VertexFormat(corner + glm::vec3(height + 20, width / 2, 0), color),
		VertexFormat(corner + glm::vec3(height, width + 20, 0), color),

		// triunghiuri spate sageata
		VertexFormat(corner + glm::vec3(5,  0, 0), color),
		VertexFormat(corner + glm::vec3(10, 0, 0), color),
		VertexFormat(corner + glm::vec3(-5, -20, 0), color),

		VertexFormat(corner + glm::vec3(5,  width, 0), color),
		VertexFormat(corner + glm::vec3(10, width, 0), color),
		VertexFormat(corner + glm::vec3(-5, width + 20, 0), color),

		VertexFormat(corner + glm::vec3(15,  0, 0), color),
		VertexFormat(corner + glm::vec3(30, 0, 0), color),
		VertexFormat(corner + glm::vec3(-10, -30, 0), color),

		VertexFormat(corner + glm::vec3(15,  width, 0), color),
		VertexFormat(corner + glm::vec3(30, width, 0), color),
		VertexFormat(corner + glm::vec3(-10, width + 30, 0), color),
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	if (!fill) {
		square->SetDrawMode(GL_TRIANGLES);
	} else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}
	
	square->InitFromData(vertices, indices);
	return square;
}


Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{	//triangle1
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length + 5, 0), color),
		
		//triangle2
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(-length - 5, length, 0), color),
		
		//triangle3
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-length, 0, 0), color),
		VertexFormat(corner + glm::vec3(-length, -length - 5, 0), color),

		//triangle4
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color),
		VertexFormat(corner + glm::vec3(length + 5, -length, 0), color),
		
	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	if (!fill) {
		shuriken->SetDrawMode(GL_TRIANGLES);
	}
	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

// folosita pt afisarea scorului
Mesh* Object2D::CreateHeart(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		//VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length * 2, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),

		VertexFormat(corner + glm::vec3(2 * length, length, 0), color),
		VertexFormat(corner + glm::vec3(length + length/2, length + length/2, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),

		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(length/2, length + length/2, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
	};

	Mesh* heart = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	heart->SetDrawMode(GL_TRIANGLES);
	heart->InitFromData(vertices, indices);
	return heart;
}

Mesh* Object2D::CreateStar(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(length * 2, length, 0), color),
		VertexFormat(corner + glm::vec3(length, length * 2 + 10, 0), color),

		VertexFormat(corner + glm::vec3(length, length - 10, 0), color),
		VertexFormat(corner + glm::vec3(length * 2, length * 2, 0), color),
		VertexFormat(corner + glm::vec3(0, length * 2, 0), color),
	};

	Mesh* star = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5 };

	star->SetDrawMode(GL_TRIANGLES);
	star->InitFromData(vertices, indices);
	return star;
}

// metoda folosita pt coliziunea dintre cerc si shuriken
bool Object2D::checkCollisionCircle(float circle1X, float circle1Y, float circle1radius, float circle2X, float circle2Y, float circle2radius) {
	float dx, dy, dist;
	dx = circle1X - circle2X;
	dy = circle1Y - circle2Y;
	dist = sqrt(dx * dx + dy * dy);

	// daca s a produs coliziune, se intoarce true, altfel false
	if (dist < circle1radius + circle2radius)
		return true;
	else
		return false;
}

bool Object2D::checkCollisionPoint(float pointX, float pointY, float circleX, float circleY, float circleRadius)
{
	float dx, dy, dist;
	dx = pointX - circleX;
	dy = pointY - circleY;
	dist = sqrt(dx * dx + dy * dy);

	// daca s a produs coliziune, se intoarce true, altfel false
	if (dist <= circleRadius)
		return true;
	else
		return false;
}

