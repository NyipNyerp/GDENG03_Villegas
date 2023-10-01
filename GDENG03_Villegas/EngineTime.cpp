#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::initialize()
{
    if (!sharedInstance)
    {
        sharedInstance = new EngineTime();
    }
}

double EngineTime::getDeltaTime()
{
    return sharedInstance->deltaTime;
}

void EngineTime::logFrameStart()
{
    sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::logFrameEnd()
{
    sharedInstance->end = std::chrono::system_clock::now();
    std::chrono::duration<double> time = sharedInstance->end - sharedInstance->start;
    sharedInstance->deltaTime = time.count();
}
