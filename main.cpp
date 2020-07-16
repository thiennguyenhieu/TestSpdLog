#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

using namespace std;

void initSpdLog()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v [%!()-%s:%#)]");

    // Create a file rotating logger with 1048b size max and 10 rotated files.
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/file_logger.txt", 1048, 10, true);
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v [%!()-%s:%#)]");

    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    spdlog::init_thread_pool(8192, 1);
    auto async_logger = std::make_shared<spdlog::async_logger>("async_logger", sinks.begin(), sinks.end(), spdlog::thread_pool(),spdlog::async_overflow_policy::block);
    async_logger->flush_on(spdlog::level::trace);

    // Set the default logger to file logger
    spdlog::set_default_logger(async_logger);
}

void threadRun()
{
    SPDLOG_INFO("Thread");
}

int main()
{
    initSpdLog();

    int nLoop = 2;

    for (int i = 0; i < nLoop; i++)
    {
        SPDLOG_WARN("Easy padding in numbers like {:08d}", 12);
        SPDLOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        SPDLOG_INFO("Support for floats {:03.2f}", 1.23456);
    }

    std::thread thread(threadRun);
    thread.join();

    for (int j = 0; j < nLoop; j++)
    {
        SPDLOG_WARN("Easy padding in numbers like {:08d}", 12);
        SPDLOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        SPDLOG_INFO("Support for floats {:03.2f}", 1.23456);
    }

    return 0;
}
