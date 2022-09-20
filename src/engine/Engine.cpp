#include "Engine.h"

#include <functional>

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

	while (!window.shouldClose()) {
		processInput();
		window.clear();

		// we need to bind the textures here, so we need a way to store textures.
		for (TextureComponent& tex : textures) {
			tex.bind();
		}

		onUpdate();

		physics.checkCollisions(bagLines, bag);

		// Put a cap on how many intersections we process per frame
		while (!physics.intersectionPoints.empty()) {
			Point3D point = physics.intersectionPoints.front();
			physics.intersectionPoints.pop();

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

Object& Engine::addCube(Point3D position, Vector3D scaleFactor, int textureId, bool isIntersectable)
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

Line& Engine::addLine(Point3D start, Point3D end, Color color)
{
	Line line;
	line.start = start;
	line.end = end;
	line.color = color;

	return bagLines.add(line);
}