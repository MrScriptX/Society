#ifndef SOCIETY_CLIENT_H
#define SOCIETY_CLIENT_H

#include <iostream>
#include <format>
#include <chrono>
#include <boost/asio.hpp>
#include <framework/message.h>
#include <framework/clock.h>

class Client
{
public:
    Client(boost::asio::io_context& ctx, const std::string& host, const std::string& username);
    ~Client();

    void receive();
    void send();
private:
    boost::asio::ip::tcp::socket m_socket;
    std::string m_name;

    std::size_t m_maximum_message_size = 512;
    std::array<char, 512> m_receiving_buffer;
    boost::asio::ip::tcp::endpoint m_remote_endpoint;
};

#endif
