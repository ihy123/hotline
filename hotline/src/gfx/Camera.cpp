#include "Camera.h"

PerspectiveCamera::PerspectiveCamera(const glm::vec3& position)
	: pos(position), dir(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f) {}

glm::mat4 PerspectiveCamera::GetViewProj(float fov, float zNear, float zFar) const noexcept {
	glm::vec2 wndSize = state.wnd.GetSize();
	auto view = glm::lookAt(pos, pos + dir, up);
	auto proj = glm::perspective(glm::radians(fov), wndSize.x / wndSize.y, zNear, zFar);
	return std::move(proj * view);
}

void PerspectiveCamera::Update(float dt) {
	// rotate
	if (state.wnd.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
		glm::vec2 wndSize = state.wnd.GetSize();
		prevMousePos = mousePos;
		mousePos = state.wnd.GetCursorPos();

		if (!mouseCaptured) {
			state.wnd.SetCursorEnabled(false);
			prevMousePos = mousePos;
			mouseCaptured = true;
		}

		glm::vec2 motion = (mousePos - prevMousePos) / wndSize * sens;
		float angleY = glm::radians(1.0f) * motion.x;
		float angleX = glm::radians(1.0f) * motion.y;
		dir = glm::rotate(dir, angleX, glm::vec3(-1.0f, 0.0f, 0.0f));
		glm::vec3 newDir = glm::rotate(dir, angleY, -up);
		if (abs(glm::angle(newDir, up) - glm::radians(90.0f)) <= glm::radians(89.0f))
			dir = newDir;
	}
	else if (mouseCaptured) {
		state.wnd.SetCursorEnabled(true);
		mouseCaptured = false;
	}

	// move
	glm::vec3 velocity(0.0f);
	if (state.wnd.GetKey(GLFW_KEY_W))
		velocity.z -= 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_S))
		velocity.z += 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_A))
		velocity.x -= 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_D))
		velocity.x += 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_LEFT_SHIFT))
		velocity.y -= 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_SPACE))
		velocity.y += 1.0f;

	if (velocity.x != 0.0f || velocity.y != 0.0f || velocity.z != 0.0f)
		velocity = glm::normalize(velocity);

	pos += speed * dt * velocity;
}

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
