#pragma once
#include <array>

#include "../../opengl/shader/ShaderProgram.h"
#include "../models/Object.h"
#include "../../opengl/buffers/BufferConfigurer.h"
#include "../models/serialisation/TriangleBufferSerialiser.h"
#include "../models/serialisation/RectBufferSerialiser.h"

class Camera;

/// <summary>
/// This class does too many things...My argument is that that is a sacrifice for having data-driven design - we want to move data around as little as possible.
/// The draw calls could be abstracted away, but it will make things harder to understand as we have to export the vertex count from here.
/// Stores objects sequentially, applies uniforms to the shader program and performs draw calls.
/// </summary>
class BagOfObjects {
public:
	void init();
	void add(const Object& o);
	void draw(const Camera& cam); // TODO: Revisit const-correctness on every class
private:
	const static unsigned int CAPACITY = 100; // The size could come as template argument, so it is known at compile time, but I am not that versed in templates and they are pain to debug and visual studio does not highlight code when using templates.
	std::array<Object, CAPACITY> objs;
	unsigned int size = 0;
	ShaderProgram shader; // We will use one shader for all our purposes, but in a real game engine this would be passed from the client. Another option is to have a shader per object.
	BufferConfigurer triangleBufferConfig;
	BufferConfigurer rectBufferConfig;
	std::shared_ptr<TriangleBufferSerialiser> triangleSerialiserPtr;
	std::shared_ptr<RectBufferSerialiser> rectSerialiserPtr;
};