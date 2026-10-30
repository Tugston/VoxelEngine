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

/*
* @file ScriptModule.h
* @brief Base class for creating scripts in the game.
* 
* @details Pure virtual class that provides all the functions required to get a script registered and working with the ECS
* 
* @author Vincent Pierce
* @date December 23, 2025
*/

//ENGN
#include "Scene/ECS/GameObjects/GameObject.h"

//STND
#include <memory>

namespace Viper
{
	class ScriptModule
	{
	public:
		/*
		* @brief Override constructor for each script usage as needed.
		* @details See Construct() for the official constructor utilized by the engine processess.
		* @warning Using the class constructor cannot guarantee engine is fully initialized! As of version 0.0.2, please only utilize this for setting script member value from the application class.
		*/
		ScriptModule() = default;
		
		///Default assigned destructor in each script
		virtual ~ScriptModule() = default;

		ScriptModule(ScriptModule&& other) = default;
		ScriptModule& operator=(ScriptModule&& other) = default;

		/**
		* @brief Official constructor for the ScriptModule supported by the engine
		* @details This construct function will be called and processed while the editor application is running and is guranteed to occur before Start(). This is called as soon as the Script is instantiated on the Scene::ECS::Components::ScriptComponent. In version 0.0.2 this feature is not implemented as of yet because the editor is still a work in progress.
		* 
		* @post The script is prepared for Start().
		*/
		virtual void Construct() = 0;

		///Called at the moment the script is loaded.
		virtual void Start() = 0;
		
		/**
		* @brief Called every frame tick of the application.
		* @param[in] deltaTime Calculated time between the current frame and last.
		*/
		virtual void Tick(float deltaTime) = 0;

		/**
		* @brief Assign the owner of the script for simple reference.
		* @details The scripts may need to interact with other entities attached to this entity. This checks if the owner is not already set as well if the ownerRef parameter is valid. If not, simply return without doing anything.
		*
		* @param[in] ownerRef Reference to the entity that this script is attached to.
		* 
		* @note In future versions this GameObject param will need to be exchanged to just and entityID. As of version 0.0.2 having a GameObject passed in for the owner prevents the script module from working with the core ECS.
		*/
		void SetOwner(Scene::ECS::GameObject* ownerRef) noexcept
		{
			//I only want script owners to be set once 
			if (m_Owner || !ownerRef)
				return;

			m_Owner = ownerRef;
		}

		/// Returns value stored in #m_Owner, does not do any validation checks.
		Scene::ECS::GameObject* GetOwner() const
		{
			return m_Owner;
		}

	private:
		/**
		* @brief The owning entity this script and Scene::ECS::Components::ScriptComponent is attached to
		* @note The owning component is destroyed when the owning game object is destroyed anyways. So, the pointer is should always be valid.
		*/
		Scene::ECS::GameObject* m_Owner = nullptr;
	};
}
