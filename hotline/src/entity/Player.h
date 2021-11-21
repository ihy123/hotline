#pragma once
#include <State.h>
#include <entity/ECS.h>

class Player {
public:
	Player(ECS& ecs) : m_Ecs(ecs), entity(ecs.New()) {}
	void Init(b2World* world, b2Vec2 pos, float radius, float speed, Texture* texture, glm::vec2 uv_min, glm::vec2 uv_max) {
		b2Body* player;
		b2BodyDef bdef;
		bdef.type = b2_dynamicBody;
		bdef.position = pos;
		player = world->CreateBody(&bdef);

		b2CircleShape shape;
		shape.m_radius = radius;

		b2FixtureDef fdef;
		fdef.shape = &shape;
		fdef.density = 1.0f;
		fdef.friction = 0.0f;
		player->CreateFixture(&fdef);

		PhysicsComponent pc{
			.size = b2Vec2{ radius * 2.0f, radius * 2.0f },
			.halfSize = b2Vec2{ radius, radius },
			.body = player
		};
		SpriteComponent sc{
			.tex = texture,
			.uv_min = uv_min,
			.uv_max = uv_max
		};
		PlayerControlComponent pcc{ .speed = speed };
		CombatComponent cc{ .prevTime = 0.0f, .cooldown = 0.5f };

		m_Ecs.Add(entity, Component::Physics, &pc);
		m_Ecs.Add(entity, Component::Sprite, &sc);
		m_Ecs.Add(entity, Component::PlayerControl, &pcc);
		m_Ecs.Add(entity, Component::Combat, &cc);
	}

	void SetPosition(b2Vec2 pos) {
		auto b = reinterpret_cast<PhysicsComponent*>(m_Ecs.Get(entity, Component::Physics))->body;
		b->SetTransform(pos, b->GetAngle());
	}
	b2Vec2 GetPosition() {
		return reinterpret_cast<PhysicsComponent*>(m_Ecs.Get(entity, Component::Physics))->body->GetPosition();
	}
	void SetSpeed(float speed) {
		reinterpret_cast<PlayerControlComponent*>(m_Ecs.Get(entity, Component::PlayerControl))->speed = speed;
	}
	float GetSpeed() {
		return reinterpret_cast<PlayerControlComponent*>(m_Ecs.Get(entity, Component::PlayerControl))->speed;
	}
	void SetTexture(Texture* texture, glm::vec2 uv_min, glm::vec2 uv_max) {
		auto sc = reinterpret_cast<SpriteComponent*>(m_Ecs.Get(entity, Component::Sprite));
		*sc = SpriteComponent{
			.tex = texture,
			.uv_min = uv_min,
			.uv_max = uv_max
		};
	}
	void Disable() {
		reinterpret_cast<PhysicsComponent*>(m_Ecs.Get(entity, Component::Physics))->body->SetEnabled(false);
		m_Ecs.Disable(entity);
	}
	void Enable() {
		reinterpret_cast<PhysicsComponent*>(m_Ecs.Get(entity, Component::Physics))->body->SetEnabled(true);
		m_Ecs.Enable(entity);
	}
public:
	Entity entity;
private:
	ECS& m_Ecs;
};
