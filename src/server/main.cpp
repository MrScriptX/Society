#include "constant.h"
#include "server.h"

int main()
{
    std::cout << message::welcome << std::endl;

    try
    {
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