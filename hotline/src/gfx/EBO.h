#pragma once
#include <glad/gl.h>

class EBO {
public:
	EBO();
	EBO(const void* indices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	EBO(const EBO&) = delete;
	EBO& operator=(const EBO&) = delete;
	~EBO() noexcept;

	inline void Bind() const noexcept { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
	inline void Data(const void* indices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) const noexcept {
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
	}
public:
	GLuint id = 0;
};
