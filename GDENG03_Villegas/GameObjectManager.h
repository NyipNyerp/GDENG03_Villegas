#pragma once
#include <list>
#include "Cube.h"


enum PrimitiveType
{
	CUBE,
	PLANE,
	PHYSICS_CUBE,
	PHYSICS_PLANE
};

class AppWindow;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

public:
	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

public:
	void update();
	void release();

	AGameObject* create(std::string name, PrimitiveType primType);
	std::list<AGameObject*> getAllGameObjects();


	AGameObject* currGameObject;

private:
	std::list<AGameObject*> object_list;

private:
	friend class AppWindow;
	friend class InspectorScreen;
};