#include <entity/ECS.h>

void HealthInit(ECS& ecs) {
	ecs.RegisterComponent<HealthComponent>(Component::Health, System{
		.onUpdate = nullptr,
		.onTick = nullptr,
		.onRender = nullptr
	});
}
