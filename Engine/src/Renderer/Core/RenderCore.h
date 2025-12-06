/*
* File: RenderCore.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-14-03 (yyyy/mm/dd)
*
* Description: Simple seperation of Glew in the case something may need to utilize it besides the renderer
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once


//ENGINE
#include "Core/Logger.h"

//VENDOR
#include <GL/glew.h>
#include <GL/GL.h>

namespace Core
{
	//NOTE: OPENGL ERRS DON'T ASSERT
	extern inline void CheckOpenGLError(const char* statement, const char* fileName, int line)
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			std::string errmsg = std::format("OpenGL error {}, at {}:{} - for {}\n", err, fileName, line, statement);
			Engine::Logger::LogMessage(Engine::Logger::LogType::Critical, errmsg);
		}
	}
}


//opengl error debug msg
#ifdef EG_DEBUG
	#ifndef GL_CHECK
		#define GL_CHECK(statement) do { \
				statement; \
				Core::CheckOpenGLError(#statement, __FILE__, __LINE__); \
				} while (glGetError())
	#endif
#else
	#ifndef GL_CHECK
		#define GL_CHECK(x)
	#endif
#endif

//disable integrated graphics, incase a graphics card and integrated gpu are present
//intel cpus must handle this themselves in their system settings
#ifdef EG_DEBUG
#ifdef __cplusplus
extern "C" {
#endif
	inline __declspec(dllexport) DWORD NvOptimusEnablement = 1;
	inline __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0;
#ifdef __cplusplus
}
#endif
#endif

