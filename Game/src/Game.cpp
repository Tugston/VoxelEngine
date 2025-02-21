
//ENGINE
#include<Engine.h>
#include<Core/EntryPoint.h>  //ENTRY POINT CAN ONLY INCLUDE ONCE

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
			Tick();
		}

		void Tick() override
		{
			while (gameIsRunning)
			{
				Engine::Application::Tick();
				Draw(GetDeltaTime());
			}
		}

	private:

	};
}

Engine::Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


