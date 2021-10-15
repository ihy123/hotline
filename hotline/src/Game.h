#pragma once
#include "State.h"
#include <Stage.h>

class Game {
public:
	Game() {
		state.curStage = new Stage();
		state.curStage->SetPlayer({ 0.0f, 0.0f }, { 0.25f, 0.25f });
		state.curStage->AddWall({ 4.0f, 4.0f }, { 1.5f, 1.5f });
	}
	~Game() noexcept { delete state.curStage; }
	void Run() {
		float dt = 0.0f, time, prevTime = (float)glfwGetTime();
		while (!state.wnd.ShouldClose()) {
			Update();

			time = (float)glfwGetTime();
			dt += time - prevTime; // ms
			prevTime = time;
			for (; dt >= TICK_TIME; dt -= TICK_TIME)
				Tick();

			Render();
		}
	}
	inline void Update() {
		state.wnd.PollEvents();
		state.curStage->Update();
	}
	inline void Tick() {
		state.curStage->Tick();
	}
	inline void Render() {
		state.renderer.Prepare();
		state.curStage->Render();
		state.wnd.SwapBuffers();
	}
};
