#include <State.h>
#include <entity/ECS.h>

void _PlayerControlOnUpdate(ECS* ecs, void* component, Entity entity) {
	assert(ecs->Has(entity, Component::Physics));
	b2Body* player = reinterpret_cast<PhysicsComponent*>(ecs->Get(entity, Component::Physics))->body;
	float speed = reinterpret_cast<PlayerControlComponent*>(component)->speed;

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
		velocity = glm::normalize(velocity) * speed;
	player->SetLinearVelocity({ velocity.x, velocity.y });
}

void PlayerControlInit(ECS& ecs) {
	ecs.RegisterComponent<PlayerControlComponent>(Component::PlayerControl, System{
		.onUpdate = _PlayerControlOnUpdate,
		.onTick = nullptr,
		.onRender = nullptr
	});
}
