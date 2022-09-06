#pragma once
#include "../engine/Engine.h"

#include "../libs/glm/glm.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/gtc/type_ptr.hpp"

class Arcanoid : public Engine {
private:
	void onStart();
	void onUpdate();
	void onStop();

	const unsigned int screenWidth = 800;
	const unsigned int screenHeight = 600;
	const std::string title = "Arcanoid";
	const Color screenClearColor = Color(4, 44, 98, 255);

	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	float rotationAngle = glm::radians(0.0f);
};