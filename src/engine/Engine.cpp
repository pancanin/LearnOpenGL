#include "Engine.h"

#include <functional>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>

#include "../../libs/glm/glm.hpp"

void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos);

void Engine::init()
{
	graphics.init();
	// Some defaults here to simplify the API, but these should be configurable.
	float width = 800;
	float height = 600;
	cam.init(glm::radians(45.0f), width / height, 0.1f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), width, height);

	window.init(width, height, "Chistkata FPS Game!", Color(0.2f, 0.2f, 0.2f, 1.0f));
	window.makeActive();
	window.disableCursor();

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!graphics.loadFunctionDefinitions())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	bag.init(100);
	bagLines.init(100);
	mouseIn.init(
		window,
		std::bind(&Engine::onMouseMove, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Engine::onMouseClick, this, std::placeholders::_1, std::placeholders::_2)
	);
}

void Engine::start()
{
	onStart();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	typedef std::chrono::high_resolution_clock Clock;

	while (!window.shouldClose()) {
		auto t0 = Clock::now();

		processInput();
		window.clear();

		for (TextureComponent& tex : textures) {
			tex.bind();
		}

		onUpdate();

		physics.checkCollisions(bagLines, bag);

		

		// Put a cap on how many intersections we process per frame
		while (!physics.collisionPoints.empty()) {
			Point3D point = physics.collisionPoints.front();
			physics.collisionPoints.pop();

			Object explosion;
			explosion.position = point;
			explosion.rotationAxis = glm::vec3(1.0f);
			explosion.velocity = glm::vec3(0.0f);
			explosion.scaleFactor = glm::vec3(0.05f, 0.05f, 0.05f);
			explosion.type = ObjectType::CUBE;
			explosion.textureUnit = 1;
			explosion.intersectible = false;

			bag.add(explosion);
		}
		
		bagLines.draw(cam);
		bag.draw(cam);

		window.swapBuffers();
		graphics.pollEvents();

		auto t1 = Clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
		
		auto sleepDur = std::chrono::milliseconds(1000 / fps) - diff;

		std::this_thread::sleep_for(sleepDur);
	}
}

bool Engine::isKeyActioned(int keyId, int action)
{
	return glfwGetKey(window.getRaw(), keyId) == action;
}

void Engine::loadTexture(int textureId, const std::string& pathToTexture)
{
	TextureComponent texture;
	texture.init(textureId);
	texture.load(pathToTexture);
	texture.bind();
	textures.push_back(texture);
}

void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos)
{
	engine.cam.onMouseMove(xpos, ypos);
	engine.onMouseMove(xpos, ypos);
}

Object& Engine::addCube(const Point3D& position, const Vector3D& scaleFactor, int textureId, bool isIntersectable)
{
	Object cube1;
	cube1.position = position;
	cube1.rotationAxis = glm::vec3(1.0f);
	cube1.velocity = glm::vec3(0.0f);
	cube1.type = ObjectType::CUBE;
	cube1.intersectible = isIntersectable;
	cube1.scaleFactor = scaleFactor;
	cube1.textureUnit = 1;

	return bag.add(cube1);
}

Line& Engine::addLine(const Point3D& start, const Point3D& end, const Color& color)
{
	return bagLines.add(Line(start, end, color));
}
