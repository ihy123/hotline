#pragma once
#include "Texture.h"
#include <map>
#include <string>

class TextureBank {
public:
	TextureBank() = default;
	TextureBank(std::initializer_list<std::string_view> namesAndPaths) {
		Add(namesAndPaths);
	}
	TextureBank(const TextureBank&) = delete;
	TextureBank& operator=(const TextureBank&) = delete;

	inline void Add(std::string_view name, std::string_view path) {
		m_Container.emplace(name, path.data());
	}
	void Add(std::initializer_list<std::string_view> namesAndPaths) {
		assert((namesAndPaths.size() % 2 == 0) &&
			"pass name string then pass path string, then name of the next texture etc...");
		for (auto it = namesAndPaths.begin(); it != namesAndPaths.end(); it += 2)
			Add(*it, *(it + 1));
	}

	inline Texture& Get(const std::string& name) {
		return m_Container[name];
	}
private:
	std::map<std::string, Texture> m_Container;
};
