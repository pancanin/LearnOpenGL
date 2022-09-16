#include <iostream>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BagOfLines.h"
#include "../camera/Camera.h"
#include "../../opengl/models/LineVertex.h"

void BagOfLines::init()
{
	shader.init();
	shader.attachVertexShader("src/engine/shaders/default_vertex");
	shader.attachFragmentShader("src/engine/shaders/default_fragment");
	shader.link();
	shader.use();

	auto lineSerPtr = std::make_shared<LineBufferSerialiser>();

	std::vector<VertexAttribute> attributes = {
		VertexAttribute{ 0, sizeof(LineVertex::position) / sizeof(float), sizeof(LineVertex) / sizeof(float), 0 },
		VertexAttribute{ 1, sizeof(LineVertex::color) / sizeof(float), sizeof(LineVertex) / sizeof(float), offsetof(LineVertex, LineVertex::color) / sizeof(float) },
	};

	bufferConfig.init(attributes, lineSerPtr);
	bufferConfig.activate();
	bufferConfig.BufferConfigurer::loadBuffer();
}

Line& BagOfLines::add(const Line& o)
{
	assert(size + 1 < CAPACITY, "Cannot add more objects - bag is full.");

	if (size + 1 < CAPACITY) {
		return objs[size++] = o;
	}
	else {
		std::cout << "Cannot add more objects - bag is full. Warning! UB!" << std::endl;
		Line l;
		return l; // TODO: use a vector and ask client for capacity size, so that UB is justified - client promised to use just 100 objects
		// but used 101, for example.
	}
}

void BagOfLines::draw(const Camera& cam)
{
	shader.use(); // TODO: Remove this after testing

	for (unsigned int idx = 0; idx < size; idx++) {
		const Line& current = objs[idx];
		auto model = glm::mat4(1.0f);

		shader.setUniformMat4("model", model);
		shader.setUniformMat4("projection", cam.getProjection());
		shader.setUniformMat4("view", cam.getView());

		bufferConfig.activate();
		bufferConfig.loadBuffer(current.start, current.end);
		// TODO: In order for the line to show we have to create a new shader

		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	}
}
