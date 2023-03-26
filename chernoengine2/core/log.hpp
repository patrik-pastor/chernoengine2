//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_LOG_HPP
#define CHERNOENGINE2_LOG_HPP

#include <spdlog/spdlog.h>

namespace chernoengine2 {

class Log {
public:
    static void Init();

    static std::shared_ptr<spdlog::logger>& GetCoreLogger();

    static std::shared_ptr<spdlog::logger>& GetAppLogger();

private:
    static std::shared_ptr<spdlog::logger> core_logger_;
    static std::shared_ptr<spdlog::logger> app_logger_;
};

} // chernoengine2

#define LOG_CORE_TRACE(...) chernoengine2::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...) chernoengine2::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...) chernoengine2::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) chernoengine2::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...) chernoengine2::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_APP_TRACE(...) chernoengine2::Log::GetAppLogger()->trace(__VA_ARGS__)
#define LOG_APP_INFO(...) chernoengine2::Log::GetAppLogger()->info(__VA_ARGS__)
#define LOG_APP_WARN(...) chernoengine2::Log::GetAppLogger()->warn(__VA_ARGS__)
#define LOG_APP_ERROR(...) chernoengine2::Log::GetAppLogger()->error(__VA_ARGS__)
#define LOG_APP_CRITICAL(...) chernoengine2::Log::GetAppLogger()->critical(__VA_ARGS__)

#endif //CHERNOENGINE2_LOG_HPP
