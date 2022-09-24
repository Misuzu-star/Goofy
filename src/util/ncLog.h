#ifndef __NC_LOG_H__
#define __NC_LOG_H__

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <spdlog/spdlog.h>

std::shared_ptr<spdlog::logger> GetLogger(void);

#define GOOFY_TRACE(...) SPDLOG_LOGGER_TRACE(GetLogger(), __VA_ARGS__)
#define GOOFY_DEBUG(...) SPDLOG_LOGGER_DEBUG(GetLogger(), __VA_ARGS__)
#define GOOFY_INFO(...)  SPDLOG_LOGGER_INFO(GetLogger(), __VA_ARGS__)
#define GOOFY_WARN(...)  SPDLOG_LOGGER_WARN(GetLogger(), __VA_ARGS__)
#define GOOFY_ERROR(...) SPDLOG_LOGGER_ERROR(GetLogger(), __VA_ARGS__)

#endif // !__NC_LOG_H__
