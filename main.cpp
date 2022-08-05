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

#include "models/TexturedTriangle.h"

#include "utils/TextureComponent.h"
#include "graphics/RectComponent.h"

const int width = 800;
const int height = 600;

int main() {
	Graphics graphics;
	graphics.init();

	std::shared_ptr<Window> window = std::make_shared<Window>();
	window->init(width, height, "Hiii, openGL!");
	window->makeActive();

	graphics.loadFunctionDefinitions();

	ShaderProgram shaderProgram;
	shaderProgram.init();

	shaderProgram.attachVertexShader("texture_vertex");
	shaderProgram.attachFragmentShader("texture_fragment");
	shaderProgram.link();
	shaderProgram.use();

	TextureComponent texture;
	texture.init();
	texture.load("assets/container.jpg");
	texture.bind(GL_TEXTURE0);
	shaderProgram.setInt("texture1", 0);

	TextureComponent myFaceTexture;
	myFaceTexture.init();
	myFaceTexture.load("assets/face.png");
	myFaceTexture.bind(GL_TEXTURE1);
	shaderProgram.setInt("texture2", 1);

	KeyboardInput keyboardInput;
	keyboardInput.init(window);

	Rect rect(
		Point3D(-0.25f, 0.25f, 0.0f),
		0.5, 0.5
	);
	RectComponent rectComp;
	rectComp.init();
	rectComp.activate();
	rectComp.addObject(rect);
	rectComp.loadBuffer();

	while (!window->shouldClose()) {
		window->clear();

		if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}

		shaderProgram.use();
		rectComp.activate();
		rectComp.draw();

		window->swapBuffers();
		graphics.pollEvents();
	}

	return 0;
}