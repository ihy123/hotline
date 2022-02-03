#include "EBO.h"

EBO::EBO() {
	glGenBuffers(1, &id);
}

EBO::EBO(const void* indices, GLsizeiptr size, GLenum usage) : EBO() {
	Data(indices, size, usage);
}

EBO::~EBO() noexcept {
	if (id) {
		glDeleteBuffers(1, &id);
		id = 0;
	}
}
