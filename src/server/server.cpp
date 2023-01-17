#include "server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& ctx) : m_ctx(ctx), m_new_socket(ctx), m_acceptor(ctx, tcp::endpoint(tcp::v4(), 13)), thread_pool(10)
{
    accept_connexion();
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
        m_clients.push_back(std::make_unique<client>(m_new_socket));

        size_t last = m_clients.size() - 1;

        std::size_t bytes_received =  m_clients[last]->socket.receive(boost::asio::buffer(m_receiving_buffer));
        std::string received_message_string = std::string(m_receiving_buffer.begin(), m_receiving_buffer.begin() + bytes_received);
        m_clients[last]->name = received_message_string;

        std::clog << "connexion established" << std::endl;

        client* t = m_clients[last].get();
        boost::asio::post(thread_pool, [this, t] {
            t->receive();
            m_ctx.run();
        });
 
        boost::asio::post(thread_pool, [this, &t]{
            t->send();
            m_ctx.run();
        });

        accept_connexion();
    }
}
