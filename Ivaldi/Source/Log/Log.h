#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace ivaldi {
	class IVALDI_API Logger {
	public:
		void setPattern(const char *fmt)
		{
			m_logger->set_pattern(fmt);
		}

		template<typename... Args>
		void trace(const char *fmt, const Args &... args)
		{
			m_logger->trace(fmt, args...);
		}

		template<typename... Args>
		void debug(const char *fmt, const Args &... args)
		{
			m_logger->debug(fmt, args...);
		}

		template<typename... Args>
		void info(const char *fmt, const Args &... args)
		{
			m_logger->info(fmt, args...);
		}

		template<typename... Args>
		void warn(const char *fmt, const Args &... args)
		{
			m_logger->warn(fmt, args...);
		}

		template<typename... Args>
		void error(const char *fmt, const Args &... args)
		{
			m_logger->error(fmt, args...);
		}

		template<typename... Args>
		void critical(const char *fmt, const Args &... args)
		{
			m_logger->critical(fmt, args...);
		}

		static Logger create(const char* name);
		static Logger get(const char* name);
		static void setGlobalPattern(const char *fmt);

	private:
		Logger() = default;

		std::shared_ptr<spdlog::logger> m_logger;
	};
}