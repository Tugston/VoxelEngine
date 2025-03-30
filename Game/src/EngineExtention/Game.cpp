
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
			m_Shader = new Renderer::Shader("TestShader");
			m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.f, 0.f, -3.f));
			m_ModelMatrix = glm::rotate(m_ModelMatrix, (0 * (EG_PI_FLOAT / 180)), glm::vec3(0.f, 1.f, 0.f));
			m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(1.f, 1.f, 1.f));

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
				m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
				m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
				m_Shader->SetUniformMat4("uModel", m_ModelMatrix);

				if (InputSystem::KeyPressed(EngineKeys::W))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Forward, GetDeltaTime());
				}
				else if (InputSystem::KeyPressed(EngineKeys::S))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Backwards, GetDeltaTime());
				}
				else if (InputSystem::KeyPressed(EngineKeys::A))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Left, GetDeltaTime());
				}
				else if (InputSystem::KeyPressed(EngineKeys::D))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Right, GetDeltaTime());
				}

				if (InputSystem::KeyTapped(EngineKeys::Space))
				{
					Logger::LogMessage(Logger::LogType::Message, "Camera Forward Vector: {}", glm::to_string(m_Camera->GetForwardVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Right Vector: {}", glm::to_string(m_Camera->GetRightVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Up Vector: {}", glm::to_string(m_Camera->GetUpVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Rotation: {}", glm::to_string(m_Camera->GetEulerRotation()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Matrix: {}", glm::to_string(m_Camera->GetProjectionMatrix()));
				}
				
				if (ENGINE_MOUSE_IDLE)
				{
				//	Logger::LogMessage(Logger::LogType::Message, "Mouse Idle");
				}
				else if (ENGINE_MOUSE_UP)
				{
				//	m_Camera.ProcessRotation(glm::vec3(1, 0, 0), true);
				//	Logger::LogMessage(Logger::LogType::Message, "Mouse UP!");
				}
				else if (ENGINE_MOUSE_DOWN)
				{
				//	m_Camera.ProcessRotation(glm::vec3(-1, 0, 0), true);
				//	Logger::LogMessage(Logger::LogType::Message, "Mouse Down!");
				}

				if (ENGINE_MOUSE_IDLE)
				{
					
				}
				else if (ENGINE_MOUSE_LEFT)
				{
				//	m_Camera.ProcessRotation(glm::vec3(0, 0, 1), false);
				//	Logger::LogMessage(Logger::LogType::Message, "Mouse Left!");
				}
				else if (ENGINE_MOUSE_RIGHT)
				{
				//	m_Camera.ProcessRotation(glm::vec3(0, 0, -1), false);
				//	Logger::LogMessage(Logger::LogType::Message, "Mouse Right!");
				}
				//***

				Application::Tick();
			}
		}

	private:
		glm::vec3 m_Color = glm::vec3(0);
		Renderer::Shader* m_Shader;

		//Renderer::PerspectiveCamera m_Camera;


		//temp model matrix
		glm::mat4 m_ModelMatrix = glm::mat4(1.f);
	};
}

Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


