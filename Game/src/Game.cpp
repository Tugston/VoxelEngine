
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
			Tick();
		}

		void Tick() override
		{
			while (gameIsRunning)
			{
				Engine::Application::Tick();

				Engine::Logger::LogMessage(Engine::Logger::LogType::Warning, "Tick Called");

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


