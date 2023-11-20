#include "UIManager.h"
#include "GraphicsEngine.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	delete sharedInstance;
}

void UIManager::drawUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++)
	{
		if (this->uiList[i]->isActive == true) this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	
	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getID3D11Device(), GraphicsEngine::get()->getID3D11DeviceContext());


	UIToolbar* toolbar = new UIToolbar("Toolbar Screen");
	this->uiTable[this->uiNames.TOOLBAR_SCREEN] = toolbar;
	this->uiList.push_back(toolbar);

	UIHierarchy* hierarchy = new UIHierarchy("Hierarchy Screen");
	this->uiTable[this->uiNames.HIERARCHY_SCREEN] = hierarchy;
	this->uiList.push_back(hierarchy);

	UIInspector* inspector = new UIInspector("Inspector Screen");
	this->uiTable[this->uiNames.INSPECTOR_SCREEN] = inspector;
	this->uiList.push_back(inspector);

	UIProfiler* profiler = new UIProfiler("Profiler Screen");
	this->uiTable[this->uiNames.PROFILER_SCREEN] = profiler;
	this->uiList.push_back(profiler);
}

UIManager::~UIManager()
{

}