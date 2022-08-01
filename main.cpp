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

	KeyboardInput keyboardInput;
	keyboardInput.init(window);

	Triangle trngl(Point3D(0, 0.5, 0.0), Point3D(-0.5, 0.0, 0.0), Point3D(0.5, 0, 0));
	Triangle trian2(Point3D(0, 0.5, 0.0), Point3D(0.75, 0.75, 0.0), Point3D(0.5, 0, 0));

	VertexAttribute coordinateAttribute(0, 3, 3, 0);
	ObjectComponent objComponent;
	objComponent.init(std::vector<VertexAttribute>{coordinateAttribute}, 3, trian2.getComponentsCount());
	objComponent.activate();
	objComponent.addObject(trngl);
	objComponent.addObject(trian2);
	objComponent.loadBuffer();

	while (!window->shouldClose()) {
		window->clear();

		if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}

		objComponent.draw();

		window->swapBuffers();
		graphics.pollEvents();
	}

	return 0;
}