#pragma once
#include "State.h"
#include <Stage.h>
#include "FrameTimer.h"

class Game {
public:
	Game() {
		Stage* stage = state.curStage = new Stage();

		stage->SetBorder({ 13.6f, 13.6f });

		//down
		stage->AddWall({ 6.5f, 2.1f }, { 4.5f, 0.1f });
		//up
		stage->AddWall({ 6.5f, 10.9f }, { 4.5f, 0.1f });
		// left
		stage->AddWall({ 2.1f, 7.1f }, { 0.1f, 3.9f });
		//right
		stage->AddWall({ 10.9f, 6.5f }, { 0.1f, 4.5f });
		//mid left
		stage->AddWall({ 4.35f, 6.1f }, { 0.65f, 0.1f });
		//mid vertical
		stage->AddWall({ 5.1f, 7.0f }, { 0.1f, 3.8f });
	}
	~Game() noexcept { delete state.curStage; }
	void Run() {
		float dt;
		while (!state.wnd.ShouldClose()) {
			Update();

			dt = frameTimer.dt;
			for (; dt >= TICK_TIME; dt -= TICK_TIME)
				Tick();

			Render();
		}
	}
	inline void Update() {
		state.wnd.PollEvents();
		frameTimer.Frame();
		state.curStage->Update(frameTimer.dt);
	}
	inline void Tick() {
		state.curStage->Tick();
	}
	inline void Render() {
		state.renderer.SetViewProj(state.curStage->camera.GetViewProj());
		state.renderer.Clear(abs(sin(frameTimer.time * 2.0f)), 0.0f, 1.0f, 1.0f);
		state.curStage->Render();
		state.wnd.SwapBuffers();
	}
private:
	FrameTimer frameTimer;
};
