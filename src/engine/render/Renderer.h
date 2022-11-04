#pragma once

#include <memory>

#include "../buffer/BufferSwitch.h"
#include "../camera/Camera.h"

struct Object;
struct Line;
struct Triangle;
struct Rect;
struct ShaderProgram;

class Renderer {
public:
	void init();

	// TODO: Maybe these methods have to be inline. Let's see if there are performance problems first.
	void render(const Camera&, const Object&);
	void render(const Camera&, const Line&);
	void render(const Camera&, const Triangle&);
	void render(const Camera&, const Rect&);
private:
	BufferSwitch bufferSwitch;
	std::shared_ptr<ShaderProgram> lineShaderProgramPtr;
};