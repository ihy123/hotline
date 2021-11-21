#include <State.h>
#include <entity/ECS.h>

void _CombatOnTick(ECS* ecs, void* component, Entity entity) {
	auto cc = reinterpret_cast<CombatComponent*>(component);
	if (!(state.wnd.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT) && (state.time - cc->prevTime > cc->cooldown)))
		return;
	assert(ecs->Has(entity, Component::Physics) && ecs->Has(entity, Component::PlayerControl));
	auto pc = reinterpret_cast<PhysicsComponent*>(ecs->Get(entity, Component::Physics));
	auto pcc = reinterpret_cast<PlayerControlComponent*>(ecs->Get(entity, Component::PlayerControl));
	b2Body* player = pc->body;
	glm::vec2 dir = pcc->direction;

	cc->prevTime = state.time;

	b2Vec2 pos = player->GetPosition();

	Entity e = ecs->New();
	b2BodyDef bdef;
	bdef.type = b2_dynamicBody;
	bdef.position = b2Vec2(pos.x + dir.x * (pc->halfSize.x + 0.07f), pos.y + dir.y * (pc->halfSize.x + 0.07f));
	bdef.linearVelocity = b2Vec2(dir.x * 6.0f, dir.y * 6.0f);
	bdef.angle = player->GetAngle();
	bdef.bullet = true;
	b2PolygonShape shape;
	shape.SetAsBox(0.05f, 0.05f);

	b2Body* body = player->GetWorld()->CreateBody(&bdef);

	b2FixtureDef fdef;
	fdef.shape = &shape;
	fdef.density = 1.0f;
	fdef.friction = 0.0f;
	body->CreateFixture(&fdef);

	PhysicsComponent pc1{
		.size = { 0.1f, 0.1f },
		.halfSize = { 0.05f, 0.05f },
		.body = body
	};
	SpriteComponent sc{
		.tex = &state.textureBank["bullet"],
		.uv_min = { 0.0f, 0.0f },
		.uv_max = { 1.0f, 1.0f }
	};

	ecs->Add(e, Component::Physics, &pc1);
	ecs->Add(e, Component::Sprite, &sc);
}

void CombatInit(ECS& ecs) {
	ecs.RegisterComponent<CombatComponent>(Component::Combat, System{
		.onUpdate = nullptr,
		.onTick = _CombatOnTick,
		.onRender = nullptr
	});
}
