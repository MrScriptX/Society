#include "client.h"

client::client(boost::asio::ip::tcp::socket& _socket) : socket(std::move(_socket))
{
}

void client::receive(const std::vector<std::unique_ptr<client>>& clients)
{
    socket.async_receive(boost::asio::buffer(m_receiving_buffer), [this, &clients](const boost::system::error_code& error_code, std::size_t bytes_received)
    {
        if (!error_code.failed() && bytes_received > 0)
        {
            society::message msg;
            msg.parse(std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received));

            for (size_t i = 0; i < clients.size(); i++)
            {
                if (clients[i]->name == name)
                    continue;

                clients[i]->send(msg.to_string());
            }

            msg.print();
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

        receive(clients);
    });
}

void client::send(const std::string& message)
{
    socket.async_send(boost::asio::buffer(message, m_maximum_message_size), [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
    });
}