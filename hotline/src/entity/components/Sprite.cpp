#include "Sprite.h"
#include <State.h>
#include <entity/ECS.h>

void _SpriteOnRender(ECS* ecs, void* component, Entity entity) {
	assert(ecs->Has(entity, Component::Physics));
	auto pc = reinterpret_cast<PhysicsComponent*>(ecs->Get(entity, Component::Physics));
	auto& pos = pc->body->GetPosition();
	state.renderer.ColoredQuad(
		{ pc->size.x, pc->size.y },
		glm::translate(glm::identity<glm::mat4>(),
			{ pos.x - pc->halfSize.x, pos.y - pc->halfSize.y, 0.0f }),
		{ 0.0f, 1.0f, 0.0f, 1.0f });
}

void SpriteInit(ECS& ecs) {
	ecs.RegisterComponent<SpriteComponent>(Component::Sprite, System{
		.onUpdate = nullptr,
		.onTick = nullptr,
		.onRender = _SpriteOnRender
	});
}
