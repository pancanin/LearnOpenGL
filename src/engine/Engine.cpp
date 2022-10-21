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

	objects.init(100);
	lines.init(100);

	mouseIn.init(
		window,
		std::bind(&Engine::onMouseMove, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Engine::onMouseClick, this, std::placeholders::_1, std::placeholders::_2)
	);

	renderer.init();

	defaultObjectShader = std::make_shared<ShaderProgram>();
	defaultObjectShader->init();
	defaultObjectShader->attachVertexShader("src/engine/shaders/default_vertex");
	defaultObjectShader->attachFragmentShader("src/engine/shaders/default_fragment");
	defaultObjectShader->link();
	defaultObjectShader->use();
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

		for (auto& line : lines.data) {
			renderer.render(cam, line);
		}

		for (auto& object : objects.data) {
			renderer.render(cam, object);
		}

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

Object& Engine::addObject(
	ObjectType type,
	const Point3D& position,
	const Vector3D& scaleFactor,
	const Vector3D& rotationAxis,
	float rotationAngle,
	int textureId,
	std::shared_ptr<ShaderProgram> shader,
	bool isIntersectable
	)
{
	Object& object = addObject(type, position, scaleFactor, rotationAxis, rotationAngle, textureId, isIntersectable);

	object.shader = shader;

	return object;
}

Object& Engine::addObject(ObjectType type, const Point3D& position, const Vector3D& scaleFactor, const Vector3D& rotationAxis, float rotationAngle, int textureId, bool isIntersectable)
{
	Object object;
	object.position = position;
	object.rotationAxis = rotationAxis;
	object.rotationAngle = rotationAngle;
	object.velocity = glm::vec3(0.0f);
	object.type = type;
	object.intersectible = isIntersectable;
	object.scaleFactor = scaleFactor;
	object.textureUnit = textureId;
	object.shader = defaultObjectShader;

	return objects.add(object);
}

Object& Engine::addCube(const Point3D& position, const Vector3D& scaleFactor, int textureId, bool isIntersectable)
{
	return addObject(ObjectType::CUBE, position, scaleFactor, Vector3D(0.0f), 0.0f, textureId, isIntersectable);
}

Object& Engine::addTriangle(
	const Point3D& position,
	const Vector3D& scaleFactor,
	const Vector3D& rotationAxis,
	float rotationAngle,
	int textureId,
	bool isIntersectable)
{
	return addObject(ObjectType::TRIANGLE, position, scaleFactor, rotationAxis, rotationAngle, textureId, isIntersectable);
}

Line& Engine::addLine(const Point3D& start, const Point3D& end, const Color& color)
{
	return lines.add(Line(start, end, color));
}
