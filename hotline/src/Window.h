#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, bool fullscreen);
	~Window() noexcept;
	void Loop();
public:
	void SetSizeCallback(GLFWframebuffersizefun func);
	void SetKeyCallback(GLFWkeyfun func);
	void SetCursorPosCallback(GLFWcursorposfun func);
	void SetMouseButtonCallback(GLFWmousebuttonfun func);
	void SetScrollCallback(GLFWscrollfun func);
private:
	static void GLFWErrorCallback(int error_code, const char* description);
private:
	GLFWwindow* m_Window;
};
