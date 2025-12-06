
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

		~Game()
		{
			delete m_Shader;
		}

		virtual void Start() override
		{
			Application::Start();


			m_TestObjectOne = std::make_shared<GameObject3D>(m_CurrentScene);
			m_TestObjectTwo = std::make_shared<GameObject2D>(m_CurrentScene);
			m_TestObjectThree = std::make_shared<GameObject3D>(m_CurrentScene);

			m_TestObjectOne->AddComponent<SpriteComponent>();
			m_TestObjectThree->AddComponent<SpriteComponent>();

			SpriteComponent* scOne = m_TestObjectOne->GetComponent<SpriteComponent>();
			TransformComponent3D* tcOne = m_TestObjectOne->GetComponent<TransformComponent3D>();
			if (scOne)
			{
				scOne->planeMesh = std::make_shared<Utility::Mesh>(Utility::CreateQuad());
				scOne->planeMesh->indexCount = 6;
				scOne->material.shader = new Shader("TestShader");
				scOne->material.shader->Create();
			}

			SpriteComponent* scTwo = m_TestObjectThree->GetComponent<SpriteComponent>();
			TransformComponent3D* tcTwo = m_TestObjectThree->GetComponent<TransformComponent3D>();
			
			if (scTwo)
			{
				scTwo->planeMesh = std::make_shared<Utility::Mesh>(Utility::CreateQuad());
				scTwo->planeMesh->indexCount = 6;
				scTwo->material.shader = new Shader("TestShader");
				scTwo->material.shader->Create();
			}

			if (tcTwo)
			{
				tcTwo->location = Maths::Vector3{ 25.f, 0.f, 0.f };
				tcTwo->rotation = Maths::Vector3{ 20.f, 10.f, 35.f };
				tcTwo->scale = Maths::Vector3{ 1.75f, 1.f, 1.2f };
			} 

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


				//m_Shader->Use();
				SpriteComponent* sc = m_TestObjectOne->GetComponent<SpriteComponent>();
				SpriteComponent* sc2 = m_TestObjectThree->GetComponent<SpriteComponent>();

				if (sc)
				{
					sc->material.shader->Use();
					sc->material.shader->SetUniformVec3("uColor", m_Color);
					sc->material.shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
					sc->material.shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
				}

				if (sc2)
				{
					sc->material.shader->Use();
					glm::vec3 blue{ 0.1f, 0.1f, 1.f };
					sc->material.shader->SetUniformVec3("uColor", blue);
					sc2->material.shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
					sc2->material.shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
				}

				if (InputSystem::KeyPressed(EngineKeys::W))
				{
					m_Camera->ProcessLocation(Camera::EditorCamera::MoveDirection::Forward, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::S))
				{
					m_Camera->ProcessLocation(Camera::EditorCamera::MoveDirection::Backwards, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::A))
				{
					m_Camera->ProcessLocation(Camera::EditorCamera::MoveDirection::Left, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::D))
				{
					m_Camera->ProcessLocation(Camera::EditorCamera::MoveDirection::Right, GetDeltaTime());
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
		Shader* m_Shader;

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


