#pragma once
#include <vector>

#include "../../opengl/shader/ShaderProgram.h"
#include "../models/Object.h"
#include "../../opengl/buffers/BufferConfigurer.h"
#include "../models/serialisation/TriangleBufferSerialiser.h"
#include "../models/serialisation/RectBufferSerialiser.h"
#include "../models/serialisation/CubeBufferSerialiser.h"
#include "../buffer/BufferSwitch.h"

class Camera;

/// <summary>
/// This class does too many things...My argument is that that is a sacrifice for having data-driven design - we want to move data around as little as possible.
/// The draw calls could be abstracted away, but it will make things harder to understand as we have to export the vertex count from here.
/// Stores objects sequentially, applies uniforms to the shader program and performs draw calls.
/// </summary>
class BagOfObjects {
public:
	void init(int bagSize);
	Object& add(const Object& o);
	void draw(const Camera& cam); // TODO: Revisit const-correctness on every class
	std::vector<Object>::const_iterator iter_begin() const;
	std::vector<Object>::const_iterator iter_end() const;
private:
	std::vector<Object> objs;
	unsigned int size = 0;
	ShaderProgram shader;
	BufferSwitch bufferSwitch;
};