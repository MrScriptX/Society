#ifndef SOCIETY_CLIENT_H
#define SOCIETY_CLIENT_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>

class Client
{
public:
    Client(boost::asio::io_context& ctx, const std::string& address, const std::string& name);

    void receive();
    void send();
private:
    boost::asio::ip::udp::socket m_socket;
    std::string m_name;

    std::size_t m_maximum_message_size = 128;
    std::array<char, 128> m_receiving_buffer;
    boost::asio::ip::udp::endpoint m_remote_endpoint;
    boost::asio::ip::udp::endpoint m_multicast_endpoint;
};

#endif
