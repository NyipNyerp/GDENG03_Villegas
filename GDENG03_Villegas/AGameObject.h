#pragma once
#include <string>

#include "Matrix4x4.h"
#include "Vector3D.h"

class VertexShader;
class PixelShader;
class AGameObject
{
public: 
	AGameObject(std::string name);
	~AGameObject();

	virtual void update() = 0;
	virtual void draw() = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	std::string getName();
	void setTransform(Vector3D position, Vector3D scale, Vector3D rotation);

	bool isEnabled();
	void setEnabled(bool enabled);

	// openGL matrix to our matrix implementation
	void recomputeMatrix(float matrix[16]);
	// our matrix implementation to openGL matrix
	float* getPhysicsLocalMatrix();

protected:
	std::string m_name;
	Vector3D m_position;
	Vector3D m_scale;
	Vector3D m_rotation;
	Matrix4x4 m_matrix;

private:
	bool enabled = true;
	friend class GameObjectManager;
};

