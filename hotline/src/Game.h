#pragma once
#include <gfx/Renderer.h>
#include "Window.h"

class Game {
public:
	Game()
		: wnd(800, 600, false),
		  floor("res/textures/spr_WoodFloor.png"),
		  cursor("res/textures/spr_Cursor.png") {
		wnd.SetVsync(true);
	}
	void Run() {
		while (!wnd.ShouldClose()) {
			wnd.PollEvents();
			renderer.Prepare();

			renderer.TexturedQuad(cursor, { 0.04f, 0.04f },
				glm::translate(glm::identity<glm::mat4>(), { wnd.GetCursorPos().x / (float)wnd.GetSize().x - 0.02f, 1.0f - wnd.GetCursorPos().y / (float)wnd.GetSize().y - 0.02f, 0.0f }),
				{ 0.0f, 0.0f }, { 1.0f, 1.0f });
			wnd.SwapBuffers();
		}
	}
private:
	Window wnd;
	Renderer renderer;
	Texture floor, cursor;
};
