#include "Graphics.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Graphics::init() const
{
	return glfwInit();
}

bool Graphics::loadFunctionDefinitions() const
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Graphics::pollEvents() const
{
	glfwPollEvents();
}

Graphics::~Graphics()
{
	glfwTerminate();
}
