#include "Engine.h"

#include <functional>
#include <chrono>
#include <thread>
#include <limits>

#include <GLFW/glfw3.h>

#include "../../libs/glm/glm.hpp"

#include "models/Object.h"
#include "models/Plane.h"
#include "camera/Camera.h"

void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos);
void key_callback(Engine&, GLFWwindow*, int key, int scancode, int action, int mods);

void Engine::init(uint32_t width, uint32_t height)
{
	graphics.init();
	
	this->width = width;
	this->height = height;

	window.init(width, height, "Chistkata FPS Game!", Color(0.2f, 0.2f, 0.2f, 1.0f));
	window.makeActive();
	window.disableCursor();

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
		std::bind(&Engine::_onMouseMove, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Engine::onMouseClick, this, std::placeholders::_1, std::placeholders::_2)
	);

	/*window.registerKeyCallback(
		std::bind(key_callback, this, window.getRaw(), std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4)
	);*/

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

		_processInput();
		window.clear();

		for (TextureComponent& tex : textures) {
			tex.bind();
		}

		onUpdate();

		for (auto& line : lines.data) {
			renderer.render(*cam, line);
		}

		for (auto& object : objects.data) {
			renderer.render(*cam, object);
		}

		for (auto& triangle : triangles.data) {
			renderer.render(*cam, triangle);
		}

		for (auto& rect : rects.data) {
			renderer.render(*cam, rect);
		}

		for (auto& point : points.data) {
			renderer.render(*cam, point);
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

void Engine::_processInput()
{
	if (isFPSCamera) { // THis can be enabled runtime
		auto fpsCam = static_cast<FPSCamera*>(cam.get());

		if (isKeyActioned(GLFW_KEY_W, GLFW_PRESS))
			fpsCam->moveForward();
		if (isKeyActioned(GLFW_KEY_S, GLFW_PRESS))
			fpsCam->moveBackward();
		if (isKeyActioned(GLFW_KEY_A, GLFW_PRESS))
			fpsCam->moveLeft();
		if (isKeyActioned(GLFW_KEY_D, GLFW_PRESS))
			fpsCam->moveRight();
	}

	if (isKeyActioned(GLFW_KEY_ESCAPE, GLFW_PRESS))
		window.close();

	processInput();
}

void Engine::_onMouseMove(double xpos, double ypos)
{
	if (isFPSCamera) {
		static_cast<FPSCamera*>(cam.get())->onMouseMove(xpos, ypos);
	}

	onMouseMove(xpos, ypos);
}

uint32_t Engine::loadTexture(uint32_t textureId, const std::string& pathToTexture)
{
	TextureComponent texture;
	texture.init(textureId);
	texture.load(pathToTexture);
	texture.bind();
	textures.push_back(texture);

	return textureId - GL_TEXTURE0;
}

void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos)
{
	if (engine.isFPSCamera) {
		static_cast<FPSCamera*>(engine.cam.get())->onMouseMove(xpos, ypos);
	}

	engine._onMouseMove(xpos, ypos);
}

void key_callback(Engine& engine, GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Engine::setCamera(std::unique_ptr<Camera> cam)
{
	this->cam = std::move(cam);
}

void Engine::setFPS(uint32_t frameRate)
{
	this->fps = frameRate;
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

Rect& Engine::addRect(
	const Point3D& p1,
	const Point3D& p2,
	const Point3D& p3,
	const Point3D& p4,
	const Vector3D& scale,
	int textureId,
	uint32_t textureScale,
	bool isIntersectable)
{
	return rects.add(Rect(p1, p2, p3, p4, scale, textureId, vertexIdxAwareShader, textureScale));
}

Point& Engine::addPoint(const Point3D& position, const Color& color, float size)
{
	return points.add(Point(position, color, size, pointShader));
}
