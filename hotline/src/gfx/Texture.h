#pragma once
#include <glad/gl.h>

class Texture {
public:
	Texture(const char* file_path);
	Texture(const Texture&) = delete;
	Texture operator=(const Texture&) = delete;
	~Texture() noexcept;
	inline void Bind() const noexcept;
	constexpr GLuint GetId() const noexcept { return m_Id; }
	constexpr int GetWidth() const noexcept { return m_Width; }
	constexpr int GetHeight() const noexcept { return m_Height; }
private:
	GLuint m_Id;
	int m_Width, m_Height;
};
