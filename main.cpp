#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>

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

	unsigned int size = 0;
	Triangle trngl(Point3D(0, 0.5, 0.0), Point3D(-0.5, 0.0, 0.0), Point3D(0.5, 0, 0));
	auto trgPtr = std::make_shared<Triangle>(trngl);
	float* trnglData = trngl.toVertexArray(size);

	Triangle trian2(Point3D(0, 0.5, 0.0), Point3D(0.75, 0.75, 0.0), Point3D(0.5, 0, 0));
	auto trian2Ptr = std::make_shared<Triangle>(trian2);
	float* trian2Data = trian2Ptr->toVertexArray(size);
	
	float* together = new float[size * 2];
	std::memcpy(together, trnglData, size * sizeof(float));
	std::memcpy(together + size, trian2Data, size * sizeof(float));

	/*unsigned int rectVertSize = 0;
	Rect rectec(Point3D(-0.25, 0.5, 0), 0.10, 0.10);
	auto rectPtr = std::make_shared<Rect>(rectec);
	float* rectData = rectPtr->toVertexArray(rectVertSize);
	unsigned int indices[] = {
				0, 1, 3,
				1, 2, 3
	};*/

	VertexBufferObject bufferObject;
	bufferObject.init(GL_ARRAY_BUFFER);
	bufferObject.bind();
	bufferObject.fillBuffer(together, size * 2);

	VertexArrayObject coordinatesAttrVAO;
	coordinatesAttrVAO.init();
	coordinatesAttrVAO.bind();
	coordinatesAttrVAO.addAttribute(0, 3, 3, 0);
	
	while (!window->shouldClose()) {
		window->clear();

		if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}

		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window->swapBuffers();
		graphics.pollEvents();
	}

	return 0;
}