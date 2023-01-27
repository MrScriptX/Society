#ifndef SOCIETY_SERVER_H
#define SOCIETY_SERVER_H

#include <string>
#include <iostream>
#include <memory>
#include <format>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <framework/message.h>

#include "client.h"

class Server
{
public:
    Server(boost::asio::io_context& ctx);
    ~Server();

    void receive();
    void send();
private:
    void accept_connexion();
    void handle_connexion(const boost::system::error_code &error);

    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::endpoint m_remote_endpoint;

    boost::asio::ip::tcp::socket m_new_socket;

    std::array<char, 512> m_receiving_buffer;
    std::size_t m_maximum_message_size = 512;
    std::string m_name;

    boost::asio::io_context& m_ctx;
    std::vector<std::unique_ptr<client>> m_clients;
    boost::asio::thread_pool thread_pool;
};

#endif
