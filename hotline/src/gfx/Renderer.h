#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"
#include "TextureBank.h"
#include "Animation.h"
#include <entity/components/Sprite.h>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#define __transform_psa(pos, scale, angle) \
	glm::rotate(__transform_ps(pos, scale), angle, glm::vec3(0.0f, 0.0f, 1.0f))
#define __transform_ps(pos, scale) \
	glm::scale(__transform_p(pos), glm::vec3(scale, 0.0f))
#define __transform_p(pos) \
	glm::translate(glm::vec3(pos, 0.0f))

class Renderer {
public:
	Renderer()
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
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void SetViewProj(const glm::mat4& viewProj) noexcept {
		coloredShader.Bind();
		coloredShader.UniformMat4("viewProj", viewProj);
		texturedShader.Bind();
		texturedShader.UniformMat4("viewProj", viewProj);
	}
	inline void Clear(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	inline void DrawColoredQuad(const glm::vec2& pos, const glm::vec2& scale, float angle, const glm::vec4& color) {
		DrawColoredQuad(__transform_psa(pos, scale, angle), color);
	}
	inline void DrawColoredQuad(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color) {
		DrawColoredQuad(__transform_ps(pos, scale), color);
	}
	inline void DrawColoredQuad(const glm::vec2& pos, const glm::vec4& color) {
		DrawColoredQuad(__transform_p(pos), color);
	}
	void DrawColoredQuad(const glm::mat4& model, const glm::vec4& color) {
		coloredVao.Bind();
		coloredShader.Bind();
		coloredShader.UniformMat4("model", model);
		coloredShader.UniformVec4("color", color);
		glDrawArrays(GL_TRIANGLES, 0, 12);
	}

	inline void DrawTexturedQuad(const glm::vec2& pos, const glm::vec2& scale, float angle, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
		DrawTexturedQuad(__transform_psa(pos, scale, angle), texture, uv_min, uv_max);
	}
	inline void DrawTexturedQuad(const glm::vec2& pos, const glm::vec2& scale, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
		DrawTexturedQuad(__transform_ps(pos, scale), texture, uv_min, uv_max);
	}
	inline void DrawTexturedQuad(const glm::vec2& pos, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
		DrawTexturedQuad(__transform_p(pos), texture, uv_min, uv_max);
	}
	inline void DrawTexturedQuad(const glm::mat4& model, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
		DrawTexturedQuad(model, texBank.Get(texture), uv_min, uv_max);
	}
	void DrawTexturedQuad(const glm::mat4& model, Texture& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
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

	inline void DrawAnimation(const glm::vec2& pos, const glm::vec2& scale, float angle, const Animation& anim) {
		DrawAnimation(__transform_psa(pos, scale, angle), anim);
	}
	inline void DrawAnimation(const glm::vec2& pos, const glm::vec2& scale, const Animation& anim) {
		DrawAnimation(__transform_ps(pos, scale), anim);
	}
	inline void DrawAnimation(const glm::vec2& pos, const Animation& anim) {
		DrawAnimation(__transform_p(pos), anim);
	}
	void DrawAnimation(const glm::mat4& model, const Animation& anim) {
		glm::vec2 uv_min, uv_max;
		anim.GetFrame(uv_min, uv_max);
		DrawTexturedQuad(model, *anim.texture, uv_min, uv_max);
	}

	inline void DrawSprite(const glm::vec2& pos, const glm::vec2& scale, float angle, const SpriteComponent& sprite) {
		DrawAnimation(pos, scale, angle, sprite.animation);
	}
	inline void DrawSprite(const glm::vec2& pos, const glm::vec2& scale, const SpriteComponent& sprite) {
		DrawAnimation(pos, scale, sprite.animation);
	}
	inline void DrawSprite(const glm::vec2& pos, const SpriteComponent& sprite) {
		DrawAnimation(pos, sprite.animation);
	}
public:
	TextureBank texBank;
private:
	ShaderProgram coloredShader;
	VAO coloredVao;
	VBO coloredVbo;

	ShaderProgram texturedShader;
	VAO texturedVao;
	VBO texturedVbo;
	EBO texturedEbo;
};

#undef __transform_psa
#undef __transform_ps
#undef __transform_p
