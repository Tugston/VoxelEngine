/*
* File: Logger.cpp
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-15 (yyyy/mm/dd)
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#include "egpch.h"
#include "Logger.h"

//VENDOR
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Engine
{
	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::s_GameLogger;
	std::shared_ptr<spdlog::logger> Logger::s_EditorLogger;

	bool Logger::Init()
	{
		
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stdout_color_mt("Engine");
		s_EngineLogger->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_GameLogger = spdlog::stdout_color_mt("Game");
		s_GameLogger->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EditorLogger = spdlog::stdout_color_mt("Editor");
		s_EditorLogger->set_level(spdlog::level::trace);

		if (s_GameLogger.get() && s_EngineLogger.get() && s_EditorLogger.get())
			return true;
		else
			return false;
	}
}