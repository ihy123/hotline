#pragma once
#include "ECSComponents.h"
#include <vector>

class Entity {
	friend class ECS;
	Entity(uint32_t id) noexcept : id(id) {}
	uint32_t id;
};

union System {
	using Callback = void(*)(void* component, Entity entity);
	struct {
		Callback onUpdate, onTick, onRender;
	};
	Callback callbacks[3];
};

enum class Event : uint32_t {
	Update = 0,
	Tick,
	Render
};

#define ECS_COMPONENT_FLAG(component) (1u << (uint32_t)component)
#define ECS_CS_COMPONENT_SIZE(cs) (cs.componentSize + sizeof(Entity))
#define ECS_CS_GET_ENTITY(cs, index) (*(Entity*)(((uint8_t*)cs.data) + index * ECS_CS_COMPONENT_SIZE(cs)))
#define ECS_CS_GET_COMPONENT(cs, index) (((uint8_t*)cs.data) + index * ECS_CS_COMPONENT_SIZE(cs) + sizeof(Entity))

class ECS {
public:
	ECS() noexcept {
		memset(components, 0, sizeof(components));
		ECSInitComponents(*this);
	}
	~ECS() noexcept {
		for (uint32_t i = 0; i < (uint32_t)Component::COUNT; ++i)
			free(components[i].data);
	}
	template<class C>
	inline void RegisterComponent(Component c, System system) noexcept {
		components[(uint32_t)c] = {
			.system = system,
			.componentSize = sizeof(C),
			.capacity = 2,
			.data = malloc(sizeof(C) * 2 + sizeof(uint32_t) * 2)
		};
	}
	Entity NewEntity() {
		if (free_ids.empty()) {
			entities.emplace_back(0u, (uint32_t)EntityState::Alive);
			for (uint32_t i = 0; i < (uint32_t)Component::COUNT; ++i) {
				auto& comp = components[i];
				++comp.count;
				if (comp.count > comp.capacity)
					comp.Grow();
			}
			return entities.size() - 1;
		}

		Entity e = free_ids.back();
		free_ids.pop_back();
		entities[e.id] = { 0u, (uint32_t)EntityState::Alive };
		return e;
	}
	inline void RemoveEntity(Entity e) {
		entities[e.id].entityState = (uint32_t)EntityState::None;
		free_ids.push_back(e);
	}
	inline void AddComponent(Entity e, Component c, void* data) noexcept {
		ActivateComponent(e, c);
		auto& comp = components[(uint32_t)c];
		ECS_CS_GET_ENTITY(comp, e.id) = e;
		memcpy(ECS_CS_GET_COMPONENT(comp, e.id), data, comp.componentSize);
	}
	inline bool HasComponent(Entity e, Component c) const noexcept {
		return entities[e.id].componentFlags & ECS_COMPONENT_FLAG(c);
	}
	inline void* GetComponent(Entity e, Component c) const noexcept {
		return ECS_CS_GET_COMPONENT(components[(uint32_t)c], e.id);
	}
	// reverts DisableComponent()
	inline void ActivateComponent(Entity e, Component c) noexcept {
		entities[e.id].componentFlags |= ECS_COMPONENT_FLAG(c);
	}
	// makes system ignore this component
	inline void DisableComponent(Entity e, Component c) noexcept {
		entities[e.id].componentFlags &= ~ECS_COMPONENT_FLAG(c);
	}

	inline void Event(Event e) const {
		for (uint32_t i = 0; i < (uint32_t)Component::COUNT; ++i) {
			auto& comp = components[i];
			auto f = comp.system.callbacks[(uint32_t)e];
			if (!f)
				continue;
			for (size_t j = 0; j < entities.size(); ++j) {
				Entity entity = ECS_CS_GET_ENTITY(comp, j);
				if (entities[j].entityState == (uint32_t)EntityState::Alive && HasComponent(entity, (Component)i))
					f(ECS_CS_GET_COMPONENT(comp, j), entity);
			}
		}
	}
private:
	enum class EntityState : uint32_t {
		None = 0,
		Alive,
		Inactive
	};
private:
	struct ComponentStore {
		static constexpr size_t GrowthFactor = 2;

		System system;
		size_t componentSize, count, capacity;
		void* data;

		inline void Grow() noexcept {
			capacity *= GrowthFactor;
			data = realloc(data, capacity * (componentSize + sizeof(Entity)));
		}
	};
private:
	struct EntityStore {
		uint32_t componentFlags, entityState;
	};
private:
	std::vector<EntityStore> entities;
	std::vector<Entity> free_ids;
	ComponentStore components[(uint32_t)Component::COUNT];
};
