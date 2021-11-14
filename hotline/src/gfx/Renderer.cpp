#include "Renderer.h"
#include <State.h>

void Renderer::SetViewProj(glm::vec2 camPos) {
	glm::vec2 size = state.wnd.GetSize();
	size /= PIXELS_IN_METER;

	view_proj = glm::ortho(0.0f, size.x, 0.0f, size.y, 0.0f, 10.0f) *
		glm::translate(glm::identity<glm::mat4>(), { size.x / 2.0f - camPos.x, size.y / 2.0f - camPos.y, 0.0f });
}
