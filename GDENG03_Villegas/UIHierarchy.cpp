#include "UIHierarchy.h"

UIHierarchy::UIHierarchy(std::string name) : AUIScreen(name)
{
	this->isActive = true;
}

UIHierarchy::~UIHierarchy()
{
}

void UIHierarchy::drawUI()
{
	ImGui::Begin("Hierarchy Window", &this->isActive, ImGuiWindowFlags_AlwaysAutoResize);	// Create a window called "Hello, world!" and append into it.

	ImGui::SeparatorText("Game Objects");

	int i = 1;
	for (auto object : GameObjectManager::getInstance()->getAllGameObjects())
	{
		this->name = object->getName() + "_" + std::to_string(i);
		if (ImGui::Button(name.c_str()))
			GameObjectManager::getInstance()->currGameObject = object;
		i++;
	}
		
	ImGui::End();
}
