#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
#include <string>

class Animation {
public:
	Animation() = default;
	Animation(const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max, float frame_width, float duration);
	void Update(float dt);
	void GetFrame(glm::vec2& _uv_min, glm::vec2& _uv_max) const;
	inline void SetFrame(int index) noexcept { cur_frame = index; }
public:
	Texture* texture;
private:
	glm::vec2 uv_min, uv_max;
	int num_frames, cur_frame = 0;
	float duration, frame_width, frame_time, time_passed = 0.0f;
};
