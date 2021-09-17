#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* file_path) {
	stbi_set_flip_vertically_on_load(1);
	auto image = stbi_load(file_path, &m_Width, &m_Height, nullptr, STBI_rgb_alpha);

	glGenTextures(1, &m_Id);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);
}

Texture::~Texture() noexcept {
	if (m_Id) glDeleteTextures(1, &m_Id);
	m_Id = 0;
}

inline void Texture::Bind() const noexcept { glBindTexture(GL_TEXTURE_2D, m_Id); }
