#include "client.h"

using boost::asio::ip::tcp;

Client::Client(boost::asio::io_context& ctx, const std::string& host, const std::string& username) : m_socket(ctx)
{
    tcp::resolver resolver(ctx);
    tcp::resolver::results_type endpoints = resolver.resolve(host, "daytime");

    boost::asio::connect(m_socket, endpoints);

    m_socket.send(boost::asio::buffer(username, m_maximum_message_size));
}

void Client::receive()
{
    m_socket.async_receive(boost::asio::buffer(m_receiving_buffer), [this](const boost::system::error_code& error_code, std::size_t bytes_received)
    {
        if (!error_code.failed() && bytes_received > 0)
        {
            auto received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);
            std::cout << "other : ";
            std::cout.write(m_receiving_buffer.data(), bytes_received);
            std::cout << std::endl <<std::flush;
        }

        receive();
    });
}

void Client::send()
{
    std::string message;
    std::getline(std::cin, message);
    m_socket.async_send(boost::asio::buffer(message, m_maximum_message_size), [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
        // std::cout << "You: " << message << std::endl;
        send();
    });
}
