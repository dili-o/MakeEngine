#pragma once

#include <memory>

#ifdef MK_PLATFORM_WINDOWS
#if MK_DYNAMIC_LINK
	#ifdef MK_BUILD_DLL
		#define MK_API __declspec(dllexport)
	#else
		#define MK_API __declspec(dllimport)
	#endif // MK_BUILD_DLL
#else 
	#define MK_API
#endif
#else
	#error Platform not supported
#endif // MK_PLATFORM_WINDOWS

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif

#ifdef MK_ENABLE_ASSERTS
	#define MK_ASSERT(x, ...) { if(!(x)) { MK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MK_CORE_ASSERT(x, ...) { if(!(x)) { MK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MK_ASSERT(x, ...)
	#define MK_CORE_ASSERT(x, ...)
#endif

#define MK_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace MK {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}