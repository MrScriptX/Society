#include <iostream>

#include "constant.h"
#include "client.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: client <host> <username>" << std::endl;
        return 1;
    }

    std::cout << message::welcome << std::endl;

    try
    {
        boost::asio::thread_pool thread_pool(2);

        boost::asio::io_context io_context;
        Client client(io_context, argv[1], argv[2]);

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