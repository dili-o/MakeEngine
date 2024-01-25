#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace MK {
	class MK_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){ return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){ return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}


// Core log macros
#define MK_CORE_TRACE(...) ::MK::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MK_CORE_INFO(...)  ::MK::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MK_CORE_WARN(...)  ::MK::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MK_CORE_ERROR(...) ::MK::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MK_CORE_CRITICAL(...) ::MK::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MK_TRACE(...)      ::MK::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MK_INFO(...)       ::MK::Log::GetClientLogger()->info(__VA_ARGS__)
#define MK_WARN(...)       ::MK::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MK_ERROR(...)      ::MK::Log::GetClientLogger()->error(__VA_ARGS__)
#define MK_CRITICAL(...)      ::MK::Log::GetClientLogger()->critical(__VA_ARGS__)