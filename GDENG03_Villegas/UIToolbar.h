#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class UIToolbar : public AUIScreen {

public:
    UIToolbar(std::string name);
    ~UIToolbar();

    virtual void drawUI() override;
};