#pragma once
#include <State.h>
#include <entity/ECS.h>
#include <box2d/box2d.h>
#include <State.h>

class Stage {
public:
	Stage() : world(new b2World({ 0.0f, 0.0f })), entPlayer(ecs.New()), entCamera(ecs.New()) {
		state.textureBank.emplace("player", Texture("res/textures/spr_Player.png"));
		state.textureBank.emplace("wood", Texture("res/textures/spr_WoodFloor.png"));
	}
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;
	~Stage() noexcept { delete world; }
	inline void Update() {
		ecs.Event(Event::Update);
	}
	inline void Tick() {
		ecs.Event(Event::Tick);
		world->Step(TICK_TIME, 8, 3);
	}
	inline void Render() {
		auto& pos = reinterpret_cast<PhysicsComponent*>(ecs.Get(entCamera, Component::Physics))->body->GetPosition();
		state.renderer.SetViewProj({ pos.x, pos.y });
		ecs.Event(Event::Render);
	}

	void SetBorder(const b2Vec2* vertices, int32 count) {
		b2Body* border;
		b2BodyDef bdef;
		bdef.type = b2_staticBody;
		b2ChainShape shape;
		shape.CreateLoop(vertices, count);

		border = world->CreateBody(&bdef);
		border->CreateFixture(&shape, 0.0f);
	}
	void SetPlayer(b2Vec2 pos, b2Vec2 halfSize) {
		b2Body* player;
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
		SpriteComponent sc{
			.tex = state.textureBank["player"],
			.uv_min = { 0.0f, 0.0f },
			.uv_max = { 1.0f, 1.0f }
		};
		PlayerControlComponent pcc{ .speed = 3.0f };

		ecs.Add(entPlayer, Component::Physics, &pc);
		ecs.Add(entPlayer, Component::Sprite, &sc);
		ecs.Add(entPlayer, Component::PlayerControl, &pcc);

		SetCamera();
	}
	void SetCamera() {
		auto target = reinterpret_cast<PhysicsComponent*>(ecs.Get(entPlayer, Component::Physics));
		b2Body* camera;
		b2BodyDef bdef;
		bdef.type = b2_kinematicBody;
		bdef.position = target->body->GetPosition();
		camera = world->CreateBody(&bdef);

		PhysicsComponent pc{
			.size = { 0.0f, 0.0f },
			.halfSize = { 0.0f, 0.0f },
			.body = camera
		};
		FollowComponent fc{
			.target = target,
			.speed = 0.1f
		};

		ecs.Add(entCamera, Component::Physics, &pc);
		ecs.Add(entCamera, Component::Follow, &fc);
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
		SpriteComponent sc{
			.tex = state.textureBank["wood"],
			.uv_min = { 0.0f, 0.0f },
			.uv_max = { 1.0f, 1.0f }
		};

		Entity e = ecs.New();
		ecs.Add(e, Component::Physics, &pc);
		ecs.Add(e, Component::Sprite, &sc);
	}
private:
	ECS ecs;
	b2World* world;
	Entity entPlayer;
	Entity entCamera;
};
