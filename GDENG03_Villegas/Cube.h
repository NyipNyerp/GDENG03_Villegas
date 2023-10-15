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

	float speed = 10.0f;


private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float deltaTime = 0.0f;
};

