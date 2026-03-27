/*
* File: RenderComponent.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2026-03-26 (yyyy/mm/dd)
*
* Description: Tag for all renderables for the layer system to filter, sort, and utilize
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "Core/Layers/LayerID.h"

namespace Engine::Scene::ECS::Components
{
	struct Renderable {
		Renderable() = default;
		Renderable(LayerID layer, bool visible) : visible(visible), layer(layer) {};
		Renderable(LayerID layer) : layer(layer) {};
		Renderable(bool visible) : visible(visible) {};

		bool visible = true;
		LayerID layer = LayerID::GameWorld;
	};
}
