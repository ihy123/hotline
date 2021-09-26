#include "Position.h"
#include <entity/ECS.h>

void PositionInit(ECS& ecs) {
	ecs.RegisterComponent<PositionComponent>(Component::Position, System{
		.onUpdate = nullptr,
		.onTick = nullptr,
		.onRender = nullptr
	});
}
