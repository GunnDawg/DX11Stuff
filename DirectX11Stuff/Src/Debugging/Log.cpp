#include "PCH.h"
#include "Log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void Logger::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	sCoreLogger = spdlog::stdout_color_mt("Debug");
	sCoreLogger->set_level(spdlog::level::trace);

	sFileLogger = spdlog::basic_logger_mt("Log", "log.txt");
	sFileLogger->set_level(spdlog::level::trace);
}