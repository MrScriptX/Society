#include "clock.h"

const std::string society::clock::parse_time_sec(const uint32_t seconds) noexcept
{
    auto time_from_sec = std::time_t(seconds);
    tm date = *gmtime(&time_from_sec);
    
    
    return std::format("{:02}:{:02}:{:02}", date.tm_hour, date.tm_min, date.tm_sec);
}
