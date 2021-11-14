#include "Texture.h"
#include <Log.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* file_path) {
	glGenTextures(1, &m_Id);
	Bind();

	stbi_set_flip_vertically_on_load(1);
	auto image = stbi_load(file_path, &m_Width, &m_Height, nullptr, STBI_rgb_alpha);
	if (image == nullptr) {
		LOG_ERROR("Failed to load texture image: %s", file_path);
		return;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
}

Texture::~Texture() noexcept {
	if (m_Id != 0)
		glDeleteTextures(1, &m_Id);
	m_Id = 0;
}

Texture::Texture(Texture&& other)
	: m_Id(other.m_Id),
	  m_Width(other.m_Width),
	  m_Height(other.m_Height) {
	other.m_Id = 0;
}

Texture& Texture::operator=(Texture&& other) {
	m_Id = other.m_Id;
	m_Width = other.m_Width;
	m_Height = other.m_Height;
	other.m_Id = 0;
	return *this;
}
