#include "egpch.h"
#include "GameLayers.h"

//ENGINE
#include "Core/Core.h"
#include "Core/Logger.h"
#include "Core/Layers/EngineLayers.h"
#include "Input/Input.h" //temporary include, game objects should handle the actual inputs

namespace Engine
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
		Logger::LogMessage(Logger::LogType::Error, "World Layer Attached!");
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
		//gotta have and here lol, haha kinda tricky. Love spending an hour fixing a small dumb bug!!!! :D
		if(InputSystem::GetInputMode() != InputSystem::InputMode::GameOnly && InputSystem::GetInputMode() != InputSystem::InputMode::UIOnly)


		//some docs for this
		//game UI layer should only be entered by the player when pausing, going to title screen, dying, inventory, etc.
		//removing layers should not be a part of the dist game at all, same with adding
		// **will want to add a command that lets you turn all of this on though, but thats for way later**
		//

#ifdef EG_DEBUG

			if (InputSystem::KeyTapped(Engine::EngineKeys::F2))
			{
				LOG_MSG("Entering Engine Layer!");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::Debug);
			}
			else if (InputSystem::KeyTapped(Engine::EngineKeys::F3))
			{
				LOG_MSG("Currently Game World Layer!");
			}
			else if (InputSystem::KeyTapped(EngineKeys::F11))
			{
				LOG_WARN("Removed Engine Layers");
				REMOVE_ENGINE_DEBUG_LAYER;
				REMOVE_ENGINE_UI_LAYER;
			}
			else if (InputSystem::KeyTapped(EngineKeys::F12))
			{
				LayerStack::PushWorldLayer(new EngineWorldLayer);
				LayerStack::PushUILayer(new EngineUILayer);
			}

#endif	

			if (InputSystem::KeyTapped(EngineKeys::F1))
			{
				//debug overlay stuff for the game, like player position and what not, y'know like how minecraft has it
				//wont get to this for a while though
			}

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
