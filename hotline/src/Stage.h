#pragma once
#include <State.h>
#include <entity/ECS.h>
#include <box2d/box2d.h>
#include <gfx/Camera.h>

#include <set>
class ContactListener : public b2ContactListener {
public:
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {
		auto bodyA = contact->GetFixtureA()->GetBody();
		auto bodyB = contact->GetFixtureB()->GetBody();
		auto world = bodyA->GetWorld();
		if (bodyA->IsBullet()) {
			contact->SetEnabled(false);
			entityRemoveList.emplace(bodyA->GetUserData().entity);
			if (!bodyB->IsBullet()) {
				// bodyB damaged
				auto& ud = bodyB->GetUserData();
				
			}
		}
		if (bodyB->IsBullet()) {
			contact->SetEnabled(false);
			entityRemoveList.emplace(bodyB->GetUserData().entity);
			if (!bodyA->IsBullet()) {
				// bodyA damaged
			}
		}
	}
	std::set<entt::entity> entityRemoveList;
};

class Stage {
public:
	Stage()
		: world(new b2World({ 0.0f, 0.0f })), player(registry.create()), camera(glm::vec2(), glm::vec2(1.0f / 5.0f)) {
		state.renderer.texBank.Add({
			"player", "res/textures/spr_Player.png",
			"wood", "res/textures/spr_WoodFloor.png",
			"bullet", "res/textures/spr_Bullet.png",
			"cursor", "res/textures/sprCursor_strip13.png"
		});

		CreatePlayer("player", b2Vec2(1.0f, 1.0f), 0.25f);

		cursorAnim = Animation("cursor", glm::vec2(), glm::vec2(1.0f), 1.0f / 13.0f, 1.0f);

		registry.on_destroy<PhysicsComponent>().connect<[](entt::registry& r, entt::entity e) {
			auto& pc = r.get<PhysicsComponent>(e);
			pc.body->GetWorld()->DestroyBody(pc.body);
		}>();

		//world->SetContactListener(&cl);
	}
	Stage(const Stage&) = delete;
	Stage& operator=(const Stage&) = delete;
	~Stage() noexcept {
		delete world;
	}
	void Update(float dt) {
		for (auto e : cl.entityRemoveList) {
			registry.destroy(e);
			printf("entity %u destroyed\n", e);
		}
		cl.entityRemoveList.clear();

		// process input
		{
			auto& physics = registry.get<PhysicsComponent>(player);
			b2Body* b2player = physics.body;

			// move
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
				velocity = glm::normalize(velocity) * playerSpeed;
			b2player->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));

			// rotate
			auto& b2pos = b2player->GetPosition();
			glm::vec2 pos(b2pos.x, b2pos.y);
			glm::vec2 cursorPos = state.wnd.GetCursorPos() / glm::vec2(state.wnd.GetSize()) * 2.0f - 1.0f;
			cursorPos.y = -cursorPos.y;
			cursorPos += pos;

			float angle = 0.0f;
			glm::vec2 dir = cursorPos - pos;
			if (dir.x != 0.0f || dir.y != 0.0f) {
				dir = glm::normalize(dir);
				angle = atan2(dir.y, dir.x);
				b2player->SetTransform(b2pos, angle);
			}

			// attack

		}

		// update animations
		{
			auto view = registry.view<SpriteComponent>();
			for (auto e : view) {
				auto[sprite] = view.get(e);
				if (sprite.isAnimated)
					sprite.animation.Update(dt);
			}
		}

		// update cursor animation
		cursorAnim.Update(dt);
	}
	void Tick() {
		// b2world tick
		world->Step(TICK_TIME, 8, 3);
		// make camera follow player
		b2Vec2 b2playerPos = registry.get<PhysicsComponent>(player).body->GetPosition();
		camera.pos += (glm::vec2(b2playerPos.x, b2playerPos.y) - camera.pos) * cameraFollowDelay;
	}
	void Render() {
		// render sprites
		state.renderer.SetViewProj(camera.GetViewProj());
		{
			auto view = registry.view<SpriteComponent, PhysicsComponent>();
			for (auto e : view) {
				auto[sprite, physics] = view.get(e);
				auto& pos = physics.body->GetPosition();
				state.renderer.DrawSprite(glm::vec2(pos.x, pos.y),
					glm::vec2(physics.halfSize.x, physics.halfSize.y), physics.body->GetAngle(), sprite);
			}
		}
		// draw cursor
		state.renderer.SetViewProj(hudCamera.GetViewProj());
		state.renderer.DrawAnimation(state.wnd.GetCursorPos(), glm::vec2(12.0f, 12.0f), cursorAnim);
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

		entt::entity e = registry.create();
		registry.emplace<PhysicsComponent>(e, b2Vec2{ halfSize.x * 2.0f, halfSize.y * 2.0f }, halfSize, body);
		registry.emplace<SpriteComponent>(e, "wood", glm::vec2(), glm::vec2(1.0f));
	}
	void CreatePlayer(const std::string& texture, const b2Vec2& pos, float radius) {
		b2Body* b2player;
		b2BodyDef bdef;
		bdef.type = b2_dynamicBody;
		bdef.position = pos;
		b2player = world->CreateBody(&bdef);

		b2CircleShape shape;
		shape.m_radius = radius;

		b2FixtureDef fdef;
		fdef.shape = &shape;
		fdef.density = 1.0f;
		fdef.friction = 0.0f;
		b2player->CreateFixture(&fdef);

		registry.emplace<PhysicsComponent>(player, b2Vec2{ radius * 2.0f, radius * 2.0f }, b2Vec2{ radius, radius }, b2player);
		registry.emplace<SpriteComponent>(player, texture, glm::vec2(), glm::vec2(1.0f));
	}
public:
	entt::registry registry;

	b2World* world = nullptr;
	b2Body* border = nullptr;
	ContactListener cl;

	entt::entity player;
	Animation cursorAnim;

	OrthoCamera camera;
	HudCamera hudCamera;

	static constexpr float playerSpeed = 3.0f;
	static constexpr float cameraFollowDelay = 0.08f;
};

/*
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
*/
