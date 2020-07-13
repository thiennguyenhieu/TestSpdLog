#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace std;

void initSpdLog()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v (%@)");

    // Create a file rotating logger with 1048b size max and 10 rotated files.
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/file_logger.txt", 1048, 10, true);
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v (%@)");

    auto file_logger = std::make_shared<spdlog::logger>(spdlog::logger("logger", {console_sink, file_sink}));

    // Set the default logger to file logger
    spdlog::set_default_logger(file_logger);
}

void threadRun()
{
    SPDLOG_INFO("Thread");
}

int main()
{
    initSpdLog();

    int nLoop = 1;

    for (int i = 0; i < nLoop; i++)
    {
        SPDLOG_WARN("Easy padding in numbers like {:08d}", 12);
        SPDLOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        SPDLOG_INFO("Support for floats {:03.2f}", 1.23456);
    }

    std::thread thread(threadRun);
    thread.join();

    auto logger = spdlog::get("logger");
    logger->sinks().at(1)->set_level(spdlog::level::off);

    for (int j = 0; j < nLoop; j++)
    {
        SPDLOG_WARN("Easy padding in numbers like {:08d}", 12);
        SPDLOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        SPDLOG_INFO("Support for floats {:03.2f}", 1.23456);
    }

    return 0;
}
