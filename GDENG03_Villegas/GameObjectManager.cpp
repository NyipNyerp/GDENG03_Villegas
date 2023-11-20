#include "GameObjectManager.h"
#include "EngineTime.h"
#include "PhysicsComponent.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}

void GameObjectManager::update()
{
	for (auto obj : this->object_list)
	{
		obj->update();
		obj->draw();
	}
}

void GameObjectManager::release()
{
	for (auto obj : this->object_list) obj->~AGameObject();
}

AGameObject* GameObjectManager::create(std::string name, PrimitiveType primType)
{
	AGameObject* obj = nullptr;

	if (primType == CUBE)
	{
		obj = new Cube(name);
		std::cout << "Cube created" << std::endl;
	}
	else if (primType == PLANE)
	{
		obj = new Cube(name);
		obj->setScale(10.0f, 0.1f, 10.0f);
		obj->setPosition(0, -10, 0);
		std::cout << "Plane created" << std::endl;
	}
	else if (primType == PHYSICS_PLANE)
	{
		obj = new Cube(name);
		obj->setScale(64.0f, 0.1f, 64.0f);
		obj->setPosition(0, -10, 0);
		PhysicsComponent* physicsCube = new PhysicsComponent(obj->getName(), obj);
		physicsCube->getRigidBody()->setType(BodyType::STATIC);
		std::cout << "Physics Plane created" << std::endl;
	}
	else if (primType == PHYSICS_CUBE)
	{
		obj = new Cube(name);
		PhysicsComponent* physicsCube = new PhysicsComponent(obj->getName(), obj);
		std::cout << "Physics Cube created" << std::endl;
	}

	this->object_list.push_back(obj);

	return obj;
}

std::list<AGameObject*> GameObjectManager::getAllGameObjects()
{
	return this->object_list;
}
