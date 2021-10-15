#pragma once
#include <State.h>
#include <entity/ECS.h>
#include <box2d/box2d.h>

static constexpr float TICK_TIME = 1.0f / 120.0f;

class Stage {
public:
	Stage() : world(new b2World({ 0.0f, 0.0f })), player(nullptr), entPlayer(ecs.New()) {}
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;
	~Stage() noexcept { delete world; }
	inline void Update() {
		b2Vec2 velocity(0.0f, 0.0f);
		if (state.wnd.GetKey(GLFW_KEY_W) | state.wnd.GetKey(GLFW_KEY_UP))
			velocity.y += 1.0f;
		if (state.wnd.GetKey(GLFW_KEY_S) | state.wnd.GetKey(GLFW_KEY_DOWN))
			velocity.y -= 1.0f;
		if (state.wnd.GetKey(GLFW_KEY_A) | state.wnd.GetKey(GLFW_KEY_LEFT))
			velocity.x -= 1.0f;
		if (state.wnd.GetKey(GLFW_KEY_D) | state.wnd.GetKey(GLFW_KEY_RIGHT))
			velocity.x += 1.0f;

		if (player)
			player->SetLinearVelocity(velocity);

		ecs.Event(Event::Update);
	}
	inline void Tick() {
		ecs.Event(Event::Tick);
		world->Step(TICK_TIME, 8, 3);
	}
	inline void Render() {
		ecs.Event(Event::Render);
	}

	void SetBorder(const b2Vec2* vertices, int32 count) {
		b2BodyDef bdef;
		bdef.type = b2_staticBody;
		b2ChainShape shape;
		shape.CreateLoop(vertices, count);

		border = world->CreateBody(&bdef);
		border->CreateFixture(&shape, 0.0f);
	}
	void SetPlayer(b2Vec2 pos, b2Vec2 halfSize) {
		b2BodyDef bdef;
		bdef.type = b2_dynamicBody;
		bdef.position = pos;
		player = world->CreateBody(&bdef);

		b2CircleShape shape;
		shape.m_radius = halfSize.x;

		b2FixtureDef fdef;
		fdef.shape = &shape;
		fdef.density = 1.0f;
		fdef.friction = 0.0f;
		player->CreateFixture(&fdef);

		PhysicsComponent pc{
			.size = b2Vec2{ halfSize.x * 2.0f, halfSize.y * 2.0f },
			.halfSize = halfSize,
			.body = player
		};
		ecs.Add(entPlayer, Component::Physics, &pc);
		ecs.Add(entPlayer, Component::Sprite, nullptr);
	}
	void AddWall(b2Vec2 pos, b2Vec2 halfSize) {
		b2BodyDef bdef;
		bdef.type = b2_staticBody;
		bdef.position = pos;
		b2PolygonShape shape;
		shape.SetAsBox(halfSize.x, halfSize.y);

		b2Body* body = world->CreateBody(&bdef);
		body->CreateFixture(&shape, 0.0f);

		PhysicsComponent pc{
			.size = b2Vec2{ halfSize.x * 2.0f, halfSize.y * 2.0f },
			.halfSize = halfSize,
			.body = body
		};

		Entity e = ecs.New();
		ecs.Add(e, Component::Physics, &pc);
		ecs.Add(e, Component::Sprite, nullptr);
	}
private:
	ECS ecs;
	b2World* world;
	b2Body* border;
	b2Body* player;
	Entity entPlayer;
};
