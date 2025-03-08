#include "EngineLayers.h"

//ENGINE
#include "Core/Logger.h"
#include "Input/Input.h"
#include "Core/Application.h"

//VENDOR
#include "VENDOR/IMGUI/imgui.h"
#include "VENDOR/IMGUI/imgui_impl_glfw.h"
#include "VENDOR/IMGUI/imgui_impl_opengl3.h"
//#include "VENDOR/IMGUI/imgui_impl_opengl3_loader.h"

namespace Engine
{
	//***********//
	//WORLD LAYER//
	//***********//
	WorldLayer::WorldLayer() : Layer(1)
	{

	}

	WorldLayer::~WorldLayer()
	{

	}

	void WorldLayer::Attach()
	{

		Logger::LogMessage(Logger::LogType::Error, "Engine World Layer Attached!");

	}

	void WorldLayer::Detach()
	{

	}

	void WorldLayer::Draw()
	{
		DebugUI::BeginUI("Engine World Layer");
		DebugUI::AddElement(DebugUI::ElementType::Text, "Layer Text");
		DebugUI::EndUI();
	}

	void WorldLayer::InputEvent()
	{
		if (InputSystem::GetInputMode() == InputSystem::InputMode::Debug)
		{
			if (InputSystem::KeyPressed(EngineKeys::Space))
			{
				Logger::LogMessage(Logger::LogType::Message, "Leaving Engine Layer! Entering Game World Layer!");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::GameOnly);
			}
			
			if (InputSystem::KeyPressed(EngineKeys::ESC))
			{
				Application::QuitGame();
			}
		}
	}

	//********//
	//UI LAYER//
	//********//

	UILayer::UILayer() : Layer(2)
	{

	}

	UILayer::~UILayer()
	{

	}

	void UILayer::Attach()
	{
		Logger::LogMessage(Logger::LogType::Error, "Engine UI Layer Attached!");
	}

	void UILayer::Detach()
	{
		Logger::LogMessage(Logger::LogType::Error, "Engine UI Layer Removed!");
	}

	void UILayer::Draw()
	{
		DebugUI::BeginUI("Engine UI");
		DebugUI::AddElement(DebugUI::ElementType::Text, ("FPS: " + std::to_string(Application::GetFrameRate())).c_str());
		DebugUI::AddElement(DebugUI::ElementType::Text, "A - Log Message");
		DebugUI::AddElement(DebugUI::ElementType::Text, "Space - Remove Engine Layers");
		DebugUI::AddElement(DebugUI::ElementType::Text, "C - Add Engine Layers");
		DebugUI::AddElement(DebugUI::ElementType::Text, "S - Enter Game UI Layer From Game World Layer");
		DebugUI::AddElement(DebugUI::ElementType::Text, "BackSpace - Enter Engine Debug Layers From Game World Layer");
		DebugUI::AddElement(DebugUI::ElementType::Text, "D - Return To Game World Layer From Game UI Layer");
		DebugUI::AddElement(DebugUI::ElementType::Text, "Return To Game Layer From Engine Debug Layer - Space");
		DebugUI::AddElement(DebugUI::ElementType::Text, "Esc - Quit, When In Debug Layer");
		DebugUI::EndUI();
	}

	void UILayer::InputEvent()
	{
		//Logger::LogMessage(Logger::LogType::Message, "Engine UI Layer Input!");
	}


}