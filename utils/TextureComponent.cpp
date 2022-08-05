#include "TextureComponent.h"

#include "../libs/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void TextureComponent::init()
{
	glGenTextures(1, &id);
	stbi_set_flip_vertically_on_load(true);
}

void TextureComponent::load(const std::string& file)
{
	data = stbi_load(file.c_str(), &width, &height, &nChannels, 0);
	hasAlpha = file.find(".png") != std::string::npos;
}

void TextureComponent::bind(int activeTexture)
{
	if (data == nullptr) return;
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	data = nullptr;
}

TextureComponent::~TextureComponent()
{
	if (data != nullptr) {
		stbi_image_free(data);
		data = nullptr;
	}
}
