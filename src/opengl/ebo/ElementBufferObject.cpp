#include "ElementBufferObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void ElementBufferObject::init()
{
	glGenBuffers(1, &id);
}

void ElementBufferObject::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBufferObject::fillBuffer(void* data, int size)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
