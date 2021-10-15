#include "ShaderProgram.h"
#include <Log.h>
#include <fstream>

Shader::Shader(Type type, const char* file_path) {
	m_Id = glCreateShader((GLenum)type);

	std::ifstream file(file_path, std::ios::ate | std::ios::binary);
	auto length = file.tellg();
	file.seekg(std::ios::beg);

	auto buf = new char[(size_t)length + 1];
	file.read(buf, length);
	buf[length] = '\0';

	glShaderSource(m_Id, 1, &buf, nullptr);
	glCompileShader(m_Id);
	delete[] buf;

	GLint success;
	glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		char err[1024];
		glGetShaderInfoLog(m_Id, 1024, nullptr, err);
		LOG_ERROR("%s", err);
	}
}

Shader::~Shader() noexcept {
	if (m_Id) glDeleteShader(m_Id);
	m_Id = 0;
}

ShaderProgram::ShaderProgram(Shader vertex, Shader fragment) {
	m_Id = glCreateProgram();
	glAttachShader(m_Id, vertex.GetId());
	glAttachShader(m_Id, fragment.GetId());
	glLinkProgram(m_Id);

	GLint success;
	glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		char err[1024];
		glGetProgramInfoLog(m_Id, 1024, nullptr, err);
		LOG_ERROR("%s", err);
	}
}

ShaderProgram::~ShaderProgram() noexcept {
	if (m_Id) glDeleteProgram(m_Id);
	m_Id = 0;
}
