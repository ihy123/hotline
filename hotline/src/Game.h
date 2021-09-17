#pragma once
#include "Window.h"

class Game {
public:
	Game() : wnd(800, 600, false) {

	}
	~Game() {

	}
	void Run() {
		wnd.Loop();
	}
private:
	Window wnd;
};
