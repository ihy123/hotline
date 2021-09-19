#include "Texture.h"
#include "Log.h"
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
}

Texture::~Texture() noexcept {
	if (m_Id) glDeleteTextures(1, &m_Id);
	m_Id = 0;
}
