#pragma once
#include <array>

#include "../../opengl/shader/ShaderProgram.h"
#include "../models/Line.h"
#include "../../opengl/buffers/LineBufferConfigurer.h"
#include "../models/serialisation/LineBufferSerialiser.h"

class Camera;

class BagOfLines {
public:
	void init();
	Line& add(const Line& o);
	void draw(const Camera& cam); // TODO: Revisit const-correctness on every class
private:
	const static unsigned int CAPACITY = 100; // The size could come as template argument, so it is known at compile time, but I am not that versed in templates and they are pain to debug and visual studio does not highlight code when using templates.
	std::array<Line, CAPACITY> objs;
	unsigned int size = 0;
	ShaderProgram shader; // We will use one shader for all our purposes, but in a real game engine this would be passed from the client. Another option is to have a shader per object.
	LineBufferConfigurer bufferConfig;
};