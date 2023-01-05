#ifndef SOCIETY_CLIENT_H
#define SOCIETY_CLIENT_H

#include <string>
#include <boost/asio.hpp>

class Client
{
public:
    Client(boost::asio::io_context& ctx, const boost::asio::ip::address& room, std::string name);

    void receive();
    void send();
private:
    boost::asio::ip::udp::socket m_socket;
};

#endif
