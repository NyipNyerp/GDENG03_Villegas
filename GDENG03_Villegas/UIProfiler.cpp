#include "UIProfiler.h"

UIProfiler::UIProfiler(std::string name) : AUIScreen(name)
{
	this->isActive = true;
}

UIProfiler::~UIProfiler()
{
}

void UIProfiler::drawUI()
{
	ImGui::Begin("Profiler Window", &this->isActive, ImGuiWindowFlags_NoResize);	// Create a window called "Hello, world!" and append into it.

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}
