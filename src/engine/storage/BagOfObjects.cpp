#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BagOfObjects.h"
#include "../camera/Camera.h"
#include "../../opengl/models/Vertex.h"

void BagOfObjects::init()
{
	shader.init();
	shader.attachVertexShader("src/engine/shaders/default_vertex");
	shader.attachFragmentShader("src/engine/shaders/default_fragment");
	shader.link();
	shader.use();

	std::vector<VertexAttribute> attributes = {
		VertexAttribute{ 0, sizeof(Vertex::position) / sizeof(float), sizeof(Vertex) / sizeof(float), 0 },
		VertexAttribute{ 1, sizeof(Vertex::normal) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::normal) / sizeof(float) },
		VertexAttribute{ 2, sizeof(Vertex::textureCoords) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::textureCoords) / sizeof(float) }
	};

	triangleSerialiserPtr = std::make_shared<TriangleBufferSerialiser>();
	
	triangleBufferConfig.init(attributes, triangleSerialiserPtr);
	triangleBufferConfig.activate();
	triangleBufferConfig.loadBuffer();

	rectSerialiserPtr = std::make_shared<RectBufferSerialiser>();

	rectBufferConfig.init(attributes, rectSerialiserPtr);
	rectBufferConfig.activate();
	rectBufferConfig.loadBuffer();
}

void BagOfObjects::add(const Object& o)
{
	if (size + 1 < CAPACITY) {
		objs[size++] = o;
	}
	else {
		std::cout << "Cannot add more objects - bag is full." << std::endl;
	}
}

void BagOfObjects::draw(const Camera& cam)
{
	shader.use(); // TODO: Remove this after testing
	
	for (unsigned int idx = 0; idx < size; idx++) {
		const Object& current = objs[idx];

		std::shared_ptr<BufferSerialiser> bufferSerPtr;

		switch (current.type) {
		case ObjectType::TRIANGLE:
			triangleBufferConfig.activate();
			bufferSerPtr = triangleSerialiserPtr;
			break;
		case ObjectType::RECT:
			rectBufferConfig.activate();
			bufferSerPtr = rectSerialiserPtr;
			break;
		default:
			std::cout << "Invalid object type" << std::endl; break;
		}

		auto model = glm::mat4(1.0f);

		// We are doing movement in the draw method...It would be good to have a separate method which we call to update the position of the object.
		model = glm::translate(model, current.position + current.velocity);
		model = glm::rotate(model, glm::radians(0.0f), current.rotation); // TODO: Explore rotation with quaternions. For now we will not rotate, but a rotation angle should be set in the object.

		shader.setUniformMat4("model", model);
		shader.setUniformMat4("projection", cam.getProjection());
		shader.setUniformMat4("view", cam.getView());
		shader.setInt("dtexture", current.textureUnit);

		glDrawElements(GL_TRIANGLES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0); // TODO: This should be taken from a map of <ObjectType, VerticeCount>
	}
}
