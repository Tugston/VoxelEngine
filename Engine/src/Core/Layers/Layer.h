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
		Layer(LayerID id) : m_ID(id) {};
	public:
		virtual ~Layer() = default;

		virtual void Attach() = 0;
		virtual void Detach() = 0;

		//registry is passed to each GetDrawData so that layers are not coupled to the Scene and can persist
		//need to copy the data so the scene can properly combine it rather than returning a const pointer
		//only returns the draw entities so not as much data
		virtual std::vector<EntityID> GetDrawData(Renderer::RenderPasses pass, ECSRegistry& registry) = 0;
		
		virtual void InputEvent() = 0;

		inline LayerID GetID() const { return m_ID; };

	protected:
		LayerID m_ID = LayerID::Unknown;
	};
}
