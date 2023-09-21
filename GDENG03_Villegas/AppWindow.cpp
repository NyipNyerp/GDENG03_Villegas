#include "AppWindow.h"
#include "Utils.h"

//struct vec3
//{
//	float x, y, z;
//};
//
//struct vertex
//{
//	vec3 position;
//};

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
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Quad quad1
	(
		{ 0.80f,-0.25f,0.0f },
		{ 0.30f,-0.25f,0.0f },
		{ 0.80f,0.25f,0.0f },
		{ 0.30f,0.25f,0.0f }
	);

	Quad quad2
	(
		{ 0.25f,-0.25f,0.0f },
		{ -0.25f,-0.25f,0.0f },
		{ 0.25f,0.25f,0.0f },
		{ -0.25f,0.25f,0.0f }
	);

	Quad quad3
	(
		{ -0.30f,-0.25f,0.0f },
		{ -0.80f,-0.25f,0.0f },
		{ -0.30f,0.25f,0.0f },
		{ -0.80f,0.25f,0.0f }
	);

	quadList.push_back(quad1);
	quadList.push_back(quad2);
	quadList.push_back(quad3);

	//for (Quad quad : quadList)
	//{
	//	quad.onLoad();
	//}

	/*
	vertex list[] =
	{
		//X - Y - Z
		{0.80f,0.30f,0.0f},		// INDEX 0
		{0.30f,0.30f,0.0f},		// INDEX 1
		{0.80f,0.80f,0.0f},		// INDEX 2
		{0.30f,0.80f,0.0f},		// INDEX 3

		{0.25f,-0.25f,0.0f},	// INDEX 4
		{-0.25f,-0.25f,0.0f},	// INDEX 5
		{0.25f,0.25f,0.0f},		// INDEX 6
		{-0.25f,0.25f,0.0f},	// INDEX 7

		{-0.30f,-0.80f,0.0f},	// INDEX 8
		{-0.80f,-0.80f,0.0f},	// INDEX 9
		{-0.30f,-0.30f,0.0f},	// INDEX 10
		{-0.80f,-0.30f,0.0f}	// INDEX 11
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(quad1.vectorList);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	*/
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->setShaders();


	for(Quad quad : quadList)
	{
		quad.onDraw();
	}


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	/*
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList()/3, 0);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList()/3, 4);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList()/3, 8);
	*/

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	for (Quad quad : quadList)
	{
		quad.onRelease();
	}
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}