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

namespace Engine
{
	class Layer
	{
	protected:
		Layer() {};
		Layer(unsigned char id) : m_ID(id) {};
	public:
		virtual ~Layer() = default;

		virtual void Attach() = 0;
		virtual void Detach() = 0;
		virtual void GetDrawData() = 0;
		virtual void InputEvent() = 0;

		inline unsigned char GetID() const { return m_ID; };

	protected:
		//there will only be a few layers
		//this can be stored in a byte obviously
		unsigned char m_ID = 0;

		std::weak_ptr<Scene::ECS::Registry> m_SceneRegistry;
	};
}
