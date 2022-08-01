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
#include "../models/VertexAttribute.h"

class ObjectComponent
{
public:
	void init(
		std::vector<VertexAttribute> attributes,
		unsigned int verticesPerObject,
		unsigned int componentsPerObject
		) {
		this->verticesPerObject = verticesPerObject;
		this->componentsPerObject = componentsPerObject;
		this->vbo.init(GL_ARRAY_BUFFER);
		this->vao.init();
		
		activate();

		for (auto& attr : attributes) {
			this->vao.addAttribute(attr);
		}
	}

	void activate() {
		this->vao.bind();
		this->vbo.bind();
	}

	void loadBuffer() {
		unsigned int totalComponentsCount = componentsPerObject * objects.size();
		float* buffer = new float[totalComponentsCount];

		int offset = 0;

		for (size_t idx = 0; idx < objects.size(); idx++) {
			auto objPtr = objects[idx];
			float* components = objPtr->toVertexArray();

			std::memcpy(buffer + offset, components, componentsPerObject * sizeof(float));
			offset += componentsPerObject;
			delete[] components;
		}

		vbo.fillBuffer(buffer, totalComponentsCount);
		delete[] buffer;
	}

	void draw() {
		// GL_TRIANGLES - hardcoded...fix
		glDrawArrays(GL_TRIANGLES, 0, verticesPerObject * objects.size());
	}

	void deactivate() {
		this->vbo.unbind();
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
	VertexArrayObject vao;
	VertexBufferObject vbo;
	unsigned int verticesPerObject;
	unsigned int componentsPerObject;
};

