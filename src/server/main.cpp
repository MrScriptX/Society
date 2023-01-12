#include "server.h"

int main()
{
    try
    {
        // boost::asio::thread_pool thread_pool(2);

        boost::asio::io_context io_context;
        Server server(io_context);
        io_context.run();

        // boost::asio::post(thread_pool, [&]{
        //     server.receive();
        //     io_context.run();
        // });

        // thread_pool.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}