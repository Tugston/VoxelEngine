#include "egpch.h"
#include "GameObject.h"

//STND
#include <memory>

namespace Engine::Scene::ECS
{
	//***********
	//GAME OBJECT
	//***********
	GameObject::GameObject(std::shared_ptr<Scene> scene): m_Scene(scene), m_ID(0)
	{
		//I just want to ensure the scene is ready before calling this
		if (Scene* currentScene = m_Scene.lock().get())
			m_ID = currentScene->RegisterObject();
		else
			LOG_ERR("<GameObject.cpp> Could Not Register Object, Scene Not Valid!");
	}

	GameObject::~GameObject()
	{
	}
	
	//***********
	//GAME OBJECT
	//***********


	//**************
	//GAME OBJECT 2D
	//**************

	GameObject2D::GameObject2D(std::shared_ptr<Scene> scene): GameObject(scene)
	{
		m_TransformComponent = AddComponent<Components::TransformComponent2D>();
	}

	GameObject2D::~GameObject2D()
	{

	}

	//**************
	//GAME OBJECT 2D
	//**************



	//**************
	//GAME OBJECT 3D
	//**************

	GameObject3D::GameObject3D(std::shared_ptr<Scene> scene): GameObject(scene)
	{
		m_TransformComponent = AddComponent<Components::TransformComponent3D>();
	}

	GameObject3D::~GameObject3D()
	{
	}

	//**************
	//GAME OBJECT 3D
	//**************
}
