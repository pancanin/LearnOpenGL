#include "Graphics.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Graphics::init() const
{
	int initResult = glfwInit();
	glfwSwapInterval(1); // V-Sync

	return initResult;
}

bool Graphics::loadFunctionDefinitions() const
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Graphics::pollEvents() const
{
	glfwPollEvents();
}

void Graphics::configure() const
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Graphics::~Graphics()
{
	glfwTerminate();
}
