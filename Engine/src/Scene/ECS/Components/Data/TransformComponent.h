/*
* File: Transform.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-11-26 (yyyy/mm/dd)
*
* Description: Transform components that ever entity has by default. Can be removed on a user basis. Currently utilizing Euler rotation, want to convert
* to quaternions at some point
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

//ENGN
#include "./Core/Maths/Math.h"

namespace Engine::Scene::ECS::Components
{

	struct TransformComponent2D
	{
		Maths::Vector2<float> location{ 0.f, 0.f};
		Maths::Vector2<float> rotation{ 0.f, 0.f };
		Maths::Vector2<float> scale{ 1.f, 1.f };
	};

	struct TransformComponent3D
	{
		Maths::Vector3<float> location{ 0.f, 0.f, 0.f };
		Maths::Vector3<float> rotation{ 0.f, 0.f, 0.f };
		Maths::Vector3<float> scale{ 1.f, 1.f, 1.f };
	};
}
