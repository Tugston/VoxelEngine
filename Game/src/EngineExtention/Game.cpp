
//this class serves as a bridge between the engine and game objects, scenes, etc
//ideally the game would only make game objects, but I want the game to have a little more control
//may change in the future, but this just makes sense to me currently

//ENGINE
#include<Engine.h>
#include<Core/EntryPoint.h> //entry point

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

		virtual void Start() override
		{
			Application::Start();



			Tick();
		}

		virtual void Tick() override
		{
			while (m_Running)
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


