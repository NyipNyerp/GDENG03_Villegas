#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->m_name = name;
	this->m_position = Vector3D::zeros();
	this->m_scale = Vector3D::ones();
	this->m_rotation = Vector3D::zeros();
}

AGameObject::~AGameObject()
{
}

void AGameObject::update(float deltaTime)
{
}

void AGameObject::draw(VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->m_position = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->m_position = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->m_position;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->m_scale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->m_scale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->m_scale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->m_rotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->m_rotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->m_rotation;
}

std::string AGameObject::getName()
{
	return this->m_name;
}

void AGameObject::setTransform(Vector3D position, Vector3D scale, Vector3D rotation)
{
	this->m_position = position;
	this->m_scale = scale;
	this->m_rotation = rotation;
}
