#include "Precompiled.h"

#include "Log.h"


namespace ivaldi {
	Logger Logger::create(const char *name)
	{
		Logger logger;
		logger.m_logger = spdlog::stdout_color_mt(name);
		return logger;
	}

	Logger Logger::get(const char *name)
	{
		Logger logger;
		logger.m_logger = spdlog::get(name);
		return logger;
	}

	void Logger::setGlobalPattern(const char *name)
	{
		spdlog::set_pattern(name);
	}
}