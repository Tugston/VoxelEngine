#include "egpch.h"
#include "EngineLayers.h"

//ENGINE
#include "Core/Application.h"
#include "Core/Logger.h"
#include "Input/Input.h"
#include "Core/Debug/DebugUI.h"


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

	//***********//
	//WORLD LAYER//
	//***********//

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
	}

	void EngineUILayer::InputEvent()
	{
	}

	//********//
	//UI LAYER//
	//********//
}