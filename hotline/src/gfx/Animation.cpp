#include "Animation.h"
#include "State.h"
#include "Renderer.h"

Animation::Animation(const std::string& texture, const glm::vec2& uv_min, const glm::vec2& uv_max, float frame_width, float duration)
	: texture(&state.renderer.texBank.Get(texture)), frame_width(frame_width), uv_min(uv_min), uv_max(uv_max), duration(duration) {
	num_frames = (int)round((uv_max.x - uv_min.x) / frame_width);
	frame_time = duration / (float)num_frames;
}

void Animation::Update(float dt) {
	time_passed += dt;
	while (time_passed >= frame_time) {
		time_passed -= frame_time;
		++cur_frame;
		cur_frame = cur_frame % num_frames;
	}
}

void Animation::GetFrame(glm::vec2& _uv_min, glm::vec2& _uv_max) const {
	_uv_min.x = uv_min.x + (float)cur_frame * frame_width;
	_uv_min.y = 0.0f;
	_uv_max.x = _uv_min.x + frame_width;
	_uv_max.y = 1.0f;
}
