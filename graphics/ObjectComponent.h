#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../models/Triangle.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

class ObjectComponent
{
public:
	void init(
		std::shared_ptr<VertexArrayObject> vertexArrayObjectPtr,
		unsigned int verticesPerObject,
		unsigned int componentsPerObject
		) {
		this->vao = vertexArrayObjectPtr;
		this->verticesPerObject = verticesPerObject;
		this->componentsPerObject = componentsPerObject;
		this->buffer = nullptr;
		this->vbo.init(GL_ARRAY_BUFFER);
	}

	void activate() {
		this->vao->bind();
		this->vbo.bind();
	}

	void loadBuffer() {
		clearBuffer();
		unsigned int totalComponentsCount = componentsPerObject * objects.size();
		buffer = new float[totalComponentsCount];

		int offset = 0;

		for (size_t idx = 0; idx < objects.size(); idx++) {
			auto objPtr = objects[idx];
			float* components = objPtr->toVertexArray();

			std::memcpy(buffer + offset, components, componentsPerObject * sizeof(float));
			offset += componentsPerObject;
		}

		vbo.fillBuffer(buffer, totalComponentsCount);
	}

	void draw() {
		// GL_TRIANGLES - hardcoded...fix
		glDrawArrays(GL_TRIANGLES, 0, verticesPerObject * objects.size());
	}

	void deactivate() {
		this->vbo.unbind();
		clearBuffer();
	}

	void clearBuffer() {
		if (buffer != nullptr) {
			delete[] buffer;
		}
	}

	std::shared_ptr<Triangle> addObject(Triangle o) {
		auto objPtr = std::make_shared<Triangle>(o);
		objects.push_back(objPtr);
		return objPtr;
	}

	~ObjectComponent() {
		deactivate();
	}
private:
	std::vector<std::shared_ptr<Triangle>> objects;
	std::shared_ptr<VertexArrayObject> vao;
	VertexBufferObject vbo;
	unsigned int verticesPerObject;
	unsigned int componentsPerObject;
	float* buffer;
};

