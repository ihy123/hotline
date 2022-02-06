
#include <glm/gtx/vector_angle.hpp>

#define __transform_psa(pos, scale, angle) \
	glm::rotate(__transform_ps(pos, scale), angle, glm::vec3(0.0f, 0.0f, 1.0f))
#define __transform_ps(pos, scale) \
	glm::scale(__transform_p(pos), glm::vec3(scale, 0.0f))
#define __transform_p(pos) \
	glm::translate(glm::vec3(pos, 0.0f))

void Renderer::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DrawColoredQuad(const glm::vec2& pos, const glm::vec2& scale, float angle, const glm::vec4& color) {
	DrawColoredQuad(__transform_psa(pos, scale, angle), color);
}

void Renderer::DrawColoredQuad(const glm::vec2& pos, const glm::vec2& scale, const glm::vec4& color) {
	DrawColoredQuad(__transform_ps(pos, scale), color);
}

void Renderer::DrawColoredQuad(const glm::vec2& pos, const glm::vec4& color) {
	DrawColoredQuad(__transform_p(pos), color);
}

void Renderer::DrawTexturedQuad(const glm::vec2& pos, const glm::vec2& scale, float angle, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
	DrawTexturedQuad(__transform_psa(pos, scale, angle), texture, uv_min, uv_max);
}
void Renderer::DrawTexturedQuad(const glm::vec2& pos, const glm::vec2& scale, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
	DrawTexturedQuad(__transform_ps(pos, scale), texture, uv_min, uv_max);
}
void Renderer::DrawTexturedQuad(const glm::vec2& pos, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
	DrawTexturedQuad(__transform_p(pos), texture, uv_min, uv_max);
}
void Renderer::DrawTexturedQuad(const glm::mat4& model, const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max) {
	DrawTexturedQuad(model, texBank.Get(texture), uv_min, uv_max);
}

void Renderer::DrawAnimation(const glm::vec2& pos, const glm::vec2& scale, float angle, const Animation& anim) {
	DrawAnimation(__transform_psa(pos, scale, angle), anim);
}
void Renderer::DrawAnimation(const glm::vec2& pos, const glm::vec2& scale, const Animation& anim) {
	DrawAnimation(__transform_ps(pos, scale), anim);
}
void Renderer::DrawAnimation(const glm::vec2& pos, const Animation& anim) {
	DrawAnimation(__transform_p(pos), anim);
}

void Renderer::DrawSprite(const glm::vec2& pos, const glm::vec2& scale, float angle, const SpriteComponent& sprite) {
	DrawAnimation(pos, scale, angle, sprite.animation);
}
void Renderer::DrawSprite(const glm::vec2& pos, const glm::vec2& scale, const SpriteComponent& sprite) {
	DrawAnimation(pos, scale, sprite.animation);
}
void Renderer::DrawSprite(const glm::vec2& pos, const SpriteComponent& sprite) {
	DrawAnimation(pos, sprite.animation);
}

#undef __transform_psa
#undef __transform_ps
#undef __transform_p
