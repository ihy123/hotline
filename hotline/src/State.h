#pragma once
#include <map>
#include <string>
#include <gfx/Renderer.h>
#include <Window.h>

struct State {
	Window wnd;
	Renderer renderer;
	std::map<std::string, Texture> textureBank;
	class Stage* curStage;

	State();
};
extern struct State state;
