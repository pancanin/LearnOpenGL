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

template <typename T>
class ObjectComponent
{
public:
	virtual void init(
		std::vector<VertexAttribute> attributes,
		unsigned int verticesPerObject,
		unsigned int componentsPerObject,
		std::shared_ptr<BufferSerialiser<T>> serialisation
		) {
		this->verticesPerObject = verticesPerObject;
		this->componentsPerObject = componentsPerObject;
		this->serialisation = serialisation;
		this->vbo.init(GL_ARRAY_BUFFER);
		this->vao.init();
		
		activate();

		for (auto& attr : attributes) {
			this->vao.addAttribute(attr);
		}
	}

	virtual void activate() {
		this->vao.bind();
		this->vbo.bind();
	}

	virtual void loadBuffer() {
		unsigned int totalComponentsCount = componentsPerObject * objects.size();
		float* buffer = new float[totalComponentsCount];

		int offset = 0;

		for (size_t idx = 0; idx < objects.size(); idx++) {
			auto objPtr = objects[idx];
			float* components = serialisation->serialise(*objPtr);

			std::memcpy(buffer + offset, components, componentsPerObject * sizeof(float));
			offset += componentsPerObject;
			delete[] components;
		}

		vbo.fillBuffer(buffer, totalComponentsCount);
		delete[] buffer;
	}

	virtual void draw() {
		// GL_Triangles - hardcoded...fix
		glDrawArrays(GL_TRIANGLES, 0, verticesPerObject * objects.size());
	}

	virtual void deactivate() {
		this->vbo.unbind();
	}

	std::shared_ptr<T> addObject(T o) {
		auto objPtr = std::make_shared<T>(o);
		objects.push_back(objPtr);
		return objPtr;
	}

	virtual ~ObjectComponent() {
		deactivate();
	}
private:
	std::vector<std::shared_ptr<T>> objects;
	VertexArrayObject vao;
	VertexBufferObject vbo;
	unsigned int verticesPerObject;
	unsigned int componentsPerObject;
	std::shared_ptr<BufferSerialiser<T>> serialisation;
};
