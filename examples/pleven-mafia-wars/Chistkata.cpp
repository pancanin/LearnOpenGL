#include "Chistkata.h"

#include "../../src/engine/models/Line.h"

// Helper to debug object position
void printVec(const Vector3D& vec) {
	using namespace std;

	cout << "x=" << vec.x << ";y=" << vec.y << ";z=" << vec.z << endl;
}

void Chistkata::onStart()
{
	loadTexture(GL_TEXTURE0, "assets/container.jpg");
	loadTexture(GL_TEXTURE1, "assets/wall.jpg");
	loadTexture(GL_TEXTURE2, "assets/blue.png");

	Rect& r = addRect(
		glm::vec3(-1.0f, 1.0f, 0.0f),
		Vector3D(1.0f, 1.0f, 0.0f),
		Vector3D(1.0f, -1.0f, 0.0f),
		Vector3D(-1.0f, -1.0f, 0.0f),
		Vector3D(1.0f),
		0,
		true);

	addLine(
		Vector3D(0.0f, 0.0f, 0.0f),
		Vector3D(0.0f, 0.0f, 1.0f),
		Color(1.0f, 0.0f, 0.0f, 1.0f)
	);
}

void Chistkata::onUpdate()
{
	updateLaserPos();
}

void Chistkata::onStop()
{
}

void Chistkata::processInput()
{
	if (isKeyActioned(GLFW_KEY_W, GLFW_PRESS)) {
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

	Engine::processInput();
}

void Chistkata::onMouseMove(double xpos, double ypos)
{
	cam.onMouseMove(xpos, ypos);
}

void Chistkata::onMouseClick(int button, int action)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			activateLaser();
		}
		else if (action == GLFW_RELEASE) {
			deactivateLaser();
		}
	}
}

void Chistkata::activateLaser()
{
	laserBeam = &addLine(cam.getPosition(), cam.getPosition() + cam.getFront() * 1000.0f, Color(1.0f, 0.0f, 0.0f, 1.0f));
}

void Chistkata::updateLaserPos()
{
	if (laserBeam != nullptr) {
		laserBeam->start = cam.getPosition() + Vector3D(0.0f, -0.2f, 0.0f);
		laserBeam->direction = cam.getPosition() + cam.getFront() * 1000.0f;
	}
}

void Chistkata::deactivateLaser()
{
	lines.remove(*laserBeam);
}
