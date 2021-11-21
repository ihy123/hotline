#pragma once
#include "ECSComponents.h"
#include <vector>

class Entity {
	friend class ECS;
	inline Entity(uint32_t id) noexcept : id(id) {}
	uint32_t id;
};

union System {
	using Callback = void(*)(ECS* ecs, void* component, Entity entity);
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

class ECS {
public:
	ECS() noexcept {
		memset(components, 0, sizeof(components));
		_ECSInitComponents(*this);
	}
	ECS(const ECS&) = delete;
	ECS& operator=(const ECS&) = delete;
	~ECS() noexcept {
		for (uint32_t i = 0; i < (uint32_t)Component::COUNT; ++i)
			free(components[i].data);
	}
	template<class C>
	inline void RegisterComponent(Component c, System system) noexcept;
	Entity New() {
		if (free_ids.empty()) {
			entities.emplace_back(0u, (uint32_t)EntityState::Alive);
			for (uint32_t i = 0; i < (uint32_t)Component::COUNT; ++i) {
				auto& comp = components[i];
				++comp.count;
				if (comp.count > comp.capacity)
					comp.Grow();
			}
			return (uint32_t)(entities.size() - 1);
		}

		Entity e = free_ids.back();
		free_ids.pop_back();
		entities[e.id] = { 0u, (uint32_t)EntityState::Alive };
		return e;
	}
	inline void Delete(Entity e);
	inline void Add(Entity e, Component c, void* data) noexcept;
	inline bool Has(Entity e, Component c) const noexcept;
	inline void* Get(Entity e, Component c) const noexcept;
	inline void Enable(Entity e, Component c) noexcept;
	inline void Disable(Entity e, Component c) noexcept;
	inline void Enable(Entity e) noexcept;
	inline void Disable(Entity e) noexcept;

	inline void Event(Event e);
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

		inline void Grow() noexcept;
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

#include "ECS.inl"
