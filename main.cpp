#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ui/Window.h"
#include "graphics/Graphics.h"
#include "input/KeyboardInput.h"

#include "utils/ShaderLoader.h"
#include "graphics/ShaderProgram.h"

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
	
	while (!window->shouldClose()) {
		window->clear();

		if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}

		window->swapBuffers();
		graphics.pollEvents();
	}

	return 0;
}