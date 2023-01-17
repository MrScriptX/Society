#include "server.h"

int main()
{
    try
    {
        // boost::asio::thread_pool thread_pool(1);

        boost::asio::io_context io_context;
        Server server(io_context);

        io_context.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}