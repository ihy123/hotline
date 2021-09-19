#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	GLuint m_Id = 0;
};

class ShaderProgram {
public:
	ShaderProgram(Shader vertex, Shader fragment);
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram operator=(const ShaderProgram&) = delete;
	~ShaderProgram() noexcept;
	inline void UniformVec4(const char* name, const glm::vec4& val) const {
		glUniform4f(glGetUniformLocation(m_Id, name), val.x, val.y, val.z, val.w);
	}
	inline void UniformMat4(const char* name, const glm::mat4& val) const {
		glUniformMatrix4fv(glGetUniformLocation(m_Id, name), 1, GL_FALSE, glm::value_ptr(val));
	}
	inline void Bind() const noexcept { glUseProgram(m_Id); }
	constexpr GLuint GetId() const noexcept { return m_Id; }
private:
	GLuint m_Id = 0;
};
