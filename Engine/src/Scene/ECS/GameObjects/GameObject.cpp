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
	GameObject::GameObject(ECS::Registry& registry): m_Registry(registry), m_ID(0)
	{
		m_ID = m_Registry.CreateEntity();
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

	GameObject2D::GameObject2D(ECS::Registry& registry): GameObject(registry)
	{
		AddComponent<Components::TransformComponent2D>();
	}

	GameObject2D::GameObject2D(ECS::Registry& registry, const Components::TransformComponent2D& transform): GameObject(registry)
	{
		AddComponent<Components::TransformComponent2D>(transform.location, transform.rotation, transform.scale);
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

	GameObject3D::GameObject3D(ECS::Registry& registry): GameObject(registry)
	{
		AddComponent<Components::TransformComponent3D>();
	}

	GameObject3D::GameObject3D(ECS::Registry& registry, const Components::TransformComponent3D& transform): GameObject(registry)
	{
		AddComponent<Components::TransformComponent3D>(transform.location, transform.rotation, transform.scale);
	}

	GameObject3D::~GameObject3D()
	{
	}

	//**************
	//GAME OBJECT 3D
	//**************
}
