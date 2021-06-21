#pragma once
#include <memory>

#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef ENGINE_DYNAMIC_LINK
		#ifdef ENGINE_BUILD_DLL
			#define ENGINE_API __declspec(dllexport)
		#else
			#define ENGINE_API __declspec(dllimport)
		#endif // ENGINE_BUILD_DLL
	#else
		#define ENGINE_API
	#endif
#else
	#error Engine only supports Windows!
#endif // ENGINE_PLATFORM_WINDOWS

#ifdef EG_ENABLE_ASSERTS
#define EG_ASSERT(x, ...) { if(!(x)){EG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#define EG_CORE_ASSERT(x, ...) { if(!(x)){EG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define EG_ASSERT(x, ...)
#define EG_CORE_ASSERT(x, ...)
#endif // EG_ENABLE_ASSERTS

#define ENGINE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace Engine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
