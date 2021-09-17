#include "VAO.h"
#include "VBO.h"

VAO::VAO() {
	glGenVertexArrays(1, &m_Id);
}

VAO::~VAO() noexcept {
	if (m_Id) glDeleteVertexArrays(1, &m_Id);
	m_Id = 0;
}

inline void VAO::Attribute(VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) const {
	Bind();
	vbo.Bind();
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}

inline void VAO::Bind() const noexcept { glBindVertexArray(m_Id); }
