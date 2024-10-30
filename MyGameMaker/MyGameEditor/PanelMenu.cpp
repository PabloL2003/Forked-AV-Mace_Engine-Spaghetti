#include "PanelMenu.h"
#include <imgui.h>

#include "MyGUI.h"

#include "PanelConsole.h"

PanelMenu::PanelMenu(PanelType type, std::string name) : Panel(type, name)
{
	SwitchState();
}

PanelMenu::~PanelMenu() {}

bool PanelMenu::Draw()
{
    if (ImGui::BeginMainMenuBar()) 
    {
        // File menu
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Scene", "Ctrl+N", nullptr, false)) {
                // Action for "New" item
            }
            if (ImGui::MenuItem("Open Scene", "Ctrl+O", nullptr, false)) {
                // Action for "Open" item
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save", "Ctrl+S", nullptr, false)) {
                // Action for "Save" item
            }  
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", nullptr, false)) {
                // Action for "Save" item
            }
            ImGui::Separator();
            if (ImGui::MenuItem("New Project", "Ctrl+Shift+N", nullptr, false)) {
                // Action for "Exit" item
            }
            if (ImGui::MenuItem("Open Project", "Ctrl+Shift+O", nullptr, false)) {
                // Action for "Exit" item
            }
            if (ImGui::MenuItem("Save Project", nullptr, nullptr, false)) {
                // Action for "Exit" item
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                // Action for "Exit" item
            }
            ImGui::EndMenu();
        }

        // Edit menu
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z", nullptr, false)) {
                // Action for "Undo" item
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Y", nullptr, false)) {
                // Action for "Redo" item
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Select All", "Ctrl+A", nullptr, false)) {
                // Action for "Undo" item
            }
            if (ImGui::MenuItem("Deselect All", "Shift+D", nullptr, false)) {
                // Action for "Undo" item
            }
            if (ImGui::MenuItem("Select Children", "Shift+C", nullptr, false)) {
                // Action for "Undo" item
            }
            if (ImGui::MenuItem("Invert Selection", "Ctrl+I", nullptr, false)) {
                // Action for "Undo" item
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Duplicate", "Ctrl+D", nullptr, false)) {
                // Action for "Undo" item
            }
            if (ImGui::MenuItem("Delete", "Supr", nullptr, false)) {
                // Action for "Undo" item
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Play", "Ctrl+P", nullptr, false)) {
                // Action for "Undo" item
            }
            if (ImGui::MenuItem("Pause", "Ctrl+Shift+P", nullptr, false)) {
                // Action for "Undo" item
            }
            if (ImGui::MenuItem("Step", "Ctrl+Alt+P", nullptr, false)) {
                // Action for "Undo" item
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Settings...")) {
                // Action for "Undo" item
            }
            ImGui::EndMenu();
        }

        // Window menu
        if (ImGui::BeginMenu("Window")) {
            
            if (ImGui::BeginMenu("Veiwport", false))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Menus"))
            {
                if (ImGui::MenuItem("Toolbar", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                if (ImGui::MenuItem("Hierarchy", nullptr, show_hierarchy)) {
					show_hierarchy = !show_hierarchy;
                }
                if (ImGui::MenuItem("Project", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                if (ImGui::MenuItem("Console", nullptr, show_console)) {
					show_console = !show_console;
                    MyGUI::Instance().console().SwitchState();

                }
				if (ImGui::MenuItem("Inspector", nullptr, show_inspector)) {
					show_inspector = !show_inspector;
				}
                if (ImGui::MenuItem("Scene", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                if (ImGui::MenuItem("Game", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::BeginMenu("DevDebug"))
            {
				if (ImGui::MenuItem("Show UI Demo")) {
					// Action for "Undo" item
				}
				if (ImGui::MenuItem("Generate Game", nullptr, nullptr, false)) {
					// Action for "Undo" item
				}
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        // GameObjects menu
        if (ImGui::BeginMenu("GameObjects")) 
        {
            if (ImGui::BeginMenu("Create..."))
            {
                if (ImGui::MenuItem("Create Empty", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                if (ImGui::MenuItem("Create Empty x10", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                if (ImGui::MenuItem("Plane", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                if (ImGui::MenuItem("Cube", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
				if (ImGui::MenuItem("Sphere", nullptr, nullptr, false)) {
					// Action for "Undo" item
				}
                if (ImGui::MenuItem("Hemisphere", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
				if (ImGui::MenuItem("Cylinder", nullptr, nullptr, false)) {
					// Action for "Undo" item
				}
                if (ImGui::MenuItem("Cone", nullptr, nullptr, false)) {

                }
                if (ImGui::MenuItem("Torus", nullptr, nullptr, false)) {
                    // Action for "Undo" item
                }
                ImGui::EndMenu();
            }

			
            if (ImGui::BeginMenu("Draw Mode")) {

                // Option 1
                if (ImGui::MenuItem("Option 1", nullptr)) {
                }

                // Option 2
                if (ImGui::MenuItem("Option 2", nullptr)) {
                }

                // Option 3
                if (ImGui::MenuItem("Option 3", nullptr)) {
                }
                ImGui::Separator();

                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        // Help menu
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) {
                // Action for "About" item
            }
            ImGui::EndMenu();
        }

        // Exit menu
        if (ImGui::MenuItem("Exit")) {

        }

        ImGui::EndMainMenuBar();
    }

	return true;
}