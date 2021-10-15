#include "State.h"

State::State()
	: wnd(800, 600, false) {
	wnd.SetVsync(true);
}

State state;
