/*
* File: Game.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-01 (yyyy/mm/dd)
*
* Description: Bridge between the engine and scripts to allow the application to have more control over the engine
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/

//ENGINE
#include<Engine.h>
#include<Core/EntryPoint.h> //entry point

#include "../MovementScript.h"
#include "../BaseColorFlashScript.h"

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
			m_TestObjectOne = std::make_shared<ScriptableMeshObject>(m_CurrentScene, std::make_shared<MovementScript>(0.1f), MeshType::CONE_MESH, (UINT16)5);

			m_TestObjectTwo = std::make_shared<ScriptableMeshObject>(m_CurrentScene, std::make_shared<MovementScript>(1.f), MeshType::CYLINDER_MESH, (UINT16)15);
			
			m_TestObjectThree = std::make_shared<ScriptableSpriteObject3D>(m_CurrentScene, std::make_shared<MovementScript>(-0.1f));

			MeshComponent* mcOne = m_TestObjectOne->GetComponent<MeshComponent>();
			if (mcOne)
				mcOne->material.shader->SetUniformVec3("uColor", { 1.f, 0.1f, 0.1f });

			MeshComponent* mcTwo = m_TestObjectTwo->GetComponent<MeshComponent>();
			if (mcTwo)
				mcTwo->material.shader->SetUniformVec3("uColor", { 0.1f, 1.f, 0.1f });

			TransformComponent3D* tcTwo = m_TestObjectTwo->GetComponent<TransformComponent3D>();
			if (tcTwo)
				tcTwo->location.x = 10.f;

			ScriptComponent* scThree = m_TestObjectThree->GetComponent<ScriptComponent>();
			if (scThree)
				scThree->AddScript(std::make_shared<BaseColorFlashScript>(Maths::Vector3<float>{1.f, 0.f, 0.f}));

		//	TransformComponent3D* tcThree = m_TestObjectThree->GetComponent<TransformComponent3D>();
		//	if (tcThree)
		//	{
		//		tcThree->location = Maths::Vector3{ 20.f, 30.f, 0.f };
		//		tcThree->rotation = Maths::Vector3{ 20.f, 10.f, 35.f };
		//		tcThree->scale = Maths::Vector3{ 1.75f, 1.f, 1.2f };
		//	} 

		//	SpriteComponent* scThree = m_TestObjectThree->GetComponent<SpriteComponent>();
		//	if (scThree)
	//			scThree->material.shader->SetUniformVec3("uColor", { 0.1f, 0.1f, 1.f });

			Application::Start();
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

				if (InputSystem::KeyPressed(EngineKeys::TAB))
				{
					TransformComponent3D* tranComponent = m_TestObjectOne->GetComponent<TransformComponent3D>();
					if (tranComponent)
						tranComponent->location.x += 1.f * GetDeltaTime();
				}

				if (InputSystem::KeyTapped(EngineKeys::Space))
				{
					Logger::LogMessage(Logger::LogType::Message, "Camera Forward Vector: {}", glm::to_string(m_GameCamera->GetForwardVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Right Vector: {}", glm::to_string(m_GameCamera->GetRightVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Up Vector: {}", glm::to_string(m_GameCamera->GetUpVector()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Rotation: {}", glm::to_string(m_GameCamera->GetEulerRotation()));
					Logger::LogMessage(Logger::LogType::Message, "Camera Matrix: {}", glm::to_string(m_GameCamera->GetProjectionMatrix()));
				}
				
				m_GameCamera->ProcessRotation(InputSystem::GetMouseDelta(), false);

				Application::Tick();
			}
		}

	private:
		glm::vec3 m_Color = glm::vec3(0);
		Shader* m_Shader;

		//sample game objects to test the instantiation and everything
		std::shared_ptr<ScriptableMeshObject> m_TestObjectOne;
		std::shared_ptr<ScriptableMeshObject> m_TestObjectTwo;
		std::shared_ptr<ScriptableSpriteObject3D> m_TestObjectThree;
		
		std::shared_ptr<Camera::PerspectiveCamera> m_GameCamera;
		

		//temp model matrix
		glm::mat4 m_ModelMatrix = glm::mat4(1.f);
	};
}

Application* Engine::CreateApplication()
{
	return new VoxelGame::Game();
}


