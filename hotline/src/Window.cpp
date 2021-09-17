#include <glad/gl.h>
#include "Window.h"
#include "Log.h"

Window::Window(int width, int height, bool fullscreen) {
	if (glfwInit() == GLFW_FALSE) {
		const char* error;
		glfwGetError(&error);
		EXIT_CRITICAL("%s", error);
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	m_Window = glfwCreateWindow(width, height, "Hotline", fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (m_Window == nullptr) {
		const char* error;
		glfwGetError(&error);
		EXIT_CRITICAL("%s", error);
	}
	glfwSetErrorCallback(GLFWErrorCallback);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);

	if (!gladLoadGL(glfwGetProcAddress))
		EXIT_CRITICAL("gladLoadGL() failed");
}

Window::~Window() noexcept {
	if (m_Window) glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Loop() {
	while (!glfwWindowShouldClose(m_Window)) {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}

void Window::SetSizeCallback(GLFWframebuffersizefun func) { glfwSetFramebufferSizeCallback(m_Window, func); }

void Window::SetKeyCallback(GLFWkeyfun func) { glfwSetKeyCallback(m_Window, func); }

void Window::SetCursorPosCallback(GLFWcursorposfun func) { glfwSetCursorPosCallback(m_Window, func); }

void Window::SetMouseButtonCallback(GLFWmousebuttonfun func) { glfwSetMouseButtonCallback(m_Window, func); }

void Window::SetScrollCallback(GLFWscrollfun func) { glfwSetScrollCallback(m_Window, func); }

void Window::GLFWErrorCallback(int error_code, const char* description) {
	LOG_ERROR("GLFW [code:%d]: %s", error_code, description);
}
