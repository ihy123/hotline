#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &id);
}

VAO::~VAO() noexcept {
	if (id) {
		glDeleteVertexArrays(1, &id);
		id = 0;
	}
}
