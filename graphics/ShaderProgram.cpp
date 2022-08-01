#include "ShaderProgram.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../glm/gtc/type_ptr.hpp"

void ShaderProgram::init()
{
	shaderProgram = glCreateProgram();
}

void ShaderProgram::attachVertexShader(const char* shaderSourceCode)
{
	attachShader(GL_VERTEX_SHADER, shaderSourceCode);
}

void ShaderProgram::attachFragmentShader(const char* shaderSourceCode)
{
	attachShader(GL_FRAGMENT_SHADER, shaderSourceCode);
}

void ShaderProgram::attachShader(unsigned int shaderType, const char* shaderSourceCode) {
	shaderTypeToShaderId[shaderType] = glCreateShader(shaderType);

	glShaderSource(shaderTypeToShaderId[shaderType], 1, &shaderSourceCode, NULL);
	glCompileShader(shaderTypeToShaderId[shaderType]);
	glAttachShader(shaderProgram, shaderTypeToShaderId[shaderType]);
}

void ShaderProgram::link()
{
	glLinkProgram(shaderProgram);

	for (auto const& pair : shaderTypeToShaderId) {
		glDeleteShader(pair.second);
	}
}

void ShaderProgram::use()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::setUniformMat4(const std::string& uniformVarName, const glm::mat4& value)
{
	int modelLoc = glGetUniformLocation(shaderProgram, uniformVarName.c_str());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(value));
}
