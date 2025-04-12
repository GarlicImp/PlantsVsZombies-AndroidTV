#ifndef HOMURA_LOGGER_H
#define HOMURA_LOGGER_H

#include <android/log.h>

#include <format>
#include <source_location>

#ifdef PVZ_DEBUG
#define LOG_DEBUG(...) homura::Logger::Instance().Debug(std::source_location::current(), __VA_ARGS__)
#define LOG_INFO(...) homura::Logger::Instance().Info(std::source_location::current(), __VA_ARGS__)
#define LOG_WARN(...) homura::Logger::Instance().Warn(std::source_location::current(), __VA_ARGS__)
#define LOG_ERROR(...) homura::Logger::Instance().Error(std::source_location::current(), __VA_ARGS__)
#else
#define LOG_DEBUG(...) ((void)0)
#define LOG_INFO(...) ((void)0)
#define LOG_WARN(...) ((void)0)
#define LOG_ERROR(...) ((void)0)
#endif // PVZ_DEBUG

namespace homura {

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
};

/**
 * @brief 简单的日志类. (接口已封装为宏)
 *
 * 调试时可在命令行工具中输入命令 <code>adb logcat -s pvztv</code> 查看日志.
 */
class Logger {
public:
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;
    Logger &operator=(const Logger &) = delete;
    Logger &operator=(Logger &&) = delete;

    /**
     * @brief 获取日志单例的引用.
     */
    [[nodiscard]] [[gnu::visibility("default")]] static Logger &Instance() {
        static Logger logger;
        return logger;
    }

    [[nodiscard]] LogLevel Level() const noexcept { return _level; }

    void SetLevel(LogLevel level) noexcept { _level = level; }

    template <typename... Args>
    void Debug(std::source_location location, std::format_string<Args...> format, Args &&...args) {
        Output(location, LogLevel::DEBUG, format.get(), std::forward<Args>(args)...);
    }

    template <typename... Args>
    void Info(std::source_location location, std::format_string<Args...> format, Args &&...args) {
        Output(location, LogLevel::INFO, format.get(), std::forward<Args>(args)...);
    }

    template <typename... Args>
    void Warn(std::source_location location, std::format_string<Args...> format, Args &&...args) {
        Output(location, LogLevel::WARN, format.get(), std::forward<Args>(args)...);
    }

    template <typename... Args>
    void Error(std::source_location location, std::format_string<Args...> format, Args &&...args) {
        Output(location, LogLevel::ERROR, format.get(), std::forward<Args>(args)...);
    }

protected:
    Logger() = default;

    void Output(std::source_location location, LogLevel level, std::string_view format, auto &&...args) {
        if (level < _level) {
            return;
        }
        std::string message = std::vformat(format, std::make_format_args(args...));
        __android_log_print(ANDROID_LOG_DEBUG, _logTag, "[%s] %s", location.function_name(), message.c_str());
    }

    LogLevel _level = LogLevel::INFO;

private:
    [[nodiscard]] static constexpr android_LogPriority GetLogPriority(LogLevel level) noexcept {
        switch (level) {
            case LogLevel::DEBUG:
                return ANDROID_LOG_DEBUG;
            case LogLevel::INFO:
                return ANDROID_LOG_INFO;
            case LogLevel::WARN:
                return ANDROID_LOG_WARN;
            case LogLevel::ERROR:
                return ANDROID_LOG_ERROR;
            default:
                return ANDROID_LOG_DEFAULT;
        }
    }

    static constexpr const char *_logTag = "pvztv";
};

} // namespace homura

#endif // HOMURA_LOGGER_H
