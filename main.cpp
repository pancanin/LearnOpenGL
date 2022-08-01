#include <iostream>
#include <memory>

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

	int size = 0;
	Triangle trngl(Point3D(0, 0.5, 0.0), Point3D(-0.5, 0.0, 0.0), Point3D(0.5, 0, 0));
	float* trnglData = trngl.toVertexArray(size);

	VertexBufferObject bufferObject;
	VertexArrayObject coordinatesAttrVAO;

	coordinatesAttrVAO.init();
	bufferObject.init();
	
	coordinatesAttrVAO.bind();
	bufferObject.bind();
	
	bufferObject.fillBuffer(trnglData, size);
	coordinatesAttrVAO.addAttribute(0, 3, 3, 0);
	
	
	while (!window->shouldClose()) {
		window->clear();

		if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}

		glDrawArrays(GL_TRIANGLES, 0, 3);

		window->swapBuffers();
		graphics.pollEvents();
	}

	return 0;
}