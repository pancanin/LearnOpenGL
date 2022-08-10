#include "Arcanoid.h"

#include "../models/TypeDefs.h"

void Arcanoid::onStart() {
	init(screenWidth, screenHeight, title, screenClearColor);
	shaderProgram.attachVertexShader("texture_vertex");
	shaderProgram.attachFragmentShader("texture_fragment");
	loadTexture(0, "assets/wall.jpg");
	loadTexture(1, "assets/container.jpg");
	shaderProgram.link();

	createRect(Point3D(0.0f, 0.0f, 0.0f), 400, 300, 1);
}

void Arcanoid::onUpdate() {

}

void Arcanoid::onStop() {

}