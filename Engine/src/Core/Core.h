#pragma once
#include <cassert>

//premake system config check
#ifdef ENGINE_PLATFORM_WINDOWS
		#define EG_PRJ //Engine Project (used as an easy way to differentiate the projects for other macros, without needing to check ENGINE_BUILD_DLL)
#else
	#error Sorry! ONLY SUPPORTED ON WINDOWS! (FUTURE ME HERE: MAY ADD MORE IN THE FUTURE, BUT ITS A PAIN AT THIS POINT!, I AM HAVING TO STATIC LINK INSTEAD OF DYNAMIC LINK AND THIS ALONE IS PAINFUL)
#endif

//I need to make a custom (debug only) assertion soon, before assertions get out of hand
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
