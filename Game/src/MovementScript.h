/*
* File: MovementScript.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-23 (yyyy/mm/dd)
*
* Description: Test script that simply moves a GameObject in the X direction at a specified speed
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once
#include "Engine.h"

namespace VoxelGame
{
	class MovementScript : public ScriptModule
	{
	public:
		MovementScript(float speed);
		virtual void Construct() override;
		virtual void Start() override;
		virtual void Tick(float deltaTime) override;

	private:
		float m_Speed = 1.f;
		TransformComponent3D* m_TransformComponent;
	};
}
