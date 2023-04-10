#pragma once

#include "stdio.h"
#include "camera_config.h"
#include <GL\glew.h>
#include "glm/glm.hpp"
#include <GLFW\glfw3.h>

class Window
{
public:
	Window();
	Window(GLint width, GLint height);
	~Window();

public:
	bool OpenGLInit();
	bool GetShouldClose() const { return glfwWindowShouldClose(_window); }
	GLFWwindow* GetWindow() { return _window; }
	void SwapBuffers() { glfwSwapBuffers(_window); }

private:
	void CreateCallbacks();
	static void Window::HandlePressKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void Window::HandleMouseClickEvent(GLFWwindow* window, double pos_x, double pos_y);

public:
	GLint GetWidth() const { return _width; }
	void SetWidth(const GLint width) { _width = width; }

	GLint GetHeight() const { return _height; }
	void SetHeight(const GLint height) { _height = height;  }

	GLint GetBufferWidth() const { return _buffer_width; }
	void SetBufferWidth(const GLint buffer_width) { _buffer_width = buffer_width;  }

	GLint GetBufferHeight() const { return _buffer_height; }
	void SetBufferHeight(const GLint buffer_height) { _buffer_height = buffer_height;  }

	float GetYawAngle() const { return _yaw_angle; }
	void SetYawAngle(const float yaw_angle) { _yaw_angle = yaw_angle;  }

	float GetPitchAngle() const { return _pitch_angle; }
	void SetPitchAngle(const float pitch_angle) { _pitch_angle = pitch_angle;  }

	glm::vec2 GetLastMousePos() const { return _last_mouse_pos; }
	void SetLastMousePos(glm::vec2 last_mouse_pos) { _last_mouse_pos = last_mouse_pos;  }

	glm::vec2 GetDeltaMousePos() const { return _delta_mouse_pos;  }
	void SetDeltaMousePos(glm::vec2 delta_mouse_pos) { _delta_mouse_pos = delta_mouse_pos; }

	bool IsMiddleMouseClicked() const { return _middle_mouse_clicked;  }
	void SetMiddleMouseClicked(bool middle_mouse_clicked) { _middle_mouse_clicked = middle_mouse_clicked; }

	bool IsLeftMouseClicked() const { return _left_mouse_clicked; }
	void SetLeftMouseClicked(bool mouse_rotate) { _left_mouse_clicked = mouse_rotate;  }

	bool IsKeyPressed() const { return _key != KEY_TYPE::UNDEFINED;  }
	KEY_TYPE GetPressedKey() const { return _key;  }
	void SetPressedKey(KEY_TYPE key) { _key = key; }


private:
	GLint _width;
	GLint _height;
	GLint _buffer_width;
	GLint _buffer_height;
	GLFWwindow* _window;

	float _yaw_angle;
	float _pitch_angle;
	glm::vec2 _last_mouse_pos;
	glm::vec2 _delta_mouse_pos;
	
	bool _middle_mouse_clicked = false;
	bool _left_mouse_clicked = false;

	KEY_TYPE _key = KEY_TYPE::UNDEFINED;
};