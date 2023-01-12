#include "server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& ctx) : m_socket(ctx), m_new_socket(ctx), m_acceptor(ctx, tcp::endpoint(tcp::v4(), 13))
{
    accept_connexion();
}

void Server::receive()
{
    m_socket.async_receive(boost::asio::buffer(m_receiving_buffer), [this](const boost::system::error_code& error_code, std::size_t bytes_received)
    {
        if (!error_code.failed() && bytes_received > 0)
        {
            auto received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);
            std::cout << m_name << " : ";
            std::cout.write(m_receiving_buffer.data(), bytes_received);
            std::cout << std::endl <<std::flush;
        }

        receive();
    });
}

void Server::send()
{
    std::string message;
    std::getline(std::cin, message);
    m_socket.async_send(boost::asio::buffer(message, m_maximum_message_size), [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
        // std::cout << "You: " << message << std::endl;
        send();
    });
}

void Server::accept_connexion()
{
    m_acceptor.async_accept(m_new_socket, boost::bind(&Server::handle_connexion, this, boost::asio::placeholders::error));
}

void Server::handle_connexion(const boost::system::error_code &error)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        accept_connexion();
    }
    else
    {
        m_socket = std::move(m_new_socket); // cpy tmp socket

        std::size_t bytes_received = m_socket.receive(boost::asio::buffer(m_receiving_buffer));
        std::string received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);
        m_name = received_message_string;

        std::clog << "connexion established" << std::endl;
        accept_connexion();
    }
}
