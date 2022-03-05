#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }
    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(std::string name, glm::vec3 center, int l, int L, glm::vec3 color)
{
	Mesh* rectangle = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(center.x - L / 2, center.y + l / 2, 0), color),
		VertexFormat(glm::vec3(center.x - L / 2, center.y - l / 2, 0), color),
		VertexFormat(glm::vec3(center.x + L / 2, center.y + l / 2, 0), color),
		VertexFormat(glm::vec3(center.x + L / 2, center.y - l / 2, 0), color)
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
	Mesh* circle = new Mesh(name);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	int number_of_triangles = 100;

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_triangles;
	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	// last triangle
	indices.push_back(0);
	indices.push_back(number_of_triangles);
	indices.push_back(1);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* object2D::CreatePlayer(std::string name, glm::vec3 playerCenter) {

	Mesh* player = new Mesh(name);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	// circle1
	float radius = 30;
	glm::vec3 center = glm::vec3(playerCenter.x - radius, playerCenter.y, 0);
	glm::vec3 color = YELLOW;

	int number_of_triangles = 100;

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_triangles;
	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	// last triangle
	indices.push_back(0);
	indices.push_back(number_of_triangles);
	indices.push_back(1); 

	// circle 3
	radius = 5;
	center = glm::vec3(playerCenter.x + 15, playerCenter.y + 15, 0);
	color = BLACK;

	// add origin
	int current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	// circle 4
	radius = 5;
	center = glm::vec3(playerCenter.x + 15, playerCenter.y - 7.5, 0);
	color = BLACK;

	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	// circle 2
	radius = 25;
	center = glm::vec3(playerCenter.x - 5, playerCenter.y + 4, 0);
	color = ORANGE;

	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	current_size = vertices.size();

	indices.push_back(current_size);
	indices.push_back(1 + current_size);
	indices.push_back(2 + current_size);

	player->InitFromData(vertices, indices);
	return player;
}

Mesh* object2D::CreateEnemy(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, length, 0), color), // 0
		VertexFormat(corner + glm::vec3(length, length, 0), color), // 1
		VertexFormat(corner, color),  // 2
		VertexFormat(corner + glm::vec3(length, 0, 0), color), // 3
		VertexFormat(corner + glm::vec3(length, -length, 0), color), // 4
		VertexFormat(corner + glm::vec3(0, -length, 0), color), // 5
		VertexFormat(corner + glm::vec3(-length, -length, 0), color), // 6
		VertexFormat(corner + glm::vec3(-length, 0, 0), color), // 7
		VertexFormat(corner + glm::vec3(-length, length, 0), color), // 8

	};

	Mesh* enemy = new Mesh(name);
	std::vector<unsigned int> indices = { 5,2,6, 2,6,7, 1,2,0, 1,2,3};
	enemy->InitFromData(vertices, indices);

	return enemy;
}

Mesh* object2D::CreateCloud(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	float initialRadius = radius;
	glm::vec3 initialCenter = center;

	Mesh* circle = new Mesh(name);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	int number_of_triangles = 100;

	//circle1

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_triangles;
	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	// last triangle
	indices.push_back(0);
	indices.push_back(number_of_triangles);
	indices.push_back(1);

	// circle2
	center = glm::vec3(center.x + 1.2 * radius, center.y - 0.6 * radius, 0);
	radius = radius * 0.8;
	// add origin
	int current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	//circle3
	center = glm::vec3(initialCenter.x + initialRadius / 4, initialCenter.y - (initialRadius * 0.7), 0);
	radius = initialRadius * 1.2;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	// circle4
	center = glm::vec3(initialCenter.x - (initialRadius * 1.1), initialCenter.y - (initialRadius * 1.1), 0);
	radius = initialRadius * 0.8;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	//circle5
	center = glm::vec3(initialCenter.x + (initialRadius * 1.3), initialCenter.y - (initialRadius * 1.5), 0);
	radius = initialRadius * 0.5;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	//circle6
	center = glm::vec3(initialCenter.x + (initialRadius * 2), initialCenter.y - (initialRadius * 1.1), 0);
	radius = initialRadius * 0.65;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* object2D::CreateScore(std::string name, glm::vec3 upRight, glm::vec3 color)
{
	glm::vec3 scorePosition = upRight;

	std::vector<VertexFormat> scoreVertices =
	{
		VertexFormat(scorePosition + glm::vec3(0, 0, 0), color),
		VertexFormat(scorePosition + glm::vec3(0.25, 0, 0), color),
		VertexFormat(scorePosition + glm::vec3(0.25, 1, 0), color),
		VertexFormat(scorePosition + glm::vec3(0, 1, 0), color),
	};

	Mesh* score = new Mesh(name);
	std::vector<unsigned int> scoreIndices =
	{
		0, 1, 2,
		0, 2, 3
	};

	score->InitFromData(scoreVertices, scoreIndices);
	return score;
}