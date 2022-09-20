#pragma once
#include <vector>

#include "../../opengl/shader/ShaderProgram.h"
#include "../models/Line.h"
#include "../../opengl/buffers/BufferConfigurer.h"
#include "../models/serialisation/LineBufferSerialiser.h"

class Camera;

class BagOfLines {
public:
	void init(int bagSize);
	Line& add(const Line& o);
	void draw(const Camera& cam);
	std::vector<Line>::const_iterator iter_begin() const;
	std::vector<Line>::const_iterator iter_end() const;
private:
	std::vector<Line> lines;
	ShaderProgram shader;
	BufferConfigurer bufferConfig;
};