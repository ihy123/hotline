#pragma once
#include <glm/glm.hpp>

class OrthoCamera {
public:
	OrthoCamera(const glm::vec2& position = glm::vec2(), const glm::vec2& scale = glm::vec2(1.0f));
	glm::mat4 GetViewProj() const noexcept;
public:
	glm::vec2 pos, scale;
};

class HudCamera {
public:
	static glm::mat4 GetViewProj() noexcept;
};
