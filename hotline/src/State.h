#pragma once
#include <gfx/Renderer.h>
#include <Window.h>

struct State {
	Window wnd;
	Renderer renderer;
	class Stage* curStage;

	State();
};
extern struct State state;
