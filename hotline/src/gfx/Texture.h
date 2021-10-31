#pragma once
#include <glad/gl.h>

class Texture {
public:
	Texture() = default;
	Texture(const char* file_path);
	~Texture() noexcept;
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other);
	Texture& operator=(Texture&& other);

	inline void Bind() const noexcept { glBindTexture(GL_TEXTURE_2D, m_Id); }
	constexpr GLuint GetId() const noexcept { return m_Id; }
	constexpr int GetWidth() const noexcept { return m_Width; }
	constexpr int GetHeight() const noexcept { return m_Height; }
private:
	GLuint m_Id = 0;
	int m_Width = 0, m_Height = 0;
};
