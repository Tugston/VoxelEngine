#pragma once

//STND
#include<string>
#include<memory>
#include<iostream>

//ENGINE
#include "Core.h"

//VENDOR
#include <spdlog/spdlog.h>


//Logger Detection
#ifdef EG_PRJ
#define GET_LOGGER() ::Engine::Logger::GetEngineLogger()
#else
#define GET_LOGGER() ::Engine::Logger::GetGameLogger()
#endif


//Log Type Macros
#define LOG_MESSAGE(...)	GET_LOGGER()->info(__VA_ARGS__) 
#define LOG_Warning(...)	GET_LOGGER()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		GET_LOGGER()->error(__VA_ARGS__)
#define LOG_FATAL(...)		GET_LOGGER()->critical(__VA_ARGS__)


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

		static bool Init();

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

		static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; };
		static std::shared_ptr<spdlog::logger> GetGameLogger() { return s_GameLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_GameLogger;

	};

}
