
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
		Game() : Application(), m_Camera(glm::vec3(100, 0, 0))
		{
			m_Shader = new Renderer::Shader("TestShader");
		}

		~Game() override
		{

		}

		virtual void Start() override
		{
			Application::Start();

			m_Shader->Create();
			Tick();
		}

		virtual void Tick() override
		{
			while (m_Running)
			{
				//ALL TEST STUFF
				Debug::UI::Refresh();
				Debug::UI::BeginUI("Engine Menu");
				Debug::UI::AddElement<std::string, glm::vec3>(Debug::ElementType::ColorEdit3, "Color", &m_Color);
				Debug::UI::EndUI();


				m_Shader->Use();

				m_Shader->SetUniformVec3("uColor", m_Color);
				m_Shader->SetUniformMat4("uProjection", m_Camera.GetProjectionMatrix());
				m_Shader->SetUniformMat4("uView", m_Camera.GetViewMatrix());
				m_Shader->SetUniformMat4("uModel", m_ModelMatrix);

				if (InputSystem::KeyPressed(EngineKeys::W))
				{
					m_Camera.Update(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), GetDeltaTime());
				}
				else if (InputSystem::KeyPressed(EngineKeys::S))
				{
					m_Camera.Update(glm::vec3(-1, 0, 0), glm::vec3(0, 0, 0), GetDeltaTime());
				}
				
				if (ENGINE_MOUSE_IDLE)
					Logger::LogMessage(Logger::LogType::Message, "Mouse Still!");
				else if (ENGINE_MOUSE_UP)
					Logger::LogMessage(Logger::LogType::Message, "Mouse UP!");
				else if (ENGINE_MOUSE_DOWN)
					Logger::LogMessage(Logger::LogType::Message, "Mouse Down!");
				
				if (ENGINE_MOUSE_IDLE)
					Logger::LogMessage(Logger::LogType::Message, "Mouse Still 2");
				else if (ENGINE_MOUSE_LEFT)
					Logger::LogMessage(Logger::LogType::Message, "Mouse Left!");
				else if (ENGINE_MOUSE_RIGHT)
					Logger::LogMessage(Logger::LogType::Message, "Mouse Right!");
				//***

				Application::Tick();
			}
		}

	private:
		glm::vec3 m_Color = glm::vec3(0);
		Renderer::Shader* m_Shader;
		Renderer::PerspectiveCamera m_Camera;

		//temp model matrix
		glm::mat4 m_ModelMatrix = glm::mat4(10);
	};
}

Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


