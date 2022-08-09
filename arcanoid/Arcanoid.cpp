#include "Arcanoid.h"

#include "../models/TypeDefs.h"

void Arcanoid::onStart() {
	init(screenWidth, screenHeight, title, screenClearColor);
	shaderProgram.attachVertexShader("texture_vertex");
	shaderProgram.attachFragmentShader("texture_fragment");

	createRect(Point3D(0.0f, 0.0f, 0.0f), 10, 10);
}

void Arcanoid::onUpdate() {

}

void Arcanoid::onStop() {

}