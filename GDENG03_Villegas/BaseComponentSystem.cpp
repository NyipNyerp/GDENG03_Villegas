#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include <iostream>

BaseComponentSystem* BaseComponentSystem::sharedInstance = NULL;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
    return sharedInstance;
}

void BaseComponentSystem::initialize()
{
    sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy()
{
    delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
    return this->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
    //std::cout << "BaseComponentSystem Constructor called..." << std::endl;
    this->physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
}
