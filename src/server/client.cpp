#include "client.h"

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

        receive();
    });
}

void client::send()
{
    std::string message;
    std::getline(std::cin, message);
    socket.async_send(boost::asio::buffer(message, m_maximum_message_size), [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
        // std::cout << "You: " << message << std::endl;
        send();
    });
}