#include "Camera.h"
#include "State.h"

glm::mat4 HudCamera::GetViewProj() noexcept {
	glm::vec2 size = state.wnd.GetSize();
	return glm::ortho(0.0f, size.x, size.y, 0.0f);
}

OrthoCamera::OrthoCamera(const glm::vec2& position, const glm::vec2& scale) : pos(position), scale(scale) {}

glm::mat4 OrthoCamera::GetViewProj() const noexcept {
	glm::vec2 size = state.wnd.GetSize();
	float aspect = size.x / size.y;
	auto view = glm::translate(glm::scale(glm::vec3(scale, 0.0f)), glm::vec3(-pos, 0.0f));
	auto proj = glm::ortho(-aspect, aspect, -1.0f, 1.0f);
	return std::move(proj * view);
}
