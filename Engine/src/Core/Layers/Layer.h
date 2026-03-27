/*
* File: LayerStack.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-08 (yyyy/mm/dd)
*
* Description: Abstraction base class for each layer to declutter the LayerStack
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGINE
#include "Core/Core.h"
#include "Scene/ECS/Registry.h"
#include "Renderer/Core/RenderPasses.h"
#include "LayerID.h"
#include "Scene/ECS/Components/Tags/RenderComponent.h"

namespace Engine
{
	class Layer
	{
	protected:
		using ECSRegistry = Scene::ECS::Registry;
		using EntityID = Scene::ECS::EntityID;
		using RenderComponent = Scene::ECS::Components::Renderable;	

		Layer() = default;
		Layer(LayerID id, std::shared_ptr<ECSRegistry> reg) : m_ID(id), m_SceneRegistry(reg) {};
	public:
		virtual ~Layer() = default;

		virtual void Attach() = 0;
		virtual void Detach() = 0;

		//need to copy the data so the scene can properly combine it rather than returning a const pointer
		//only returns the draw entities so not as much data
		virtual std::vector<EntityID> GetDrawData(Renderer::RenderPasses pass) = 0;
		
		virtual void InputEvent() = 0;

		inline LayerID GetID() const { return m_ID; };

	protected:
		LayerID m_ID = LayerID::Unknown;

		std::weak_ptr<ECSRegistry> m_SceneRegistry;
	};
}
