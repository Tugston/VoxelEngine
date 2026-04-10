/*
* File: SceneManager.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-04-04 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "SceneManager.h"

//ENGN
#include "Scene.h"

namespace Engine::Scene
{
	SceneManager::SceneManager()
	{
		CreateScene("Untitled Scene");
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::CreateScene(std::string_view sceneName)
	{
		if (m_CurrentScene)
		{
			SaveCurrentScene();
			m_CurrentScene.reset();
		}

		m_CurrentScene = std::make_unique<Scene>(sceneName);
	}

	void SceneManager::LoadScene(std::string_view sceneName)
	{
		//same with saving, not important at the moment
	}

	void SceneManager::SaveCurrentScene()
	{
		//not here yet WIP
		//not rly important right now
	}
}