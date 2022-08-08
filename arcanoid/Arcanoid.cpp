#include "Arcanoid.h"

#include "../models/TypeDefs.h"

void Arcanoid::onStart() {
	init(800, 600, "Arcanoid", Color(4.0/255, 44.0/255, 98.0/255, 1.0f));
	shaderProgram.attachVertexShader("texture_vertex");
	shaderProgram.attachFragmentShader("texture_fragment");

	createRect(Point3D(0.0f, 0.0f, 0.0f), 0.1, 0.1);
}

void Arcanoid::onUpdate() {

}

void Arcanoid::onStop() {

}