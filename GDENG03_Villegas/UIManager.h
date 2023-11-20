#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "GraphicsEngine.h"

#include "UIToolbar.h"
#include "UIInspector.h"
#include "UIHierarchy.h"
#include "UIProfiler.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"


class UINames
{
public:
    const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
    const std::string TOOLBAR_SCREEN = "TOOLBAR_SCREEN";
    const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
    const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
};

class AUIScreen;

class UIManager {

public:
    typedef std::vector<AUIScreen*> UIList;
    typedef std::unordered_map<std::string, AUIScreen*> UITable;

    static UIManager* getInstance();
    static void initialize(HWND windowHandle);
    static void destroy();

    void drawUI();

    static const int WINDOW_WIDTH = 1440;
    static const int WINDOW_HEIGHT = 900;

private:
    UIManager(HWND windowHandle);
    ~UIManager();

    UIManager(UIManager const&) {};
    UIManager& operator=(UIManager const&) {};

    static UIManager* sharedInstance;

    UIList uiList;
    UITable uiTable;

    UINames uiNames;

private:
    friend class AUIScreen;
};