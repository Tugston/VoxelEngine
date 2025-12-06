/*
* File: GameObject.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-26 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
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
		m_SecondTransformComponent = AddComponent<Components::TransformComponent2D>();
	}

	GameObject2D::~GameObject2D()
	{

	}

	void GameObject2D::Start()
	{
	}

	void GameObject2D::Tick(float deltaTime)
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
		//RemoveComponent<Components::TransformComponent3D>(m_TransformComponent);
		LOG_MSG("Location: {}", m_TransformComponent->location.x);
	}

	GameObject3D::~GameObject3D()
	{
	}

	void GameObject3D::Start()
	{
	}

	void GameObject3D::Tick(float deltaTime)
	{
	}

	//**************
	//GAME OBJECT 3D
	//**************
}
