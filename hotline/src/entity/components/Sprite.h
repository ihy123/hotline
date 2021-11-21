#pragma once
#include <glm/glm.hpp>
#include <gfx/Texture.h>

struct SpriteComponent {
	Texture* tex;
	glm::vec2 uv_min, uv_max;
};
