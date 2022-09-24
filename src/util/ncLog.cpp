#include <spdlog/sinks/basic_file_sink.h>
#include "ncLog.h"

const char* LOG_NAME = "Goofy_Log";
const char* LOG_FILE_PATH = "goofy.log";
const int   FLUSH_RATE = 3; // 日志刷新时间频率(单位: 秒)

static std::shared_ptr<spdlog::logger> defLogger = nullptr;

std::shared_ptr<spdlog::logger>
GetLogger(void)
{
    return defLogger;
}

struct _Initor_
{
    _Initor_(void)
    {
        defLogger = spdlog::basic_logger_mt(LOG_NAME, LOG_FILE_PATH);
        defLogger->set_level(spdlog::level::trace);
        defLogger->set_pattern("%Y-%m-%d %H:%M:%S.%e    [%P]  [%t]  [%l]  %s(%#) %!: %v");
        spdlog::flush_every(std::chrono::seconds(FLUSH_RATE));
    }
};

static _Initor_ initor;
