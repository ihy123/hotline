#pragma once
#include "gfx/Renderer.h"
#include "Window.h"

class Game {
public:
	Game() : wnd(800, 600, false) {}
	void Run() {
		while (!wnd.ShouldClose()) {
			wnd.PollEvents();
			renderer.Draw();
			wnd.SwapBuffers();
		}
	}
private:
	Window wnd;
	Renderer renderer;
};
