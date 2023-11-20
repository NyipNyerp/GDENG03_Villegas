#include "Camera.h"
#include "AppWindow.h"
#include "InputSystem.h"
#include <iostream>
#include "EngineTime.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	//this->setPosition(0.0f, 4.0f, -10.0f);
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update()
{
	updateViewMatrix();
}

void Camera::draw()
{
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->m_view_cam;
}

void Camera::onKeyDown(int key)
{
	if (InputSystem::getInstance()->isKeyDown('W'))
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
	}
}

void Camera::onKeyUp(int key)
{
	std::cout << "Key Up" << std::endl;
	this->m_cam_forward = 0.0f;
	this->m_cam_rightward = 0.0f;
}

void Camera::onMouseMove(const Point& mouse_pos)
{
	//std::cout << "Mouse moved\n";

	if (canMoveCamera)
	{
		//int width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
		//int height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

		int width = 3;
		int height = 3;

		this->m_cam_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * this->mouse_sensitivity;
		this->m_cam_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * this->mouse_sensitivity;

		std::cout << "Camera_X: [" << this->m_cam_rot_x << "]     Camera Y: [" << this->m_cam_rot_y << "]" << std::endl;

		//InputSystem::getInstance()->setCursorPosition(Point((width / 2.0f), (1080 / 2.0f)));
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
	this->canMoveCamera = true;
	InputSystem::getInstance()->showCursor(false);
	std::cout << "Camera Enabled" << std::endl;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
	this->canMoveCamera = false;
	InputSystem::getInstance()->showCursor(true);
	std::cout << "Camera Disabled" << std::endl;
}

void Camera::updateViewMatrix()
{
	//Matrix4x4 worldCam;
	//worldCam.setIdentity();
	//Matrix4x4 temp;
	//temp.setIdentity();

	//Vector3D localRot = this->getLocalRotation();

	//temp.setQuaternionRotation(localRot.m_x, 1, 0, 0);	
	//worldCam *= temp;

	//temp.setIdentity();
	//temp.setQuaternionRotation(localRot.m_y, 0, 1, 0);
	//worldCam *= temp;


	////NEW POSITION FOR FREECAM MOVEMENT
	//temp.setIdentity();
	//Vector3D new_pos = this->m_matrix.getTranslation() + worldCam.getZDirection() * (this->m_cam_forward * this->speed);
	//new_pos = new_pos + worldCam.getXDirection() * (this->m_cam_rightward * this->speed);
	//temp.setTranslation(new_pos);
	//worldCam *= temp;
	//this->m_matrix = worldCam;


	//worldCam.inverse();
	//this->m_view_cam = worldCam;


	Matrix4x4 world_cam;
	world_cam.setIdentity();
	Matrix4x4 temp;
	temp.setIdentity();

	temp.setRotationX(m_cam_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_cam_rot_y);
	world_cam *= temp;


	Vector3D new_pos = this->m_matrix.getTranslation() + world_cam.getZDirection() * (m_cam_forward * this->speed);
	new_pos = new_pos + world_cam.getXDirection() * (m_cam_rightward * this->speed);
	temp.setTranslation(new_pos);
	world_cam *= temp;
	this->m_matrix = world_cam;
	world_cam.inverse();

	this->m_view_cam = world_cam;


}