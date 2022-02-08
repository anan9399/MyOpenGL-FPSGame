#include "Camera.h"


Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 worldup) {
	Position = _position;
	Forward = glm::normalize(_target - Position);
	WorldUp = worldup;
	Right = glm::normalize(glm::cross(Position, Forward));
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera::Camera(glm::vec3 _position,float pitch,float yaw, glm::vec3 worldup) {
	Position = _position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}


Camera::~Camera(){}

glm::mat4 Camera:: GetViewMatrix() {
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::UpdateCameraVectors() {
	Forward.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));

}

void Camera::UpdateCameraPos(float nowy,float dt) {
	tHeight = nowy;
	if (abs(shock + shock_step) > 0.2)
		shock_step = -shock_step;
	shock += shock_step;
	Position += WorldUp * SpeedY;

	Position.y += gravity;
	//	
	float PosY = Position.y;
	if (PosY < nowy + 5.0f) {
		//isJump = false;
		PosY = nowy + 5.0f;
	}
	//bounder check
	if (Position.x < 2)
		Position.x = 2;
	if (Position.x > 699)
		Position.x = 699;
	if (Position.z < 2)
		Position.z = 2;
	if (Position.z > 699)
		Position.z = 699;


	
	//if (SpeedZ != 0 || SpeedX != 0) {
	//	Position.y = PosY + shock;
	//}
	//else {
		Position.y = PosY;

	//jump check
	jump(nowy);

}

void Camera::MoveForward(float dt)
{
	Position += Forward * cameraSpeed * dt;
}

void Camera::MoveRight(float dt)
{
	Position += Right * cameraSpeed * dt;
}

void Camera::jump(float nowy)
{
	if (isJump) {
		upwardSpeed += 0.02f;
		Position.y += (1.0f - upwardSpeed);
		if (Position.y < nowy + 7.0f) {
			upwardSpeed = 0.0f;
			Position.y = nowy + 7.0f;
			isJump = false;
		}
	
	}
	else
	{
		Position.y = nowy + 7.0f;
		inAir = false;
	}
}

void Camera::inversePitch()
{
	if (invert == 0)
		invert = 1;
	else
		invert = 0;
}

void Camera::ProcessMouseScroll(float yoffset) {
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	if (invert == 0)
		Pitch += deltaY * sensitivity;
	else
		Pitch -= deltaY * sensitivity;
	Yaw += deltaX * sensitivity;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	UpdateCameraVectors();
}

