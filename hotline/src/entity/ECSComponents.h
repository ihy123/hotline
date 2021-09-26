#pragma once
#include <stdint.h>
#include "components/Position.h"

enum class Component : uint32_t {
	Position = 0,
	COUNT
};

#define _ECS_DECL_COMPONENT(name) \
	extern void name##Init(class ECS& ecs); \
	name##Init(ecs)

inline static void ECSInitComponents(class ECS& ecs) {
	_ECS_DECL_COMPONENT(Position);
}
