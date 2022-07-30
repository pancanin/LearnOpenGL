#include "Graphics.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Graphics::init() const
{
	glfwInit();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
}

void Graphics::pollEvents() const
{
	glfwPollEvents();
}

Graphics::~Graphics()
{
	glfwTerminate();
}
