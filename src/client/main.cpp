#include <iostream>

#include "client.h"

int main(int argc, char *argv[])
{
    try
    {
        boost::asio::thread_pool thread_pool(2);

        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        Client client(io_context, argv[1]);

        boost::asio::post(thread_pool, [&]{
            client.receive();
            io_context.run();
        });

        boost::asio::post(thread_pool, [&]{
            client.send();
            io_context.run();
        });

        thread_pool.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}