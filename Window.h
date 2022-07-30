#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

class Window
{
public:
	~Window();

	int init(int width, int height, const std::string& label);
	void assignAsMain();
	void close();
	GLFWwindow* getRaw();
	void deinit();

	int getWidth() const { return width; }
	int getHeight() const { return height; }
private:
	GLFWwindow* window;
	int width;
	int height;
	std::string label;
};
