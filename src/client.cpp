#include "client.h"

Client::Client(boost::asio::io_context& ctx, const boost::asio::ip::address& room, std::string name) : m_socket(ctx)
{
    boost::asio::ip::udp::endpoint listen_endpoint(room, 30000);
    m_socket.open(listen_endpoint.protocol());
    m_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    m_socket.bind(listen_endpoint);
    m_socket.set_option(boost::asio::ip::multicast::join_group(room));
}
