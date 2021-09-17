#include "VBO.h"

VBO::VBO(Type type, bool dynamic)
	: m_Type(type), m_Dynamic(dynamic) {
	glGenBuffers(1, &m_Id);
}

VBO::~VBO() noexcept {
	if (m_Id) glDeleteBuffers(1, &m_Id);
	m_Id = 0;
}
