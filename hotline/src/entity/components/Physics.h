#pragma once
#include <box2d/box2d.h>

struct PhysicsComponent {
	b2Vec2 size, halfSize;
	b2Body* body;
};
