#pragma once
#include "AGameObject.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

class Cube : public AGameObject
{
public:
	Cube(std::string name);
	~Cube();

	void update(float deltaTime) override;
	void draw(VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);
	float getAnimSpeed();



	void setCameraRotX(float xRotation);
	void setCameraRotY(float yRotation);
	void setCameraScaleCube(float scaleCube);
	void setCameraForward(float forward);
	void setCameraRightward(float rightward);

	float getCameraRotX();
	float getCameraRotY();
	float getCameraScaleCube();
	float getCameraForward();
	float getCameraRightward();



	float normSpeed = 10.0f;
	float flipSpeed = -10.0f;

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;

	float m_cam_rot_x = 0.0f;
	float m_cam_rot_y = 0.0f;

	float m_cam_scale_cube = 1.0f;
	float m_cam_forward = 0.0f;
	float m_cam_rightward = 0.0f;

	Matrix4x4 m_world_cam;
};

