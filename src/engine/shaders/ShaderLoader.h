#pragma once

#include <string>

class ShaderLoader
{
public:
	std::string load(const std::string& shaderName);
private:
	std::string shaderFolder = "shaders/";
};
