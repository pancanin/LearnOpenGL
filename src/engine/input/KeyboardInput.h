#pragma once

#include <memory>

#include "../ui/Window.h"

class KeyboardInput
{
public:
	void init(std::shared_ptr<Window> window);
	bool isKeyPressed(int keyId) const;

private:
	std::shared_ptr<Window> window;
};
