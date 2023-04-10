#include "GraphicLib/includes/window.h"
#include <iostream>

namespace {
	const char* WINDOW_TITLE = "OpenGL";
}

Window::Window():
	_width(800),
	_height(600),
	_buffer_width(800),
	_buffer_height(600),
	_yaw_angle(0.0),
	_pitch_angle(0.0),
	_last_mouse_pos(glm::vec2(_width / 2.0, _height / 2.0))
{
}

Window::Window(GLint width, GLint height):
	_width(width),
	_height(height),
	_buffer_width(800),
	_buffer_height(600),
	_yaw_angle(0.0),
	_pitch_angle(0.0),
	_last_mouse_pos(glm::vec2(_width / 2.0, _height / 2.0))
{
}

bool Window::OpenGLInit()
{
	// GLFW init
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	// GLFW configuration
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// GLFW window creation
	_window = glfwCreateWindow(_width, _height, WINDOW_TITLE, NULL, NULL);
	if (_window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(_window);
	glfwGetFramebufferSize(_window, &_buffer_width, &_buffer_height);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowUserPointer(_window, this);
	glfwSetCursorPos(_window, _width / 2.0, _height / 2.0);
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
	CreateCallbacks();

	// GLEW init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwDestroyWindow(_window);
		glfwTerminate();
		return false;
	}

	// Define the viewport dimensions
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, _buffer_width, _buffer_height);
	return true;
}

void Window::CreateCallbacks()
{
	glfwSetKeyCallback(_window, HandlePressKeyEvent);
	glfwSetCursorPosCallback(_window, HandleMouseClickEvent);
}

void Window::HandlePressKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Window* this_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (glfwGetKey(this_window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		this_window->SetPressedKey(KEY_TYPE::KEY_W);
	}
	if (glfwGetKey(this_window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		this_window->SetPressedKey(KEY_TYPE::KEY_S);
	}
	if (glfwGetKey(this_window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		this_window->SetPressedKey(KEY_TYPE::KEY_A);
	}
	if (glfwGetKey(this_window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		this_window->SetPressedKey(KEY_TYPE::KEY_D);
	}
}

void Window::HandleMouseClickEvent(GLFWwindow* window, double pos_x, double pos_y)
{
	Window* this_window = static_cast<Window*>(glfwGetWindowUserPointer(window));
	this_window->SetMiddleMouseClicked(false);
	this_window->SetLeftMouseClicked(false);
	if (glfwGetMouseButton(this_window->GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == 1)
	{
		this_window->SetLeftMouseClicked(true);
		this_window->SetYawAngle(this_window->GetYawAngle() - (static_cast<float>(pos_x) - this_window->GetLastMousePos().x) * ROTATE_SENSITIVITY);
		this_window->SetPitchAngle(this_window->GetPitchAngle() + (static_cast<float>(pos_y) - this_window->GetLastMousePos().y) * ROTATE_SENSITIVITY);
	}
	else if (glfwGetMouseButton(this_window->GetWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == 1)
	{
		this_window->SetMiddleMouseClicked(true);
		this_window->SetDeltaMousePos(glm::vec2((static_cast<float>(pos_x) - this_window->GetLastMousePos().x) * PAN_BY_MOUSE_SENSITIVITY, (static_cast<float>(pos_y) - this_window->GetLastMousePos().y) * PAN_BY_MOUSE_SENSITIVITY));
	}
	this_window->SetLastMousePos(glm::vec2(static_cast<float>(pos_x), static_cast<float>(pos_y)));
}

Window::~Window()
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}
