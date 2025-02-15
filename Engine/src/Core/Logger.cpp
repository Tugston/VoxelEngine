#include "Logger.h"

#include<iostream>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Engine
{
	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::s_GameLogger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_EngineLogger = spdlog::stdout_color_mt("Engine");
		s_EngineLogger->set_level(spdlog::level::trace);

		s_GameLogger = spdlog::stdout_color_mt("Game");
		s_GameLogger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger> Logger::GetLogger()
	{
		//return engine logger when used in engine and game logger when used in game
		#ifdef EG_PRJ
		return s_EngineLogger;
		#else
		return s_GameLogger;
		#endif
	}
}