#ifndef ENGINE_MODELS_DRAWING_DATA
#define ENGINE_MODELS_DRAWING_DATA

#include <memory>
#include <cstdint>

#include "../../opengl/shader/ShaderProgram.h"

struct DrawingData {
	DrawingData(uint32_t textureId, std::shared_ptr<ShaderProgram> shaderProgramPtr, uint32_t textureScale) :
		textureId(textureId), shaderProgramPtr(shaderProgramPtr), textureScale(textureScale) {}
	DrawingData() = default;

	std::shared_ptr<ShaderProgram> shaderProgramPtr;
	uint32_t textureId;
	uint32_t textureScale;
};

#endif // !ENGINE_MODELS_DRAWING_DATA
