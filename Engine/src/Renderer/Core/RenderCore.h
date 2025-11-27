#pragma once

//created a render core just in case there is something in the renderer that may want glew but doesnt need the actual renderer class and everything


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

