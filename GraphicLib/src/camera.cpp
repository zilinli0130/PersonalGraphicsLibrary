#include "GraphicLib/includes/camera.h"
#include "glm/gtx/transform.hpp"

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(_eye, _view_center, _up_direction);
}

Camera::Camera():
	_eye(glm::vec3(0.0f, 0.0f, 0.0f)),
	_view_center(glm::vec3(0.0f, 0.0f, 0.0f)),
	_up_direction(glm::vec3(0.0f, 1.0f, 0.0f)),
	_look_at_direction(glm::vec3(0.0f, 0.0f, -1.0f)),
	_right_direction(glm::vec3(1.0f, 0.0f, 0.0f)),
	_yaw_angle(glm::pi<float>()),
	_pitch_angle(0)
{
	UpdateCameraView();
}

Camera::Camera(const glm::vec3& eye_position, const glm::vec3& view_center, const float radius):
	_eye(eye_position),
	_view_center(view_center),
	_radius(radius)
{
}

void Camera::SetRadius(const float radius)
{
	_radius = glm::clamp(radius, 2.0f, 80.0f);
}

OrbitCamera::OrbitCamera()
{
}

OrbitCamera::OrbitCamera(const glm::vec3& eye_position, const glm::vec3& view_center, const float radius):
	Camera(eye_position, view_center, radius)
{
	UpdateCameraView();
}

void OrbitCamera::RotationByMouseHandler(const float yaw, const float pitch)
{
	_yaw_angle = glm::radians(yaw);
	_pitch_angle = glm::radians(pitch);
	_pitch_angle = glm::clamp(_pitch_angle, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);

	_eye.x = _view_center.x + _radius * cosf(_pitch_angle) * sinf(_yaw_angle);
	_eye.y = _view_center.y + _radius * sinf(_pitch_angle);
	_eye.z = _view_center.z + _radius * cosf(_pitch_angle) * cosf(_yaw_angle);

	UpdateCameraView();
}

void OrbitCamera::PanningByMouseHandler(const float delta_x, const float delta_y)
{
	_eye -= glm::normalize(_right_direction) * delta_x;
	_eye += glm::normalize(_up_direction) * delta_y;
	_view_center = _eye + _look_at_direction;
}

void OrbitCamera::PanningByPressedKeyHandler(const KEY_TYPE key)
{
	switch (key)
	{
		case KEY_TYPE::KEY_W:
			_eye += glm::normalize(_look_at_direction) * PAN_BY_KEY_SENSITIVITY;
			break;
		case KEY_TYPE::KEY_S:
			_eye -= glm::normalize(_look_at_direction) * PAN_BY_KEY_SENSITIVITY;
			break;
		case KEY_TYPE::KEY_A:
			_eye += glm::normalize(_right_direction) * PAN_BY_KEY_SENSITIVITY;
			break;
		case KEY_TYPE::KEY_D:
			_eye -= glm::normalize(_right_direction) * PAN_BY_KEY_SENSITIVITY;
			break;
		default:
			break;
	}
	_view_center = _eye + _look_at_direction;
}

void OrbitCamera::UpdateCameraView()
{
	_look_at_direction = _view_center - _eye;
	_right_direction = glm::cross(_look_at_direction, WORLD_UP_DIRECTION);
	_up_direction = glm::cross(_right_direction, _look_at_direction);
}


