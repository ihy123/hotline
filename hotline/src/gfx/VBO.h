#pragma once
#include <glad/gl.h>

class VBO {
public:
	VBO();
	VBO(const void* vertices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;
	~VBO() noexcept;

	inline void Bind() const noexcept { glBindBuffer(GL_ARRAY_BUFFER, id); }
	inline void Data(const void* vertices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) const noexcept {
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	}
public:
	GLuint id = 0;
};
