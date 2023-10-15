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

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;


	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point deltaPos);

	virtual void onLeftMouseDown(const Point deltaPos);
	virtual void onLeftMouseUp(const Point deltaPos);

	virtual void onRightMouseDown(const Point deltaPos);
	virtual void onRightMouseUp(const Point deltaPos);

private:
	std::vector<Cube*> cubeList;

	SwapChain* m_swap_chain;

	VertexBuffer* m_vb;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	VertexShader* m_vs;
	PixelShader* m_ps;

	float multiplier = 0.1f;
};