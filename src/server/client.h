#ifndef SOCIETY_CLIENT_H
#define SOCIETY_CLIENT_H

#include <string>
#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <framework/message.h>
#include <framework/clock.h>

struct client
{
    client(boost::asio::ip::tcp::socket& _socket);

    int16_t id;
    std::string secret;
    std::string name;
    std::string address;
    boost::asio::ip::tcp::socket socket;

    std::array<char, 512> m_receiving_buffer;
    std::size_t m_maximum_message_size = 512;

    void receive(const std::vector<std::unique_ptr<client>>& clients);
    void send(const std::string& message);
};

#endif
