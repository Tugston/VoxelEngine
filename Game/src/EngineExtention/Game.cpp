#pragma once

//this class serves as a bridge between the engine and game objects, scenes, etc
//ideally the game would only make game objects, but I want the game to have a little more control
//may change in the future, but this just makes sense to me currently

//ENGINE
#include<Engine.h>
#include<Core/EntryPoint.h>  //ENTRY POINT CAN ONLY INCLUDE ONCE

//GAME
#include "GameLayers.h"

namespace VoxelGame
{
	class Game : public Application
	{
	public:
		Game() : Application()
		{
		}

		~Game() override
		{

		}

		void Start() override
		{
			Logger::LogMessage(Logger::LogType::Warning, "Started!");

			//I want to create a simpler system for the game to add new layers
			//this is temporary, the scenes will automatically add layers when it is instantiated
			Application::AddLayer(new UILayer, true);
			Application::AddLayer(new Engine::UILayer, true);
			Application::AddLayer(new WorldLayer, false);
			Application::AddLayer(new Engine::WorldLayer, false);

			Application::Start();
			Tick();
		}

		void Tick() override
		{
			while (gameIsRunning)
			{
				if (InputSystem::KeyPressed(EngineKeys::Enter))
				{
					Logger::LogMessage(Logger::LogType::Message, "Mouse Pos ({}, {})", InputSystem::GetMouseX(),
						InputSystem::GetMouseY());
				}

				Application::Tick();
			}
		}

	private:

	};
}

Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


