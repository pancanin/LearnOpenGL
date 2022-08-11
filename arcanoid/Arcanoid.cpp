#include "Arcanoid.h"

#include "../models/TypeDefs.h"

void Arcanoid::onStart() {
	init(screenWidth, screenHeight, title, screenClearColor);
	shaderProgram.attachVertexShader("texture_vertex");
	shaderProgram.attachFragmentShader("texture_fragment");
	shaderProgram.link();
	loadTexture(2, "assets/container.jpg");
	loadTexture(1, "assets/wall.jpg");

	createRect(Point3D(0.0f, 0.0f, 0.0f), 400, 300, 2);
}

void Arcanoid::onUpdate() {

}

void Arcanoid::onStop() {

}