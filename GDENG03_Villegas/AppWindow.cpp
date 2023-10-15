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

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	for (int i = 1; i <= 10; i++)
	{
		std::string name = "cube_" + std::to_string(i);
		Cube* cube = new Cube(name);
		float tempMult = i * multiplier;
		cube->setScale(0 + tempMult, 0 + tempMult, 0 + tempMult);
		cube->setPosition(0 + tempMult, 0 + tempMult, 0 + tempMult);
		cube->setAnimSpeed(1 + (tempMult * multiplier));

		//multiplier *= -1;
		cout << cube->getName() << endl;
		this->cubeList.push_back(cube);
	}

	/*float multiplier = 0.35f;
	for (int i = 0; i < 5; i++)
	{
		float x = MathUtils::randomFloat(-0.75, 0.75f);
		float y = MathUtils::randomFloat(-0.75, 0.75f);
		float z = MathUtils::randomFloat(-0.75, 0.75f);

		std::string name = "cube_" + std::to_string(i + 1);
		Cube* cube = new Cube(name);
		cube->setPosition(0,0, i * multiplier);
		cube->setScale(0.25, 0.25, 0.25);
		cube->setAnimSpeed(5 * multiplier);
		this->cubeList.push_back(cube);

		multiplier *= -1;


		cout << cube->getName() << ".x = " << cube->getLocalPosition().m_x << "    random_x = " << x << endl;
		cout << cube->getName() << ".y = " << cube->getLocalPosition().m_y << "    random_y = " << y << endl;
		cout << cube->getName() << ".z = " << cube->getLocalPosition().m_z << "    random_z = " << z << endl << endl;
	}*/

	//Vertex vertex_list[] =
	//{
	//	//X - Y - Z
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
	//	{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	//};

	//m_vb = GraphicsEngine::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(vertex_list);


	//unsigned int index_list[] =
	//{
	//	//FRONT SIDE
	//	0,1,2,  //FIRST TRIANGLE
	//	2,3,0,  //SECOND TRIANGLE
	//	//BACK SIDE
	//	4,5,6,
	//	6,7,4,
	//	//TOP SIDE
	//	1,6,5,
	//	5,2,1,
	//	//BOTTOM SIDE
	//	7,0,3,
	//	3,4,7,
	//	//RIGHT SIDE
	//	3,2,5,
	//	5,4,3,
	//	//LEFT SIDE
	//	7,6,1,
	//	1,0,7
	//};


	//m_ib = GraphicsEngine::get()->createIndexBuffer();
	//UINT size_index_list = ARRAYSIZE(index_list);

	//m_ib->load(index_list, size_index_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//m_vb->load(vertex_list, sizeof(Vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	/*Constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(Constant));*/

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

	InputSystem::getInstance()->update();

	//updateQuadPosition();


	for (Cube* cube : cubeList)
	{
		cube->update(EngineTime::getDeltaTime());
		cube->draw(m_vs, m_ps);

		/*cout << cube->getName() << ".x = " << cube->getLocalPosition().m_x << "   scale_x = " << cube->getLocalScale().m_x << endl;
		cout << cube->getName() << ".y = " << cube->getLocalPosition().m_y << "   scale_y = " << cube->getLocalScale().m_y << endl;
		cout << cube->getName() << ".z = " << cube->getLocalPosition().m_z << "   scale_z = " << cube->getLocalScale().m_z << endl << endl;*/
	}
	//
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	////SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	////SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	////SET THE INDICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);


	//// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);


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

void AppWindow::onKeyDown(int key)
{
	//cout << "onkeydown:\n";
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "W pressed\n";
		multiplier *= -1;
		cout << "keyDown multiplier = " << multiplier << endl;
	}
}

void AppWindow::onKeyUp(int key)
{
	//cout << "onkeyup:\n";
	if (InputSystem::getInstance()->isKeyUp('W'))
	{
		cout << "W released\n";
		multiplier *= -1;
		cout << "keyUp multiplier = " << multiplier << endl;
	}
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	//cout << " mouse moved: " << deltaPos.m_x << ", " << deltaPos.m_y << "\n";
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}
