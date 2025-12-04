#pragma once

//ENGINE
#include "Core/Core.h"
#include "Core/Logger.h"
#include "Scene/Scene.h"
#include "Scene/ECS/Components/Positionals/Transform.h"

//this is purely an abstraction class that allows the engine api to only use GameObjects for everything like normal
//masks away the underlying ecs

namespace Engine::Scene::ECS
{
	class GameObject
	{
	public:
		//delete default for now, until I get the scene manager all setup
		GameObject() = delete;
		GameObject(std::shared_ptr<Scene> scene);
		~GameObject();

		virtual void Start() = 0;
		virtual void Tick(float deltaTime) = 0;

	public:
		template<typename t, typename... Args>
		t* AddComponent(Args&&... args)
		{
			if (Scene* currentScene = m_Scene.lock().get())
			{
				Logger::LogMessage(Logger::LogType::Message, "<GameObject.h> Adding {} component to Object [ {} ]", typeid(t).name(), m_ID);
				return currentScene->RegisterComponent<t>(m_ID, std::forward<Args>(args)...);
			}
			else
			{
				LOG_ERR("<GameObject.h> Could Not Create Component for Object [ {} ]", m_ID);
			}

			return nullptr;
		}

		template<typename t>
		void RemoveComponent(t*& componentRef)
		{
			if (Scene* currentScene = m_Scene.lock().get())
			{
				LOG_MSG("<GameObject.h> Removing {} component from Object [ {} ]", typeid(t).name(), m_ID);
				currentScene->DestroyComponent<t>(m_ID);
				componentRef = nullptr;
			}
		}

		//returns nullptr if component cannot be found
		template<typename t>
		t* GetComponent()
		{
			if (Scene* currentScene = m_Scene.lock().get())
				return currentScene->GetObjectComponent<t>(m_ID);
			return nullptr;
		}

		//this is utilized for testing, objectID is internal use
		EntityID GetID() const { return m_ID; }

	private:
		EntityID m_ID;
		std::weak_ptr<Scene> m_Scene;
	};

	class GameObject2D : public GameObject
	{
	public:
		GameObject2D(std::shared_ptr<Scene> scene);
		~GameObject2D();

		virtual void Start() override;
		virtual void Tick(float deltaTime) override;

	protected:
		Components::TransformComponent2D* m_TransformComponent;
		Components::TransformComponent2D* m_SecondTransformComponent;
	};

	class GameObject3D : public GameObject
	{
	public:
		GameObject3D(std::shared_ptr<Scene> scene);
		~GameObject3D();

		virtual void Start() override;
		virtual void Tick(float deltaTime) override;

	protected:
		Components::TransformComponent3D* m_TransformComponent;
	};
}
