#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class UIHierarchy : public AUIScreen {

public:
    UIHierarchy(std::string name);
    ~UIHierarchy();

    virtual void drawUI() override;
};