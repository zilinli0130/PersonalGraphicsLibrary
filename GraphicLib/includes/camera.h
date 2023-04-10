#ifndef CAMERA_H
#define CAMERA_H

#include "camera_config.h"
#include "glm/glm.hpp"
#include <iostream>
class Camera
{
public:
	
	// Event Handlers
	virtual void RotationByMouseHandler(const float yaw, const float pitch) {};
	virtual void PanningByMouseHandler(const float delta_x, const float delta_y) {};
	virtual void PanningByPressedKeyHandler(const KEY_TYPE key) {};

	// Setters
	void SetViewCenter(const glm::vec3& view_center) { _view_center = view_center; }
	void SetEyePosition(const glm::vec3& eye) { _eye = eye; }
	void SetFOV(const float fov) { _fov = fov; }
	void SetRadius(const float radius);

	// Getters
	const glm::vec3 GetLookAtDirection() const { return _look_at_direction;  }
	const glm::vec3 GetRightDirection() const { return _right_direction; }
	const glm::vec3 GetUpDirection() const { return _up_direction; }
	
	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetEyePosition() const { return _eye; }
	glm::vec3 GetViewCenter() const { return _view_center; }
	
	float GetFOV() const { return _fov; }
	
private:
	virtual void UpdateCameraView() {}

protected:
	Camera();
	Camera(const glm::vec3& eye_position, const glm::vec3& view_center, const float radius);

protected:
	// Camera parameters
	glm::vec3 _eye;
	glm::vec3 _view_center;
	glm::vec3 _up_direction;
	glm::vec3 _right_direction;
	glm::vec3 _look_at_direction;
	
	// Euler angle (radians)
	float _radius;
	float _yaw_angle;
	float _pitch_angle;

	// FOV
	float _fov;
};

class OrbitCamera : public Camera
{
public:
	OrbitCamera();
	OrbitCamera(const glm::vec3& eye_position, const glm::vec3& view_center, const float radius);

	void RotationByMouseHandler(const float yaw, const float pitch) override;
	void PanningByMouseHandler(const float delta_x, const float delta_y) override;
	void PanningByPressedKeyHandler(const KEY_TYPE key) override;

private:
	void UpdateCameraView() override;

};

#endif

