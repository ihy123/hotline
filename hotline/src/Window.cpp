#include <glad/gl.h>
#include "Window.h"
#include "Log.h"

Window::Window(int width, int height, bool fullscreen)
	: m_Size(width, height) {
	if (glfwInit() == GLFW_FALSE) {
		const char* error;
		glfwGetError(&error);
		EXIT_CRITICAL("%s", error);
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
#ifndef NDEBUG
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#endif
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

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, (GLFWframebuffersizefun)GLFWSizeCallback);
	glfwSetCursorPosCallback(m_Window, (GLFWcursorposfun)GLFWCursorPosCallback);
	glfwSetKeyCallback(m_Window, (GLFWkeyfun)GLFWKeyCallback);
	glfwSetMouseButtonCallback(m_Window, (GLFWmousebuttonfun)GLFWMouseCallback);

	if (!gladLoadGL(glfwGetProcAddress))
		EXIT_CRITICAL("gladLoadGL() failed");

#ifndef NDEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback((GLDEBUGPROC)GLDebugCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif
}

Window::~Window() noexcept {
	if (m_Window) glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::SetMouseRawInput(bool state) const noexcept {
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, (int)state);
}

void GLAD_API_PTR Window::GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			LOG_CRITICAL("OpenGL: %s", message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			LOG_ERROR("OpenGL: %s", message);
			break;
		default:
			LOG_INFO("OpenGL: %s", message);
			break;
	}
}

void Window::GLFWErrorCallback(int error_code, const char* description) {
	LOG_ERROR("GLFW [code:%d]: %s", error_code, description);
}

void Window::GLFWSizeCallback(GLFWwindow* window, int width, int height) noexcept {
	auto& size = ((Window*)glfwGetWindowUserPointer(window))->m_Size;
	size.x = width;
	size.y = height;
	glViewport(0, 0, width, height);
}

void Window::GLFWCursorPosCallback(GLFWwindow* window, double x, double y) noexcept {
	auto& pos = ((Window*)glfwGetWindowUserPointer(window))->m_CursorPos;
	pos.x = (float)x;
	pos.y = (float)y;
}

void Window::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept {
	auto& keys = ((Window*)glfwGetWindowUserPointer(window))->m_Keyboard;
	switch (action) {
		case GLFW_PRESS:
			keys[key] = true;
			break;
		//case GLFW_REPEAT:
		//	break;
		case GLFW_RELEASE:
			keys[key] = false;
			break;
	}
}

void Window::GLFWMouseCallback(GLFWwindow* window, int button, int action, int mods) noexcept {
	auto& mouse = ((Window*)glfwGetWindowUserPointer(window))->m_Mouse;
	switch (action) {
		case GLFW_PRESS:
			mouse[button] = true;
			break;
		//case GLFW_REPEAT:
		//	break;
		case GLFW_RELEASE:
			mouse[button] = false;
			break;
	}
}
