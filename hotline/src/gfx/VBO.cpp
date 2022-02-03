#include "VBO.h"

VBO::VBO() {
	glGenBuffers(1, &id);
}

VBO::VBO(const void* vertices, GLsizeiptr size, GLenum usage) : VBO() {
	Data(vertices, size, usage);
}

VBO::~VBO() noexcept {
	if (id) {
		glDeleteBuffers(1, &id);
		id = 0;
	}
}
