#include <iostream>
#include <assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BagOfObjects.h"
#include "../camera/Camera.h"
#include "../../opengl/models/Vertex.h"

void BagOfObjects::init(int bagSize)
{
	objs.reserve(bagSize);
	shader.init();
	shader.attachVertexShader("src/engine/shaders/default_vertex");
	shader.attachFragmentShader("src/engine/shaders/default_fragment");
	shader.link();
	shader.use();

	bufferSwitch.init();
}

Object& BagOfObjects::add(const Object& o)
{
	objs.push_back(o);
	return objs[objs.size() - 1];
}

void BagOfObjects::draw(const Camera& cam)
{
	shader.use();
	
	for (Object& obj : objs) {
		std::shared_ptr<BufferSerialiser> bufferSerPtr = bufferSwitch.switchBuffer(obj.type);
		auto model = glm::mat4(1.0f);

		// We are doing movement in the draw method...It would be good to have a separate method which we call to update the position of the object.
		model = glm::translate(model, obj.position + obj.velocity);
		model = glm::rotate(model, glm::radians(obj.rotationAngle), obj.rotationAxis); // TODO: Explore rotation with quaternions. For now we will not rotate, but a rotation angle should be set in the object.
		model = glm::scale(model, obj.scaleFactor);

		shader.setUniformMat4("model", model);
		shader.setUniformMat4("projection", cam.getProjection());
		shader.setUniformMat4("view", cam.getView());
		shader.setInt("dtexture", obj.textureUnit);

		glDrawElements(GL_TRIANGLES, bufferSerPtr->indicesCount(), GL_UNSIGNED_INT, 0);
	}
}

std::vector<Object>::const_iterator BagOfObjects::iter_begin() const
{
	return objs.cbegin();
}

std::vector<Object>::const_iterator BagOfObjects::iter_end() const
{
	return objs.cend();
}
