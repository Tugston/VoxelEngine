/*
* File: BaseColorFlashScript.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-26 (yyyy/mm/dd)
*
* Description: Test script that randomly changes the base color of the object's mesh shader
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
	class BaseColorFlashScript : public ScriptModule
	{
	public:
		BaseColorFlashScript(Maths::Vector3<float> startColor);

		virtual void Construct() override;
		virtual void Start() override;
		virtual void Tick(float deltaTime) override;

	private:
		Maths::Vector3<float> m_CurrentColor;
		Components::SpriteComponent* m_MeshComponent;
		float scaleMultiplier = 0.1f;
	};
}
