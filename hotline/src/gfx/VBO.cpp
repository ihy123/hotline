#include "VBO.h"

VBO::VBO(Type type, bool dynamic)
	: m_Type(type), m_Dynamic(dynamic) {
	glGenBuffers(1, &m_Id);
}

VBO::~VBO() noexcept {
	if (m_Id) glDeleteBuffers(1, &m_Id);
	m_Id = 0;
}

inline void VBO::Data(const void* data, GLsizeiptr size) const {
	Bind();
	glBufferData((GLenum)m_Type, size, data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

inline void VBO::Bind() const noexcept { glBindBuffer((GLenum)m_Type, m_Id); }
