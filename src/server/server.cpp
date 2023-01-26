#include "server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& ctx) : m_ctx(ctx), m_new_socket(ctx), m_acceptor(ctx, tcp::endpoint(tcp::v4(), 13)), thread_pool(48)
{
    std::clog << "server started..." << std::endl;

    accept_connexion();

    boost::asio::post(thread_pool, [&] {
        send();
        m_ctx.run();
    });
}

Server::~Server()
{
    thread_pool.join();
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
        // create new socket
        m_clients.push_back(std::make_unique<client>(m_new_socket));
        size_t last = m_clients.size() - 1;

        // receive message
        std::size_t bytes_received =  m_clients[last]->socket.receive(boost::asio::buffer(m_receiving_buffer));
        std::string received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);

        // parse message
        society::message msg;
        msg.parse(received_message_string);

        m_clients[last]->id = msg.id;
        m_clients[last]->secret = msg.secret;
        m_clients[last]->name = msg.name;
        m_clients[last]->address = m_clients[last]->socket.remote_endpoint().address().to_string();
        
        std::clog << std::format("connexion established [{}] [{}]", m_clients[last]->name, m_clients[last]->address) << std::endl;

        // start receiving thread
        client* t = m_clients[last].get();
        boost::asio::post(thread_pool, [this, t] {
            t->receive(this->m_clients);
            m_ctx.run();
        });

        accept_connexion();
    }
}

void Server::send()
{
    std::string message;
    std::getline(std::cin, message);
    std::string buffer = "server : " + message;
    for (size_t i = 0; i < m_clients.size(); i++)
    {
        m_clients[i]->send(buffer);
    }

    send();
}
