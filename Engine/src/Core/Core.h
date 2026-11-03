/*
* File: Core.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-15 (yyyy/mm/dd)
*
* Description: The very core systems of the entire engine and all ecosystems. Dynamic linking macros should be defined here, but I had issues with it
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once
#include <cassert>
#include <numbers>

/**
* @file Core.h
* @brief Contains global types, macros, and values for the engine, game, and editor.
* @details Detects the os through premake build, currently only supported on Windows. Adds the assertion macro for major fatal errors that are better for the application to crash than continue. Defines GLFW_INCLUDE_NONE to allow application to handle gl.h. Defines various types and provides base utility macros.
* 
* @author Vincent Pierce
* @date February 15, 2025
*/

//premake system config check
#ifdef ENGINE_PLATFORM_WINDOWS
		#define EG_PRJ //Engine Project (used as an easy way to differentiate the projects for other macros, without needing to check ENGINE_BUILD_DLL)
#else
	#error Sorry! ONLY SUPPORTED ON WINDOWS! (FUTURE ME HERE: MAY ADD MORE IN THE FUTURE, BUT ITS A PAIN AT THIS POINT!, I AM HAVING TO STATIC LINK INSTEAD OF DYNAMIC LINK AND THIS ALONE IS PAINFUL)
#endif

//I need to make a custom assertion soon, before assertions get out of hand.
//Needs to work in distribution as well to display crash dump info.
#ifdef EG_DEBUG
	#ifndef EG_ASSERT
		#define EG_ASSERT(...) assert(__VA_ARGS__)
	#endif
#else
	#ifndef EG_ASSERT
		#define EG_ASSERT(x)
	#endif
#endif


//allow the application to handle gl.h
#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif


//type defines
//lots of these are competing with basetsd.h, so carefully use these
//could consider making macros, but typenames are cleaner imo and serving their designed purpose
namespace Viper {
	using UINT8 = uint8_t;
	using UINT16 = uint16_t;
	using UINT32 = uint32_t;
	using UINT64 = uint64_t;
}


//API MACROS
#define EG_PI			std::numbers::pi
#define EG_PI_FLOAT		(float)std::numbers::pi
