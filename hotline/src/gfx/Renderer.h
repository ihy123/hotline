#pragma once
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"

class Renderer {
public:
	Renderer()
		: vbo(VBO::Type::VertexBuffer, false), shaders{
			ShaderProgram(
				{Shader::Type::Vertex, "res/shaders/basic_color.vert"},
				{Shader::Type::Fragment, "res/shaders/basic_color.frag" })} {
		const float vertices[]{
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 0.0f,  1.0f
		};
		vbo.Data(vertices, sizeof(vertices));
		vao.Attribute(vbo, 0, 2, GL_FLOAT, 0, 0);
	}
	void Draw() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		vao.Bind();
		shaders.basic.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
private:
	VBO vbo;
	VAO vao;
	struct {
		ShaderProgram basic;
	} shaders;
};
