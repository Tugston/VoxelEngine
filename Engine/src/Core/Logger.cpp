#include "Logger.h"

//STND
#include<iostream>

//VENDOR
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Engine
{
	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::s_GameLogger;

	bool Logger::Init()
	{
		
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stdout_color_mt("Engine");
		s_EngineLogger->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_GameLogger = spdlog::stdout_color_mt("Game");
		s_GameLogger->set_level(spdlog::level::trace);
		
		if (s_GameLogger.get() && s_EngineLogger.get())
			return true;
		else
			return false;
	}
}