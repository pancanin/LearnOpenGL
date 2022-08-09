#include "Engine.h"

#include "../libs/glm/glm.hpp"

#include "../utils/TextureComponent.h"
#include "../utils/MathUtils.h"

void Engine::init(int width, int height, const std::string& label, const Color& clearScreenColor)
{
	graphics.init();
	window = std::make_shared<Window>();
	window->init(width, height, label, glm::normalize(clearScreenColor));
	window->makeActive();
	graphics.loadFunctionDefinitions();
	shaderProgram.init();
	keyboardInput.init(window);
	rectComp.init();
	rectComp.activate();
}

void Engine::start()
{
	onStart();

	while (!window->shouldClose()) {
		window->clear();

		if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}

		onUpdate();

		shaderProgram.use();
		rectComp.activate();
		rectComp.draw();

		window->swapBuffers();
		graphics.pollEvents();
	}
}

void Engine::loadTexture(int textureId, const std::string& pathToTexture) const
{
	TextureComponent texture;
	texture.init();
	texture.load(pathToTexture);
	texture.bind(GL_TEXTURE0 + (textureId * 16));
	shaderProgram.setInt(textureVarPrefix + std::to_string(textureId), textureId);
}

std::shared_ptr<Rect> Engine::createRect(Point3D origin, float width, float height)
{
	rectComp.activate();
	auto rect = rectComp.addObject(
		Rect(
			MathUtils::mapScreenToVertexCoordinates(origin, window->getWidth(), window->getHeight()),
			width / window->getWidth(),
			height / window->getHeight()
		)
	);
	rectComp.loadBuffer();

	return rect;
}
