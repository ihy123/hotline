#pragma once
#include <cstdint>
#include "components/Physics.h"
#include "components/Sprite.h"
#include "components/PlayerControl.h"
#include "components/Follow.h"
#include "components/Combat.h"
#include "components/Health.h"

enum class Component : uint32_t {
	// add components here
	Physics = 0,
	Sprite,
	PlayerControl,
	Follow,
	Combat,
	Health,
	COUNT
};

#define _ECS_DECL_COMPONENT(name) \
	extern void name##Init(class ECS& ecs); \
	name##Init(ecs)

inline static void _ECSInitComponents(class ECS& ecs) {
	// add components here also
	_ECS_DECL_COMPONENT(Physics);
	_ECS_DECL_COMPONENT(Sprite);
	_ECS_DECL_COMPONENT(PlayerControl);
	_ECS_DECL_COMPONENT(Follow);
	_ECS_DECL_COMPONENT(Combat);
	_ECS_DECL_COMPONENT(Health);
}

#undef _ECS_DECL_COMPONENT
