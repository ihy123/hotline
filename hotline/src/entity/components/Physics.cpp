#include "Physics.h"
#include <entity/ECS.h>

void PhysicsInit(ECS& ecs) {
	ecs.RegisterComponent<PhysicsComponent>(Component::Physics, System{
		.onUpdate = nullptr,
		.onTick = nullptr,
		.onRender = nullptr
	});
}
