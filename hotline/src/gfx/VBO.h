#pragma once
#include <glad/gl.h>

class VBO {
public:
	enum class Type : GLenum {
		VertexBuffer = GL_ARRAY_BUFFER,
		IndexBuffer = GL_ELEMENT_ARRAY_BUFFER,
		TextureBuffer = GL_TEXTURE_BUFFER,
		UniformBuffer = GL_UNIFORM_BUFFER
	};
public:
	VBO(Type type, bool dynamic);
	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;
	~VBO() noexcept;
	inline void Data(const void* data, GLsizeiptr size) const {
		Bind();
		glBufferData((GLenum)m_Type, size, data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}
	inline void Bind() const noexcept { glBindBuffer((GLenum)m_Type, m_Id); }
	constexpr GLuint GetId() const noexcept { return m_Id; }
private:
	GLuint m_Id = 0;
	Type m_Type;
	bool m_Dynamic;
};
