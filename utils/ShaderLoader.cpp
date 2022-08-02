#include "ShaderLoader.h"

#include <fstream>
#include <iostream>

std::string ShaderLoader::load(const std::string& shaderName)
{
	std::string shaderSource;
	std::ifstream readingStream(shaderFolder + shaderName + ".glsl");

	if (!readingStream.is_open()) {
		return "";
	}

	readingStream.seekg(0, std::ios::end);
	shaderSource.resize(readingStream.tellg());
	readingStream.seekg(0);
	readingStream.read(const_cast<char*>(shaderSource.data()), shaderSource.size());

  return shaderSource;
}
