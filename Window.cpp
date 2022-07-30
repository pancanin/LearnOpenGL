#include "Window.h"

#include <GLFW/glfw3.h>

bool Window::init(int width, int height, const std::string& label) {
	window = glfwCreateWindow(width, height, label.c_str(), NULL, NULL);
	glViewport(0, 0, width, height);
	this->width = width;
	this->height = height;

	return window == nullptr;
}

void Window::makeActive() {
	glfwMakeContextCurrent(window);
}

void Window::close()
{
	glfwSetWindowShouldClose(window, true);
}

const GLFWwindow* Window::getRaw() {
	return window;
}

void Window::deinit()
{
	if (window != nullptr) {
		glfwDestroyWindow(window);
	}
}

Window::~Window()
{
	deinit();
}
