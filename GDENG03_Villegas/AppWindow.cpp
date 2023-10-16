#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "Utils.h"
#include "EngineTime.h"
#include <iostream>

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

//void AppWindow::updateCamera()
//{
//	Constant cc;
//	cc.m_time = ::GetTickCount();
//	cc.m_world.setIdentity();
//
//	Matrix4x4 temp;
//
//	Matrix4x4 world_cam;
//	world_cam.setIdentity();
//
//	temp.setIdentity();
//	temp.setRotationX(m_rot_x);
//	world_cam *= temp;
//
//	temp.setIdentity();
//	temp.setRotationY(m_rot_y);
//	world_cam *= temp;
//
//
//	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);
//
//	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);
//
//	world_cam.setTranslation(new_pos);
//
//	m_world_cam = world_cam;
//
//
//	world_cam.inverse();
//
//
//	cc.m_view = world_cam;
//	/*cc.m_proj.setOrthoLH
//	(
//		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
//		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
//		-4.0f,
//		4.0f
//	);*/
//
//	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
//	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
//
//
//	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
//
//
//	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
//}


void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//float multiplier = 0.1f;
	//for (int i = 1; i <= 10; i++)
	//{
	//	std::string name = "cube_" + std::to_string(i);
	//	Cube* cube = new Cube(name);
	//	float tempMult = i * multiplier;
	//	cube->setScale(0 + tempMult, 0 + tempMult, 0 + tempMult);
	//	cube->setPosition(0 + tempMult, 0 + tempMult, 0 + tempMult);
	//	cube->setAnimSpeed(1 + (tempMult * multiplier));
	//	cube->normSpeed = cube->getAnimSpeed();
	//	cube->flipSpeed = cube->getAnimSpeed() * -1;

	//	//multiplier *= -1;
	//	std::cout << cube->getName() << std::endl;
	//	this->cubeList.push_back(cube);
	//}

	float multiplier = 0.35f;
	for (int i = 0; i < 5; i++)
	{
		float x = MathUtils::randomFloat(-0.75, 0.75f);
		float y = MathUtils::randomFloat(-0.75, 0.75f);
		float z = MathUtils::randomFloat(-0.75, 0.75f);

		std::string name = "cube_" + std::to_string(i + 1);
		Cube* cube = new Cube(name);
		cube->setPosition(x,y,z);
		cube->setScale(0.25, 0.25, 0.25);
		cube->setAnimSpeed(multiplier);
		cube->normSpeed = cube->getAnimSpeed();
		cube->flipSpeed = cube->getAnimSpeed() * -1;


		this->cubeList.push_back(cube);

		//multiplier *= -1;


		/*cout << cube->getName() << ".x = " << cube->getLocalPosition().m_x << "    random_x = " << x << endl;
		cout << cube->getName() << ".y = " << cube->getLocalPosition().m_y << "    random_y = " << y << endl;
		cout << cube->getName() << ".z = " << cube->getLocalPosition().m_z << "    random_z = " << z << endl << endl;*/
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//m_vb->load(vertex_list, sizeof(Vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	InputSystem::get()->update();

	//updateCamera();


	for (Cube* cube : cubeList)
	{
		if (!flipAnim) cube->setAnimSpeed(cube->normSpeed);
		else cube->setAnimSpeed(cube->flipSpeed);
		cube->update(EngineTime::getDeltaTime());
		cube->draw(m_vs, m_ps);
		//cout << cube->getName() << " speed: " << cube->getAnimSpeed() << endl;
		/*cout << cube->getName() << ".x = " << cube->getLocalPosition().m_x << "   scale_x = " << cube->getLocalScale().m_x << endl;
		cout << cube->getName() << ".y = " << cube->getLocalPosition().m_y << "   scale_y = " << cube->getLocalScale().m_y << endl;
		cout << cube->getName() << ".z = " << cube->getLocalPosition().m_z << "   scale_z = " << cube->getLocalScale().m_z << endl << endl;*/
	}
	
	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		std::cout << "W pressed\n";
		flipAnim = true;
		//m_rot_x += 3.14f*m_delta_time;
		//m_forward = 1.0f;

		for (Cube* cube : cubeList)
		{
			cube->setCameraForward(1.0f);
		}
	}
	else if (key == 'S')
	{
		std::cout << "S pressed\n";
		flipAnim = false;
		//m_rot_x -= 3.14f*m_delta_time;
		//m_forward = -1.0f;

		for (Cube* cube : cubeList)
		{
			cube->setCameraForward(-1.0f);
		}
	}
	else if (key == 'A')
	{
		std::cout << "A pressed\n";
		//m_rot_y += 3.14f*m_delta_time;
		//m_rightward = -1.0f;

		for (Cube* cube : cubeList)
		{
			cube->setCameraRightward(-1.0f);
		}
	}
	else if (key == 'D')
	{
		std::cout << "D pressed\n";
		//m_rot_y -= 3.14f*m_delta_time;
		//m_rightward = 1.0f;

		for (Cube* cube : cubeList)
		{
			cube->setCameraRightward(1.0f);
		}
	}
}

void AppWindow::onKeyUp(int key)
{
	//m_forward = 0.0f;
	//m_rightward = 0.0f;
	for (Cube* cube : cubeList)
	{
		cube->setCameraForward(0.0f);
		cube->setCameraRightward(0.0f);
	}
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	for (Cube* cube : cubeList)
	{
		float tempX = cube->getCameraRotX();
		float tempY = cube->getCameraRotY();

		tempX += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
		tempY += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

		cube->setCameraRotX(tempX);
		cube->setCameraRotY(tempY);
	}

	//m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	//m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;

	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	//m_scale_cube = 0.5f;

	for (Cube* cube : cubeList)
	{
		cube->setCameraScaleCube(0.5f);
	}
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	//m_scale_cube = 1.0f;

	for (Cube* cube : cubeList)
	{
		cube->setCameraScaleCube(1.0f);
	}
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	//m_scale_cube = 2.0f;

	for (Cube* cube : cubeList)
	{
		cube->setCameraScaleCube(2.0f);
	}
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	//m_scale_cube = 1.0f;

	for (Cube* cube : cubeList)
	{
		cube->setCameraScaleCube(1.0f);
	}
}