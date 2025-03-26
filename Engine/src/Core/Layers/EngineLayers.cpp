#include "egpch.h"
#include "EngineLayers.h"

//ENGINE
#include "Core/Application.h"
#include "Core/Logger.h"
#include "Input/Input.h"
#include "Core/Debug/DebugUI.h"
#include "Renderer/Core/RenderData.h"


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

	void WorldLayer::GetDrawData()
	{
	//	DebugUI::BeginUI("Engine World Layer");
	//	DebugUI::AddElement(DebugUI::ElementType::Text, "Layer Text");
	//	DebugUI::EndUI();
		return;
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

	void UILayer::GetDrawData()
	{
		
		Debug::UI::BeginUI("Engine UI");
		const std::string& frameRate = std::to_string(Application::GetFrameRate());
		const unsigned int& frameRateVal = Application::GetFrameRate();
		if (frameRateVal > 50)
		{
			unsigned int color = 0x00FF00FF;
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::ColoredText, frameRate, nullptr, color);
		}
		else if (frameRateVal <= 50 && frameRateVal > 20)
		{
			unsigned int color = 0xFFFF00FF;
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::ColoredText, frameRate, nullptr, color);
		}
		else if (frameRateVal <= 20)
		{
			unsigned int color = 0xFF0000FF;
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::ColoredText, frameRate, nullptr, color);
		}
		
		if (m_ShowAllData)
		{
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "A - Log Message", nullptr, NULL);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Space - Remove Engine Layers", nullptr, NULL);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "C - Add Engine Layers", nullptr, NULL);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "S - Enter Engine Debug Layer From Game World Layer", nullptr, NULL);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Backspace - Enter Engine Debug Layers From Game World Layer", nullptr, NULL);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "D - Return To Game World Layer From Game UI Layer", nullptr, NULL);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Return To Game Layer From Engine Debug Layer - Space", nullptr, NULL);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Esc - Quit, When In Debug Layer", nullptr, NULL);

			Debug::UI::AddElement<std::string, float>(Debug::ElementType::DragFloat, "Test Float", &m_TestFloat, 1.f, -5.f, 10.f, "%.3f", 0);
		}

		
		Debug::UI::AddElement<std::string, bool>(Debug::ElementType::CheckBox, "Show Controls and Dev Tests", &m_ShowAllData, NULL);

	
		Debug::UI::EndUI();
		return;
	}

	void UILayer::InputEvent()
	{
	}


}