#include "Camera.h"
#include "AppWindow.h"
#include "InputSystem.h"
#include <iostream>
#include "EngineTime.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	/*this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);*/

	this->setPosition(0.0f, 5.0f, -10.0f);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update()
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;

	float deltaTime = EngineTime::getDeltaTime();

	if (InputSystem::getInstance()->isKeyDown('W')) {
		//std::cout << "W...\n";
		Vector3D direction = m_matrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * moveSpeed,
			y + direction.m_y * deltaTime * moveSpeed,
			z + direction.m_z * deltaTime * moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		Vector3D direction = m_matrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * -moveSpeed,
			y + direction.m_y * deltaTime * -moveSpeed,
			z + direction.m_z * deltaTime * -moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		Vector3D direction = m_matrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * -moveSpeed,
			y + direction.m_y * deltaTime * -moveSpeed,
			z + direction.m_z * deltaTime * -moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		Vector3D direction = m_matrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * moveSpeed,
			y + direction.m_y * deltaTime * moveSpeed,
			z + direction.m_z * deltaTime * moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('Q')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * -moveSpeed,
			y + direction.m_y * deltaTime * -moveSpeed,
			z + direction.m_z * deltaTime * -moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('E')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.m_x * deltaTime * moveSpeed,
			y + direction.m_y * deltaTime * moveSpeed,
			z + direction.m_z * deltaTime * moveSpeed);

		this->setPosition(newPos.m_x, newPos.m_y, newPos.m_z);
		this->updateViewMatrix();
	}
	//std::cout << "Camera Rotation: [" << this->rotation.m_x << ", " << this->rotation.m_y << ", " << this->rotation.m_z << "]\n";
}

void Camera::draw()
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

void Camera::onKeyDown(int key)
{
	/*if (InputSystem::getInstance()->isKeyDown('W'))
	{
		std::cout << "W pressed\n";
		this->m_cam_forward = 1.0;
	}
	else if (InputSystem::getInstance()->isKeyDown('S'))
	{
		std::cout << "S pressed\n";
		this->m_cam_forward = -1.0f;
	}
	else if (InputSystem::getInstance()->isKeyDown('A'))
	{
		std::cout << "A pressed\n";
		this->m_cam_rightward = -1.0f;
	}
	else if (InputSystem::getInstance()->isKeyDown('D'))
	{
		std::cout << "D pressed\n";
		this->m_cam_rightward = 1.0;
	}*/
}

void Camera::onKeyUp(int key)
{
	/*std::cout << "Key Up" << std::endl;
	this->m_cam_forward = 0.0f;
	this->m_cam_rightward = 0.0f;*/
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	if (this->canCameraMove) {
		float speed = 0.001f;

		float x = this->m_rotation.m_x;
		float y = this->m_rotation.m_y;
		float z = this->m_rotation.m_z;

		this->setRotation(Vector3D(x + mouse_pos.m_y * speed, y + mouse_pos.m_x * speed, z));

		this->updateViewMatrix();
	}
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
	//std::cout << "LMB_Down" << std::endl;
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
	//std::cout << "LMB_Up" << std::endl;
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
	this->canCameraMove = true;
	InputSystem::getInstance()->showCursor(false);
	std::cout << "Camera Enabled" << std::endl;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
	this->canCameraMove = false;
	InputSystem::getInstance()->showCursor(true);
	std::cout << "Camera Disabled" << std::endl;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;

	this->m_matrix = worldCam;

	worldCam.inverse();

	this->viewMatrix = worldCam;


}