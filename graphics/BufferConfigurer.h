#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "../models/VertexAttribute.h"
#include "../serialisation/BufferSerialiser.h"

/* Sets up buffers for shapes/objects */
class BufferConfigurer
{
public:
	void init(
		std::vector<VertexAttribute> attributes,
		std::shared_ptr<BufferSerialiser> serialisation
	);

	void activate();

	void loadBuffer();

	void deactivate();

	~BufferConfigurer();
private:
	VertexArrayObject vao;
	VertexBufferObject vbo;
	std::shared_ptr<BufferSerialiser> serialisation;
};
