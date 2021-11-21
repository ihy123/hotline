#include <State.h>
#include <entity/ECS.h>

void _SpriteOnRender(ECS* ecs, void* component, Entity entity) {
	assert(ecs->Has(entity, Component::Physics));
	auto sc = reinterpret_cast<SpriteComponent*>(component);
	auto pc = reinterpret_cast<PhysicsComponent*>(ecs->Get(entity, Component::Physics));
	auto& pos = pc->body->GetPosition();
	state.renderer.TexturedQuad(sc->tex,
		{ pc->halfSize.x, pc->halfSize.y },
		glm::rotate(glm::translate(glm::identity<glm::mat4>(),
			{ pos.x, pos.y, 0.0f }), pc->body->GetAngle(), { 0.0f, 0.0f, 1.0f }),
		sc->uv_min, sc->uv_max);
}

void SpriteInit(ECS& ecs) {
	ecs.RegisterComponent<SpriteComponent>(Component::Sprite, System{
		.onUpdate = nullptr,
		.onTick = nullptr,
		.onRender = _SpriteOnRender
	});
}
