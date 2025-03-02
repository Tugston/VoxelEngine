#include "GameLayers.h"

namespace VoxelGame
{
	//***********//
	//WORLD LAYER//
	//***********//
	WorldLayer::WorldLayer()
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

	void WorldLayer::Draw()
	{
		Engine::Logger::LogMessage(Engine::Logger::LogType::Message, "World Layer Draw!");
	}

	void WorldLayer::InputEvent()
	{
		if (InputSystem::GetInputMode() == InputSystem::InputMode::GameOnly)
		{
			if (Engine::InputSystem::KeyPressed(Engine::EngineKeys::A))
			{
				Logger::LogMessage(Logger::LogType::Warning, "World Layer Input");
			}
			else if (InputSystem::KeyPressed(Engine::EngineKeys::S))
			{
				Logger::LogMessage(Logger::LogType::Warning, "Leaving World Layer!");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::UIOnly);
			}
		}
	}


	//********//
	//UI LAYER//
	//********//
	UILayer::UILayer()
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

	void UILayer::Draw()
	{
		Engine::Logger::LogMessage(Engine::Logger::LogType::Message, "UI Layer Draw!");
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
