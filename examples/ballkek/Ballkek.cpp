#include "Ballkek.h"

#include "../../src/engine/camera/FPSCamera.h"

void Ballkek::onStart()
{
	std::unique_ptr<FPSCamera> cam = std::make_unique<FPSCamera>();

	cam->init(glm::radians(45.0f), width / height, 0.01f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), width, height);
	setCamera(std::move(cam));

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
