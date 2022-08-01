#include "VertexArrayObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void VertexArrayObject::init()
{
	glGenVertexArrays(1, &id);
}

void VertexArrayObject::bind()
{
	glBindVertexArray(id);
}

void VertexArrayObject::addAttribute(unsigned int id, unsigned int size, unsigned int stride, unsigned int offset) const
{
	glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(id);
}
