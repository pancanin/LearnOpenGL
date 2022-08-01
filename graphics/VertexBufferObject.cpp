#include "VertexBufferObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void VertexBufferObject::init()
{
	glGenBuffers(1, &id);
}

void VertexBufferObject::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferObject::fillBuffer(float* data, int size)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &id);
}
