/*
* File: SceneManager.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-19 (yyyy/mm/dd)
*
* Description: Controls object instantiation, saving, loading, and everything concerning scene processing
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "Scene.h"
#include "ECS/GameObjects/GameObject.h"

//STND
#include <memory>

//I would like to add level streaming eventually and have scenes that can be loaded and closed during runtime which would allow the player to 
//transition through scenes and not even realize it

namespace Engine::Scene
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void CreateScene(std::string_view sceneName);
		void LoadScene(std::string_view sceneName);
		void SaveCurrentScene();

		inline Scene* GetCurrentScene() { return m_CurrentScene.get(); }

		//NOTE: this should eventually be a unique_ptr because the overall game should only hold this, may already need to add it
		// keeping it shared for now just in case though
		//
		//The different GameObject types only do constructor stuff, so can just simply return the base GameObject for the id
		template<typename t, typename... Args>
		ECS::GameObject* CreateEntity(Args&&... args)
		{
			if (m_CurrentScene)
			{
				std::unique_ptr<t> object = std::make_unique<t>(m_CurrentScene->GetRegistry(), std::forward<Args>(args)...);
				m_ObjectPool.push_back(std::move(object));
				return m_ObjectPool.back().get();
			}

			return nullptr;
		};

	private:
		//heap allocate; scene will contain a lot of stuff and wont be unloaded and reloaded frequently
		std::unique_ptr<Scene> m_CurrentScene = nullptr;
		std::vector<std::unique_ptr<ECS::GameObject>> m_ObjectPool; //storing game objects in the scene manager since they are a lyaer above the ECS
	};

}
