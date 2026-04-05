/*
* File: Scene.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-14 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Scene.h"

//ENGINE
#include "../Core/Layers/GameLayers.h"
#include "Core/Logger.h"


namespace Engine::Scene
{

	Scene::Scene()
	{
		SetupScene();
	}

	Scene::Scene(std::string_view name) : m_Name(name)
	{
		SetupScene();
	}

	Scene::~Scene()
	{
	}

	ECS::EntityID Scene::RegisterObject()
	{
		return m_Registry->CreateEntity();
	}

	const std::vector<ECS::EntityID> Scene::CollectRenderData(Renderer::RenderPasses type)
	{
		std::vector<ECS::EntityID> sortedData;

		for (size_t i = 0; i < LayerStack::GetLayers().size(); i++)
		{
			std::vector<ECS::EntityID> currentData = LayerStack::GetLayers().at(i)->GetDrawData(type, GetRegistry());

			if (currentData[0] == (std::numeric_limits<UINT32>::max)())
				continue;
			
			sortedData.insert(std::end(sortedData), std::begin(currentData), std::end(currentData));
		}

		return sortedData;
	}

	ECS::Registry& Scene::GetRegistry()
	{
		EG_ASSERT(m_Registry && "<Scene.cpp> (GetRegistry) Attempted to access a Scene Registry before it was initialized!");
		return *m_Registry;
	}

	void Scene::AddUI() const
	{
		//check if the layer exists already, if not add it
		if (!(LayerStack::CheckLayerExists(LayerID::GameUI)))
		{
			LayerStack::PushUILayer(new UILayer());
		}
	}

	void Scene::RemoveUI() const
	{
		REMOVE_UI;
	}

	void Scene::SetupScene()
	{
		Logger::LogMessage(Logger::LogType::Message, "New Scene Created!");
	
		m_Registry = std::make_unique<ECS::Registry>();

		//layer setup
		LayerStack::Clear(); //clear the layer stack to refresh for the new scene
		LayerStack::PushWorldLayer(new EngineWorldLayer());
		LayerStack::PushUILayer(new UILayer());
		LayerStack::PushWorldLayer(new WorldLayer());
		LayerStack::PushUILayer(new EngineUILayer());
	}

}
