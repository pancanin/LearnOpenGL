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
	void remove(const Line& l);
	void draw(const Camera& cam);
	std::vector<Line>::const_iterator iter_begin() const;
	std::vector<Line>::const_iterator iter_end() const;
private:
	// Actually, we are not taking most of cache locallity here, because still we have to make a jump to iterate 'lines'.
	// We can use template argument for the size and use an std::array, but I will do that only if performance suffers a lot from this code.
	std::vector<Line> lines;
	ShaderProgram shader;
	BufferConfigurer bufferConfig;
};