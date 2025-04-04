#include "egpch.h"
#include "GameLayers.h"

//ENGINE
#include "Core/Core.h"
#include "Core/Logger.h"
#include "Core/Layers/EngineLayers.h"
#include "Input/Input.h" //temporary include, game objects should handle the actual inputs

namespace Engine::API
{
	//***********//
	//WORLD LAYER//
	//***********//
	WorldLayer::WorldLayer() : Layer(3)
	{
	}

	WorldLayer::~WorldLayer()
	{
	}

	void WorldLayer::Attach()
	{
		Engine::Logger::LogMessage(Engine::Logger::LogType::Error, "World Layer Attached!");
	}

	void WorldLayer::Detach()
	{
	}

	void WorldLayer::GetDrawData()
	{
	//	Engine::Logger::LogMessage(Engine::Logger::LogType::Message, "World Layer Draw!");
		return;
	}

	void WorldLayer::InputEvent()
	{
		/*
		if (InputSystem::GetInputMode() == InputSystem::InputMode::GameOnly)
		{
			if (Engine::InputSystem::KeyPressed(Engine::EngineKeys::A))
			{
				Logger::LogMessage(Logger::LogType::Warning, "World Layer Input");
			}
			else if (InputSystem::KeyPressed(Engine::EngineKeys::S))
			{
				Logger::LogMessage(Logger::LogType::Error, "Leaving Game World Layer! Entering Game UI Layer!");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::UIOnly);
			}
			else if (InputSystem::KeyPressed(Engine::EngineKeys::BackSpace))
			{
				Logger::LogMessage(Logger::LogType::Error, "Leaving Game World Layer! Entering Engine Layer!");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::Debug);
			}
			else if (InputSystem::KeyPressed(Engine::EngineKeys::Space))
			{
				Logger::LogMessage(Logger::LogType::Warning, "Removed Engine Layers");

				REMOVE_ENGINE_DEBUG_LAYER;
				REMOVE_ENGINE_UI_LAYER;
			}
			else if (InputSystem::GetScrollDirection() == 1)
			{
				Logger::LogMessage(Logger::LogType::Warning, "Positive Scroll Direction");
				Logger::LogMessage(Logger::LogType::Message, "{}", InputSystem::GetScrollDirection());
			}
			else if (InputSystem::KeyPressed(EngineKeys::LSHIFT) && InputSystem::KeyPressed(EngineKeys::P))
			{
				Logger::LogMessage(Logger::LogType::Message, "Compound keys work");
			}
			else if (InputSystem::KeyTapped(EngineKeys::C))
			{
				Engine::LayerStack::PushSpaceLayer(new Engine::WorldLayer);
				Engine::LayerStack::PushUILayer(new Engine::UILayer);
				
			}
		}*/
	}


	//********//
	//UI LAYER//
	//********//
	UILayer::UILayer() : Layer(4)
	{
	}

	UILayer::~UILayer()
	{
	}

	void UILayer::Attach()
	{
		Engine::Logger::LogMessage(Engine::Logger::LogType::Error, "UI Layer Attached!");
	}

	void UILayer::Detach()
	{		
	}

	void UILayer::GetDrawData()
	{
		return;
	}

	void UILayer::InputEvent()
	{
		if (InputSystem::GetInputMode() == InputSystem::InputMode::UIOnly)
		{
			if (InputSystem::KeyPressed(EngineKeys::A))
			{
				Logger::LogMessage(Logger::LogType::Warning, "UI Layer Input!");
			}
			else if (InputSystem::KeyPressed(EngineKeys::D))
			{
				Logger::LogMessage(Logger::LogType::Warning, "Leaving UI Layer");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::GameOnly);
			}
		}
	}

}
