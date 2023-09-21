#include "Quad.h"

Quad::Quad(vec3 a, vec3 b, vec3 c, vec3 d)
{
	this->vectorList[0].position = a;
	this->vectorList[1].position = b;
	this->vectorList[2].position = c;
	this->vectorList[3].position = d;

	onLoad();
}

Quad::~Quad()
{
}

void Quad::onLoad()
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(this->vectorList);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(this->vectorList, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void Quad::onDraw()
{
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
}

void Quad::onRelease()
{
	m_vb->release();
}
