#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ui/Window.h"
#include "graphics/Graphics.h"
#include "input/KeyboardInput.h"

#include "utils/ShaderLoader.h"
#include "graphics/ShaderProgram.h"

#include "graphics/VertexArrayObject.h"
#include "graphics/VertexBufferObject.h"

#include "models/TypeDefs.h"
#include "models/Triangle.h"
#include "models/Rect.h"
#include "models/ColorTriangle.h"
#include "models/Vertex.h"

#include "graphics/ObjectComponent.h"
#include "models/VertexAttribute.h"

const int width = 800;
const int height = 600;

int main() {
	Graphics graphics;
	graphics.init();

	std::shared_ptr<Window> window = std::make_shared<Window>();
	window->init(width, height, "Hiii, openGL!");
	window->makeActive();

	graphics.loadFunctionDefinitions();

	ShaderLoader loader;

	std::string vertexShaderSource = loader.load("simple_vertex");
	std::string fragmentShaderSource = loader.load("simple_fragment");

	ShaderProgram shaderProgram;
	shaderProgram.init();

	shaderProgram.attachVertexShader(vertexShaderSource.data());
	shaderProgram.attachFragmentShader(fragmentShaderSource.data());
	shaderProgram.link();
	shaderProgram.use();

	std::string colorVertexShader = loader.load("color_vertex");
	std::string fragmentShaderSource2 = loader.load("fragment_2");
	ShaderProgram shaderProgram2;
	shaderProgram2.init();

	shaderProgram2.attachVertexShader(colorVertexShader.data());
	shaderProgram2.attachFragmentShader(fragmentShaderSource2.data());
	shaderProgram2.link();

	KeyboardInput keyboardInput;
	keyboardInput.init(window);

	Triangle trngl(Point3D(0, 0.5, 0.0), Point3D(-0.5, 0.0, 0.0), Point3D(0.5, 0, 0));
	

	VertexAttribute coordinateAttribute(0, 3, 3, 0);
	ObjectComponent<Triangle> objComponent;
	objComponent.init(std::vector<VertexAttribute>{coordinateAttribute}, 3, trngl.getComponentsCount());
	objComponent.activate();
	objComponent.addObject(trngl);
	objComponent.loadBuffer();

	ColorTriangle clrTr(
		Vertex(Point3D(0, 0.5, 0.0), Color(1.0f, 0.0f, 0.0f, 1.0f)),
		Vertex(Point3D(0.75, 0.75, 0.0), Color(0.0f, 1.0f, 0.0f, 1.0f)),
		Vertex(Point3D(0.5, 0, 0), Color(0.0f, 0.0f, 1.0f, 1.0f))
	);

	unsigned int stride = 7; // 3 for coordinates and 4 for color
	VertexAttribute coordinateAttributeForColorTriangle(0, 3, stride, 0);
	VertexAttribute colorAttribute(1, 4, stride, 3);
	ObjectComponent<ColorTriangle> objComponent2;
	objComponent2.init(std::vector<VertexAttribute>{coordinateAttributeForColorTriangle, colorAttribute}, 3, clrTr.getComponentsCount());
	objComponent2.activate();
	objComponent2.addObject(clrTr);
	objComponent2.loadBuffer();

	while (!window->shouldClose()) {
		window->clear();

		if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}

		auto time = glfwGetTime();
		float green = (sin(time) / 2.0f) + 0.75f;

		std::cout << green << std::endl;

		shaderProgram.use();
		shaderProgram.setUniformF("offset", 0.5);
		objComponent.activate();
		objComponent.draw();
		shaderProgram2.use();
		objComponent2.activate();
		objComponent2.draw();

		window->swapBuffers();
		graphics.pollEvents();
	}

	return 0;
}