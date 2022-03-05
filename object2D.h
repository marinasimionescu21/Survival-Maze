#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


#define WHITE	glm::vec3(1.f, 1.f, 1.f)
#define GREY	glm::vec3(0.3f, 0.3f, 0.3f)
#define RED		glm::vec3(1.f, 0.f, 0.f)
#define GREEN	glm::vec3(0.f, 1.f, 0.f)
#define YELLOW	glm::vec3(1.f, 1.f, 0.f)
#define BROWN	glm::vec3(0.7f, 0.6f, 0.4f)
#define BLACK   glm::vec3(0, 0, 0)
#define ORANGE  glm::vec3(1, 0.5f, 0)
#define PINK	glm::vec3(1, 0.6f, 0.8f)


namespace object2D
{
	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);

	Mesh* CreateRectangle(std::string name, glm::vec3 center, int l, int L, glm::vec3 color);

	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill);

	Mesh* CreatePlayer(std::string name, glm::vec3 playerCenter);

	Mesh* CreateScore(std::string name, glm::vec3 upRight, glm::vec3 color);

	Mesh* CreateEnemy(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);

	Mesh* CreateCloud(std::string name, glm::vec3 center, float radius, glm::vec3 color);
}
