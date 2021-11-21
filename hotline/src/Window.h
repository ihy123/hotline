#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, bool fullscreen);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window() noexcept;

	const glm::ivec2& GetSize() const { return m_Size; }
	const glm::vec2& GetCursorPos() const { return m_CursorPos; }
	inline bool GetKey(int key) const noexcept { return m_Keyboard[key]; }
	inline bool GetMouseButton(int button) const noexcept { return m_Mouse[button]; }

	inline void SetVsync(bool state) const noexcept { glfwSwapInterval(state); }
	inline void SetCursorEnabled(bool state) const noexcept { glfwSetInputMode(m_Window, GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED); }
	void SetMouseRawInput(bool state) const noexcept;

	inline int ShouldClose() const noexcept { return glfwWindowShouldClose(m_Window); }
	inline void PollEvents() const noexcept { glfwPollEvents(); }
	inline void SwapBuffers() const noexcept { glfwSwapBuffers(m_Window); }
public:
	void SetScrollCallback(GLFWscrollfun func) { glfwSetScrollCallback(m_Window, func); }
private:
	static void GLAD_API_PTR GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	static void GLFWErrorCallback(int error_code, const char* description);
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
