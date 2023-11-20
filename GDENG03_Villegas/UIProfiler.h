#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class UIProfiler : public AUIScreen {

public:
    UIProfiler(std::string name);
    ~UIProfiler();

    virtual void drawUI() override;
};