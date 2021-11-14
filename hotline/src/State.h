#pragma once
#include <map>
#include <string>
#include <gfx/Renderer.h>
#include <Window.h>

static constexpr float TICK_TIME = 1.0f / 120.0f;

struct State {
	Window wnd;
	Renderer renderer;
	std::map<std::string, Texture> textureBank;
	class Stage* curStage;

	State();
};
extern struct State state;
