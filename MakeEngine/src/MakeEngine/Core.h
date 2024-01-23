#pragma once

#ifdef MK_PLATFORM_WINDOWS
	#ifdef MK_BUILD_DLL
		#define MK_API __declspec(dllexport)
	#else
		#define MK_API __declspec(dllimport)
	#endif // MK_BUILD_DLL
#else
	#error Platform not supported
#endif // MK_PLATFORM_WINDOWS
