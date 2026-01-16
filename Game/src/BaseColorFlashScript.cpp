/*
* File: BaseColorFlashScript.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-12-26 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "BaseColorFlashScript.h"

#include<random>

namespace VoxelGame
{
	BaseColorFlashScript::BaseColorFlashScript(Maths::Vector3<float> startColor):
		m_CurrentColor(startColor)
	{
	
	}

	void BaseColorFlashScript::Construct()
	{
		m_MeshComponent = GetOwner()->GetComponent<SpriteComponent>();
	}

	void BaseColorFlashScript::Start()
	{
	}

	void BaseColorFlashScript::Tick(float deltaTime)
	{	
		if (InputSystem::KeyTapped(EngineKeys::RARROW))
			scaleMultiplier += 0.1f;
		else if (InputSystem::KeyTapped(EngineKeys::LARROW) && scaleMultiplier != 0.1f)
			scaleMultiplier -= 0.1f;

		float scalar = deltaTime * scaleMultiplier;

		float r = RandomFloatInRange(-1, 1) * scalar;
		float g = RandomFloatInRange(-1, 1) * scalar;
		float b = RandomFloatInRange(-1, 1) * scalar;

		Logger::LogMessage(Logger::LogType::Message, "Red Channel: {}", r);

		m_CurrentColor.x += r;
		m_CurrentColor.y += g;
		m_CurrentColor.z += b;

		if (m_MeshComponent)
			m_MeshComponent->material.shader->SetUniformVec3("uColor", { m_CurrentColor.x, m_CurrentColor.y, m_CurrentColor.z });
	}
}
