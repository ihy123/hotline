#pragma once
#include <glm/glm.hpp>
#include <gfx/Texture.h>
#include <gfx/Animation.h>
#include <string>

struct SpriteComponent {
	Animation animation;
	bool isAnimated;

	SpriteComponent(Animation&& anim, bool isAnimated)
		: animation(anim), isAnimated(isAnimated) {}
	SpriteComponent(const std::string& texture, glm::vec2 uv_min, glm::vec2 uv_max)
		: animation(texture, uv_min, uv_max, 1.0f, 0.0f), isAnimated(false) {}
	SpriteComponent(const std::string& texture, const glm::vec2& uv_min,
		const glm::vec2& uv_max, float animDuration, float animFrameWidth, bool isAnimated)
		: animation(texture, uv_min, uv_max, animFrameWidth, animDuration), isAnimated(isAnimated) {}
};
