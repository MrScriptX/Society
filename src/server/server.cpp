#include "server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& ctx) : m_socket(ctx), m_acceptor(ctx, tcp::endpoint(tcp::v4(), 13))
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
            std::cout.write(m_receiving_buffer.data(), bytes_received);
            std::cout << std::endl <<std::flush;
            
            receive();
        }
    });
}

void Server::send()
{
    // std::string name = m_name;
    // std::string message;
    // std::getline(std::cin, message);
    // std::string buffer = name.append(": " + message);
    // m_socket.async_send_to(boost::asio::buffer(buffer, m_maximum_message_size), m_remote_endpoint, [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
    //     std::cout << "You: " << message << std::endl;
    //     send();
    // });
}

void Server::accept_connexion()
{
    m_acceptor.async_accept(m_socket, boost::bind(&Server::handle_connexion, this, boost::asio::placeholders::error));
}

void Server::handle_connexion(const boost::system::error_code &error)
{
    receive();
    accept_connexion();
}
