#pragma once
#include <State.h>

class Weapon {
public:
	void Update(float dt) {
		attackTime += dt;
		if (state.wnd.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
			if (attackTime >= attackDelay) {
				attackTime = 0.0f;
				Attack();
			}
		}
	}
	virtual void Attack() = 0;
	float attackDelay, attackTime;
};
