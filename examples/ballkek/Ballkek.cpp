#include "Ballkek.h"

void Ballkek::onStart()
{
	configureFPSCamera();
	auto textureId = loadTexture(GL_TEXTURE0, "assets/container.jpg");
	auto textureId2 = loadTexture(GL_TEXTURE1, "assets/wall.jpg");

	Rect& r = addRect(
		Vector3D(-1.0f, -.5f, -1.0f),
		Vector3D(1.0f, -.5f, -1.0f),
		Vector3D(1.0f, -.5f, 1.0f),
		Vector3D(-1.0f, -.5f, 1.0f),
		Vector3D(3.5f),
		textureId2,
		8,
		true);
}

void Ballkek::onUpdate()
{
}

void Ballkek::onStop()
{
}

void Ballkek::processInput()
{
}

void Ballkek::onMouseMove(double xpos, double ypos)
{
}

void Ballkek::onMouseClick(int button, int action)
{
}
