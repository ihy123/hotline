#pragma once
#include <glad/gl.h>

class VAO {
public:
	VAO();
	VAO(const VAO&) = delete;
	VAO operator=(const VAO&) = delete;
	~VAO() noexcept;
	inline void Attribute(class VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) const;
	inline void Bind() const noexcept;
	constexpr GLuint GetId() const noexcept { return m_Id; }
private:
	GLuint m_Id;
};
