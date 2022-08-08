#pragma once

#include <string>
#include <memory>

#include "../models/TypeDefs.h"

struct GLFWwindow;

class Window
{
public:
	~Window();

	bool init(int width, int height, const std::string& label, const Color& clearScreenColor = Color(0.2f, 0.3f, 0.3f, 1.0f));
	void makeActive() const;
	void clear() const;
	void close() const;
	bool shouldClose() const;
	void swapBuffers() const;
	GLFWwindow* getRaw() const;
	void deinit() const;

	int getWidth() const { return width; }
	int getHeight() const { return height; }
private:
	GLFWwindow* window;
	Color clearScreenColor;
	int width;
	int height;
	std::string label;
};
