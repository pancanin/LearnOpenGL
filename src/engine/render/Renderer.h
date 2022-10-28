#pragma once

#include <memory>

#include "../buffer/BufferSwitch.h"
#include "../camera/Camera.h"

struct Object;
struct Line;
struct Triangle;
struct ShaderProgram;

class Renderer {
public:
	void init();
	void render(const Camera&, const Object&);
	void render(const Camera&, const Line&);
	void render(const Camera&, const Triangle&);
private:
	BufferSwitch bufferSwitch;
	std::shared_ptr<ShaderProgram> lineShaderProgramPtr;
};