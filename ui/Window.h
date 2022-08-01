#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

class Window
{
public:
	~Window();

	bool init(int width, int height, const std::string& label);
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
	int width;
	int height;
	std::string label;
};
