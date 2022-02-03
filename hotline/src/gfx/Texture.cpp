#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Log.h"

Texture::Texture() {
	glGenTextures(1, &id);
}

Texture::Texture(const char* path) : Texture() {
	Init(path);
}

Texture::~Texture() noexcept {
	if (id) {
		glDeleteTextures(1, &id);
		id = 0;
	}
}

void Texture::Init(const char* path) {
	stbi_set_flip_vertically_on_load(1);
	auto image = stbi_load(path, &width, &height, nullptr, STBI_rgb_alpha);
	if (image == nullptr) {
		LOG_ERROR("Failed to load texture image: %s", path);
		return;
	}

	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
}
