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
}

void Engine::start()
{
	onStart();

	while (!window->shouldClose()) {
		window->clear();

		/*if (keyboardInput.isKeyPressed(GLFW_KEY_ESCAPE)) {
			window->close();
		}*/

		onUpdate();

		
		for (auto texturePtr : textures) {
			texturePtr->bind();
		}

		shaderProgram.use();
		//rectComp.activate();
		//rectComp.draw();
		//trectComp.activate();
		//trectComp.draw();

		window->swapBuffers();
		graphics.pollEvents();
	}
}

void Engine::loadTexture(int textureId, const std::string& pathToTexture)
{
	auto texture = std::make_shared<TextureComponent>();
	//texture->init(GL_TEXTURE0 + textureId);
	texture->load(pathToTexture);
	shaderProgram.use();
	shaderProgram.setInt(textureVarPrefix + std::to_string(textureId), textureId);
	textures.push_back(texture);
}

//std::shared_ptr<Rect> Engine::createRect(Point3D origin, float width, float height)
//{
//	rectComp.activate();
//	auto rect = rectComp.addObject(
//		Rect(
//			MathUtils::mapScreenToVertexCoordinates(origin, window->getWidth(), window->getHeight()),
//			(width * 2) / window->getWidth(),
//			(height * 2) / window->getHeight()
//		)
//	);
//	rectComp.loadBuffer();
//
//	return rect;
//}

//std::shared_ptr<TexturedRect> Engine::createRect(Point3D origin, float width, float height, unsigned int textureId)
//{
//	trectComp.activate();
//	auto rect = trectComp.addObject(
//		TexturedRect(
//			MathUtils::mapScreenToVertexCoordinates(origin, window->getWidth(), window->getHeight()),
//			(width * 2) / window->getWidth(),
//			(height * 2) / window->getHeight(),
//			textureId
//		)
//	);
//
//	return rect;
//}
