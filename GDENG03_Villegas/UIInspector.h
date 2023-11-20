#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class UIInspector : public AUIScreen {

public:
    UIInspector(std::string name);
    ~UIInspector();

    virtual void drawUI() override;

    AGameObject* currGameObject;
    float objectPosition[3];
    float objectRotation[3];
    float objectScale[3];
};