#ifndef SOCIETY_CLIENT_H
#define SOCIETY_CLIENT_H

#include <string>
#include <iostream>
#include <boost/asio/ip/tcp.hpp>

struct client
{
    std::string name;
    boost::asio::ip::tcp::socket socket;

    std::array<char, 128> m_receiving_buffer;
    std::size_t m_maximum_message_size = 128;

    void receive();
    void send();
};

#endif
