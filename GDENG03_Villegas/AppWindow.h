#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "InputListener.h"
#include "GameObjectManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "Cube.h"

#include "imgui.h"

#include "reactphysics3d/reactphysics3d.h"

#include <vector>

using namespace reactphysics3d;



class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;


	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	SwapChain* m_swap_chain;

	ImVec4 clear_color = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
};