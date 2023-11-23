#include "AppWindow.h"
#include "InputSystem.h"

#include "EngineTime.h"
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Utils.h"
#include <iostream>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <reactphysics3d/reactphysics3d.h>
#include "PhysicsSystem.h"


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();

	InputSystem::getInstance()->initialize();
	//InputSystem::getInstance()->addListener(this);
	//InputSystem::getInstance()->showCursor(false);

	GameObjectManager::initialize();
	CameraManager::initialize();
	UIManager::initialize(this->m_hwnd);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	BaseComponentSystem::initialize();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);


	InputSystem::getInstance()->update();
	CameraManager::getInstance()->update();
	GameObjectManager::sharedInstance->update();	
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	UIManager::getInstance()->drawUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

	InputSystem::destroy();
	CameraManager::destroy();
	UIManager::getInstance()->destroy();
	GraphicsEngine::get()->release();
}