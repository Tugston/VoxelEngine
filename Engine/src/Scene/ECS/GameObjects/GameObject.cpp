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
		AddComponent<Components::TransformComponent2D>();
	}

	GameObject2D::GameObject2D(std::shared_ptr<Scene> scene, const Components::TransformComponent2D& transform): GameObject(scene)
	{
		AddComponent<Components::TransformComponent2D>();
		Components::TransformComponent2D* transformComp = GetComponent<Components::TransformComponent2D>();
		transformComp->location = transform.location;
		transformComp->rotation = transform.rotation;
		transformComp->scale = transform.scale;
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
		AddComponent<Components::TransformComponent3D>();
	}

	GameObject3D::GameObject3D(std::shared_ptr<Scene> scene, const Components::TransformComponent3D& transform): GameObject(scene)
	{
		AddComponent<Components::TransformComponent3D>();
		Components::TransformComponent3D* transformComp = GetComponent<Components::TransformComponent3D>();
		transformComp->location = transform.location;
		transformComp->rotation = transform.rotation;
		transformComp->scale = transform.scale;
	}

	GameObject3D::~GameObject3D()
	{
	}

	//**************
	//GAME OBJECT 3D
	//**************
}
