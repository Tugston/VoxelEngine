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
	EngineWorldLayer::EngineWorldLayer() : Layer(1)
	{

	}

	EngineWorldLayer::~EngineWorldLayer()
	{

	}

	void EngineWorldLayer::Attach()
	{
		//theres probably some sort of debug line drawing subsystem that needs to go here
		Logger::LogMessage(Logger::LogType::Error, "Engine World Layer Attached!");
	}

	void EngineWorldLayer::Detach()
	{

	}

	void EngineWorldLayer::GetDrawData()
	{
		//need to collect all the verts, textures, etc from ecs so then the renderer can draw them
		return;
	}

	void EngineWorldLayer::InputEvent()
	{
		if (InputSystem::GetInputMode() == InputSystem::InputMode::Debug)
		{
			if (InputSystem::KeyTapped(EngineKeys::F1))
			{
				Logger::LogMessage(Logger::LogType::Message, "Leaving Debug Mode");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::GameOnly);
			}
			else if (InputSystem::KeyPressed(EngineKeys::ESC))
			{
				//game should handle pause menu with escape, so quitting application for engine layer
				Application::QuitGame();
			}
		}
	}

	//********//
	//UI LAYER//
	//********//

	EngineUILayer::EngineUILayer() : Layer(2)
	{

	}

	EngineUILayer::~EngineUILayer()
	{

	}

	void EngineUILayer::Attach()
	{
		Logger::LogMessage(Logger::LogType::Error, "Engine UI Layer Attached!");
	}

	void EngineUILayer::Detach()
	{
		Logger::LogMessage(Logger::LogType::Error, "Engine UI Layer Removed!");
	}

	void EngineUILayer::GetDrawData()
	{
	/*
		Debug::UI::BeginUI("Engine UI", false);
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
		
		if (!m_ShowAllData)
		{
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "A - Log Message", nullptr);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Space - Remove Engine Layers", nullptr);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "C - Add Engine Layers", nullptr);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "S - Enter Engine Debug Layer From Game World Layer", nullptr);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Backspace - Enter Engine Debug Layers From Game World Layer", nullptr);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "D - Return To Game World Layer From Game UI Layer", nullptr);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Return To Game Layer From Engine Debug Layer - Space", nullptr);
			Debug::UI::AddElement<std::string, char>(Debug::ElementType::Text, "Esc - Quit, When In Debug Layer", nullptr);

			Debug::UI::AddElement<std::string, float>(Debug::ElementType::DragFloat, "Test Float", &m_TestFloat, 1.f, -5.f, 10.f, "%.3f", 0);
		}

		
		Debug::UI::AddElement<std::string, bool>(Debug::ElementType::CheckBox, "Show Controls and Dev Tests", &m_ShowAllData, NULL);

	
		Debug::UI::EndUI();
		return;
		*/
	}

	void EngineUILayer::InputEvent()
	{
	}


}