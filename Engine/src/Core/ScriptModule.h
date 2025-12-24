/*
* File: ScriptModule.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-23 (yyyy/mm/dd)
*
* Description: Base class for creating scripts for the application
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "Scene/ECS/GameObjects/GameObject.h"

//STND
#include <memory>

namespace Engine
{
	class ScriptModule
	{
	public:
		//using classe's constructor cannot gurantee engine is fully initialized!
		//so please only utilize this for setting script members from the application
		ScriptModule() = default;
		~ScriptModule() = default;

		ScriptModule(ScriptModule&& other) = default;
		ScriptModule& operator=(ScriptModule&& other) = default;

		virtual void Construct() = 0;
		virtual void Start() = 0;
		virtual void Tick(float deltaTime) = 0;


		void SetOwner(Scene::ECS::GameObject* ownerRef) noexcept
		{
			//I only want script owners to be set once 
			if (m_Owner || !ownerRef)
				return;

			m_Owner = ownerRef;
		}

		Scene::ECS::GameObject* GetOwner() const
		{
			return m_Owner;
		}

	private:
		//this component is destroyed when the owning game object is destroyed anyways
		Scene::ECS::GameObject* m_Owner = nullptr;
	};
}
