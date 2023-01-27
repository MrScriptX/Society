#include "message.h"

#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>

const std::string society::message::to_string() const noexcept
{
    return std::format("{}||{}||{}||{}||{}", id, name, secret, text, timestamp);
}

void society::message::parse(const std::string& str) noexcept
{
    std::vector<std::string> result;
    boost::algorithm::split_regex(result, str, boost::regex(R"(\|\|)"));

    id = std::stoi(result[0]);
    name = result[1];
    secret = result[2];
    text = result[3];
    timestamp = std::stoi(result[4]);
}

#ifdef WIN32
#include <windows.h>

void society::message::print() const noexcept
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN);
    std::cout << std::format("[{}]", society::clock::parse_time_sec(timestamp));

    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);
    std::cout << std::format("{} : ", name);

    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << std::format("{}", text);

    std::cout << std::endl <<std::flush;
}
#else
void society::message::print() const noexcept
{

}
#endif
