#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>

class Texture {
public:
	Texture();
	Texture(const char* path);
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	~Texture() noexcept;

	void Init(const char* path);

	inline void Bind() const noexcept { glBindTexture(GL_TEXTURE_2D, id); }
	inline void BindUnit(GLenum nUnit) const noexcept { glActiveTexture(GL_TEXTURE0 + nUnit); }
public:
	GLuint id = 0;
	int width, height;
};
