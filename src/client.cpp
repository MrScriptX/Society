#include "client.h"

Client::Client(boost::asio::io_context& ctx, const std::string& address, const std::string& name) : m_socket(ctx), m_name(name)
{
    boost::asio::ip::address listen_addr = boost::asio::ip::address::from_string("127.0.0.1"); // 0.0.0.0
    boost::asio::ip::address mcast_addr = boost::asio::ip::address::from_string(address);

    m_multicast_endpoint = boost::asio::ip::udp::endpoint(mcast_addr, 9999);

    boost::asio::ip::udp::endpoint listen_endpoint(listen_addr.to_v4(), 9999);
    m_socket.open(listen_endpoint.protocol());

    m_socket.set_option(boost::asio::ip::multicast::enable_loopback(true));
    m_socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    m_socket.bind(listen_endpoint);

    boost::system::error_code ec;
    m_socket.set_option(boost::asio::ip::multicast::join_group(mcast_addr.to_v4(), listen_addr.to_v4()), ec);

    std::cerr << ec.message() << std::endl;

    auto welcome_message = std::string(m_name + " connected to the chat");
    m_socket.async_send_to(boost::asio::buffer(welcome_message), m_multicast_endpoint, [this](const boost::system::error_code& error_code, std::size_t bytes_sent) {
        if (!error_code.failed())
        {
            std::cout << "Entered chat room successfully" << std::endl;
        }
    });
}

void Client::receive()
{
    m_socket.async_receive_from(boost::asio::buffer(m_receiving_buffer), m_remote_endpoint, [this](const boost::system::error_code& error_code, std::size_t bytes_received)
    {
        if (!error_code.failed() && bytes_received > 0)
        {
            auto received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);
            // We don't want to receive the messages we produce
            if (received_message_string.find(m_name) != 0)
            {
                std::cout.write(m_receiving_buffer.data(), bytes_received);
                std::cout << std::endl <<std::flush;
            }
            
            receive();
        }
    });
}

void Client::send()
{
    std::string name = m_name;
    std::string message;
    std::getline(std::cin, message);
    std::string buffer = name.append(": " + message);
    m_socket.async_send_to(boost::asio::buffer(buffer, m_maximum_message_size), m_multicast_endpoint, [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
        std::cout << "You: " << message << std::endl;
        send();
    });
}
