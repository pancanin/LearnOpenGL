#include <iostream>
#include <assert.h>

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

	bufferSwitch.init();
}

Object& BagOfObjects::add(const Object& o)
{
	assert(size + 1 < CAPACITY, "Cannot add more objects - bag is full.");

	if (size + 1 < CAPACITY) {
		return objs[size++] = o;
	}
	else {
		std::cout << "Cannot add more objects - bag is full. Warning! UB!" << std::endl;
		Object o;
		return o; // TODO: use a vector and ask client for capacity size, so that UB is justified - client promised to use just 100 objects
		// but used 101, for example.
	}
}

void BagOfObjects::draw(const Camera& cam)
{
	shader.use(); // TODO: Remove this after testing
	
	for (unsigned int idx = 0; idx < size; idx++) {
		const Object& current = objs[idx];
		std::shared_ptr<BufferSerialiser> bufferSerPtr = bufferSwitch.switchBuffer(current.type);
		auto model = glm::mat4(1.0f);

		// We are doing movement in the draw method...It would be good to have a separate method which we call to update the position of the object.
		model = glm::translate(model, current.position + current.velocity);
		model = glm::rotate(model, glm::radians(current.rotationAngle), current.rotationAxis); // TODO: Explore rotation with quaternions. For now we will not rotate, but a rotation angle should be set in the object.

		shader.setUniformMat4("model", model);
		shader.setUniformMat4("projection", cam.getProjection());
		shader.setUniformMat4("view", cam.getView());
		shader.setInt("dtexture", current.textureUnit);

		if (current.type == ObjectType::LINE) {
			glDrawElements(GL_LINES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawElements(GL_TRIANGLES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0);
		}
	}
}
