#include "Cube.h"
//#include "AppWindow.h"
#include "CameraManager.h"
#include "Utils.h"
#include "EngineTime.h"

Cube::Cube(std::string name):AGameObject(name)
{
	Vertex quadList[] =
	{
		// X, Y, Z
		// FRONT FACE
		{ Vector3D(-0.5f, -0.5f, -0.5f),		Vector3D(1,0,0),	Vector3D(0.25f,0.0f,0.0f) },
		{ Vector3D(-0.5f, 0.5f, -0.5f),			Vector3D(1,1,0),	Vector3D(0.25f,0.25f,0.0f) },
		{ Vector3D(0.5f, 0.5f, -0.5f),			Vector3D(1,1,0),	Vector3D(0.25f,0.25f,0.0f) },
		{ Vector3D(0.5f, -0.5f, -0.5f),			Vector3D(1,0,0),	Vector3D(0.25f,0.0f,0.0f) },

		// BACK FACE
		{ Vector3D(0.5f, -0.5f, 0.5f),			Vector3D(0,0,1),	Vector3D(0.0f,0.0f,0.25f) },
		{ Vector3D(0.5f, 0.5f, 0.5f),			Vector3D(0,1,1),	Vector3D(0.0f,0.25f,0.25f) },
		{ Vector3D(-0.5f, 0.5f, 0.5f),			Vector3D(0,1,1),	Vector3D(0.0f,0.25f,0.25f) },
		{ Vector3D(-0.5f, -0.5f, 0.5f),			Vector3D(0,0,1),	Vector3D(0.0f,0.0f,0.25f) },
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(quadList);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib = GraphicsEngine::get()->createIndexBuffer();
	m_ib->load(index_list, size_index_list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	// Vertex Buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(quadList, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	// Pixel Shader
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	// Constant Buffer
	Constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(Constant));
}

Cube::~Cube()
{
}

void Cube::update()
{
	this->deltaScale += EngineTime::getDeltaTime() * this->speed;
	this->ticks += EngineTime::getDeltaTime();


	Constant cc;

	Matrix4x4 allMatrix; allMatrix.setIdentity();

	float scaleDelta = (sin((this->ticks * 5 / this->duration)) + 1.0f) / 2.0f;
	Vector3D startScale = Vector3D::ones();
	Vector3D endScale = Vector3D(1.5f, 0.01f, 1.5f);
	Vector3D currScale = Vector3D::lerp(startScale, endScale, scaleDelta);
	//this->setScale(currScale);

	float posDelta = sin(this->ticks * 5 / this->duration);
	Vector3D currPos = Vector3D(posDelta, posDelta, 0);
	//this->setPosition(currPos);

	allMatrix.setScale(this->getLocalScale());

	/*Matrix4x4 rotationMatrix;
	rotationMatrix.setIdentity();
	rotationMatrix.setRotationZ(this->deltaScale);
	allMatrix *= rotationMatrix;

	rotationMatrix.setIdentity();
	rotationMatrix.setRotationY(this->deltaScale);
	allMatrix *= rotationMatrix;

	rotationMatrix.setIdentity();
	rotationMatrix.setRotationX(this->deltaScale);
	allMatrix *= rotationMatrix;*/

	allMatrix.setTranslation(this->getLocalPosition());

	cc.m_world = allMatrix;
	//cc.m_time = GetTickCount();

	/*Matrix4x4 temp;

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_cam_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_cam_rot_y);
	world_cam *= temp;


	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_cam_forward * 0.1f);
	new_pos = new_pos + world_cam.getXDirection() * (m_cam_rightward * 0.1f);
	world_cam.setTranslation(new_pos);
	m_world_cam = world_cam;
	world_cam.inverse();*/

	//cc.m_view = world_cam;

	cc.m_view = CameraManager::getInstance()->getCameraViewMatrix();

	//float width = (AppWindow::getInstance()->getClientWindowRect().right - AppWindow::getInstance()->getClientWindowRect().left);
	//float height = (AppWindow::getInstance()->getClientWindowRect().bottom - AppWindow::getInstance()->getClientWindowRect().top);

	float width = 2;
	float height = 3;

	//cc.m_view.setIdentity();
	/*cc.m_proj.setOrthoLH
	(
		width,
		height,
		-4.0f,
		4.0f
	);*/
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void Cube::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->m_vs, this->m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->m_ps, this->m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(this->m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Cube::destroy()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

float Cube::getAnimSpeed()
{
	return this->speed;
}