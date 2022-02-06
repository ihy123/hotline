#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"
#include "TextureBank.h"
#include "Animation.h"
#include <entity/components/Sprite.h>
#include <glm/glm.hpp>

class Renderer {
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void SetViewProj(const glm::mat4& viewProj) noexcept;
	inline void Clear(float r, float g, float b, float a);

	inline void DrawColoredQuad(const glm::vec2& pos, const glm::vec2& scale, float angle, const glm::vec4& color);
	inline void DrawColoredQuad(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color);
	inline void DrawColoredQuad(const glm::vec2& pos, const glm::vec4& color);
	void DrawColoredQuad(const glm::mat4& model, const glm::vec4& color);

	inline void DrawTexturedQuad(const glm::vec2& pos, const glm::vec2& scale, float angle, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max);
	inline void DrawTexturedQuad(const glm::vec2& pos, const glm::vec2& scale, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max);
	inline void DrawTexturedQuad(const glm::vec2& pos, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max);
	inline void DrawTexturedQuad(const glm::mat4& model, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max);
	void DrawTexturedQuad(const glm::mat4& model, Texture& texture, const glm::vec2& uv_min, const glm::vec2& uv_max);

	inline void DrawAnimation(const glm::vec2& pos, const glm::vec2& scale, float angle, const Animation& anim);
	inline void DrawAnimation(const glm::vec2& pos, const glm::vec2& scale, const Animation& anim);
	inline void DrawAnimation(const glm::vec2& pos, const Animation& anim);
	void DrawAnimation(const glm::mat4& model, const Animation& anim);

	inline void DrawSprite(const glm::vec2& pos, const glm::vec2& scale, float angle, const SpriteComponent& sprite);
	inline void DrawSprite(const glm::vec2& pos, const glm::vec2& scale, const SpriteComponent& sprite);
	inline void DrawSprite(const glm::vec2& pos, const SpriteComponent& sprite);
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

#include "Renderer.inl"
