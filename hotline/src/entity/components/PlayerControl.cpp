#include <State.h>
#include <entity/ECS.h>
#include <entity/Camera.h>

void _PlayerControlOnUpdate(ECS* ecs, void* component, Entity entity) {
	assert(ecs->Has(entity, Component::Physics));
	auto pc = reinterpret_cast<PhysicsComponent*>(ecs->Get(entity, Component::Physics));
	b2Body* player = pc->body;

	// move
	auto pcc = reinterpret_cast<PlayerControlComponent*>(component);
	glm::vec2 velocity(0.0f, 0.0f);
	if (state.wnd.GetKey(GLFW_KEY_W))
		velocity.y += 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_S))
		velocity.y -= 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_A))
		velocity.x -= 1.0f;
	if (state.wnd.GetKey(GLFW_KEY_D))
		velocity.x += 1.0f;

	if (velocity.x != 0.0f || velocity.y != 0.0f)
		velocity = glm::normalize(velocity) * pcc->speed;
	player->SetLinearVelocity({ velocity.x, velocity.y });

	// rotate
	glm::vec2 wndSize = glm::vec2(state.wnd.GetSize()) / PIXELS_IN_METER;
	auto& b2pos = player->GetPosition();
	glm::vec2 pos(b2pos.x, b2pos.y);
	glm::vec2 cursorPos = state.wnd.GetCursorPos() / PIXELS_IN_METER;
	cursorPos.y = wndSize.y - cursorPos.y;
	cursorPos -= wndSize / 2.0f - glm::vec2{ pos.x, pos.y };

	float angle = 0.0f;
	glm::vec2 dir = cursorPos - glm::vec2{ pos.x, pos.y };
	if (dir.x != 0.0f || dir.y != 0.0f) {
		dir = glm::normalize(dir);
		angle = atan2(dir.y, dir.x);
		player->SetTransform(b2pos, angle);

		pcc->direction = dir;
		pcc->angle = angle;
	}
}

void PlayerControlInit(ECS& ecs) {
	ecs.RegisterComponent<PlayerControlComponent>(Component::PlayerControl, System{
		.onUpdate = _PlayerControlOnUpdate,
		.onTick = nullptr,
		.onRender = nullptr
	});
}
