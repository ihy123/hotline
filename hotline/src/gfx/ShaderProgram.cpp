#include "ShaderProgram.h"
#include <fstream>
#include "Log.h"

static GLuint CreateShader(const char* file_path, GLenum type) {
	GLuint id = glCreateShader(type);

	std::ifstream file(file_path, std::ios::ate | std::ios::binary);
	auto length = file.tellg();
	file.seekg(std::ios::beg);

	auto buf = new char[(size_t)length + 1];
	file.read(buf, length);
	file.close();
	buf[length] = '\0';

	glShaderSource(id, 1, &buf, nullptr);
	glCompileShader(id);
	delete[] buf;

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		char err[1024];
		glGetShaderInfoLog(id, 1024, nullptr, err);
		LOG_ERROR("%s", err);
	}

	return id;
}

ShaderProgram::ShaderProgram(const char* vert_path, const char* frag_path) {
	Init(vert_path, frag_path);
}

ShaderProgram::~ShaderProgram() noexcept {
	if (id) {
		glDeleteProgram(id);
		id = 0;
	}
}

void ShaderProgram::Init(const char* vert_path, const char* frag_path) {
	GLuint vert = CreateShader(vert_path, GL_VERTEX_SHADER);
	GLuint frag = CreateShader(frag_path, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vert);
	glAttachShader(id, frag);
	glLinkProgram(id);

	glDeleteShader(vert);
	glDeleteShader(frag);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		char err[1024];
		glGetProgramInfoLog(id, 1024, nullptr, err);
		LOG_ERROR("%s", err);
	}
}
