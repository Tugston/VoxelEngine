
//ENGINE
#include<Engine.h>
#include<Core/EntryPoint.h>  //ENTRY POINT CAN ONLY INCLUDE ONCE

//this class serves as a bridge between the engine and game objects, scenes, etc
namespace VoxelGame
{
	class Game : public Engine::Application
	{
	public:
		Game() : Engine::Application()
		{

		}

		~Game() override
		{

		}

		void Start() override
		{
			Engine::Logger::LogMessage(Engine::Logger::LogType::Warning, "Started!");
			Engine::Application::Start();
			Tick();
		}

		void Tick() override
		{
			while (gameIsRunning)
			{
				if (Engine::InputSystem::KeyPressed(Engine::EngineKeys::Enter))
				{
					Engine::Logger::LogMessage(Engine::Logger::LogType::Message, "Mouse Pos ({}, {})", Engine::InputSystem::GetMouseX(),
						Engine::InputSystem::GetMouseY());
				}

				Engine::Application::Tick();
			}
		}

	private:

	};
}

Engine::Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


