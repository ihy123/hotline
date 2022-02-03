#include "State.h"

State::State()
	: wnd("Hotline", 800, 600, false) {
	wnd.SetVsync(true);
}

struct State state;
