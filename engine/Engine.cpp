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

	rectSerialisationPtr = std::make_shared<RectBufferSerialiser>();

	rectComp.init(rectAttributeConfigurer, rectSerialisationPtr);
	rectComp.activate();

	trectSerialisationPtr = std::make_shared<TexturedRectBufferSerialiser>();
	trectComp.init(trectAttributeStrategy, trectSerialisationPtr);
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
		trectComp.activate();
		trectComp.draw();

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
	std::string s = textureVarPrefix + std::to_string(textureId);
	shaderProgram.setInt(textureVarPrefix + std::to_string(textureId), textureId);
}

std::shared_ptr<Rect> Engine::createRect(Point3D origin, float width, float height)
{
	rectComp.activate();
	auto rect = rectComp.addObject(
		Rect(
			MathUtils::mapScreenToVertexCoordinates(origin, window->getWidth(), window->getHeight()),
			(width * 2) / window->getWidth(),
			(height * 2) / window->getHeight()
		)
	);
	rectComp.loadBuffer();

	return rect;
}

std::shared_ptr<TexturedRect> Engine::createRect(Point3D origin, float width, float height, unsigned int textureId)
{
	trectComp.activate();
	auto rect = trectComp.addObject(
		TexturedRect(
			MathUtils::mapScreenToVertexCoordinates(origin, window->getWidth(), window->getHeight()),
			(width * 2) / window->getWidth(),
			(height * 2) / window->getHeight(),
			0
		)
	);
	trectComp.loadBuffer();

	return rect;
}
