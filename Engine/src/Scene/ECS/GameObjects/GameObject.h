/*
* File: GameObject.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-26 (yyyy/mm/dd)
*
* Description: Pure abstraction class over the ecs. Allows end user to utilize entities more efficiently. Can opt out of using it if desired.
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGINE
#include "Core/Core.h"
#include "Core/Logger.h"
#include "Scene/Scene.h"

#include "Scene/ECS/Components/Data/TransformComponent.h"

//maybe there is a better place for this, I might add some default engine settings or something
//so then this can be easily customizable in engine preferences or something?
//but right now, just going to be a macro here until there are more default settings
#ifndef DEFAULT_COLOR
#define DEFAULT_COLOR glm::vec3{0.9f, 0.7f, 0.5f}
#endif

namespace Engine::Scene::ECS
{
	class GameObject
	{
	public:
		//delete default for now, until I get the scene manager all setup
		GameObject() = delete;
		GameObject(ECS::Registry& registry);
		~GameObject();

	public:
		template<typename t, typename... Args>
		void AddComponent(Args&&... args)
		{
			LOG_MSG("<GameObject.h> Adding {} component to Object [ {} ]", typeid(t).name(), m_ID);
			m_Registry.AddComponent<t>(m_ID, std::forward<Args>(args)...);
		}

		template<typename t>
		void RemoveComponent(t*& componentRef)
		{
			LOG_MSG("<GameObject.h> Removing {} component from Object [ {} ]", typeid(t).name(), m_ID);
			m_Registry.RemoveComponent<t>(m_ID);
		}

		//returns nullptr if component cannot be found
		template<typename t>
		t* GetComponent()
		{
			return m_Registry.GetComponent<t>(m_ID);
		}

		//this is utilized for testing, objectID is internal use
		EntityID GetID() const { return m_ID; }

	private:
		EntityID m_ID;

		//Game Objects will never outlive the Scene, which contains the ECS registry
		//Before a scene ends, it cleans up all the current GameObjects that are stored in the Scene Manager
		ECS::Registry& m_Registry;
	};

	class GameObject2D : public GameObject
	{
	public:
		GameObject2D(ECS::Registry& registry);
		GameObject2D(ECS::Registry& registry, const Components::TransformComponent2D& transform);
		~GameObject2D();
	};

	class GameObject3D : public GameObject
	{
	public:
		GameObject3D(ECS::Registry& registry);
		GameObject3D(ECS::Registry& registry, const Components::TransformComponent3D& transform);
		~GameObject3D();
	};
}