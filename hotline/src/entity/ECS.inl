#include <Log.h>
#include <errno.h>

#define ECS_COMPONENT_FLAG(component) (1u << (uint32_t)component)
#define ECS_CS_COMPONENT_SIZE(cs) ((cs).componentSize + sizeof(Entity))
#define ECS_CS_GET_ENTITY(cs, index) (*(Entity*)(((uint8_t*)cs.data) + index * ECS_CS_COMPONENT_SIZE(cs)))
#define ECS_CS_GET_COMPONENT(cs, index) (((uint8_t*)cs.data) + index * ECS_CS_COMPONENT_SIZE(cs) + sizeof(Entity))

inline void ECS::Delete(Entity e) {
	entities[e.id].entityState = (uint32_t)EntityState::None;
	free_ids.push_back(e);
}

inline void ECS::Add(Entity e, Component c, void* data) noexcept {
	Enable(e, c);
	auto& comp = components[(uint32_t)c];
	ECS_CS_GET_ENTITY(comp, e.id) = e;
	if (data)
		memcpy(ECS_CS_GET_COMPONENT(comp, e.id), data, comp.componentSize);
}

inline bool ECS::Has(Entity e, Component c) const noexcept {
	return entities[e.id].componentFlags & ECS_COMPONENT_FLAG(c);
}

inline void* ECS::Get(Entity e, Component c) const noexcept {
	return ECS_CS_GET_COMPONENT(components[(uint32_t)c], e.id);
}

inline void ECS::Enable(Entity e, Component c) noexcept {
	entities[e.id].componentFlags |= ECS_COMPONENT_FLAG(c);
}

inline void ECS::Disable(Entity e, Component c) noexcept {
	entities[e.id].componentFlags &= ~ECS_COMPONENT_FLAG(c);
}

inline void ECS::Event(::Event e) {
	for (uint32_t i = 0; i < (uint32_t)Component::COUNT; ++i) {
		auto& comp = components[i];
		auto f = comp.system.callbacks[(uint32_t)e];
		if (!f)
			continue;
		for (size_t j = 0; j < entities.size(); ++j) {
			Entity entity = ECS_CS_GET_ENTITY(comp, j);
			if (entities[j].entityState == (uint32_t)EntityState::Alive && Has(entity, (Component)i))
				f(this, ECS_CS_GET_COMPONENT(comp, j), entity);
		}
	}
}

template<class C>
inline void ECS::RegisterComponent(Component c, System system) noexcept {
	const size_t size = sizeof(C) * 2 + sizeof(uint32_t) * 2;
	void* data = malloc(size);
	if (data == nullptr)
		EXIT_CRITICAL("Memory allocation failed: %s", strerror(errno));
	memset(data, 0, size);
	components[(uint32_t)c] = {
		.system = system,
		.componentSize = sizeof(C),
		.capacity = 2,
		.data = data
	};
}

inline void ECS::ComponentStore::Grow() noexcept {
	capacity *= GrowthFactor;
	void* p = realloc(data, capacity * (componentSize + sizeof(Entity)));
	memset(reinterpret_cast<char*>(p) + count * ECS_CS_COMPONENT_SIZE(*this), 0, (capacity - count) * ECS_CS_COMPONENT_SIZE(*this));
	if (p == nullptr)
		EXIT_CRITICAL("Memory reallocation failed: %s", strerror(errno));
	data = p;
}

#undef ECS_COMPONENT_FLAG
#undef ECS_CS_COMPONENT_SIZE
#undef ECS_CS_GET_ENTITY
#undef ECS_CS_GET_COMPONENT
