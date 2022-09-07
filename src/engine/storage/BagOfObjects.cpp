#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BagOfObjects.h"
#include "../camera/Camera.h"
#include "../../opengl/models/Vertex.h"
#include "../models/serialisation/TriangleBufferSerialiser.h"

void BagOfObjects::init()
{
	shader.init();
	shader.attachVertexShader("src/engine/shaders/default_vertex");
	shader.attachFragmentShader("src/engine/shaders/default_fragment");
	shader.link();
	shader.use();

	std::vector<VertexAttribute> triangleAtris = {
		VertexAttribute{ 0, sizeof(Vertex::position) / sizeof(float), sizeof(Vertex) / sizeof(float), 0 },
		VertexAttribute{ 1, sizeof(Vertex::normal) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::normal) / sizeof(float) },
		VertexAttribute{ 2, sizeof(Vertex::textureCoords) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::textureCoords) / sizeof(float) }
	};

	auto serialiserPtr = std::make_shared<TriangleBufferSerialiser>();
	
	triangleBufferConfig.init(triangleAtris, serialiserPtr);
	triangleBufferConfig.activate();
	triangleBufferConfig.loadBuffer();
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
	// Maybe this draw method will be on the object itself, because triangles are drawn differently...but we can also draw triangles with element buffer objects... :)
	// Calculate vertice count and call opengl draw

	shader.use(); // TODO: Remove this after testing
	triangleBufferConfig.activate();
	
	for (unsigned int idx = 0; idx < size; idx++) {
		const Object& current = objs[idx];
		triangleBufferConfig.activate();

		auto model = glm::mat4(1.0f);

		// We are doing movement in the draw method...It would be good to have a separate method which we call to update the position of the object.
		model = glm::translate(model, current.position + current.velocity);
		model = glm::rotate(model, glm::radians(0.0f), current.rotation); // TODO: Explore rotation with quaternions. For now we will not rotate, but a rotation angle should be set in the object.

		shader.setUniformMat4("model", model);
		shader.setUniformMat4("projection", cam.getProjection());
		shader.setUniformMat4("view", cam.getView());
		glDrawArrays(GL_TRIANGLES, 0, 3); // TODO: This should be taken from a map of <ObjectType, VerticeCount>
	}
}
