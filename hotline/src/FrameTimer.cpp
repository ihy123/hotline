#include "FrameTimer.h"
#include "State.h"
#include <sstream>
#include <iomanip>

FrameTimer::FrameTimer() : time((float)glfwGetTime()), prevTime(time), prevMeasure(time) {}

void FrameTimer::Frame() {
	// get current time and calculate delta time
	prevTime = time;
	time = (float)glfwGetTime();
	dt = time - prevTime;

	// measure fps
	if constexpr (doMeasureFps) {
		++nFrames;
		measureDiff = time - prevMeasure;
		if (measureDiff >= fpsOutputDelay) {
			std::ostringstream ss;
			ss << "OpenGL [" << (int)((float)nFrames / measureDiff) << " fps]";
			state.wnd.SetTitle(ss.str().c_str());
			prevMeasure = time;
			nFrames = 0;
		}
	}
}
