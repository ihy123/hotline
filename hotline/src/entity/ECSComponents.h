#pragma once
#include <cstdint>
#include "components/Physics.h"
#include "components/Sprite.h"

enum class Component : uint32_t {
	// add components here
	Physics = 0,
	Sprite,
	COUNT
};

#define _ECS_DECL_COMPONENT(name) \
	extern void name##Init(class ECS& ecs); \
	name##Init(ecs)

inline static void _ECSInitComponents(class ECS& ecs) {
	// add components here also
	_ECS_DECL_COMPONENT(Physics);
	_ECS_DECL_COMPONENT(Sprite);
}

#undef _ECS_DECL_COMPONENT
