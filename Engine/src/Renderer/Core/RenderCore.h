#pragma once

//would want this in the Core/Core.h, but it needs to include glew
//that is problematic because I only really want the renderer to know that glew exists
//so making a RenderCore is the next best thing I guess
//idk this is my first engine, I am just winging it tbh...

//VENDOR
#include <gl/glew.h>

//ENGINE
#include "Core/Logger.h"

//opengl error debug msg
#ifdef EG_DEBUG
	#ifndef GL_Check
		#define GL_CHECK(statement) do { \
				statement; \
				Core::CheckOpenGLError(#statement, __FILE__, __LINE__); \
				} while (glGetError())
	#endif
#else
	#ifndef GL_Check
		#define GL_Check(x)
	#endif
#endif

namespace Core
{
	//NOTE: OPENGL ERRS DON'T ASSERT
	void CheckOpenGLError(const char* statement, const char* fileName, int line)
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			std::string errmsg = std::format("OpenGL error %08x, at %s:%i - for %s\n", err, fileName, line, statement);
			Engine::Logger::LogMessage(Engine::Logger::LogType::Critical, errmsg);
		}
	}
}

//disable integrated graphics, incase a graphics card and integrated gpu are present
//intel cpus must handle this themselves in their system settings
#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) DWORD NvOptimusEnablement = 1;
	__declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0;
#ifdef __cplusplus
}
#endif

