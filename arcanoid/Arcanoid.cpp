#include "Arcanoid.h"

#include "../models/TypeDefs.h"

void Arcanoid::onStart() {
	init(screenWidth, screenHeight, title, screenClearColor);
	shaderProgram.attachVertexShader("texture_vertex");
	shaderProgram.attachFragmentShader("texture_fragment");
	shaderProgram.link();
	loadTexture(1, "assets/wall.jpg");
	loadTexture(2, "assets/container.jpg");
	createRect(Point3D(200.0f, 150.0f, 0.0f), 400, 300, 1);
	createRect(Point3D(100.0f, 100.0f, 0.0f), 50, 50, 2);
	trectComp.loadBuffer();
}

void Arcanoid::onUpdate() {
	rotationAngle = 0.0001;
	
	transform = glm::rotate(transform, rotationAngle, rotationAxis);
	
	shaderProgram.setUniformMat4("transform", transform);
}

void Arcanoid::onStop() {

}