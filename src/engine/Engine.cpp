#include "Engine.h"

#include <functional>
#include <chrono>
#include <thread>
#include <limits>

#include <GLFW/glfw3.h>

#include "../../libs/glm/glm.hpp"

#include "models/Object.h"
#include "models/Plane.h"

void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos);

void Engine::init()
{
	graphics.init();
	// Some defaults here to simplify the API, but these should be configurable.
	float width = 800;
	float height = 600;
	cam.init(glm::radians(45.0f), width / height, 0.001f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), width, height);

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
	triangles.init(100);
	rects.init(100);
	points.init(100);

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

	vertexIdxAwareShader = std::make_shared<ShaderProgram>();
	vertexIdxAwareShader->init();
	vertexIdxAwareShader->attachVertexShader("src/engine/shaders/vertex_index_aware_vertex_shader");
	vertexIdxAwareShader->attachFragmentShader("src/engine/shaders/default_fragment");
	vertexIdxAwareShader->link();

	pointShader = std::make_shared<ShaderProgram>();
	pointShader->init();
	pointShader->attachVertexShader("src/engine/shaders/point_vs");
	pointShader->attachFragmentShader("src/engine/shaders/point_fs");
	pointShader->link();
}

void Engine::start()
{
	onStart();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_PROGRAM_POINT_SIZE);

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

		for (auto& triangle : triangles.data) {
			renderer.render(cam, triangle);
		}

		for (auto& rect : rects.data) {
			renderer.render(cam, rect);
		}

		for (auto& point : points.data) {
			renderer.render(cam, point);
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

void Engine::processInput()
{
	if (isKeyActioned(GLFW_KEY_ESCAPE, GLFW_PRESS))
		window.close();
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

Triangle& Engine::addTriangle(
	const Point3D& p1,
	const Point3D& p2,
	const Point3D& p3,
	int textureId,
	bool isIntersectable)
{
	return addTriangle(p1, p2, p3, Vector3D(1.0f), textureId, isIntersectable);
}

Triangle& Engine::addTriangle(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Vector3D& scale, int textureId, bool isIntersectable)
{
	return triangles.add(Triangle(p1, p2, p3, scale, textureId, vertexIdxAwareShader));
}

Line& Engine::addLine(const Point3D& start, const Point3D& end, const Color& color)
{
	return lines.add(Line(start, end, color));
}

Plane& Engine::addPlane(const Vector3D& point, const Vector3D& normal, const Color& color)
{
	Vector3D p2 = glm::cross(point, normal);
	Vector3D p3 = glm::cross(p2 - point, normal);
	Vector3D p4 = p2 + p3;

	Plane p;
	return p;
}

Rect& Engine::addRect(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4, const Vector3D& scale, int textureId, bool isIntersectable)
{
	return rects.add(Rect(p1, p2, p3, p4, scale, textureId, vertexIdxAwareShader));
}

Point& Engine::addPoint(const Point3D& position, const Color& color, float size)
{
	return points.add(Point(position, color, size, pointShader));
}
