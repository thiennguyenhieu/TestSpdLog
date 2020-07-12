#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace std;

void initSpdLog()
{
    // Create a file rotating logger with 5mb size max and 3 rotated files.
    auto file_logger = spdlog::rotating_logger_mt("file_logger", "logs/file_logger.txt", 1048576 * 5, 3);

    // Customize log format
    file_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v (%@)");

    // Set the default logger to file logger
    spdlog::set_default_logger(file_logger);
}

int main()
{
    initSpdLog();

    SPDLOG_WARN("Easy padding in numbers like {:08d}", 12);
    SPDLOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    SPDLOG_INFO("Support for floats {:03.2f}", 1.23456);

    return 0;
}
