#include "Cube.h"
#include "Utils.h"
#include "EngineTime.h"

Cube::Cube(std::string name):AGameObject(name)
{
	Vertex quadList[] =
	{
		// X, Y, Z
		// FRONT FACE
		{ Vector3D(-0.5f, -0.5f, -0.5f),		Vector3D(1,0,0),	Vector3D(0.2f,0.0f,0.0f) },
		{ Vector3D(-0.5f, 0.5f, -0.5f),			Vector3D(1,1,0),	Vector3D(0.2f,0.2f,0.0f) },
		{ Vector3D(0.5f, 0.5f, -0.5f),			Vector3D(1,1,0),	Vector3D(0.2f,0.2f,0.0f) },
		{ Vector3D(0.5f, -0.5f, -0.5f),			Vector3D(1,0,0),	Vector3D(0.2f,0.0f,0.0f) },

		// BACK FACE
		{ Vector3D(0.5f, -0.5f, 0.5f),			Vector3D(0,1,0),	Vector3D(0.0f,0.2f,0.0f) },
		{ Vector3D(0.5f, 0.5f, 0.5f),			Vector3D(0,1,1),	Vector3D(0.0f,0.2f,0.2f) },
		{ Vector3D(-0.5f, 0.5f, 0.5f),			Vector3D(0,1,1),	Vector3D(0.0f,0.2f,0.2f) },
		{ Vector3D(-0.5f, -0.5f, 0.5f),			Vector3D(0,1,0),	Vector3D(0.0f,0.2f,0.0f) },
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

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	m_vb->load(quadList, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	Constant cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(Constant));
}

Cube::~Cube()
{
}

void Cube::update(float deltaTime)
{
	Constant cc;

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	allMatrix.setScale(this->getLocalScale());

	this->deltaScale += EngineTime::getDeltaTime() * this->speed;

	Matrix4x4 rotationMatrix;
	rotationMatrix.setIdentity();
	rotationMatrix.setRotationZ(this->deltaScale);
	allMatrix *= rotationMatrix;

	rotationMatrix.setIdentity();
	rotationMatrix.setRotationY(this->deltaScale);
	allMatrix *= rotationMatrix;

	rotationMatrix.setIdentity();
	rotationMatrix.setRotationX(this->deltaScale);
	allMatrix *= rotationMatrix;

	allMatrix.setTranslation(this->getLocalPosition());

	cc.m_world = allMatrix;


	Matrix4x4 temp;

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
	world_cam.inverse();

	cc.m_view = world_cam;

	float height = 3;
	float width = 2;

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

void Cube::draw(VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

float Cube::getAnimSpeed()
{
	return this->speed;
}

void Cube::setCameraRotX(float xRotation)
{
	this->m_cam_rot_x = xRotation;
}

void Cube::setCameraRotY(float yRotation)
{
	this->m_cam_rot_y = yRotation;
}

void Cube::setCameraScaleCube(float scaleCube)
{
	this->m_cam_scale_cube = scaleCube;
}

void Cube::setCameraForward(float forward)
{
	this->m_cam_forward = forward;
}

void Cube::setCameraRightward(float rightward)
{
	this->m_cam_rightward = rightward;
}

float Cube::getCameraRotX()
{
	return this->m_cam_rot_x;
}

float Cube::getCameraRotY()
{
	return this->m_cam_rot_y;
}

float Cube::getCameraScaleCube()
{
	return this->m_cam_scale_cube;
}

float Cube::getCameraForward()
{
	return this->m_cam_forward;
}

float Cube::getCameraRightward()
{
	return this->m_cam_rightward;
}
