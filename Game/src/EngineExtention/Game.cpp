
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

		~Game()
		{
			delete m_Shader;
		}

		virtual void Start() override
		{
			Application::Start();

			m_Shader->Create();


			m_TestObjectOne = std::make_shared<GameObject3D>(m_CurrentScene);
			m_TestObjectTwo = std::make_shared<GameObject2D>(m_CurrentScene);
			m_TestObjectThree = std::make_shared<GameObject3D>(m_CurrentScene);


			Logger::LogMessage(Logger::LogType::Message, "Object One ID (Should be 1): {}", m_TestObjectOne->GetID());
			Logger::LogMessage(Logger::LogType::Message, "Object Two ID (Should be 2): {}", m_TestObjectTwo->GetID());
			Logger::LogMessage(Logger::LogType::Message, "Object Three ID (Should be 3): {}", m_TestObjectThree->GetID());

			Tick();
		}

		virtual void Tick() override
		{
			while (m_Running)
			{

				//ALL TEST STUFF
				/*
				Debug::UI::Refresh();
				Debug::UI::BeginUI("Engine Menu", false);
				Debug::UI::AddElement<std::string, glm::vec3>(Debug::ElementType::ColorEdit3, "Color", &m_Color);
				Debug::UI::AddElement<std::string, float>(Debug::ElementType::InputFloat, "Camera Rot Sensitivity",
					&m_Camera->GetSettings()->sensitivity, 0.005f, 1.f, "%.005f", 0);
				Debug::UI::AddElement<std::string, float>(Debug::ElementType::InputFloat, "Camera Move Speed",
					&m_Camera->GetSettings()->speed, 0.f, 3.f, "%.01f", 0);
				Debug::UI::EndUI(); */


				m_Shader->Use();

				m_Shader->SetUniformVec3("uColor", m_Color);
				m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
				m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
				m_Shader->SetUniformMat4("uModel", m_ModelMatrix);

				if (InputSystem::KeyPressed(EngineKeys::W))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Forward, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::S))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Backwards, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::A))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Left, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::D))
				{
					m_Camera->ProcessLocation(Renderer::MoveDirection::Right, GetDeltaTime());
				}

				if (InputSystem::KeyTapped(EngineKeys::TAB))
				{
					m_GameFocus = !m_GameFocus;
					Logger::LogMessage(Logger::LogType::Message, "tab pressed");
				}

				if (InputSystem::KeyTapped(EngineKeys::Space))
				{
					Logger::LogMessage(Logger::LogType::Message, "Camera Forward Vector: {}", glm::to_string(m_Camera->GetForwardVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Right Vector: {}", glm::to_string(m_Camera->GetRightVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Up Vector: {}", glm::to_string(m_Camera->GetUpVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Rotation: {}", glm::to_string(m_Camera->GetEulerRotation()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Matrix: {}", glm::to_string(m_Camera->GetProjectionMatrix()));
				}
				
				if (m_GameFocus)
				{
					m_Camera->ProcessRotation(InputSystem::GetMouseDelta(), false);
					InputSystem::SetPreviousMousePos(InputSystem::GetMousePos());
				}
			

				Application::Tick();
			}
		}

	private:
		glm::vec3 m_Color = glm::vec3(0);
		Renderer::Shader* m_Shader;

		//sample game objects to test the instantiation and everything
		std::shared_ptr<GameObject3D> m_TestObjectOne;
		std::shared_ptr<GameObject2D> m_TestObjectTwo;
		std::shared_ptr<GameObject3D> m_TestObjectThree;
		
		//Renderer::PerspectiveCamera m_Camera;
		
		bool m_GameFocus = true;

		//temp model matrix
		glm::mat4 m_ModelMatrix = glm::mat4(1.f);
	};
}

Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


