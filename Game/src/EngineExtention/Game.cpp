
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
			m_GameCamera = std::make_shared<Camera::PerspectiveCamera>(glm::vec3{ 0.f, 0.f, 0.f });
			SetViewTargetCamera(m_GameCamera);
		}

		~Game()
		{
			delete m_Shader;
		}

		virtual void Start() override
		{
			Application::Start();


			m_TestObjectOne = std::make_shared<MeshObject>(m_CurrentScene, MeshType::CONE_MESH, 8);
			m_TestObjectTwo = std::make_shared<MeshObject>(m_CurrentScene, MeshType::CYLINDER_MESH, 15);
			m_TestObjectThree = std::make_shared<SpriteObject3D>(m_CurrentScene);

			MeshComponent* mcOne = m_TestObjectOne->GetComponent<MeshComponent>();
			if (mcOne)
				mcOne->material.shader->SetUniformVec3("uColor", { 1.f, 0.1f, 0.1f });

			TransformComponent3D* tcTwo = m_TestObjectTwo->GetComponent<TransformComponent3D>();
			if (tcTwo)
				tcTwo->location = Maths::Vector3{ 10.f, 0.f, 0.f };

			MeshComponent* mcTwo = m_TestObjectTwo->GetComponent<MeshComponent>();
			if (mcTwo)
				mcTwo->material.shader->SetUniformVec3("uColor", { 0.1f, 1.f, 0.1f });

			TransformComponent3D* tcThree = m_TestObjectThree->GetComponent<TransformComponent3D>();
			if (tcThree)
			{
				tcThree->location = Maths::Vector3{ 20.f, 0.f, 0.f };
				tcThree->rotation = Maths::Vector3{ 20.f, 10.f, 35.f };
				tcThree->scale = Maths::Vector3{ 1.75f, 1.f, 1.2f };
			} 

			SpriteComponent* scThree = m_TestObjectThree->GetComponent<SpriteComponent>();
			if (scThree)
				scThree->material.shader->SetUniformVec3("uColor", { 0.1f, 0.1f, 1.f });

			Tick();
		}

		virtual void Tick() override
		{
			while (m_Running)
			{		
				if (InputSystem::KeyPressed(EngineKeys::W))
				{
					m_GameCamera->ProcessLocation(Camera::EditorCamera::MoveDirection::Forward, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::S))
				{
					m_GameCamera->ProcessLocation(Camera::EditorCamera::MoveDirection::Backwards, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::A))
				{
					m_GameCamera->ProcessLocation(Camera::EditorCamera::MoveDirection::Left, GetDeltaTime());
				}
				
				if (InputSystem::KeyPressed(EngineKeys::D))
				{
					m_GameCamera->ProcessLocation(Camera::EditorCamera::MoveDirection::Right, GetDeltaTime());
				}

				if (InputSystem::KeyTapped(EngineKeys::TAB))
				{
					m_GameFocus = !m_GameFocus;
					Logger::LogMessage(Logger::LogType::Message, "tab pressed");
				}

				if (InputSystem::KeyTapped(EngineKeys::Space))
				{
					Logger::LogMessage(Logger::LogType::Message, "Camera Forward Vector: {}", glm::to_string(m_GameCamera->GetForwardVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Right Vector: {}", glm::to_string(m_GameCamera->GetRightVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Up Vector: {}", glm::to_string(m_GameCamera->GetUpVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Rotation: {}", glm::to_string(m_GameCamera->GetEulerRotation()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Matrix: {}", glm::to_string(m_GameCamera->GetProjectionMatrix()));
				}
				
				if (m_GameFocus)
				{
					m_GameCamera->ProcessRotation(InputSystem::GetMouseDelta(), false);
				}
			

				Application::Tick();
			}
		}

	private:
		glm::vec3 m_Color = glm::vec3(0);
		Shader* m_Shader;

		//sample game objects to test the instantiation and everything
		std::shared_ptr<MeshObject> m_TestObjectOne;
		std::shared_ptr<MeshObject> m_TestObjectTwo;
		std::shared_ptr<SpriteObject3D> m_TestObjectThree;
		
		std::shared_ptr<Camera::PerspectiveCamera> m_GameCamera;
		
		bool m_GameFocus = true;

		//temp model matrix
		glm::mat4 m_ModelMatrix = glm::mat4(1.f);
	};
}

Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


