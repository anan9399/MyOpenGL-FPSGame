#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:
	Camera(glm::vec3 _position, float pitch, float yaw,glm::vec3 worldup);
	Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 worldup);
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	int invert = 0;
	float Zoom = 45.0f;
	float Pitch, Yaw;
	float SpeedX=0,SpeedY=0,SpeedZ=0;
	bool isJump = false, inAir = false;
	float upwardSpeed = 0.0f;
    glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float deltaX,float deltaY);
	void UpdateCameraPos(float nowy, float dt);
	void MoveForward(float dt);
	void MoveRight(float dt);
	void jump(float nowy);
	void inversePitch();
	void ProcessMouseScroll(float yoffset);

private:
	float sensitivity = 0.05f;
	void UpdateCameraVectors();
	float shock = 0, shock_step = 0.01f;
	float cameraSpeed = 0.5;
	float gravity = -0.5f;
	float tHeight = 0.0f;
};