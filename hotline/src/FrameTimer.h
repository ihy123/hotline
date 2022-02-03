#pragma once
#include <cstdint>

class FrameTimer {
public:
	FrameTimer();
	void Frame();
public:
	static constexpr bool doMeasureFps = true;
	static constexpr float fpsOutputDelay = 2.0f; // seconds
	float time, prevTime, dt = 0.0f;
private:
	float prevMeasure, measureDiff = 0.0f;
	size_t nFrames = 0;
};
