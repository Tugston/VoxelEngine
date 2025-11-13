#pragma once

//ENGINE
#include "Core/Core.h"

//VENDOR
#include <spdlog/spdlog.h>

//STND
#include <memory>


//Logger Detection
#ifdef EG_PRJ
	#if defined(EG_DEBUG) || defined(APP_DEBUG)
		#define GET_LOGGER() ::Engine::Logger::GetEngineLogger()
	#else
		#define GET_LOGGER(x) 
	#endif //EG_DEBUG
#else
	#ifdef APP_DEBUG
		#define GET_LOGGER() ::Engine::Logger::GetGameLogger()
	#else
		#define GET_LOGGER(x)
	#endif //APP_DEBUG
#endif


//Log Type Macros
#if defined(EG_DEBUG) || defined(APP_DEBUG)
#define LOG_MESSAGE(...)	GET_LOGGER()->info(__VA_ARGS__) 
#define LOG_WARNING(...)	GET_LOGGER()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		GET_LOGGER()->error(__VA_ARGS__)
#define LOG_FATAL(...)		GET_LOGGER()->critical(__VA_ARGS__)
#else
#define LOG_MESSAGE(x)
#define LOG_WARNING(x)
#define LOG_ERROR(x)
#define LOG_FATAL(x)
#endif

//internal use only, tired of writing out these logs everywhere
#if defined(EG_DEBUG) || defined(EDITOR_DEBUG)
#define LOG_MSG(...)	Engine::Logger::LogMessage(Engine::Logger::LogType::Message, __VA_ARGS__)
#define LOG_WARN(...)	Engine::Logger::LogMessage(Engine::Logger::LogType::Warning, __VA_ARGS__)
#define LOG_ERR(...)	Engine::Logger::LogMessage(Engine::Logger::LogType::Error, __VA_ARGS__)
#define LOG_CRIT(...)	Engine::Logger::LogMessage(Engine::Logger::LogType::Critical, __VA_ARGS__)
#else
#define LOG_MSG(...)
#define LOG_Warn(...)
#define LOG_ERR(...)
#define LOG_CRIT(...)
#endif

namespace Engine
{
	class Logger
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

		template <typename... Args>
		static inline void LogMessage(LogType type, const std::string& message, Args&&... args)
		{
			std::string formattedMsg = std::vformat(message, std::make_format_args(std::forward<Args>(args)...));
	
			switch (type)
			{
				case LogType::Message:		LOG_MESSAGE(formattedMsg); break;
				case LogType::Warning:		LOG_WARNING(formattedMsg); break;
				case LogType::Error:		LOG_ERROR(formattedMsg); break;
				case LogType::Critical:		LOG_FATAL(formattedMsg); break;
			};
		};

		static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; };
		static std::shared_ptr<spdlog::logger> GetGameLogger() { return s_GameLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_GameLogger;

	};

}
