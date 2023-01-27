#include "client.h"

using boost::asio::ip::tcp;

Client::Client(boost::asio::io_context& ctx, const std::string& host, const std::string& username) : m_socket(ctx), m_name(username)
{
    std::clog << "connecting..." << std::endl;

    tcp::resolver resolver(ctx);
    tcp::resolver::results_type endpoints = resolver.resolve(host, "daytime");

    boost::asio::connect(m_socket, endpoints);

    society::message init_message;
    init_message.text = "first message";
    init_message.name = username;

    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    init_message.timestamp = now.time_since_epoch().count();

    m_socket.send(boost::asio::buffer(init_message.to_string(), m_maximum_message_size));

    std::clog << std::format("connected to [{}]\n\n", m_socket.remote_endpoint().address().to_string());
    std::clog << std::endl;
}

Client::~Client()
{
    m_socket.close();
}

void Client::receive()
{
    m_socket.async_receive(boost::asio::buffer(m_receiving_buffer), [this](const boost::system::error_code& error_code, std::size_t bytes_received)
    {
        if (!error_code.failed() && bytes_received > 0)
        {
            auto received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);

            society::message msg;
            msg.parse(received_message_string);

            msg.print();
        }

        receive();
    });
}

void Client::send()
{
    std::string message;
    std::getline(std::cin, message);

    society::message msg;
    msg.id = 0;
    msg.name = m_name;
    msg.text = message;

    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    msg.timestamp = now.time_since_epoch().count();

    m_socket.async_send(boost::asio::buffer(msg.to_string(), m_maximum_message_size), [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
        send();
    });
}
