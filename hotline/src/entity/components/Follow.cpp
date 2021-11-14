#include <State.h>
#include <entity/ECS.h>

void _FollowOnTick(ECS* ecs, void* component, Entity entity) {
	assert(ecs->Has(entity, Component::Physics));
	auto fc = reinterpret_cast<FollowComponent*>(component);
	auto pc = reinterpret_cast<PhysicsComponent*>(ecs->Get(entity, Component::Physics));
	auto& pos = pc->body->GetPosition();
	auto& targetPos = fc->target->body->GetPosition();
	glm::vec2 newPos = glm::mix(glm::vec2{ pos.x, pos.y }, glm::vec2{ targetPos.x, targetPos.y }, fc->speed);
	glm::vec2 velocity = (newPos - glm::vec2{ pos.x, pos.y }) / TICK_TIME;
	pc->body->SetLinearVelocity({ velocity.x, velocity.y });
}

void FollowInit(ECS& ecs) {
	ecs.RegisterComponent<FollowComponent>(Component::Follow, System{
		.onUpdate = nullptr,
		.onTick = _FollowOnTick,
		.onRender = nullptr
	});
}
