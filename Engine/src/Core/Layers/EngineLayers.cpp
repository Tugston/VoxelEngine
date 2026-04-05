/*
* File: EngineLayers.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-03-08 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "EngineLayers.h"

//ENGINE
#include "Core/Application.h"
#include "Core/Logger.h"
#include "Input/Input.h"
#include "Core/Debug/DebugUI.h"


namespace Engine
{
	//***********//
	//WORLD LAYER//
	//***********//

	EngineWorldLayer::EngineWorldLayer() : Layer(LayerID::EngineWorld)
	{

	}

	EngineWorldLayer::~EngineWorldLayer()
	{

	}

	void EngineWorldLayer::Attach()
	{
		//theres probably some sort of debug line drawing subsystem that needs to go here
		Logger::LogMessage(Logger::LogType::Error, "Engine World Layer Attached!");
	}

	void EngineWorldLayer::Detach()
	{

	}

	std::vector<EngineWorldLayer::EntityID> EngineWorldLayer::GetDrawData(Renderer::RenderPasses, ECSRegistry& registry)
	{
		//temporary
		return std::vector<EntityID>{std::numeric_limits<UINT32>().max()};
	}

	void EngineWorldLayer::InputEvent()
	{
		if (InputSystem::GetInputMode() == InputSystem::InputMode::Debug)
		{
			if (InputSystem::KeyTapped(EngineKeys::F1))
			{
				Logger::LogMessage(Logger::LogType::Message, "Leaving Debug Mode");
				InputSystem::SetCurrentInputMode(InputSystem::InputMode::GameOnly);
			}
			else if (InputSystem::KeyPressed(EngineKeys::ESC))
			{
				//game should handle pause menu with escape, so quitting application for engine layer
				Application::QuitGame();
			}
		}
	}

	//***********//
	//WORLD LAYER//
	//***********//

	//********//
	//UI LAYER//
	//********//

	EngineUILayer::EngineUILayer() : Layer(LayerID::EngineUI)
	{

	}

	EngineUILayer::~EngineUILayer()
	{

	}

	void EngineUILayer::Attach()
	{
		Logger::LogMessage(Logger::LogType::Error, "Engine UI Layer Attached!");
	}

	void EngineUILayer::Detach()
	{
		Logger::LogMessage(Logger::LogType::Error, "Engine UI Layer Removed!");
	}

	std::vector<EngineUILayer::EntityID> EngineUILayer::GetDrawData(Renderer::RenderPasses pass, ECSRegistry& registry)
	{
		return std::vector<EntityID>{std::numeric_limits<UINT32>().max()};
	}

	void EngineUILayer::InputEvent()
	{
	}

	//********//
	//UI LAYER//
	//********//
}