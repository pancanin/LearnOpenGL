#pragma once

#include <string>
#include <unordered_map>

#include "../glm/glm.hpp"

/*
* A shader program is a configuration of vertex, fragment and optionally geometry shader.
* We can load the shaders into the program and link them.
* Later when we need to use the shaders we call use().
*/
class ShaderProgram
{
public:
	void init();
	void attachVertexShader(const char* shaderSourceCode);
	void attachFragmentShader(const char* shaderSourceCode);
	void link();
	void use();
	void setUniformMat4(const std::string& uniformVarName, const glm::mat4& value);
	void setUniformVec4(const std::string& uniformVarName, const glm::vec4& value);
private:
	unsigned int shaderProgram;
	std::unordered_map<unsigned int, unsigned int> shaderTypeToShaderId;

	void attachShader(unsigned int shaderType, const char* shaderSourceCode);
	int findLocation(const std::string& uniformVarName);
};

