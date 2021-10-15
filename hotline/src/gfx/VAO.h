#pragma once
#include <glad/gl.h>
#include "VBO.h"

class VAO {
public:
	VAO();
	VAO(const VAO&) = delete;
	VAO& operator=(const VAO&) = delete;
	~VAO() noexcept;
	inline void Attribute(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) const {
		Bind();
		vbo.Bind();
		glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(index);
	}
	inline void Bind() const noexcept { glBindVertexArray(m_Id); }
	constexpr GLuint GetId() const noexcept { return m_Id; }
private:
	GLuint m_Id = 0;
};
