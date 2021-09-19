#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, bool fullscreen);
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;
	~Window() noexcept;

	const glm::ivec2& GetSize() const { return m_Size; }
	const glm::vec2& GetCursorPos() const { return m_CursorPos; }

	inline void SetVsync(bool state) const noexcept { glfwSwapInterval(state); }

	inline int ShouldClose() const noexcept { return glfwWindowShouldClose(m_Window); }
	inline void PollEvents() const noexcept { glfwPollEvents(); }
	inline void SwapBuffers() const noexcept { glfwSwapBuffers(m_Window); }
public:
	void SetKeyCallback(GLFWkeyfun func) { glfwSetKeyCallback(m_Window, func); }
	void SetMouseButtonCallback(GLFWmousebuttonfun func) { glfwSetMouseButtonCallback(m_Window, func); }
	void SetScrollCallback(GLFWscrollfun func) { glfwSetScrollCallback(m_Window, func); }
private:
	static void GLAD_API_PTR GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	static void GLFWErrorCallback(int error_code, const char* description);
	static void GLFWSizeCallback(GLFWwindow* window, int width, int height) noexcept;
	static void GLFWCursorPosCallback(GLFWwindow* window, double x, double y) noexcept;
private:
	GLFWwindow* m_Window;
	glm::ivec2 m_Size;
	glm::vec2 m_CursorPos;
};
