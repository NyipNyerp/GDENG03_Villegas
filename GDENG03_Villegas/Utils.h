#pragma once

struct Vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16))
struct Constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


class MathUtils
{
public:
	static float randomFloat(float a, float b)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
	static int randomInt(int a, int b)
	{
		int range = a - b + 1;
		int num = rand() % range + a;

		return num;
	}
};