#pragma once

//premake system config check
#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
		#define EG_PRJ //Engine Project
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Sorry! ONLY SUPPORTED ON WINDOWS!
#endif

//I need to make a custom (debug only) assertion soon, before assertions get out of hand
#ifndef EG_ASSERT
#define EG_ASSERT
#endif

