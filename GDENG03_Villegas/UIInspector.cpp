#include "UIInspector.h"

UIInspector::UIInspector(std::string name) : AUIScreen(name)
{
	this->isActive = true;
}

UIInspector::~UIInspector()
{
}

void UIInspector::drawUI()
{
    this->currGameObject = GameObjectManager::getInstance()->currGameObject;

	ImGui::Begin("Inspector Window", &this->isActive, 0);	// Create a window called "Hello, world!" and append into it.

    if (this->currGameObject != nullptr)
    {
        ImGui::Text(this->currGameObject->getName().c_str());

        this->objectPosition[0] = this->currGameObject->getLocalPosition().m_x;
        this->objectPosition[1] = this->currGameObject->getLocalPosition().m_y;
        this->objectPosition[2] = this->currGameObject->getLocalPosition().m_z;

        this->objectRotation[0] = this->currGameObject->getLocalRotation().m_x;
        this->objectRotation[1] = this->currGameObject->getLocalRotation().m_y;
        this->objectRotation[2] = this->currGameObject->getLocalRotation().m_z;

        this->objectScale[0] = this->currGameObject->getLocalScale().m_x;
        this->objectScale[1] = this->currGameObject->getLocalScale().m_y;
        this->objectScale[2] = this->currGameObject->getLocalScale().m_z;

        ImGui::DragFloat3("Position", this->objectPosition, 1);
        ImGui::DragFloat3("Rotation", this->objectRotation, 1);
        ImGui::DragFloat3("Scale", this->objectScale, 1);

        this->currGameObject->setScale(this->objectScale[0], this->objectScale[1], this->objectScale[2]);
        this->currGameObject->setRotation(this->objectRotation[0], this->objectRotation[1], this->objectRotation[2]);
        this->currGameObject->setPosition(this->objectPosition[0], this->objectPosition[1], this->objectPosition[2]);
    }

	ImGui::End();

}
