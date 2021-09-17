#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, bool fullscreen);
	~Window() noexcept;
	inline int ShouldClose() const noexcept { return glfwWindowShouldClose(m_Window); }
	inline void PollEvents() const noexcept { glfwPollEvents(); }
	inline void SwapBuffers() const noexcept { glfwSwapBuffers(m_Window); }
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
