#include "Window.h"

#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool Window::init(int width, int height, const std::string& label)
{
	this->width = width;
	this->height = height;

	window = glfwCreateWindow(width, height, label.c_str(), NULL, NULL);
	
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return window == nullptr;
}

void Window::makeActive() const
{
	glfwMakeContextCurrent(window);
}

void Window::clear() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::close() const
{
	glfwSetWindowShouldClose(window, true);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* Window::getRaw() const 
{
	return window;
}

void Window::deinit() const
{
	if (window != nullptr) {
		glfwDestroyWindow(window);
	}
}

Window::~Window()
{
	deinit();
}
