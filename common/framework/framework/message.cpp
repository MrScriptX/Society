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
