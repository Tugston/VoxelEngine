/*
* File: Logger.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-15 (yyyy/mm/dd)
*
* Description: Wrapper to simplify spdlog and provide engine and game differential logging
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

/**
* @file Logger.h
* @brief Handles logging text to the console window
* 
* @details Logs various color text to the console representing the severity of the text. Each log also outputs the project it has been reported from. The time stamp for each log is also listed to indicate the exact frame it was called.
*/

//ENGINE
#include "Core/Core.h"

//VENDOR
#include <spdlog/spdlog.h>

//STND
#include <memory>


//Logger Detection
#ifdef EG_PRJ
	#if defined(APP_DEBUG) //check app debug first, because engine may also be valid in game project
		#define GET_LOGGER() GetGameLogger()
	#elif defined(EDTR_DEBUG) //same with the editor
		#define GET_LOGGER() GetEditorLogger()
	#elif defined(EG_DEBUG)
		#define GET_LOGGER() GetEngineLogger()
	#else
		#define GET_LOGGER(x)
	#endif //APP_DEBUG
#else
	#define GET_LOGGER(x)
#endif //EG_PRJ determines windows support, so shouldnt ever reach invalid logger


//Log Type Macros
//DO NOT USE THESE, GET_LOGGER() intentionally prevents these macros to be utilized.
//The proper LogMessage function performs formatting on the message.
#if defined(EG_DEBUG) || defined(APP_DEBUG) || defined(EDTR_DEBUG)
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
//but nothing is rly stopping external use, so use them I guess
#if defined(EG_DEBUG) || defined(EDTR_DEBUG) || defined(APP_DEBUG)
#define LOG_MSG(...)	Viper::Logger::LogMessage(Viper::Logger::LogType::Message, __VA_ARGS__)
#define LOG_WARN(...)	Viper::Logger::LogMessage(Viper::Logger::LogType::Warning, __VA_ARGS__)
#define LOG_ERR(...)	Viper::Logger::LogMessage(Viper::Logger::LogType::Error, __VA_ARGS__)
#define LOG_CRIT(...)	Viper::Logger::LogMessage(Viper::Logger::LogType::Critical, __VA_ARGS__)
#else
#define LOG_MSG(...)
#define LOG_Warn(...)
#define LOG_ERR(...)
#define LOG_CRIT(...)
#endif

namespace Viper
{
	class Logger
	{
	public:
		
		/// Type to specify what type of log to output.
		enum class LogType
		{
			Message,
			Warning,
			Error,
			Critical
		};

		/**
		* @brief Formats and setus up spd_log and verifies setup.
		* @details Sets the pattern of the spd_log #s_EngineLogger, assigns a multithreaded logger object to the #s_EngineLogger, sets the level to trace. Proceeds to do the same for the #s_GameLogger and #s_EditorLogger. All loggers have the same patters setup of being highlighted by their severity color, displaying time in brackets, outputting logger name, and finally the formatted message.
		* 
		* @post Loggers are fully setup and initialized to print outputs.
		* 
		* @return True if all loggers are successfully created and initialized. Return false otherwise.
		*/
		static bool Init();

		/**
		* @brief Prints the provided message to the screen with args based on LogType
		* @details Utilizes std::vformat to emplace the arg values into the printed message. Checks to see what LogType value was provided and utilizes a series of macros to print the appropriate severity through the correct logger.
		* 
		* @param[in] type The severity of the log to be printed.
		* @param[in] message String to be printed to the console.
		* @param[in] args Variable values to display in the string.
		* 
		* @note In order to display the args, add a {} for each value where it should be displayed. Then add the args in the order of the required printing.
		*/
		template <typename... Args>
		static inline void LogMessage(LogType type, std::string_view message, Args&&... args)
		{
			std::string formattedMsg = std::vformat(message, std::make_format_args(args...));
	
			switch (type)
			{
				case LogType::Message:		LOG_MESSAGE(formattedMsg); break;
				case LogType::Warning:		LOG_WARNING(formattedMsg); break;
				case LogType::Error:		LOG_ERROR(formattedMsg); break;
				case LogType::Critical:		LOG_FATAL(formattedMsg); break;
			};
		};

	private:
		/// Return #s_EngineLogger and utilized for the macro to make them look nice.
		static std::shared_ptr<spdlog::logger> GetEngineLogger()	{ return s_EngineLogger; }
		/// Return #s_GameLogger and utilized for the macro to make them look nice.
		static std::shared_ptr<spdlog::logger> GetGameLogger()		{ return s_GameLogger; }
		/// Return #s_EditorLogger and utilized for the macro to make them look nice.
		static std::shared_ptr<spdlog::logger> GetEditorLogger()	{ return s_EditorLogger; }

		/// Configured to specify the message originated form the Engine.
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		/// Configured to specify the message originated from the Game.
		static std::shared_ptr<spdlog::logger> s_GameLogger;
		/// Configured to specify the message originated from the Editor.
		static std::shared_ptr<spdlog::logger> s_EditorLogger;
	};

}
