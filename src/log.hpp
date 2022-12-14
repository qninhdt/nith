#pragma once

namespace nith
{
    class Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> GetCoreLogger();
        static std::shared_ptr<spdlog::logger> GetClientLogger();

    private:

        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };

    inline std::shared_ptr<spdlog::logger> Log::GetCoreLogger()
    {
        return s_coreLogger;
    }

    inline std::shared_ptr<spdlog::logger> Log::GetClientLogger()
    {
        return s_clientLogger;
    }

}

#define NITH_CORE_INFO(...)  nith::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NITH_CORE_WARN(...)   nith::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NITH_CORE_TRACE(...) nith::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NITH_CORE_ERROR(...) nith::Log::GetCoreLogger()->error(__VA_ARGS__)

#define NITH_CLIENT_INFO(...)  nith::Log::GetClientLogger()->info(__VA_ARGS__)
#define NITH_CLIENT_WARN(...)   nith::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NITH_CLIENT_TRACE(...) nith::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NITH_CLIENT_ERROR(...) nith::Log::GetClientLogger()->error(__VA_ARGS__)

#ifdef NITH_DEBUG
#define NITH_CORE_ASSERT(check ,msg) if (!(check)) { NITH_CORE_ERROR(msg); NITH_DEBUGBREAK(); }
#define NITH_CLIENT_ASSERT(check ,msg) if (!(check)) { NITH_CORE_ERROR(msg); NITH_DEBUGBREAK(); }
#else
#define NITH_CORE_ASSERT(check ,msg) 
#define NITH_CLIENT_ASSERT(check ,msg)
#endif