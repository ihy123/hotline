#pragma once
#include <entity/ECS.h>
#include "Player.h"

static constexpr float PIXELS_IN_METER = 64.0f;

class Camera {
public:
	Camera(ECS& ecs) : m_Ecs(ecs), entity(ecs.New()) {}
	void Init(b2World* world, Player& target, float speed) {
		auto tpc = reinterpret_cast<PhysicsComponent*>(m_Ecs.Get(target.entity, Component::Physics));
		b2Body* camera;
		b2BodyDef bdef;
		bdef.type = b2_kinematicBody;
		bdef.position = tpc->body->GetPosition();
		camera = world->CreateBody(&bdef);

		PhysicsComponent pc{
			.size = { 0.0f, 0.0f },
			.halfSize = { 0.0f, 0.0f },
			.body = camera
		};
		FollowComponent fc{
			.target = tpc,
			.speed = speed
		};

		m_Ecs.Add(entity, Component::Physics, &pc);
		m_Ecs.Add(entity, Component::Follow, &fc);
	}
	void SetSpeed(float speed) {
		reinterpret_cast<FollowComponent*>(m_Ecs.Get(entity, Component::Follow))->speed = speed;
	}
	float GetSpeed() {
		return reinterpret_cast<FollowComponent*>(m_Ecs.Get(entity, Component::Follow))->speed;
	}
	glm::mat4 GetViewProj() {
		auto& pos = reinterpret_cast<PhysicsComponent*>(m_Ecs.Get(entity, Component::Physics))->body->GetPosition();
		glm::vec2 size = state.wnd.GetSize();
		size /= PIXELS_IN_METER;
		return glm::ortho(0.0f, size.x, 0.0f, size.y, 0.0f, 10.0f) *
			glm::translate(glm::identity<glm::mat4>(), { size.x / 2.0f - pos.x, size.y / 2.0f - pos.y, 0.0f });
	}
public:
	Entity entity;
private:
	ECS& m_Ecs;
};
