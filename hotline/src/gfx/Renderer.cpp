#include "Renderer.h"

Renderer::Renderer()
	: coloredShader("res/shaders/colored.vert", "res/shaders/colored.frag"),
	texturedShader("res/shaders/textured.vert", "res/shaders/textured.frag") {
	// prepare for drawing colored quads
		{
			const float vertices[]{
				-1.0f, -1.0f,
				 1.0f, -1.0f,
				 1.0f,  1.0f,
				 1.0f,  1.0f,
				-1.0f,  1.0f,
				-1.0f, -1.0f
			};
			coloredVbo.Data(vertices, sizeof(vertices));
			coloredVao.Attribute(coloredVbo, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);
		}
		// prepare for drawing textured quads
		{
			const float vertices[]{
				-1.0f, -1.0f,   0.0f, 0.0f,
				 1.0f, -1.0f,   1.0f, 0.0f,
				 1.0f,  1.0f,   1.0f, 1.0f,
				-1.0f,  1.0f,   0.0f, 1.0f
			};
			const unsigned short indices[]{
				0, 1, 2, 2, 3, 0
			};
			texturedVao.Bind();
			texturedVbo.Data(vertices, sizeof(vertices));
			texturedEbo.Data(indices, sizeof(indices));
			texturedVao.Attribute(texturedVbo, 0, 2, GL_FLOAT, 4 * sizeof(float), 0);
			texturedVao.Attribute(texturedVbo, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));
			texturedShader.Bind();
			texturedShader.BindTextureUnit("tex0", 0);
		}
}

void Renderer::SetViewProj(const glm::mat4& viewProj) noexcept {
	coloredShader.Bind();
	coloredShader.UniformMat4("viewProj", viewProj);
	texturedShader.Bind();
	texturedShader.UniformMat4("viewProj", viewProj);
}

void Renderer::DrawColoredQuad(const glm::mat4& model, const glm::vec4& color) {
	coloredVao.Bind();
	coloredShader.Bind();
	coloredShader.UniformMat4("model", model);
	coloredShader.UniformVec4("color", color);
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void Renderer::DrawTexturedQuad(const glm::mat4& model, Texture& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
	const float vertices[]{
		-1.0f, -1.0f,   uv_min.x, uv_min.y,
		 1.0f, -1.0f,   uv_max.x, uv_min.y,
		 1.0f,  1.0f,   uv_max.x, uv_max.y,
		-1.0f,  1.0f,   uv_min.x, uv_max.y
	};
	texturedVbo.Data(vertices, sizeof(vertices));

	texturedVao.Bind();
	texturedShader.Bind();
	texturedShader.UniformMat4("model", model);
	texture.BindUnit(0);
	texture.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void Renderer::DrawAnimation(const glm::mat4& model, const Animation& anim) {
	glm::vec2 uv_min, uv_max;
	anim.GetFrame(uv_min, uv_max);
	DrawTexturedQuad(model, *anim.texture, uv_min, uv_max);
}
