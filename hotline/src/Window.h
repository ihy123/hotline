#pragma once
#include "Log.h"
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, bool fullscreen) {
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

		//glfwSetFramebufferSizeCallback;
		//glfwSetKeyCallback;
		//glfwSetCharCallback;
		//glfwSetCursorPosCallback;
		//glfwSetMouseButtonCallback;
		//glfwSetScrollCallback;

		glfwSwapInterval(1);
	}
	~Window() noexcept {
		if (m_Window) glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void Loop() {
		while (!glfwWindowShouldClose(m_Window)) {
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
	}
private:
	static void GLFWErrorCallback(int error_code, const char* description) {
		LOG_ERROR("GLFW [code:%d]: %s", error_code, description);
	}
private:
	GLFWwindow* m_Window;
};
