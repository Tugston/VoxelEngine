/*
* File: MovementScript.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-23 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "MovementScript.h"


namespace VoxelGame
{
	MovementScript::MovementScript(float speed):
		m_Speed(speed)
	{
	}

	void MovementScript::Construct()
	{
		m_TransformComponent = GetOwner()->GetComponent<TransformComponent3D>();
	}

	void MovementScript::Start()
	{
	}

	void MovementScript::Tick(float deltaTime)
	{
		m_TransformComponent->location.x += m_Speed * deltaTime;
	}
}