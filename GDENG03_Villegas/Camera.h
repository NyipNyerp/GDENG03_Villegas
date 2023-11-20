#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	// Inherited via AGameObject
	virtual void update() override;
	virtual void draw() override;
	Matrix4x4 getViewMatrix();


	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void onLeftMouseUp(const Point& delta_mouse_pos) override;
	virtual void onRightMouseDown(const Point& delta_mouse_pos) override;
	virtual void onRightMouseUp(const Point& delta_mouse_pos) override;

private:
	void updateViewMatrix();

	bool canMoveCamera = false;

	float m_cam_rot_x = 0.0f;
	float m_cam_rot_y = 0.0f;

	float m_cam_scale_cube = 1.0f;
	float m_cam_forward = 0.0f;
	float m_cam_rightward = 0.0f;

	float speed = 0.1f;
	float mouse_sensitivity = 0.01f;

	Matrix4x4 m_view_cam;
};