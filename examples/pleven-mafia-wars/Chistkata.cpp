#include "Chistkata.h"

void Chistkata::onStart()
{
	loadTexture(GL_TEXTURE0, "assets/container.jpg");
	loadTexture(GL_TEXTURE1, "assets/wall.jpg");

	addCube(glm::vec3(-1.0f, -0.2f, 0.0f), Vector3D(1.0f), 1, true);
	laserBeam = &addLine(cam.getPosition(), cam.getPosition() + cam.getFront() * 1000.0f, Color(1.0f, 0.0f, 0.0f, 1.0f));
}

void Chistkata::onUpdate()
{
	laserBeam->start = cam.getPosition() + Vector3D(0.0f, -0.2f, 0.0f);
	laserBeam->end = cam.getPosition() + cam.getFront() * 1000.0f;
}

void Chistkata::onStop()
{
}

void Chistkata::processInput()
{
	if (isKeyActioned(GLFW_KEY_ESCAPE, GLFW_PRESS))
		window.close();
	else if (isKeyActioned(GLFW_KEY_W, GLFW_PRESS)) {
		cam.moveForward();
	}
	else if (isKeyActioned(GLFW_KEY_S, GLFW_PRESS)) {
		cam.moveBackward();
	}
	else if (isKeyActioned(GLFW_KEY_A, GLFW_PRESS)) {
		cam.moveLeft();
	}
	else if (isKeyActioned(GLFW_KEY_D, GLFW_PRESS)) {
		cam.moveRight();
	}
}

void Chistkata::onMouseMove(double xpos, double ypos)
{
	cam.onMouseMove(xpos, ypos);
}

void Chistkata::activateLaser()
{
}

void Chistkata::updateLaserPos()
{
}

void Chistkata::deactivateLaser()
{
}
