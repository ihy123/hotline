#pragma once
#include <glad/gl.h>

class Shader {
public:
	enum class Type : GLenum {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};
public:
	Shader(Type type, const char* file_path);
	Shader(const Shader&) = delete;
	Shader operator=(const Shader&) = delete;
	~Shader() noexcept;
	constexpr GLuint GetId() const noexcept { return m_Id; }
private:
	GLuint m_Id;
};

class ShaderProgram {
public:
	ShaderProgram(Shader vertex, Shader fragment);
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram operator=(const ShaderProgram&) = delete;
	~ShaderProgram() noexcept;
	inline void Bind() const noexcept { glUseProgram(m_Id); }
	constexpr GLuint GetId() const noexcept { return m_Id; }
private:
	GLuint m_Id;
};
