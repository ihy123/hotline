#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {
public:
	Window(const char* title, int width, int height, bool fullscreen);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window() noexcept;

	const glm::ivec2& GetSize() const { return m_Size; }
	const glm::vec2& GetCursorPos() const { return m_CursorPos; }
	inline bool GetKey(int key) const noexcept { return m_Keyboard[key]; }
	inline bool GetMouseButton(int button) const noexcept { return m_Mouse[button]; }

	inline void SetVsync(bool state) const noexcept { glfwSwapInterval((int)state); }
	inline void SetCursorEnabled(bool state) const noexcept { glfwSetInputMode(m_Window, GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED); }
	// this function automatically disables the cursor
	// because raw input in GLFW works only when the cursor is grabbed
	inline void SetMouseRawInput(bool state) const noexcept {
		if (glfwRawMouseMotionSupported()) {
			SetCursorEnabled(!state);
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, (int)state);
		}
	}
	inline void SetTitle(const char* title) const noexcept {
		glfwSetWindowTitle(m_Window, title);
	}

	inline int ShouldClose() const noexcept { return glfwWindowShouldClose(m_Window); }
	inline static void PollEvents() noexcept { glfwPollEvents(); }
	inline void SwapBuffers() const noexcept { glfwSwapBuffers(m_Window); }
public:
	void SetScrollCallback(GLFWscrollfun func) { glfwSetScrollCallback(m_Window, func); }
private:
	static void GLFWSizeCallback(GLFWwindow* window, int width, int height) noexcept;
	static void GLFWCursorPosCallback(GLFWwindow* window, double x, double y) noexcept;
	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;
	static void GLFWMouseCallback(GLFWwindow* window, int button, int action, int mods) noexcept;
private:
	GLFWwindow* m_Window;
	glm::ivec2 m_Size;
	glm::vec2 m_CursorPos;

	bool m_Keyboard[GLFW_KEY_LAST + 1];
	bool m_Mouse[GLFW_MOUSE_BUTTON_LAST + 1];
};
