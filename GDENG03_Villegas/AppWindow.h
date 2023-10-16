#pragma once
#include "Window.h"
#include "InputListener.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <vector>
#include "Cube.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	//void updateCamera();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	std::vector<Cube*> cubeList;

	SwapChain* m_swap_chain;

	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	VertexShader* m_vs;
	PixelShader* m_ps;

	bool flipAnim = false;

	/*float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4 m_world_cam;*/
};