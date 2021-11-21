#pragma once
#include <State.h>
#include <entity/ECS.h>
#include <box2d/box2d.h>
#include <State.h>
#include <entity/Player.h>
#include <entity/Camera.h>

#include <set>
class ContactListener : public b2ContactListener {
public:
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {
		auto bodyA = contact->GetFixtureA()->GetBody();
		auto bodyB = contact->GetFixtureB()->GetBody();
		auto world = bodyA->GetWorld();
		if (bodyA->IsBullet()) {
			contact->SetEnabled(false);
			bodyRemoveList.emplace(bodyA);
			if (!bodyB->IsBullet()) {
				// bodyB damaged
			}
		}
		if (bodyB->IsBullet()) {
			contact->SetEnabled(false);
			bodyRemoveList.emplace(bodyB);
			if (!bodyA->IsBullet()) {
				// bodyA damaged
			}
		}
	}
	std::set<b2Body*> bodyRemoveList;
};

class Stage {
public:
	Stage()
		: world(new b2World({ 0.0f, 0.0f })), player(ecs), camera(ecs) {
		state.textureBank.emplace("player", Texture("res/textures/spr_Player.png"));
		state.textureBank.emplace("wood", Texture("res/textures/spr_WoodFloor.png"));
		state.textureBank.emplace("bullet", Texture("res/textures/spr_Bullet.png"));

		world->SetContactListener(&cl);

		player.Init(world, { 1.0f, 1.0f }, 0.25f, 3.0f,
			&state.textureBank["player"], {0.0f, 0.0f}, {1.0f, 1.0f});
		camera.Init(world, player, 0.1f);
	}
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;
	~Stage() noexcept { delete world; }
	inline void Update() {
		for (auto e : cl.bodyRemoveList) {
			world->DestroyBody(e);
		}
		cl.bodyRemoveList.clear();
		ecs.Event(Event::Update);
	}
	inline void Tick() {
		ecs.Event(Event::Tick);
		world->Step(TICK_TIME, 8, 3);
	}
	inline void Render() {
		state.renderer.SetViewProj(camera.GetViewProj());
		ecs.Event(Event::Render);
	}
	void SetBorder(b2Vec2 size) {
		const b2Vec2 vertices[]{
			{ 0.0f, 0.0f },
			{ 0.0f, size.y },
			{ size.x, size.y },
			{ size.x, 0.0f }
		};
		constexpr int32 count = sizeof(vertices) / sizeof(*vertices);

		b2BodyDef bdef;
		bdef.type = b2_staticBody;
		b2ChainShape shape;
		shape.CreateLoop(vertices, count);

		if (border != nullptr)
			world->DestroyBody(border);
		border = world->CreateBody(&bdef);
		border->CreateFixture(&shape, 0.0f);
	}
	void AddWall(b2Vec2 center, b2Vec2 halfSize) {
		b2BodyDef bdef;
		bdef.type = b2_staticBody;
		bdef.position = center;
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
			.tex = &state.textureBank["wood"],
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
	b2Body* border;
	Player player;
	Camera camera;
	ContactListener cl;
};
