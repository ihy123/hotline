#pragma once
#include "Physics.h"

struct FollowComponent {
	PhysicsComponent* target;
	float speed;
};
