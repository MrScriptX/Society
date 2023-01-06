#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include "client.h"

int main(int argc, char* argv[])
{
    boost::asio::thread_pool thread_pool(2);

    if(argc != 3){
        std::cerr << "Usage: ./society <your_nickname> <multicast_address>" << std::endl;
        std::exit(1);
    }

    boost::asio::io_context io_context;
    Client peer(io_context, argv[2], argv[1]);

    boost::asio::post(thread_pool, [&]{
        peer.receive();
        io_context.run();
    });
    boost::asio::post(thread_pool, [&]{
        peer.send();
        io_context.run();
    });
    thread_pool.join();

    return 0;
}
