#pragma once
#include "Utils.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

class Quad
{
public:
	Quad(vec3 a, vec3 b, vec3 c, vec3 d);
	~Quad();

	void onLoad();
	void onDraw();
	void onRelease();

	vertex vectorList[4];
	VertexBuffer* m_vb;
};

