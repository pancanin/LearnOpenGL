#include <iostream>

#include "MouseInput.h"

#include "../ui/Window.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void MouseInput::init(
	Window& window,
	std::function<void(double, double)> handler,
	std::function<void(int, int)> buttonClickHandler
	// Add the key handler in the mouse input for now...it's not great but maybe this class should handle
	// more things than just mouse...
	)
{
	MouseInput::handler = handler;
	MouseInput::buttonClickHandler = buttonClickHandler;
	window.registerCursorPositionCallback(mouse_callback);
	window.registerMouseButtonCallback(mouse_button_callback);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	MouseInput::handler(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	MouseInput::buttonClickHandler(button, action);
}

std::function<void(double, double)> MouseInput::handler;
std::function<void(int, int)> MouseInput::buttonClickHandler;