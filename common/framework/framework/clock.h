#ifndef SOCIETY_CLOCK_H
#define SOCIETY_CLOCK_H

#include <string>
#include <chrono>

namespace society::clock
{
    const std::string parse_time_sec(const uint32_t seconds) noexcept;
}

#endif // !SOCIETY_CLOCK_H
