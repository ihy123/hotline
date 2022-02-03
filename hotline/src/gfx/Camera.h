#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "State.h"

class PerspectiveCamera {
public:
	PerspectiveCamera(const glm::vec3& position = glm::vec3());

	glm::mat4 GetViewProj(float fov, float zNear, float zFar) const noexcept;
	void Update(float dt);
public:
	glm::vec3 pos, dir, up;
	float speed = 0.5f;
	float sens = 50.0f;

	bool mouseCaptured = false;
	glm::vec2 mousePos, prevMousePos;
};

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
