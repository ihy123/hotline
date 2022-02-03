#pragma once
#include <glad/gl.h>
#include "VBO.h"

class VAO {
public:
	VAO();
	VAO(const VAO&) = delete;
	VAO& operator=(const VAO&) = delete;
	~VAO() noexcept;

	inline void Bind() const noexcept { glBindVertexArray(id); }
	inline void Attribute(VBO& vbo, GLuint index, GLint count, GLenum type, GLsizei stride, size_t offset) const noexcept {
		Bind();
		vbo.Bind();
		glVertexAttribPointer(index, count, type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(index);
	}
public:
	GLuint id = 0;
};
