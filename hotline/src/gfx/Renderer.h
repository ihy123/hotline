#pragma once
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"

static constexpr float PIXELS_IN_METER = 64.0f;

class Renderer {
public:
	Renderer()
		: vbo(VBO::Type::VertexBuffer, true), ibo(VBO::Type::IndexBuffer, true), shaders{
			ShaderProgram(
				{ Shader::Type::Vertex, "res/shaders/basic_color.vert" },
				{ Shader::Type::Fragment, "res/shaders/basic_color.frag" }),
			ShaderProgram(
				{ Shader::Type::Vertex, "res/shaders/basic_texture.vert" },
				{ Shader::Type::Fragment, "res/shaders/basic_texture.frag" }) } {
		view_proj = /* proj */ glm::ortho(0.0f, 800.0f / PIXELS_IN_METER, 0.0f, 600.0f / PIXELS_IN_METER, 0.0f, 10.0f);
	}
	void ColoredQuad(const glm::vec2& size, const glm::mat4& model, const glm::vec4& color) {
		const float vertices[]{
			0.0f,   0.0f,
			size.x, 0.0f,
			size.x, size.y,
			size.x, size.y,
			0.0f,   size.y,
			0.0f,   0.0f
		};
		vbo.Data(vertices, sizeof(vertices));
		vao.Attribute(vbo, 0, 2, GL_FLOAT, 0, 0);

		shaders.basic_color.Bind();
		shaders.basic_color.UniformMat4("model", model);
		shaders.basic_color.UniformMat4("view_proj", view_proj);
		shaders.basic_color.UniformVec4("color", color);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	void TexturedQuad(const Texture& tex, const glm::vec2& size, const glm::mat4& model, const glm::vec2& uv_min, const glm::vec2& uv_max) {
		const float vertices[]{
			0.0f,   0.0f,      uv_min.x, uv_min.y,
			size.x, 0.0f,      uv_max.x, uv_min.y,
			size.x, size.y,    uv_max.x, uv_max.y,
			0.0f,   size.y,	   uv_min.x, uv_max.y
		};
		const unsigned short indices[]{
			0, 1, 2, 2, 3, 0
		};

		shaders.basic_texture.Bind();
		shaders.basic_texture.UniformMat4("model", model);
		shaders.basic_texture.UniformMat4("view_proj", view_proj);
		tex.Bind();
		vbo.Data(vertices, sizeof(vertices));
		vao.Attribute(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), 0);
		vao.Attribute(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));
		ibo.Data(indices, sizeof(indices));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	}
	inline void Prepare() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
private:
	VBO vbo, ibo;
	VAO vao;
	struct {
		ShaderProgram basic_color;
		ShaderProgram basic_texture;
	} shaders;
	glm::mat4 view_proj;
};
