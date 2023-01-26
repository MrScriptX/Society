#ifndef SOCIETY_MESSAGE_H
#define SOCIETY_MESSAGE_H

#include <string>

namespace society
{
    struct message
    {
        uint16_t id = 0; // client ID
        std::string secret; // client secret
        std::string name; // client name
        std::string text; // body of the message
        uint32_t timestamp; // message send time
    };
}

#endif // !SOCIETY_MESSAGE_H