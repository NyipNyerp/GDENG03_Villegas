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

	float ticks = 0.0f;
	float mouseDown = false;

	Vector3D forwardDirection;
	Vector3D backwardDirection;
	Matrix4x4 viewMatrix;
	//float forwardDirection = 0.0f;
	//Matrix4x4 worldCameraMatrix;

	bool canCameraMove = true;
};