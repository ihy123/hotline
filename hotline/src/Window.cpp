#include <glad/gl.h>
#include "Window.h"
#include "Log.h"

static void GLAD_API_PTR GLDebugCallback(GLenum, GLenum, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*) {
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH_ARB:
			LOG_CRITICAL("OpenGL: %s", message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM_ARB:
			LOG_ERROR("OpenGL: %s", message);
			break;
		default:
			LOG_INFO("OpenGL: %s", message);
			break;
	}
}

static void GLFWErrorCallback(int error_code, const char* description) {
	LOG_ERROR("GLFW [code:%d]: %s", error_code, description);
}

Window::Window(const char* title, int width, int height, bool fullscreen)
	: m_Size(width, height) {
	// init glfw
	if (!glfwInit()) {
		const char* error;
		glfwGetError(&error);
		EXIT_CRITICAL("%s", error);
	}
	// set opengl 3.3
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// set core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// make context forward compat
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	// create the window
	m_Window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!m_Window) {
		const char* error;
		glfwGetError(&error);
		EXIT_CRITICAL("%s", error);
	}
	// set glfw error callback to catch runtime errors
	glfwSetErrorCallback(GLFWErrorCallback);
	// make window current
	glfwMakeContextCurrent(m_Window);

	// set callbacks
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, (GLFWframebuffersizefun)GLFWSizeCallback);
	glfwSetCursorPosCallback(m_Window, (GLFWcursorposfun)GLFWCursorPosCallback);
	glfwSetKeyCallback(m_Window, (GLFWkeyfun)GLFWKeyCallback);
	glfwSetMouseButtonCallback(m_Window, (GLFWmousebuttonfun)GLFWMouseCallback);

	// init glad
	if (!gladLoadGL(glfwGetProcAddress))
		EXIT_CRITICAL("gladLoadGL() failed");

	// enable debug callback when in debug mode and needed extension is present
#ifndef NDEBUG
	if (GLAD_GL_ARB_debug_output) {
		//glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW_ARB, 0, nullptr, GL_FALSE);
		glDebugMessageCallbackARB(GLDebugCallback, nullptr);
	}
#endif
}

Window::~Window() noexcept {
	if (m_Window)
		glfwDestroyWindow(m_Window);
	glfwTerminate();
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
