#pragma once

//STND
#include<string>
#include<memory>
#include<iostream>

//ENGINE
#include "Core.h"

//VENDOR
#include <spdlog/spdlog.h>



//Log Type Macros
namespace
{
	#define LOG_MESSAGE(...)  ::Engine::Logger::GetLogger()->info(__VA_ARGS__)
	#define LOG_Warning(...)  ::Engine::Logger::GetLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)    ::Engine::Logger::GetLogger()->error(__VA_ARGS__)
	#define LOG_FATAL(...)    ::Engine::Logger::GetLogger()->critical(__VA_ARGS__)
}

namespace Engine
{
	class ENGINE_API Logger
	{
	public:

		enum class LogType
		{
			Message,
			Warning,
			Error,
			Critical
		};

		static void Init();

		template <typename... t>
		static inline void LogMessage(LogType type, const std::string& message, t&&... args)
		{
			try
			{
				std::string formattedMsg = fmt::vformat(message, fmt::make_format_args(std::forward<t>(args)...));

				switch (type)
				{
				case LogType::Message:		LOG_MESSAGE(formattedMsg); break;
				case LogType::Warning:		LOG_Warning(formattedMsg); break;
				case LogType::Error:		LOG_ERROR(formattedMsg); break;
				case LogType::Critical:		LOG_FATAL(formattedMsg); break;
				};
			}
			catch (const std::exception& x)
			{
				std::cerr << "Logging Failed: " << x.what() << std::endl;
			}
		};

		static std::shared_ptr<spdlog::logger> GetLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_GameLogger;
	};

}
