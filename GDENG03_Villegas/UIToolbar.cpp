#include "UIToolbar.h"

UIToolbar::UIToolbar(std::string name) : AUIScreen(name)
{
    this->isActive = true;
}

UIToolbar::~UIToolbar()
{
}

void UIToolbar::drawUI()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New", "Ctrl+N");
            ImGui::MenuItem("Save", "Ctrl+S");
            ImGui::MenuItem("Open", "Ctrl+O");
            ImGui::MenuItem("Exit", "Ctrl+E");

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("GameObject"))
        {
            ImGui::SeparatorText("Primitives");
            if (ImGui::MenuItem("Create Cube", NULL))
            {
                // Create Cube Object
                GameObjectManager::getInstance()->create("Cube", CUBE);
            }

            if (ImGui::MenuItem("Create Sphere", NULL)) // Non-functional
            {
                // Create Sphere Object
            }

            if (ImGui::MenuItem("Create Plane", NULL))
            {
                // Create Plane Object
                GameObjectManager::getInstance()->create("Plane", PLANE);
            }

            ImGui::SeparatorText("Physics Primitives");
            if (ImGui::MenuItem("Create Physics Cube", NULL))
            {
                // Create Physics Cube Object
                GameObjectManager::getInstance()->create("Physics_Cube", PHYSICS_CUBE);
            }
            if (ImGui::MenuItem("Create Physics Plane", NULL))
            {
                // Create Physics Plane Object
                GameObjectManager::getInstance()->create("Physics_Plane", PHYSICS_PLANE);
            }


            ImGui::SeparatorText("Other Objects");
            if (ImGui::BeginMenu("Create Light")) // Non-functional
            {
                if (ImGui::MenuItem("Point Light", NULL)) // Non-functional
                {
                    // Create Point Light Object
                }
                if (ImGui::MenuItem("Spot Light", NULL)) // Non-functional
                {
                    // Create Spot Light Object
                }
                if (ImGui::MenuItem("Directional Light", NULL)) // Non-functional
                {
                    // Create Directional Light Object
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
