#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &m_Id);
}

VAO::~VAO() noexcept {
	if (m_Id) glDeleteVertexArrays(1, &m_Id);
	m_Id = 0;
}
