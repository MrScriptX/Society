#include "client.h"

client::client(boost::asio::ip::tcp::socket& _socket) : socket(std::move(_socket))
{
}

void client::receive()
{
    socket.async_receive(boost::asio::buffer(m_receiving_buffer), [this](const boost::system::error_code& error_code, std::size_t bytes_received)
    {
        if (!error_code.failed() && bytes_received > 0)
        {
            auto received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);
            std::cout << name << " : ";
            std::cout.write(m_receiving_buffer.data(), bytes_received);
            std::cout << std::endl <<std::flush;
        }
        else if (error_code == boost::asio::error::eof)
        {
            std::cerr << "connexion closed" << std::endl;
            return;
        }
        else if (error_code.failed())
        {
            std::cerr << error_code.message() << std::endl;
            return;
        }

        receive();
    });
}

void client::send(const std::string& message)
{
    socket.async_send(boost::asio::buffer(message, m_maximum_message_size), [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
    });
}