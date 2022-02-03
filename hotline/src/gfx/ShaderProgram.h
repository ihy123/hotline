#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
public:
	ShaderProgram() = default;
	ShaderProgram(const char* vert_path, const char* frag_path);
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;
	~ShaderProgram() noexcept;

	void Init(const char* vert_path, const char* frag_path);

	inline void Bind() const noexcept { glUseProgram(id); }
	inline void BindTextureUnit(const char* name, GLenum nUnit) const noexcept {
		glUniform1i(glGetUniformLocation(id, name), nUnit);
	}

	inline void UniformVec3(const char* name, const glm::vec3& vec) const noexcept {
		glUniform3f(glGetUniformLocation(id, name), vec.x, vec.y, vec.z);
	}
	inline void UniformVec4(const char* name, const glm::vec4& vec) const noexcept {
		glUniform4f(glGetUniformLocation(id, name), vec.x, vec.y, vec.z, vec.w);
	}
	inline void UniformMat4(const char* name, const glm::mat4& mat) const noexcept {
		glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
public:
	GLuint id = 0;
};
