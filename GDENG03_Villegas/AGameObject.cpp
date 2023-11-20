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

void AGameObject::update()
{
}

void AGameObject::draw()
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

bool AGameObject::isEnabled()
{
	return this->enabled;
}

void AGameObject::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->m_scale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->m_position);
	this->m_matrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	this->setPosition(newMatrix.m_mat[3][0], newMatrix.m_mat[3][1], newMatrix.m_mat[3][2]);
	this->setRotation(newMatrix.m_mat[2][0], newMatrix.m_mat[2][1], newMatrix.m_mat[2][2]);
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 matrix;
	matrix.setIdentity();
	matrix.setScale(this->getLocalScale());

	Matrix4x4 rotZ;
	rotZ.setIdentity();
	rotZ.setRotationZ(m_rotation.m_z);
	matrix = rotZ;

	Matrix4x4 rotY;
	rotY.setIdentity();
	rotY.setRotationY(m_rotation.m_y);
	matrix = rotY;

	Matrix4x4 rotX;
	rotX.setIdentity();
	rotX.setRotationX(m_rotation.m_x);
	matrix *= rotX;

	matrix.setTranslation(this->getLocalPosition());

	return matrix.getMatrix();

}