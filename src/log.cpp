#include "log.hpp"

namespace nith
{
    std::shared_ptr<spdlog::logger> Log::s_coreLogger;
    std::shared_ptr<spdlog::logger> Log::s_clientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        
        s_coreLogger = spdlog::stdout_color_mt("core");
        s_coreLogger->set_level(spdlog::level::trace);

        s_clientLogger = spdlog::stdout_color_mt("client");
        s_clientLogger->set_level(spdlog::level::trace);
    }
}